// Copyright (c) 2013 MIT License

#ifndef _POLY_H
#define _POLY_H

#include <stdio.h>

struct Polynomial {
    int *coefficients;
    int size;
};

typedef struct Polynomial Polynomial;

Polynomial *polynomial_new(int size);
void polynomial_delete(Polynomial *polynomial);
Polynomial *multiply(Polynomial *p1, Polynomial *p2);
Polynomial *multiply_karat(Polynomial *p1, Polynomial *p2);
void print_string(Polynomial *p);
bool equals(Polynomial *p1, Polynomial *p2);

#endif  // _POLY_H
