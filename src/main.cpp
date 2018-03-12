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
#include "numerical_formula/monominal.hpp"
#include "numerical_formula/expression.hpp"

using namespace std;

int main ()
{
    // 2 * y + 5 = 3 * y - 5
    //    Equation *eq = new Equation("2 * y + 5 = 3 * y - 5");
    // Expression [2 * y + 5] [3 * y - 5]
    // Monominal [5 / 2 * y / 3] [5] [3 * y] [5]
//    Monominal *m = new Monominal("3 / ((4*x*y/3)+(y/(2+x)))");
    Expression *ex = new Expression("(4*x*y/3)+(y/(2+x))");
//    cout << m->to_string() << endl;
}
