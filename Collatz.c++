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

// ------------
// cache_array
// ------------

#ifdef cache_mac
int cache[1000000];   	// Large cache map
#endif

// ------------
// namespace_shortcut
// ------------

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
	int temp = 0;
	int quickCheck;
#ifdef cache_mac
	cache_check();
#endif
	if(j > i){ //Forwards direction
		quickCheck = j/2 + 1; //magic math to reduce range
		if( i < quickCheck)
			i = quickCheck;
		for(int z = i; z <= j; ++z)
		{
			
#ifdef cache_mac
			if(cache[z] != 0){
				temp = cache[z];
			}else {
				temp = collatz_eval2(z);
			}
#endif
			if(temp > max){
#ifdef cache_mac
				if(cache[z] == 0){
					cache[z] = temp;
				}
#endif
				max = temp;
			}
			temp = 0;
		}
	} 
	else if(i > j) //backwards direction
	{
		quickCheck = i/2 + 1; //magic math to reduce range
		if( j < quickCheck)
			j = quickCheck;
		for(int z = j; z <= i; ++z)
		{
#ifdef cache_mac
			if(cache[z] != 0){
				temp = cache[z];
			}else {
				temp = collatz_eval2(z);
			}
#endif	
			if(temp > max){
#ifdef cache_mac
				if(cache[z] == 0){
					cache[z] = temp;
				}
#endif
				max = temp;
			}
			temp = 0;
		}
	}
	else
	{
		max = collatz_eval2(i); //They are the same
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
#ifdef cache_mac
// ------------
// cache_check
// ------------

void cache_check(){
#ifndef cachstuff
#define cachstuff
	cache[1] = 0;
	cache[2] = 1;
	cache[4] = 2;
	cache[8] = 3;
	cache[16] = 4;
	cache[32] = 5;
	cache[128] = 6;
	cache[256] = 7;
	cache[512] = 8;
	cache[1024] = 9;
	cache[2048] = 10;
	cache[4096] = 11;
	cache[8192] = 12;
	cache[16384] = 13;
	cache[32786] = 14;
	cache[65536] = 15;
#endif
}
#endif

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
