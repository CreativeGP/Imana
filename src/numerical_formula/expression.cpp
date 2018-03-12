/* ========================================================================
   ╦┌┬┐┌─┐┌┐┌┌─┐
   ║│││├─┤│││├─┤
   ╩┴ ┴┴ ┴┘└┘┴ ┴
   2018/03/03

   $File: expression.cpp $
   $Date: 2018/03/08 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP, Inc. All Rights Reserved. $
   ======================================================================== */

#include "numerical.hpp"

#include <algorithm>
#include <iostream>


string
pr(string s) {
    if (s.front() == '(' && s.back() == ')') {
        s = s.substr(1,s.size()-2);
    }
    return s;
}

Expression::
Expression()
{
}

Expression::
Expression(string str)
    : _str(str)
{
    cout << "Expression: " << str << endl;
    parse();
}

void Expression::
simplify()
{
}

void Expression::
parse()
{
    string strt = _str;
    string::size_type pos = 0;
    while ((pos = strt.find(" ", pos)) != string::npos) {
        strt.replace(pos, 1, "");
    }

    reverse(strt.begin(), strt.end());

    vector<string> up;
    vector<string> down;
    string token;
    int root = 0;
    for (char c : strt) {
        if (c == ')') root++;
        if (c == '(') root--;
        if (c == '+' && root == 0) {
            _monominals.push_back(new Monominal(pr(token)));
            token = "";
        } else if (c == '-' && root == 0) {
            _monominals.push_back(new Monominal('-'+token));
            token = "";
        } else {
            token = c + token;
        }
    }
    _monominals.push_back(new Monominal(pr(token)));
}

string Expression::
to_string()
{
    if (_monominals.size() == 0) return "";

    string result;
    if (_monominals.size() > 1)
    {
        for (auto it = _monominals.begin();
             it != _monominals.end()-1;
             ++it)
        {
            result += (*it)->to_string() + " + ";
        }
    }
    result += _monominals.back()->to_string();
    return result;
}

