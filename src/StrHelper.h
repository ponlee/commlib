/**********************************
 * File: StrHelper.h
 * Author: ponlee
 * Version:1.0
 * Date: 2014-04
 * Desc:�����ַ���������װ��
***********************************/

#ifndef _STR_BASE_HPP__
#define _STR_BASE_HPP__

#include <stdint.h>
#include <string>
#include <vector>
#include <cstdio>

#include <algorithm> 
#include <functional>
#include <cctype>
#include <regex.h>

class CStrHelper
{
public:
	CStrHelper(){}
	~CStrHelper(){}

public:
	
	//////////////////�ַ�������ת��ϵ�к���//////////////////
	/**
	* @DESC: ʮ�������ַ���ת��Ϊ64λ�������
	**/
	static int64_t StringToHex64( const std::string& str );

	/**
	* @DESC: 32λ����ת��Ϊʮ�������ַ������
	**/
	static std::string  HexTo32String( int32_t val );

	/**
	* @DESC: 64λ����ת��Ϊʮ�������ַ������
	**/
	static std::string  HexTo64String( int64_t val );
	/**
	* @DESC: �����ַ���ת��Ϊ64λ����������
	**/
	static int64_t atoi_l( const char* str,size_t len,int radix );

	/**********************************************
	** @DESC ��������buff��ʮ��������ʽ�ַ������
	** @param pBuffer char*	: ������buff�׵�ַָ��
	** @param iLength int	: ������buff����,��λ�ֽ�
	** @param outStr string	: ת���������ʮ�������ַ���
	************************************************/
	static void ConvertBinToStr( const char* pBuffer, int iLength, std::string& outStr );


	//////////////////�ַ�����������//////////////////

	/****************************************
	** @DESC: ȥ���ַ�����ߵĿ��ַ�
	**
	******************************************/
	static std::string &ltrim(std::string &s);

	/****************************************
	** @DESC: ȥ���ַ����ұߵĿ��ַ�
	**
	*****************************************/
	static std::string &rtrim(std::string &s);
	/****************************************
	** @DESC: ȥ���ַ������ߵĿ��ַ�
	**
	*****************************************/
	static std::string &trim(std::string &s);

	/**********************************************
	** @DESC �ַ�����ĳһ�ַ����е������ַ��ָ��vector<std::string>
	** @param in_str string		: ��������ַ���
	** @param out_vec vector	: ����������vector
	** @param delim string		: �ָ���ַ���
	************************************************/
	static int32_t SplitStrToVector( const std::string &in_str, std::vector<std::string> &out_vec, const char *delim );

	/**********************************************
	** @DESC �ַ�����ĳһ�ַ����е������ַ��ָ��vector<int>
	** @param in_str string		: ��������ַ���
	** @param out_vec vector	: ����������vector<int>
	** @param delim string		: �ָ���ַ���
	************************************************/
	static int32_t SplitStrToVecInt( const std::string &in_str, std::vector<int> &out_vec, const char *delim );

	/**********************************************
	** @DESC �ַ�������ƥ������
	** input:
	** @param strSrc string		: ��Ҫƥ���ԭ��
	** @param strRegular string	: ������ʽ
	** @param strErrmsg string	: ����������vector
	** @param cflags int		: ƥ��ѡ�Ĭ����posix ��չ������ʽ
	** output:
	** 0: ƥ��ɹ�1:  ƥ��ʧ��2:  ��������
	************************************************/
	static bool RegexMatch( const std::string& strSrc,const std::string& strRegular
		,std::string& strErrmsg,int cflags = REG_EXTENDED );

	//////////////////�ַ�������ת������//////////////////

	/**********************************************
	** @DESC ��Utf-8������ַ���ת��Ϊgb������ַ���
	** @input gbStr char*		: ��������ַ���
	** @output 					: ָ��ת�����buff
	** @Notice		:���ص��ⲿָ����Ҫ����delete�ͷſռ�
	************************************************/
	static char* ConvUtfToGb( const char* utfStr );

	/**********************************************
	** @DESC ��gb������ַ���ת��ΪUtf-8������ַ���
	** @input gbStr char*		: ��������ַ���
	** @output 					: ָ��ת�����buff
	** @Notice		:���ص��ⲿָ����Ҫ����delete�ͷſռ�
	************************************************/
	static char* ConvGbToUtf( const char* gbStr );

private:
	
};


#endif
