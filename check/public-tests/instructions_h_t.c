/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2015 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <fcml_assembler.h>
#include "instructions_h_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_h_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_h_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_instruction_HADDPD(void) {
    FCML_I64( "haddpd xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x7C, 0x40, 0x20 );
    FCML_I32( "haddpd xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x7C, 0x40, 0x20 );

    FCML_I64( "vhaddpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x7C, 0x14, 0x01 );
    FCML_I32_D( "vhaddpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x7C, 0x14, 0x01 );
    FCML_I32_D( "vhaddpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x7C, 0x14, 0x01 );
    FCML_I32( "vhaddpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc1, 0x7c, 0x14, 0x01 );
    FCML_I32( "vhaddpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xe9, 0x7c, 0x14, 0x01 );
    /* GAS */
    FCML_A64( "haddpd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x7c, 0x40, 0x20 );
    FCML_A64( "vhaddpd (%r9,%rax),%ymm14,%ymm10", 0xc4, 0x41, 0x0d, 0x7c, 0x14, 0x01 );
    FCML_A64( "vhaddpd (%rcx,%rax),%xmm2,%xmm2", 0xc5, 0xe9, 0x7c, 0x14, 0x01 );
}

void fcml_tf_instruction_HADDPS(void) {
    FCML_I64( "haddps xmm0,xmmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x7C, 0x40, 0x20 );
    FCML_I32( "haddps xmm0,xmmword ptr [eax+00000020h]", 0xF2, 0x0F, 0x7C, 0x40, 0x20 );

    FCML_I64( "vhaddps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0F, 0x7C, 0x14, 0x01 );
    FCML_I32_D( "vhaddps xmm2,xmm7,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x43, 0x7C, 0x14, 0x01 );
    FCML_I32_D( "vhaddps xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x6B, 0x7C, 0x14, 0x01 );
    FCML_I32( "vhaddps xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc3, 0x7c, 0x14, 0x01 );
    FCML_I32( "vhaddps xmm2,xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xeb, 0x7c, 0x14, 0x01 );
    /* GAS */
    FCML_A64( "haddps 0x0000000000000020(%rax),%xmm0", 0xf2, 0x0f, 0x7c, 0x40, 0x20 );
    FCML_A64( "vhaddps (%r9,%rax),%ymm14,%ymm10", 0xc4, 0x41, 0x0f, 0x7c, 0x14, 0x01 );
    FCML_A64( "vhaddps (%rcx,%rax),%xmm2,%xmm2", 0xc5, 0xeb, 0x7c, 0x14, 0x01 );
}

void fcml_tf_instruction_HLT(void) {
    FCML_I3264( "hlt", 0xF4 );
    FCML_A64( "hlt", 0xf4 );
}

void fcml_tf_instruction_HSUBPD(void) {
    FCML_I64( "hsubpd xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x7D, 0x40, 0x20 );
    FCML_I32( "hsubpd xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x7D, 0x40, 0x20 );

    FCML_I64( "vhsubpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x7D, 0x14, 0x01 );
    FCML_I32_D( "vhsubpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x7D, 0x14, 0x01 );
    FCML_I32( "vhsubpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc1, 0x7d, 0x14, 0x01 );
    /* GAS */
    FCML_A64( "hsubpd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x7d, 0x40, 0x20 );
    FCML_A64( "vhsubpd (%r9,%rax),%ymm14,%ymm10", 0xc4, 0x41, 0x0d, 0x7d, 0x14, 0x01 );
    FCML_A64( "vhsubpd (%rcx,%rax),%xmm7,%xmm2", 0xc5, 0xc1, 0x7d, 0x14, 0x01 );
}

void fcml_tf_instruction_HSUBPS(void) {

    FCML_I64( "hsubps xmm0,xmmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x7D, 0x40, 0x20 );
    FCML_I32( "hsubps xmm0,xmmword ptr [eax+00000020h]", 0xF2, 0x0F, 0x7D, 0x40, 0x20 );

    FCML_I64( "vhsubps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0F, 0x7D, 0x14, 0x01 );
    FCML_I32_D( "vhsubps xmm2,xmm7,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x43, 0x7D, 0x14, 0x01 );
    FCML_I32( "vhsubps xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc3, 0x7d, 0x14, 0x01 );
}

fcml_stf_test_case fctl_ti_instructions_h[] = {
    { "fcml_tf_instruction_HADDPD", fcml_tf_instruction_HADDPD },
    { "fcml_tf_instruction_HADDPS", fcml_tf_instruction_HADDPS },
    { "fcml_tf_instruction_HLT", fcml_tf_instruction_HLT },
    { "fcml_tf_instruction_HSUBPD", fcml_tf_instruction_HSUBPD },
    { "fcml_tf_instruction_HSUBPS", fcml_tf_instruction_HSUBPS },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_h = {
    "suite-fctl_ti_instructions_h", fcml_tf_instructions_h_suite_init, fcml_tf_instructions_h_suite_cleanup, fctl_ti_instructions_h
};


