// Auto-generated file. Do not edit!
//   Template: src/qs8-igemm/c8-neondot.c.in
//   Generator: tools/xngen
//
// Copyright 2023 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/gemm.h>
#include <xnnpack/math.h>


void xnn_qs8_igemm_minmax_rndnu_ukernel_1x8c8__aarch64_neondot_ld128(
    size_t mr,
    size_t nc,
    size_t kc,
    size_t ks,
    const int8_t** restrict a,
    const void* restrict w,
    int8_t* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    size_t a_offset,
    const int8_t* zero,
    const union xnn_qs8_conv_minmax_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(mr != 0);
  assert(mr <= 1);
  assert(nc != 0);
  assert(kc != 0);
  assert(ks != 0);
  assert(ks % (1 * sizeof(void*)) == 0);
  assert(a_offset % sizeof(int8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  kc = round_up_po2(kc, 8 * sizeof(int8_t));
  int8_t* c0 = c;

  do {
    const int32x4_t vinit0x0123 = vld1q_s32(w); w = (const int32_t*) w + 4;
    const int32x4_t vinit0x4567 = vld1q_s32(w); w = (const int32_t*) w + 4;
    int32x4_t vacc0x01 = vreinterpretq_s32_u64(vmovl_u32(vget_low_u32(vreinterpretq_u32_s32(vinit0x0123))));
    int32x4_t vacc0x23 = vreinterpretq_s32_u64(vmovl_u32(vget_high_u32(vreinterpretq_u32_s32(vinit0x0123))));
    int32x4_t vacc0x45 = vreinterpretq_s32_u64(vmovl_u32(vget_low_u32(vreinterpretq_u32_s32(vinit0x4567))));
    int32x4_t vacc0x67 = vreinterpretq_s32_u64(vmovl_u32(vget_high_u32(vreinterpretq_u32_s32(vinit0x4567))));

    size_t p = ks;
    do {
      const int8_t* restrict a0 = a[0];
      if XNN_UNPREDICTABLE(a0 != zero) {
        a0 = (const int8_t*) ((uintptr_t) a0 + a_offset);
      }
      a += 1;

      size_t k = kc;
      for (; k >= 16 * sizeof(int8_t); k -= 16 * sizeof(int8_t)) {
        const uint64x2x2_t va0c0123456789ABCDEF = vld2q_dup_u64((const void*) a0); a0 += 16;

        const int8x16_t vb01c01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb23c01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb45c01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb67c01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;

        vacc0x01 = vdotq_s32(vacc0x01, vb01c01234567, vreinterpretq_s8_u64(va0c0123456789ABCDEF.val[0]));
        vacc0x23 = vdotq_s32(vacc0x23, vb23c01234567, vreinterpretq_s8_u64(va0c0123456789ABCDEF.val[0]));
        vacc0x45 = vdotq_s32(vacc0x45, vb45c01234567, vreinterpretq_s8_u64(va0c0123456789ABCDEF.val[0]));
        vacc0x67 = vdotq_s32(vacc0x67, vb67c01234567, vreinterpretq_s8_u64(va0c0123456789ABCDEF.val[0]));

        const int8x16_t vb01c89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb23c89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb45c89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb67c89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;

        vacc0x01 = vdotq_s32(vacc0x01, vb01c89ABCDEF, vreinterpretq_s8_u64(va0c0123456789ABCDEF.val[1]));
        vacc0x23 = vdotq_s32(vacc0x23, vb23c89ABCDEF, vreinterpretq_s8_u64(va0c0123456789ABCDEF.val[1]));
        vacc0x45 = vdotq_s32(vacc0x45, vb45c89ABCDEF, vreinterpretq_s8_u64(va0c0123456789ABCDEF.val[1]));
        vacc0x67 = vdotq_s32(vacc0x67, vb67c89ABCDEF, vreinterpretq_s8_u64(va0c0123456789ABCDEF.val[1]));
      }
      if XNN_LIKELY(k != 0) {
        assert(k == 8 * sizeof(int8_t));

        const int8x16_t va0c01234567 = vreinterpretq_s8_u64(vld1q_dup_u64((const void*) a0)); a0 += 8;

        const int8x16_t vb01c01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb23c01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb45c01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb67c01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;

        vacc0x01 = vdotq_s32(vacc0x01, vb01c01234567, va0c01234567);
        vacc0x23 = vdotq_s32(vacc0x23, vb23c01234567, va0c01234567);
        vacc0x45 = vdotq_s32(vacc0x45, vb45c01234567, va0c01234567);
        vacc0x67 = vdotq_s32(vacc0x67, vb67c01234567, va0c01234567);
      }
      p -= 1 * sizeof(void*);
    } while (p != 0);

    #if XNN_ARCH_ARM64
      int32x4_t vacc0x0123 = vpaddq_s32(vacc0x01, vacc0x23);
      int32x4_t vacc0x4567 = vpaddq_s32(vacc0x45, vacc0x67);
    #else
      int32x4_t vacc0x0123 = vcombine_s32(vpadd_s32(vget_low_s32(vacc0x01), vget_high_s32(vacc0x01)), vpadd_s32(vget_low_s32(vacc0x23), vget_high_s32(vacc0x23)));
      int32x4_t vacc0x4567 = vcombine_s32(vpadd_s32(vget_low_s32(vacc0x45), vget_high_s32(vacc0x45)), vpadd_s32(vget_low_s32(vacc0x67), vget_high_s32(vacc0x67)));
    #endif

    const int32x4_t vright_pre_shift = vld1q_dup_s32(&params->rndnu_neon.right_pre_shift);
    const int32x4_t vmultiplier = vld1q_dup_s32(&params->rndnu_neon.multiplier);
    const int32x4_t vright_post_shift = vld1q_dup_s32(&params->rndnu_neon.right_post_shift);

    vacc0x0123 = vqshlq_s32(vacc0x0123, vright_pre_shift);
    vacc0x4567 = vqshlq_s32(vacc0x4567, vright_pre_shift);

    vacc0x0123 = vqdmulhq_s32(vacc0x0123, vmultiplier);
    vacc0x4567 = vqdmulhq_s32(vacc0x4567, vmultiplier);

    vacc0x0123 = vrshlq_s32(vacc0x0123, vright_post_shift);
    vacc0x4567 = vrshlq_s32(vacc0x4567, vright_post_shift);

    const int16x8_t voutput_zero_point = vld1q_dup_s16(&params->rndnu_neon.output_zero_point);
    #if XNN_ARCH_ARM64
      const int16x8_t vacc0x01234567 = vqaddq_s16(vqmovn_high_s32(vqmovn_s32(vacc0x0123), vacc0x4567), voutput_zero_point);

      int8x8_t vout0x01234567 = vqmovn_s16(vacc0x01234567);
    #else
      const int16x8_t vacc0x01234567 = vqaddq_s16(vcombine_s16(vqmovn_s32(vacc0x0123), vqmovn_s32(vacc0x4567)), voutput_zero_point);

      int8x8_t vout0x01234567 = vqmovn_s16(vacc0x01234567);
    #endif
    const int8x8_t voutput_min = vld1_dup_s8(&params->rndnu_neon.output_min);
    const int8x8_t voutput_max = vld1_dup_s8(&params->rndnu_neon.output_max);

    vout0x01234567 = vmax_s8(vout0x01234567, voutput_min);

    vout0x01234567 = vmin_s8(vout0x01234567, voutput_max);

    if (nc >= 8) {
      // Main case where there the 8 columns fit in the destination.
      vst1_s8(c0 + 0, vout0x01234567);

      // Advance to the next 8 columns.
      c0 = (int8_t*) ((uintptr_t) c0 + cn_stride);

      a = (const int8_t**restrict) ((uintptr_t) a - ks);

      nc -= 8;
    } else {
      // Final case where not all of the 8 columns fit in the destination.
      if (nc & 4) {
        vst1_lane_u32((void*) c0, vreinterpret_u32_s8(vout0x01234567), 0); c0 += 4;
        vout0x01234567 = vext_s8(vout0x01234567, vout0x01234567, 4);
      }
      if (nc & 2) {
        vst1_lane_u16((void*) c0, vreinterpret_u16_s8(vout0x01234567), 0); c0 += 2;
        vout0x01234567 = vext_s8(vout0x01234567, vout0x01234567, 2);
      }
      if (nc & 1) {
        vst1_lane_s8(c0, vout0x01234567, 0);
      }

      nc = 0;
    }
  } while (nc != 0);
}