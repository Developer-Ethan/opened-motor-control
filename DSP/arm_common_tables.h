/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_common_tables.h
 * Description:  Extern declaration for common tables
 *
 * @version  V1.10.0
 * @date     08 July 2021
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ARM_COMMON_TABLES_H
#define _ARM_COMMON_TABLES_H

#include "arm_math_types.h"
#include "fast_math_functions.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FAST_ALLOW_TABLES)

  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_RECIP_Q15)
    extern const q15_t armRecipTableQ15[64];
  #endif /* !defined(ARM_DSP_CONFIG_TABLES) defined(ARM_ALL_FAST_TABLES) */

  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_RECIP_Q31)
    extern const q31_t armRecipTableQ31[64];
  #endif /* !defined(ARM_DSP_CONFIG_TABLES) defined(ARM_ALL_FAST_TABLES) */

  /* Tables for Fast Math Sine and Cosine */
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_F32)
    extern const float32_t sinTable_f32[FAST_MATH_TABLE_SIZE + 1];
  #endif /* !defined(ARM_DSP_CONFIG_TABLES) defined(ARM_ALL_FAST_TABLES) */

  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_Q31)
    extern const q31_t sinTable_q31[FAST_MATH_TABLE_SIZE + 1];
  #endif /* !defined(ARM_DSP_CONFIG_TABLES) defined(ARM_ALL_FAST_TABLES) */

  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_Q15)
    extern const q15_t sinTable_q15[FAST_MATH_TABLE_SIZE + 1];
  #endif /* !defined(ARM_DSP_CONFIG_TABLES) defined(ARM_ALL_FAST_TABLES) */

  /* Fast vector sqrt */
  #if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
     #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_FAST_SQRT_Q31_MVE)
       extern const q31_t sqrtTable_Q31[256];
     #endif /* !defined(ARM_DSP_CONFIG_TABLES) defined(ARM_ALL_FAST_TABLES) */
  #endif 

  /* Accurate scalar sqrt */
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SQRT_Q31) 
       extern const q31_t sqrt_initial_lut_q31[32];
  #endif

  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SQRT_Q15) 
       extern const q15_t sqrt_initial_lut_q15[16];
  #endif

  #if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
     #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_FAST_SQRT_Q15_MVE)
       extern const q15_t sqrtTable_Q15[256];
     #endif /* !defined(ARM_DSP_CONFIG_TABLES) defined(ARM_ALL_FAST_TABLES) */
  #endif

#endif /* if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FAST_TABLES) */

#if (defined(ARM_MATH_MVEF) || defined(ARM_MATH_HELIUM)) && !defined(ARM_MATH_AUTOVECTORIZE)
       extern const float32_t exp_tab[8];
       extern const float32_t __logf_lut_f32[8];
#endif /* (defined(ARM_MATH_MVEF) || defined(ARM_MATH_HELIUM)) && !defined(ARM_MATH_AUTOVECTORIZE) */

#if (defined(ARM_MATH_MVEI) || defined(ARM_MATH_HELIUM)) && !defined(ARM_MATH_AUTOVECTORIZE)
extern const unsigned char hwLUT[256];
#endif /* (defined(ARM_MATH_MVEI) || defined(ARM_MATH_HELIUM)) */

#ifdef   __cplusplus
}
#endif

#endif /*  ARM_COMMON_TABLES_H */

