#include <stdio.h>
#include "include/s21_decimal.h"

static void dump(const char *title, s21_decimal *d);

int main(){
  s21_decimal x = {.bits = {0,0,0,0}};
  dump("Стартовое значение", &x);

  s21_set_bit(&x, 0, 1);
  s21_set_bit(&x, 1, 1);
  s21_set_bit(&x, 2, 1);
  s21_set_bit(&x, 3, 1);
  x.bits[3] = 0x00140001;

  s21_flags_normalize(&x);

  dump("Обновленное значение, normalize", &x);
  printf("is validate: %d\n", s21_flags_is_valid(x));
  return 0;
}

static void dump(const char *title, s21_decimal *d) {
  printf("%s\n", title);
  printf("%08X %08X %08X %08X\n", d->bits[0], d->bits[1], d->bits[2], d->bits[3]);
}