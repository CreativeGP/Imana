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


bool is_number(const std::string& s)
{
    string test = s;
    test.erase(remove(test.begin(), test.end(), '-'), test.end());
    std::string::const_iterator it = test.begin();
    while (it != test.end() && std::isdigit(*it)) ++it;
    return !test.empty() && it == test.end();
}


void Monominal_Without_Fraction::
add_token(string token)
{
    if (is_number(token)) {
        long long v;
        if (token.find('-') == string::npos) v = atoi(token.c_str());
        else v = - atoi(token.c_str());
        scalars.push_back(v);
    } else {
        variables.push_back(token);
    }
}


void Monominal_Without_Fraction::
simplify_scalars()
{
    long long n = 1;
    for (long long i : scalars) {
        n *= i;
    }
    scalars.clear();
    scalars.push_back(n);
}


void Monominal_Without_Fraction::
invert()
{
    minus = !minus;
    scalars.insert(scalars.begin(), minus?-1:1);
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

decimal_t
Fraction::value()
{
    return (decimal_t)_numerator / (decimal_t)_denominator;
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


Fraction
Fraction::operator *(Fraction &rhs)
{
    Fraction result;

    result._numerator = _numerator * rhs._numerator;
    result._denominator = _denominator * rhs._denominator;

    return result;
}

Fraction
Fraction::operator /(Fraction &rhs)
{
    Fraction result;

    result._numerator = _numerator * rhs._denominator;
    result._denominator = _denominator * rhs._numerator;

    return result;
}
