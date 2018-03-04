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

class Fraction
{
private:
    int _numerator,
        _denominator;

public:
    Fraction();
    Fraction(int numerator, int denominator);

    std::string to_string();
};

#endif

