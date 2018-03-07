/* ========================================================================
   ╦┌┬┐┌─┐┌┐┌┌─┐
   ║│││├─┤│││├─┤
   ╩┴ ┴┴ ┴┘└┘┴ ┴
   2018/03/03

   $File: monominal.hpp $
   $Date: 2018/03/05 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP, Inc. All Rights Reserved. $
   ======================================================================== */

#ifndef __MONOMINAL_HPP__
#define __MONOMINAL_HPP__

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

struct Monominal_Without_Fraction
{
    vector<string> variables;
    vector<long long> scalars;

    void add_token(string token);
    void simplify_scalars();
};

class Monominal
{
public:
    Monominal();
    Monominal(string str);

    void simplify();
    string to_string();

private:
    void parse();

    string _str;
    Monominal_Without_Fraction _up;
    Monominal_Without_Fraction _down;
};

#endif

