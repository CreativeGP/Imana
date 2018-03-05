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
    Fraction *f1 = new Fraction(1, 2);
    Fraction *f2 = new Fraction(1, 3);
    cout << f2->value() << endl;
}
