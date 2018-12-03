/**
  * @file   util.hpp
  * @brief  utility functions
  *
  * @author Changrui
  * @date   2018/11/29
  *
  */
#ifndef util_hpp
#define util_hpp

#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::begin;
using std::end;
using std::cout;
using std::endl;
using std::for_each;

template<typename T>
void print_list(vector<T>& vec)
{
	for_each(begin(vec), end(vec), [](int &x) {
		cout << x << " ";
	});
	cout << endl;
}


#endif
