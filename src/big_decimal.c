#include "big_internal.h"

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