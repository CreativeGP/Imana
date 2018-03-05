/* ========================================================================
   ╦┌┬┐┌─┐┌┐┌┌─┐
   ║│││├─┤│││├─┤
   ╩┴ ┴┴ ┴┘└┘┴ ┴
   2018/03/03

   $File: fraction.cpp $
   $Date: 2018/03/04 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP, Inc. All Rights Reserved. $
   ======================================================================== */

#include <iostream>
#include <sstream>
#include <memory>

#include "fraction.hpp"

using namespace std;

int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b)
{
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

Fraction::Fraction() {}
Fraction::Fraction(int numerator, int denominator)
    : _numerator(numerator), _denominator(denominator)
{
}

string
Fraction::to_string()
{
    ostringstream ss;
    ss << _numerator << "/" << _denominator;
    string result(ss.str());
    return result;
}

Fraction &
Fraction::operator ++()
{
    _numerator += _denominator;
    return *this;
}

Fraction &
Fraction::operator --()
{
    _numerator -= _denominator;
    return *this;
}

Fraction
Fraction::operator +(Fraction &rhs)
{
    // NOTE: 分母が0だった場合エラーが発生する

    Fraction result;

    // 最小公倍数を求める（これが新しい分母になる）
    int newdenom = lcm(this->_denominator, rhs._denominator);

    // this_factor, rhs_factor >= 1
    int this_factor = newdenom / this->_denominator;
    int rhs_factor = newdenom / rhs._denominator;

    result._numerator = this->_numerator*this_factor + rhs._numerator*rhs_factor;
    result._denominator = newdenom;

    return result;
}

Fraction
Fraction::operator -(Fraction &rhs)
{
    // NOTE: 分母が0だった場合エラーが発生する

    Fraction result;

    // 最小公倍数を求める（これが新しい分母になる）
    int newdenom = lcm(this->_denominator, rhs._denominator);

    // this_factor, rhs_factor >= 1
    int this_factor = newdenom / this->_denominator;
    int rhs_factor = newdenom / rhs._denominator;

    result._numerator = this->_numerator*this_factor - rhs._numerator*rhs_factor;
    result._denominator = newdenom;

    return result;
}
