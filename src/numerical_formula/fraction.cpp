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

#include <sstream>

#include "fraction.hpp"

Fraction::Fraction() {}
Fraction::Fraction(int numerator, int denominator)
    : _numerator(numerator), _denominator(denominator)
{
}

std::string
Fraction::to_string()
{
    std::ostringstream ss;
    ss << _numerator << "/" << _denominator;
    std::string result(ss.str());
    return result;
}
