/**********************************
 * File:	Algor_Base.h
 * Author:	ponlee
 * Version:	1.0
 * Date:	2014-06
 * Desc:	�����㷨���װ
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
	** @DESC nѡm��ϵ��㷨ʵ��
	************************************************/
	static int32_t ListCombination( int n, int m, std::vector<std::string> &combinList );

	/**********************************************
	** @DESC ���ֲ����㷨ʵ��
	************************************************/
	static int32_t BinarySearch( const int arr[], int low, int high, int key );

private:

};

#endif
