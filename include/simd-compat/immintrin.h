/*
 * DISTRHO Cardinal Plugin
 * Copyright (C) 2021-2024 Filipe Coelho <falktx@falktx.com>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "simd-compat.h"

#if defined(CARDINAL_INCLUDING_EMULATED_IMMINTRIN_H) || defined(SIMDE_X86_SSE_NATIVE)
# define CARDINAL_INCLUDING_IMMINTRIN_H
/* simde's native-alias macros (from simde/x86/sse2.h etc) would otherwise get
 * macro-expanded inside the system AVX512 headers below, silently renaming
 * their own function definitions and causing redefinition errors. */
# undef _mm_loadu_epi8
# undef _mm_loadu_epi16
# undef _mm_loadu_epi32
# undef _mm_loadu_epi64
# include_next <immintrin.h>
# undef CARDINAL_INCLUDING_IMMINTRIN_H
#else
# define CARDINAL_INCLUDING_EMULATED_IMMINTRIN_H
# include "mmintrin.h"
# include "xmmintrin.h"
# include "emmintrin.h"
# include "pmmintrin.h"
# include "tmmintrin.h"
# include "smmintrin.h"
# undef CARDINAL_INCLUDING_EMULATED_IMMINTRIN_H
#endif
