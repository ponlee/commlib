/**********************************
 * File:	Algor_Base.h
 * Author:	ponlee
 * Version:	1.0
 * Date:	2014-06
 * Desc:	基本算法类封装
***********************************/

#ifndef __BASE_ALGORITHM_H__
#define __BASE_ALGORITHM_H__

#include <vector>
#include <string>
#include <stdint.h>
#include <algorithm>

class CAlgoriHelper
{
public:
	CAlgoriHelper(){}
	~CAlgoriHelper(){}

public:
	/**********************************************
	** @DESC n选m组合的算法实现
	************************************************/
	static int32_t ListCombination( int n, int m, std::vector<std::string> &combinList );

	/**********************************************
	** @DESC 二分查找算法实现
	************************************************/
	static int32_t BinarySearch( const int arr[], int low, int high, int key );

private:

};

#endif
