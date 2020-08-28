/*
Copyright <2020> <Koichi Mori>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef FUNC
#define FUNC
#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
extern "C" {
   #include <quadmath.h>
}
#include "macro.h"

int debug,flag_nsp,flag_bonferroni_factor,flag_wild,flag_testable;
char wild_card;

void combination(ld2 &ans,unsigned long n,unsigned long r);
double least(ll support,ll count0,ll count1);
void prefixspan(succession suc,string let,database db,ll minsup, pattern &pattern,constraint c);
void print_result(string let,pattern &pattern,ll num_minsup,double alpha,ll minsup,ll total,ll count0,ll count1,database db,string fname_nsp);
string complement(string s);
#endif
