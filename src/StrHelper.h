/**********************************
 * File: StrHelper.h
 * Author: ponlee
 * Version:1.0
 * Date: 2014-04
 * Desc:基本字符串操作封装类
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
	
	//////////////////字符串类型转化系列函数//////////////////
	/**
	* @DESC: 十六进制字符串转化为64位整数输出
	**/
	static int64_t StringToHex64( const std::string& str );

	/**
	* @DESC: 32位整数转化为十六进制字符串输出
	**/
	static std::string  HexTo32String( int32_t val );

	/**
	* @DESC: 64位整数转化为十六进制字符串输出
	**/
	static std::string  HexTo64String( int64_t val );
	/**
	* @DESC: 整数字符串转化为64位任意进制输出
	**/
	static int64_t atoi_l( const char* str,size_t len,int radix );

	/**********************************************
	** @DESC 将二进制buff按十六进制形式字符串输出
	** @param pBuffer char*	: 二进制buff首地址指针
	** @param iLength int	: 二进制buff长度,单位字节
	** @param outStr string	: 转化后输出的十六进制字符串
	************************************************/
	static void ConvertBinToStr( const char* pBuffer, int iLength, std::string& outStr );


	//////////////////字符串操作函数//////////////////

	/****************************************
	** @DESC: 去除字符串左边的空字符
	**
	******************************************/
	static std::string &ltrim(std::string &s);

	/****************************************
	** @DESC: 去除字符串右边的空字符
	**
	*****************************************/
	static std::string &rtrim(std::string &s);
	/****************************************
	** @DESC: 去除字符串两边的空字符
	**
	*****************************************/
	static std::string &trim(std::string &s);

	/**********************************************
	** @DESC 字符串按某一字符串中的任意字符分割成vector<std::string>
	** @param in_str string		: 带处理的字符串
	** @param out_vec vector	: 输出处理完的vector
	** @param delim string		: 分割的字符集
	************************************************/
	static int32_t SplitStrToVector( const std::string &in_str, std::vector<std::string> &out_vec, const char *delim );

	/**********************************************
	** @DESC 字符串按某一字符串中的任意字符分割成vector<int>
	** @param in_str string		: 带处理的字符串
	** @param out_vec vector	: 输出处理完的vector<int>
	** @param delim string		: 分割的字符集
	************************************************/
	static int32_t SplitStrToVecInt( const std::string &in_str, std::vector<int> &out_vec, const char *delim );

	/**********************************************
	** @DESC 字符串正则匹配运算
	** input:
	** @param strSrc string		: 需要匹配的原串
	** @param strRegular string	: 正则表达式
	** @param strErrmsg string	: 输出处理完的vector
	** @param cflags int		: 匹配选项，默认用posix 扩展正则表达式
	** output:
	** 0: 匹配成功1:  匹配失败2:  发生错误
	************************************************/
	static bool RegexMatch( const std::string& strSrc,const std::string& strRegular
		,std::string& strErrmsg,int cflags = REG_EXTENDED );

	//////////////////字符串编码转化函数//////////////////

	/**********************************************
	** @DESC 将Utf-8编码的字符串转化为gb编码的字符串
	** @input gbStr char*		: 待处理的字符串
	** @output 					: 指向转化后的buff
	** @Notice		:返回的外部指针需要调用delete释放空间
	************************************************/
	static char* ConvUtfToGb( const char* utfStr );

	/**********************************************
	** @DESC 将gb编码的字符串转化为Utf-8编码的字符串
	** @input gbStr char*		: 待处理的字符串
	** @output 					: 指向转化后的buff
	** @Notice		:返回的外部指针需要调用delete释放空间
	************************************************/
	static char* ConvGbToUtf( const char* gbStr );

private:
	
};


#endif
