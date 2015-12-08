#include <iconv.h>
#include <vector>
#include <cstring>
#include "StrHelper.h"
using namespace std;

int64_t CStrHelper::StringToHex64( const string& str )
{
	int64_t sum=0;
	int		len = str.length();
	int		end = len ;

	if ( len > 16 )
		end = 16;

	string	tmp( str.c_str(),end );
	int64_t pow = 1;

	for ( int i=0; i<end; ++i )
	{
		if ( tmp[i]>='a' && tmp[i]<='f' )
			tmp[i] += 'A'-'a';
	}

	for ( int i=end-1; i>=0; --i )
	{
		int	num = 0;
		if ( tmp[i]>='A' && tmp[i]<='F' )
		{
			num = tmp[i] - ( 'A' - 10 );
		}
		else if ( tmp[i]>='0' && tmp[i]<='9' )
		{
			num = tmp[i] - '0';
		}
		else
		{
			sum = 0;
			return sum;
		}

		sum += pow * num;
		pow *= 16;
	}

	return  sum;
}

std::string CStrHelper::HexTo32String( int32_t val )
{
	char str[31] = "";
	::sprintf( str,"%x",val);
	return str;
}

std::string CStrHelper::HexTo64String( int64_t val )
{
	char str[100] = "";
	::sprintf( str,"%x%x",(int32_t)(val>>32)&0xFFFFFFFF,(int32_t)val&0xFFFFFFFF );
	return str;
}

int64_t CStrHelper::atoi_l( const char* str,size_t len,int radix )
{
	if ( 0==str || 0==*str || 0==len )
		return 0;

	const char* p = str;
	size_t l = len;

	// Find number begin position.
	const char* beg = str;
	while ( 0!=*beg && 0!=l && !::isdigit(*beg) )
		++ beg, -- l;

	if ( 0==*beg || 0==l )
		return 0;

	// Find number end position.
	const char* end = beg;
	while ( 0!=*end && 0!=l && ::isdigit(*end) )
		++end, --l;

	// Calculate the number.
	uint64_t num = 0;
	uint64_t pow = 1;
	for ( const char* pos=end; pos>=beg; --pos )
	{
		num += pow * (*pos-'0');
		pow *= radix;
	}

	return num;
}


void CStrHelper::ConvertBinToStr( const char* pBuffer, int iLength, string& outStr )
{
	if( iLength <= 0 || pBuffer == NULL )
		return;

	if(iLength > 2048)
	{
		iLength = 512;
	}

	char szTmp[10240]={0};
	for(int i = 0; i < iLength; i++ )
	{
		sprintf(szTmp+strlen(szTmp),"%02x", (unsigned char)pBuffer[i]);
	}
	outStr.assign(szTmp,strlen(szTmp));
}

string & CStrHelper::ltrim( std::string &s )
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(ptr_fun<int, int>(std::isspace))));
	return s;
}

string & CStrHelper::rtrim( std::string &s )
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

string & CStrHelper::trim( std::string &s )
{
	return ltrim(rtrim(s));
}

int32_t CStrHelper::SplitStrToVector( const std::string &in_str, std::vector<std::string> &out_vec, const char *delim )
{
	out_vec.clear();
	if (0 == in_str.size())
	{
		return 0;
	}

	char *buffer = new char[in_str.length() + 1];
	memcpy(buffer, in_str.c_str(), in_str.length() + 1);

	char *ptr = NULL;
	char *token = strtok_r(buffer, delim, &ptr);
	while (token)
	{
		out_vec.push_back(token);
		token = strtok_r(NULL, delim, &ptr);
	}

	delete [] buffer;
	return 0;

}

int32_t CStrHelper::SplitStrToVecInt( const std::string &in_str, std::vector<int> &out_vec, const char *delim )
{
	out_vec.clear();
	if (0 == in_str.size()){
		return -1;
	}
	size_t iStart = 0, iEnd = 0;
	while (iStart < in_str.size()){
		int32_t iNumber = atoi(in_str.c_str() + iStart);	//atoi函数会把第一个非数字字符之前的都转换为整形
		out_vec.push_back(iNumber);
		iEnd = in_str.find(*delim, iStart);
		if (string::npos != iEnd){
			iStart = iEnd + 1;
		}
		else{
			iStart = in_str.size();
		}
	}   
	return 0;
}

char* CStrHelper::ConvUtfToGb( const char* utfStr )
{
	iconv_t cd;
	cd = iconv_open("gb2312", "utf-8");

	const char* in_buf = utfStr;
	int in_len = strlen(in_buf);
	char gb_buf[100] = {0};
	char* out_buf = (char*)&gb_buf;
	int out_len = sizeof(gb_buf);

	iconv(cd, (char**)&in_buf, (size_t *)&in_len, &out_buf, (size_t *)&out_len);
	iconv_close(cd);

	char* gb = new char[100];
	strcpy(gb, gb_buf);
	return gb;
}

char* CStrHelper::ConvGbToUtf( const char* gbStr )
{
	iconv_t cd;
	cd = iconv_open("utf-8", "gb2312");

	const char* in_buf = gbStr;
	int in_len = strlen(in_buf);
	char gb_buf[100] = {0};
	char* out_buf = (char*)&gb_buf;
	int out_len = sizeof(gb_buf);

	iconv(cd, (char**)&in_buf, (size_t *)&in_len, &out_buf, (size_t *)&out_len);
	iconv_close(cd);

	char* gb = new char[100];
	strcpy(gb, gb_buf);
	return gb;
}

bool CStrHelper::RegexMatch( const string& strSrc,const string& strRegular,string& strErrmsg,int cflags /*= REG_EXTENDED */ )
{
	int iRet = -1;
	regex_t      reg;  
	char		 ebuf[128] = {0} ; 
	regmatch_t   regmatch[10] ;  
	const int 	 nmatch = 10 ;
	int iSuccess = 2 ;

	iRet = regcomp(&reg, strRegular.c_str(), cflags);
	if(iRet != 0)
	{
		regerror(iRet, &reg, ebuf, sizeof(ebuf)-1);
		strErrmsg = ebuf ;
		regfree(&reg);
		return 2 ;
	}

	iRet = regexec(&reg, strSrc.c_str(), nmatch, regmatch, 0) ;
	if(iRet == 0)
	{
		iSuccess = 0 ;
	}
	else if(iRet == REG_NOMATCH)
	{
		iSuccess = 1 ;
	}
	else
	{
		regerror(iRet, &reg, ebuf, sizeof(ebuf)-1);
		strErrmsg = ebuf ;
		iSuccess = 2 ;
	}
	regfree(&reg);
	return iSuccess ;
}
