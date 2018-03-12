/* ========================================================================
   ╦┌┬┐┌─┐┌┐┌┌─┐
   ║│││├─┤│││├─┤
   ╩┴ ┴┴ ┴┘└┘┴ ┴
   2018/03/03

   $File: fraction.hpp $
   $Date: 2018/03/04 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP, Inc. All Rights Reserved. $
   ======================================================================== */

#ifndef __FRACTION_HPP__
#define __FRACTION_HPP__

#include <string>
#include <vector>
#include <algorithm>


using namespace std;

typedef long double decimal_t;

class Fraction
{
public:
    Fraction();
    Fraction(int numerator, int denominator);

    Fraction& operator--();
    Fraction& operator++();
    Fraction operator-(Fraction&);
    Fraction operator+(Fraction&);
    Fraction operator*(Fraction&);
    Fraction operator/(Fraction&);

    string to_string();
    decimal_t value();

private:
    int _numerator,
        _denominator;

};

#endif

