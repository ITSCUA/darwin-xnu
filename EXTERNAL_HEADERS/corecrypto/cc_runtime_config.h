/*
 *  cc_runtime_config.h
 *  corecrypto
 *
 *  Created on 09/18/2012
 *
 *  Copyright (c) 2012,2014,2015 Apple Inc. All rights reserved.
 *
 */

#ifndef CORECRYPTO_CC_RUNTIME_CONFIG_H_
#define CORECRYPTO_CC_RUNTIME_CONFIG_H_

#include <corecrypto/cc_config.h>

/* Only intel systems have these runtime switches today. */
#if (CCSHA1_VNG_INTEL || CCSHA2_VNG_INTEL || CCAES_INTEL_ASM) \
    && (defined(__x86_64__) || defined(__i386__))

#if CC_KERNEL
    #include <i386/cpuid.h>
    #define CC_HAS_AESNI() ((cpuid_features() & CPUID_FEATURE_AES) != 0)
    #define CC_HAS_SupplementalSSE3() ((cpuid_features() & CPUID_FEATURE_SSSE3) != 0)
    #define CC_HAS_AVX1() ((cpuid_features() & CPUID_FEATURE_AVX1_0) != 0)
    #define CC_HAS_AVX2() ((cpuid_info()->cpuid_leaf7_features & CPUID_LEAF7_FEATURE_AVX2) != 0)

#elif CC_XNU_KERNEL_AVAILABLE
    # include <System/i386/cpu_capabilities.h>

    #ifndef kHasAVX2_0 /* 10.8 doesn't have kHasAVX2_0 defined */
    #define kHasAVX2_0 0
    #endif

    extern int _cpu_capabilities;
    #define CC_HAS_AESNI() (_cpu_capabilities & kHasAES)
    #define CC_HAS_SupplementalSSE3() (_cpu_capabilities & kHasSupplementalSSE3)
    #define CC_HAS_AVX1() (_cpu_capabilities & kHasAVX1_0)
    #define CC_HAS_AVX2() (_cpu_capabilities & kHasAVX2_0)
#else
    #define CC_HAS_AESNI() 0
    #define CC_HAS_SupplementalSSE3() 0
    #define CC_HAS_AVX1() 0
    #define CC_HAS_AVX2() 0
#endif

#endif /* !(defined(__x86_64__) || defined(__i386__)) */

#endif /* CORECRYPTO_CC_RUNTIME_CONFIG_H_ */
