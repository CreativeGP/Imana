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

#include "monominal.hpp"

Monominal::Monominal()
{
}

Monominal::Monominal(string str)
    : _str(str)
{
    parse();
}

void Monominal::
parse()
{
    /*
      単項式を表す文字列を最大まで分解します
      全ての単項式は分数で表せると思うから全部分数として定義する
      3 * a * 4 -> [3(scalar), 4(scalar), a(variable)]
      3 / 2 * a -> [(3(scalar)/2(scalar))(fraction), a(variable)]
      3 / (2 * a) -> [(3(scalar) / [2(scalar), a(variable)])(fraction)]
     */
    string strt = _str;
    string::size_type pos = 0;
    while ((pos = strt.find(" ", pos)) != string::npos) {
        strt.replace(pos, 1, "");
    }

    if (strt[0] == '-')
        _up.invert(); // 分母をマイナスにする

    reverse(strt.begin(), strt.end());

    vector<string> up;
    vector<string> down;
    string token;
    for (char c : strt) {
        if (c == '*') {
            _up.add_token(token);
            token = "";
        } else if (c == '/') {
            _down.add_token(token);
            token = "";
        } else {
            token = c + token;
        }
    }

    _up.add_token(token);
}

void Monominal::
simplify()
{
    // 現状は数量を全てかけ合わせるだけ
    _up.simplify_scalars();
    _down.simplify_scalars();
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

    if (_down.scalars[0]==1) downst << "";
    else downst << _down.scalars[0];
    for (string var : _down.variables) {
        downst << var;
    }

    result = upst.str() + (downst.str()=="" ? "" : " / "+downst.str());

    return result;
}
