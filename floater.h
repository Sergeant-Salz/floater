
/**
 * Defines a singe precision floating point numer.
 * one bit sign, 8 bit characteristic (offset 127), 23 bit fraction
 */
typedef unsigned int i_float;

#define sign(i_float) ((i_float >> 23) & 1)
#define characteristic(i_float) ((i_float >> 23) & 0xFF)
#define fraction(i_float) (i_float & 0x7FFFFF)

unsigned short get_characteristic(i_float value);
unsigned short get_sign(i_float value);
unsigned short get_fraction(i_float value);

i_float f_add(i_float num1, i_float num2);

i_float f_sub(i_float num1, i_float num2);

i_float f_mul(i_float num1, i_float num2);

i_float f_div(i_float num1, i_float num2);
