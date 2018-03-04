/* ========================================================================
   ╦┌┬┐┌─┐┌┐┌┌─┐
   ║│││├─┤│││├─┤
   ╩┴ ┴┴ ┴┘└┘┴ ┴
   2018/03/03

   $File: main.cpp $
   $Date: 2018/03/03 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP, Inc. All Rights Reserved. $
   ======================================================================== */

#include <iostream>
#include <string>

#include "numerical_formula/fraction.hpp"

using namespace std;

int main ()
{
    Fraction *frac = new Fraction(5, 3);
    cout << frac->to_string() << endl;
}
