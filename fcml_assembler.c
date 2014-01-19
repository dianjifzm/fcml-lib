/*
 * fcml_assembler.c
 *
 *  Created on: 24-03-2013
 *      Author: tAs
 */

#include "fcml_assembler.h"

#include <stddef.h>

#include "fcml_dialect_int.h"
#include "fcml_encoding.h"
#include "fcml_env.h"
#include "fcml_errors.h"
#include "fcml_utils.h"

typedef struct fcml_ist_asm_enc_assembler {
    fcml_coll_map instructions_map;
    fcml_st_dialect_context_int *dialect_context;
} fcml_ist_asm_enc_assembler;

fcml_ceh_error fcml_fn_assembler_init( fcml_st_dialect *context, fcml_st_assembler **assembler ) {

	// Allocate assembler instance.
	fcml_ist_asm_enc_assembler *enc_asm = fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_asm_enc_assembler ) );
	if( !enc_asm ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	fcml_ceh_error error = fcml_fn_asm_init_instruction_encodings( (fcml_st_dialect_context_int*)context, &(enc_asm->instructions_map) );
	if( error ) {
		fcml_fn_env_memory_free( enc_asm );
		return error;
	}

	enc_asm->dialect_context = (fcml_st_dialect_context_int*)context;

	*assembler = (fcml_st_assembler *)enc_asm;

	return FCML_CEH_GEC_NO_ERROR;
}

void fcml_ifn_asm_free_instruction_chain( fcml_st_assembled_instruction *chain ) {
    while( chain ) {
        fcml_st_assembled_instruction *instruction = chain;
        chain = chain->next;
        fcml_fn_env_memory_free( instruction->code );
        fcml_fn_env_memory_free( instruction );
    }
}

void fcml_fn_assembler_result_free( fcml_st_assembler_result *result ) {
	if( result ) {
		fcml_fn_ceh_free_errors_only( &(result->errors) );
        fcml_ifn_asm_free_instruction_chain( result->instructions );
		fcml_fn_env_memory_free( result );
	}
}

fcml_ceh_error fcml_fn_assemble( fcml_st_assembler_context *asm_context, const fcml_st_instruction *instruction, fcml_st_assembler_result **result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( instruction == NULL ) {
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	// Take into account that dialect can modify source instruction by preparing it for assembler, so we have to use local copy.
	fcml_st_instruction tmp_instruction = *instruction;

	fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler*)asm_context->assembler;

	// First place where dialect can ingerate instruction definition.
	fcml_fnp_asm_dialect_prepare_assembler_preprocessor assembler_preprocessor = enc_asm->dialect_context->assembler_preprocessor;
	if( assembler_preprocessor ) {
		assembler_preprocessor( (fcml_st_dialect*)enc_asm->dialect_context, &tmp_instruction, NULL, NULL, NULL );
	}

	// Find instruction addressing modes.
	fcml_st_asm_instruction_addr_modes *addr_modes = NULL;
	error = fcml_fn_asm_get_instruction_encodings( enc_asm->instructions_map, tmp_instruction.mnemonic, &addr_modes );
	if( error ) {
		return error;
	}

	if( !asm_context->address_size_attribute ) {
		asm_context->address_size_attribute = fcml_fn_utils_get_default_ASA(asm_context->addr_form);
	}
	if( !asm_context->operand_size_attribute ) {
		asm_context->operand_size_attribute = fcml_fn_utils_get_default_OSA(asm_context->addr_form);
	}

	fcml_st_assembler_result *asm_result = fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_asm_encoder_result ) );
	if( !asm_result ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Execute instruction encoder.
	if( addr_modes != NULL ) {
		if( addr_modes->instruction_encoder ) {

			fcml_st_asm_encoder_result enc_result = {{0}};

			error = addr_modes->instruction_encoder( asm_context, enc_asm->dialect_context, &tmp_instruction, &enc_result, addr_modes );
			if( !error ) {
				asm_result->instructions = enc_result.instructions;
				asm_result->number_of_instructions = enc_result.number_of_instructions;
				asm_result->chosen_instruction = enc_result.chosen_instruction;
			}

			// Convert encoding result to assembler result.
			asm_result->errors = enc_result.errors;

		} else {
			// Unavailable instruction encoder.
			error = FCML_CEH_GEC_INTERNAL_BUG;
		}
	} else {
		error = FCML_EN_UNKNOWN_MNEMONIC;
	}

	// Free results but only if there is no error messages.
	if( error ) {
		if( !asm_result->errors.errors ) {
			fcml_fn_assembler_result_free( asm_result );
			asm_result = NULL;
		} else {
			// Free only instructions, error messages should be returned to user.
		    fcml_ifn_asm_free_instruction_chain( asm_result->instructions );
			asm_result->instructions = NULL;
		}
	}

	*result = asm_result;

	return error;
}

void fcml_fn_assembler_free( fcml_st_assembler *assembler ) {
	if( assembler ) {
		fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler *)assembler;
		if( enc_asm->instructions_map ) {
			fcml_fn_asm_free_instruction_encodings( enc_asm->instructions_map );
		}
		// Assembler is not the owner of the dialect context.
		enc_asm->dialect_context = NULL;
		fcml_fn_env_memory_free( enc_asm );
	}
}


