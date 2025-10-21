#ifndef S21_BIG_INTERNAL_H
#define S21_BIG_INTERNAL_H

#include "include/s21_decimal.h"

typedef struct {
  uint32_t bits[7];
  int scale;
  int sign;
} s21_big_decimal;

void s21_big_set_zero(s21_big_decimal *d);
int s21_big_is_zero(const s21_big_decimal d);

int s21_big_from_decimal(s21_decimal src, s21_big_decimal *dst);
int s21_big_to_decimal(s21_big_decimal src, s21_decimal *dst);

int s21_big_mul10(s21_big_decimal *d);
int s21_big_div10(s21_big_decimal *d, uint32_t *rem);
int s21_big_scale_down_bankers(s21_big_decimal *d, int target_scale);

#endif