#include "big_internal.h"
#include <string.h>

static inline int is_zero_words(const uint32_t *w, int n) {
  for (int i = 0; i < n; ++i) {
    if(w[i]) return 0;
  }
  return 1;
}

static inline int add_words_inplace(uint32_t *w, const uint32_t *add, int n) {
  unsigned long long carry = 0;
  for (int i = 0; i < n; ++i) {
    unsigned long long s = (unsigned long long)w[i] + add[i] + carry;
    w[i] = (uint32_t)s;
    carry = s >> 32;
  }
  return (int)carry;
}

static inline int shl1_words(uint32_t *w, int n) {
  uint32_t carry = 0;
  for (int i = 0; i < n; ++i) {
    unsigned long long v = ((unsigned long long)w[i] << 1) | carry;
    w[i] = (uint32_t)v;
    carry = (uint32_t)(v >> 32);
  }
  return carry;
}

void s21_big_set_zero(s21_big_decimal *v) {
  memset(v, 0, sizeof(*v));
}

int s21_big_is_zero(const s21_big_decimal v) {
  return is_zero_words(v.bits, 7);
}

int s21_big_from_decimal(s21_decimal src, s21_big_decimal *dst) {
  if(!dst) return 1;
  if(!s21_flags_is_valid(src)) return 1;
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->scale = s21_get_scale(src);
  dst->sign = s21_get_sign(src);
  return 0;
}

int s21_big_mul10(s21_big_decimal *d) {
  uint32_t a[7];
  uint32_t x3[7];
  memcpy(a, d->bits, sizeof(a));
  memcpy(x3, d->bits, sizeof(x3));
  for(int s = 0; s < 3; ++s) {
    if(shl1_words(x3, 7) == 0) {
      return 1;
    }
  }
  uint32_t carry = 0;
  for(int i = 0; i < 7; ++i) {
    unsigned long long t = ((unsigned long long)a[i] << 1) | carry;
    a[i] = (uint32_t)t;
    carry = (uint32_t)(t >> 32);
  }
  if(add_words_inplace(a, x3, 7)) return 1;
  memcpy(d->bits, a, sizeof(a));
  return 0;
}

