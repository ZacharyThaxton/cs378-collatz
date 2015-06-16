// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    assert(i > 0);
    assert(j > 0);
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
	assert(i > 0);
	assert(j > 0);
	int max = 0;
	if(j > i){
		for(int z = i; z <= j; ++z)
		{
			int temp = collatz_eval2(z);
			if(temp > max){
				max = temp;
			}
		}
	} 
	else if(i > j) 
	{
		for(int z = j; z <= i; ++z)
		{
			int temp = collatz_eval2(z);
			if(temp > max){
				max = temp;
			}
		}
	}
	else
	{
		max = collatz_eval2(i);
	}
	assert(max > 0);
	return max;
}

// ------------
// collatz_eval2
// ------------

int collatz_eval2 (int i){
	assert(i > 0);
    	int c = 1;
    	while (i > 1) {
        	if ((i % 2) == 0)
            		i = (i / 2);
        	else
            		i = (3 * i) + 1;
        	++c;}
    	assert(c > 0);
    	return c;
}


// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
