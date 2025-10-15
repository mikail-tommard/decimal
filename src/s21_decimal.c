#include "s21_decimal.h"
/*
  @brief: Установить нулевое значение. Обнулить все биты
  @param: d - указатель на структуру децимал
*/
void s21_set_zero(s21_decimal *d) {
  d->bits[0] = d->bits[1] = d->bits[2] = d->bits[3] = 0;
}

/*
  @brief: Проверка на нулевое значение
  @param: d - структура децимал
*/
int s21_is_zero(const s21_decimal d) {
  return (d.bits[0] | d.bits[1] | d.bits[2]) == 0;
}

/*
  @brief: Получить знак децимала
  @param: d - структура децимала
*/
int s21_get_sign(const s21_decimal d) {
  return s21_bits3u(d) & S21_SIGN_MASK ? 1 : 0;
}

/*
  @brief: Установить знак децимала
  @param: d - указатель на струртуру децимала
  @param: sing - знак(0 - положительный, 1 - отрицательный)
*/
void s21_set_sign(s21_decimal *d, int sign) {
  uint32_t b3 = (uint32_t)d->bits[3];
  b3 &= ~S21_SIGN_MASK;
  if(sign) b3 |= S21_SIGN_MASK;
  d->bits[3] = (int)b3;
}

/*
  @brief: Получить количество знаков после запятой
  @param: d - структура децимала
*/
int s21_get_scale(const s21_decimal d) {
  return (int)((s21_bits3u(d) & S21_SCALE_MASK) >> S21_SCALE_SHIFT);
}

/*
  @brief: Установить количество знаков после запятой
  @param: d - указатель на структуру децимала
  @param: scale - количество знаков
*/
void s21_set_scale(s21_decimal *d, int scale) {
  if (scale < 0) scale = 0;
  if (scale > 28) scale = 28;
  uint32_t b3 = (uint32_t)d->bits[3];
  b3 &= ~S21_SCALE_MASK;
  b3 |= ((uint32_t)scale << S21_SCALE_SHIFT) & S21_SCALE_MASK;
  d->bits[3] = (int)b3;
}

static inline word_index(int index) {
  return index / 32;
}

static inline bit_offset(int index) {
  return index % 32;
}

int s21_get_bit(const s21_decimal d, int index) {
  if (index < 0 || index > 95) return 0;
  unsigned w = (unsigned)d.bits[word_index(index)];
  return (int)((w >> bit_offset(index)) & 1u);
}

void s21_set_bit(s21_decimal *d, int index, int value) {
  if (!d) return;
  if (index < 0 || index > 95) return;
  unsigned w = (unsigned)d->bits[word_index(index)];
  unsigned m = (1u << bit_offset(index));
  if (value) w |= m; else w &= ~m;
  d->bits[word_index(index)] = (int)w;
}