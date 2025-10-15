#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include<stdint.h>

typedef struct {
  int bits[4];
} s21_decimal;

#define S21_SIGN_MASK (1u << 31)
#define S21_SCALE_MASK (0xFFu << 16)
#define S21_SCALE_SHIFT 16

int s21_get_sign(const s21_decimal d);
void s21_set_sign(s21_decimal *d, int sing);
int s21_get_scale(const s21_decimal d);
void s21_set_scale(s21_decimal *d, int scale);
void s21_flags_normalize(s21_decimal *d);
int s21_flags_is_valid(const s21_decimal d);
void s21_set_zero(s21_decimal *d);
int s21_is_zero(const s21_decimal d);

int s21_get_bit(const s21_decimal d, int index);
void s21_set_bit(s21_decimal *d, int index, int value);

static inline uint32_t s21_bits3u(s21_decimal d) {
  return (uint32_t)d.bits[3];
}

#endif