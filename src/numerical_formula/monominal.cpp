/* ========================================================================
   ╦┌┬┐┌─┐┌┐┌┌─┐
   ║│││├─┤│││├─┤
   ╩┴ ┴┴ ┴┘└┘┴ ┴
   2018/03/03

   $File: monominal.cpp $
   $Date: 2018/03/05 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP, Inc. All Rights Reserved. $
   ======================================================================== */

#include "numerical.hpp"

#include <algorithm>
#include <sstream>
#include <iostream>

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



Monominal::Monominal()
{
}

Monominal::Monominal(string str)
    : _str(str)
{
    cout << "Monominal: " << str << endl;
    parse();
}

void Monominal::
parse()
{
    /*
      単項式を表す文字列を最大まで分解します
      全ての単項式は分数で表せると思うから全部分数として定義する

      NOTE: 分数式と呼ばれるものも単項式として分類される
      詳しく言うとその中でも分母に複数項あるものはここに入ってくるので
      しっかり分類しなければならない
     */
    string strt = _str;
    string::size_type pos = 0;
    while ((pos = strt.find(" ", pos)) != string::npos) {
        strt.replace(pos, 1, "");
    }

    if (strt[0] == '-')
        _up.invert(); // 分母をマイナスにする

    reverse(strt.begin(), strt.end());


    vector<string> down;
    string token;
    int root = 0;
    for (char c : strt) {
        if (c == ')') root++;
        if (c == '(') root--;
        if (c == '*' && root == 0) {
            _up.add_token(token);
            token = "";
        } else if (c == '/' && root == 0) {
            if (token.front() == '(' && token.back() == ')') {
                token = token.substr(1,token.size()-2);
            }
            down.push_back(token);
            token = "";
        } else {
            token = c + token;
        }
    }
    _up.add_token(token);

    string all;
    if (down.size() >= 2) {
        for (string t : down) {
            all += "("+t+")"+"*";
        }
        all = all.substr(0, all.size()-1);
    }
    else if (down.size() == 1) all = down[0];
//    else all = "1";

    if (_down) delete _down;

    if (all != "") _down = new Expression(all);
}

// void Monominal::
// reduce()
// {
//     // 分子を使って分母から割り算を消し去る、再帰的
//     bool ok = true;
//     for (auto mono : _down) {
//     }
// }

void Monominal::
simplify()
{
    // 現状は数量を全てかけ合わせるだけ
    _up.simplify_scalars();
//    _down->simplify();
}

string Monominal::
to_string()
{
    string result;
    stringstream upst, downst;

    simplify();

    if (_up.scalars[0]==1) upst << "";
    else upst << _up.scalars[0];
    for (string var : _up.variables) {
        upst << var;
    }
    if (upst.str() == "") upst << "1";

    // if (_down.scalars[0]==1) downst << "";
    // else downst << _down.scalars[0];
    // for (string var : _down.variables) {
    //     downst << var;
    // }

    if (_down) downst << _down->to_string();

    result = upst.str() + (downst.str()=="" ? "" : " / "+downst.str());

    return result;
}
