/*
Copyright 2021 Masaru Nemoto <nemolize@gmail.com>
*/

#pragma once

typedef int32_t FIXED_POINT_NUMBER;

#define FIXED_POINT_SIZE 14
#define FLOAT_TO_FPN(fval) ((FIXED_POINT_NUMBER)round(fval * (1 << FIXED_POINT_SIZE)))
#define FPN_TO_INT(fval) (fval >> FIXED_POINT_SIZE)
#define FPN_MUL(fval1, fval2) ((fval1 * fval2) >> FIXED_POINT_SIZE)
#define FPN_DIV(fval1, fval2) ((fval1 << FIXED_POINT_SIZE) / fval2)
