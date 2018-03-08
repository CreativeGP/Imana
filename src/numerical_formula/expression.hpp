/* ========================================================================
   ╦┌┬┐┌─┐┌┐┌┌─┐
   ║│││├─┤│││├─┤
   ╩┴ ┴┴ ┴┘└┘┴ ┴
   2018/03/03

   $File: expression.hpp $
   $Date: 2018/03/08 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP, Inc. All Rights Reserved. $
   ======================================================================== */

#ifndef __EXPRESSION_HPP__
#define __EXPRESSION_HPP__

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "monominal.hpp"

using namespace std;

class Expression
{
public:
    Expression();
    Expression(string str);

    void simplify();
    string to_string();

private:
    void parse();

    string _str;
    vector<Monominal *> _monominals;
};

#endif

