/**********************************
 * File: ByteStream.h
 * Author: ponlee
 * Version: 1.0
 * Date: 2015-12
 * Desc: 二进制buff序列化接口
***********************************/

#ifndef BYTE_STREAM_H
#define BYTE_STREAM_H

#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <bitset>

static const uint32_t MAX_STD_CONTAINER_LEN = 3 * 1024 * 1024;

template <class ConvertorType>
class CByteStreamT
{
public:
    CByteStreamT(char* pStreamBuf = NULL, uint32_t nBufLen = 0, bool bRealWrite = true);
    char* resetStreamBuf(char* pStreamBuf, uint32_t nBufLen, bool bRealWrite = true);

    // bStore - true  (Serialize) , Default
    //        - false (Unserialize)
    void isStoring(bool bStore);
    bool isStoring() const;

	void setVersion(uint16_t wVersion);
	uint16_t getVersion() const;
    
    /////////////////////// Write ////////////////////////
    CByteStreamT<ConvertorType>& operator << (int8_t c);
    CByteStreamT<ConvertorType>& operator << (uint8_t c);
    CByteStreamT<ConvertorType>& operator << (int16_t n);
    CByteStreamT<ConvertorType>& operator << (uint16_t n);
    CByteStreamT<ConvertorType>& operator << (int32_t n);
    CByteStreamT<ConvertorType>& operator << (uint32_t n);
    CByteStreamT<ConvertorType>& operator << (std::string& str);
    CByteStreamT<ConvertorType>& operator << (uint64_t n);
	CByteStreamT<ConvertorType>& operator << (int64_t n);
    CByteStreamT<ConvertorType>& operator << (bool b);
	template<size_t SIZE>
    CByteStreamT<ConvertorType>& operator << (std::bitset<SIZE>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator << (std::vector<DATA>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator << (std::list<DATA>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator << (std::set<DATA>& v);
    template<class DATA1, class DATA2>
    CByteStreamT<ConvertorType>& operator << (std::map<DATA1, DATA2>& v);
    template<class DATA1, class DATA2>
    CByteStreamT<ConvertorType>& operator << (std::multimap<DATA1, DATA2>& v);    
    template<class DATA>
    CByteStreamT<ConvertorType>& operator << (DATA& v);
    
    /////////////////////// Read ////////////////////////
    CByteStreamT<ConvertorType>& operator >> (int8_t& c);
    CByteStreamT<ConvertorType>& operator >> (uint8_t& c);
    CByteStreamT<ConvertorType>& operator >> (int16_t& n);
    CByteStreamT<ConvertorType>& operator >> (uint16_t& n);
    CByteStreamT<ConvertorType>& operator >> (int32_t& n);
    CByteStreamT<ConvertorType>& operator >> (uint32_t& n);
    CByteStreamT<ConvertorType>& operator >> (std::string& str);
    CByteStreamT<ConvertorType>& operator >> (uint64_t& n);
	CByteStreamT<ConvertorType>& operator >> (int64_t& n);
    CByteStreamT<ConvertorType>& operator >> (bool& b);
	template<size_t SIZE>
    CByteStreamT<ConvertorType>& operator >> (std::bitset<SIZE>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator >> (std::vector<DATA>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator >> (std::list<DATA>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator >> (std::set<DATA>& v);
    template<class DATA1, class DATA2>
    CByteStreamT<ConvertorType>& operator >> (std::map<DATA1, DATA2>& v);
    template<class DATA1, class DATA2>
    CByteStreamT<ConvertorType>& operator >> (std::multimap<DATA1, DATA2>& v);    
    template<class DATA>
    CByteStreamT<ConvertorType>& operator >> (DATA& v);
	CByteStreamT<ConvertorType>& mmap (void** pStr, uint32_t n);
    /////////////////////// Read or Write ////////////////////////
    CByteStreamT<ConvertorType>& operator & (int8_t& c);
    CByteStreamT<ConvertorType>& operator & (uint8_t& c);
    CByteStreamT<ConvertorType>& operator & (int16_t& n);
    CByteStreamT<ConvertorType>& operator & (uint16_t& n);
    CByteStreamT<ConvertorType>& operator & (int32_t& n);
    CByteStreamT<ConvertorType>& operator & (uint32_t& n);
    CByteStreamT<ConvertorType>& operator & (std::string& str);
    CByteStreamT<ConvertorType>& operator & (uint64_t& n);
	CByteStreamT<ConvertorType>& operator & (int64_t& n);
    CByteStreamT<ConvertorType>& operator & (bool& b);
	template<size_t SIZE>
    CByteStreamT<ConvertorType>& operator & (std::bitset<SIZE>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator & (std::vector<DATA>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator & (std::list<DATA>& v);
    template<class DATA>
    CByteStreamT<ConvertorType>& operator & (std::set<DATA>& v);
    template<class DATA1, class DATA2>
    CByteStreamT<ConvertorType>& operator & (std::map<DATA1, DATA2>& v);
    template<class DATA1, class DATA2>
    CByteStreamT<ConvertorType>& operator & (std::multimap<DATA1, DATA2>& v);    
    template<class DATA>
    CByteStreamT<ConvertorType>& operator & (DATA& v);
    
    ///////////////// Read & Write directly /////////////////
    CByteStreamT<ConvertorType>& Read(void *pvDst, uint32_t nLen);
    CByteStreamT<ConvertorType>& Write(const void *pvSrc, uint32_t nLen);
    
    //////////////////////// Utils //////////////////////
    /*
    *	Check this after one read or write
    */
    bool isGood();
    
    /*
    *	Get valid length after written
    */
    uint32_t getWrittenLength();

    /*
    *	Get valid length after read
    */
    uint32_t getReadLength();

	/*
    *	Get remain length to read
    */
	uint32_t getRemainLength2Read();

	/*
    *	Get remain length to write
    */
	uint32_t getRemainLength2Write();

	/*
    *	Get raw buf start point
    */
	char* getRawBufStart();

	/*
    *	Get raw buf curr point
    */
	char* getRawBufCur();

	/*
	 *  Get & Copy RemainData to User Buffer
	 *  dwLen[INOUT] : [IN] indicate max length of pszbuff
	 *                 [OUT] value of length of remain data
	 */
	bool GetRemainData(char *pszbuff, uint32_t &dwLen);

	/*
	 *  Read or Write point go forward
	 */
	void goForward(uint32_t dwOffset);

	/*
	 *  Read or Write point go backward
	 */
	void goBackward(uint32_t dwOffset);

protected:
    
    void assignStdString(std::string& str, uint32_t nLen);
    
private:
    bool m_bReadGood;
    bool m_bWriteGood;
    
    char* m_pStreamBuf;
    uint32_t m_nBufLen;
    uint32_t m_nReadBufLenLeft;
    uint32_t m_nWriteBufLenLeft;

    static const uint32_t UINT64_HEX_BUF_LEN = 16 + 1;
    char m_sllBuffer[UINT64_HEX_BUF_LEN];

    bool m_bStore;
    bool m_bRealWrite;  // false for calculate written length

	uint16_t m_wVersion;

    char* m_pBufStart;
};

struct CHostNetworkConvertorNormal
{
    static void Host2Network(uint32_t &dwVal)
    {
        dwVal = htonl(dwVal);
    }
    
    static void Host2Network(uint16_t &wVal)
    {
        wVal = htons(wVal);
    }
    static void Network2Host(uint32_t &dwVal)
    {
        dwVal = ntohl(dwVal);
    }
    static void Network2Host(uint16_t &wVal)
    {
        wVal = ntohs(wVal);
    }
};

struct CHostNetworkConvertorNull
{
    static void Host2Network(uint32_t &dwVal) {};
    static void Host2Network(uint16_t &wVal) {};
    static void Network2Host(uint32_t &dwVal) {};
    static void Network2Host(uint16_t &wVal) {};
};

///////////////////////////////////////////////////////
template <class ConvertorType>
inline CByteStreamT<ConvertorType>::CByteStreamT(
                                                 char* pStreamBuf, 
                                                 uint32_t nBufLen,
                                                 bool bRealWrite)
                                                 : m_bReadGood(true)
                                                 , m_bWriteGood(true)
                                                 , m_pStreamBuf(pStreamBuf)
                                                 , m_nBufLen(nBufLen)
                                                 , m_nReadBufLenLeft(nBufLen)
                                                 , m_nWriteBufLenLeft(nBufLen)
                                                 , m_bStore(true)
                                                 , m_bRealWrite(bRealWrite)
												 , m_wVersion(0)
												 , m_pBufStart(pStreamBuf)
{
}

template <class ConvertorType>
inline 
char* CByteStreamT<ConvertorType>::resetStreamBuf(
                                                  char* pStreamBuf, 
                                                  uint32_t nBufLen,
                                                  bool bRealWrite)
{
    char* l_pStreamBuf = m_pStreamBuf;
    m_pStreamBuf = pStreamBuf;
	m_pBufStart = pStreamBuf;
    m_bReadGood = true;
    m_bWriteGood = true;
    m_nBufLen = nBufLen;
    m_nReadBufLenLeft = nBufLen;
    m_nWriteBufLenLeft = nBufLen;
    m_bRealWrite = bRealWrite;
    
    return l_pStreamBuf;
}

template <class ConvertorType>
inline 
void CByteStreamT<ConvertorType>::isStoring(bool bStore)
{
    m_bStore = bStore;
}

template <class ConvertorType>
inline 
bool CByteStreamT<ConvertorType>::isStoring() const
{
    return m_bStore;
}

template <class ConvertorType>
inline 
void CByteStreamT<ConvertorType>::setVersion(uint16_t wVersion)
{
    m_wVersion = wVersion;
}

template <class ConvertorType>
inline 
uint16_t CByteStreamT<ConvertorType>::getVersion() const
{
    return m_wVersion;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(int8_t c)
{
    Write(&c, sizeof(int8_t));
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(uint8_t c)
{
    Write(&c, sizeof(uint8_t));
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(bool b)
{
	uint8_t c = (b ? 1 : 0);
    Write(&c, sizeof(uint8_t));
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(int16_t n)
{
    return *this << (uint16_t)n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(uint16_t n)
{
    ConvertorType::Host2Network(n);
    Write(&n, sizeof(uint16_t));
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(int32_t n)
{
    return *this << (uint32_t)n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(uint32_t n)
{
    ConvertorType::Host2Network(n);
    Write(&n, sizeof(uint32_t));
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(std::string& str)
{
    uint32_t nLen = str.length();
    (*this) << nLen;
    
    if(nLen > 0)
    {
        Write(reinterpret_cast<const void*>(str.c_str()), nLen);
    }
    
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(uint64_t n)
{
    memset(m_sllBuffer, 0, sizeof(m_sllBuffer));
#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64)	
    snprintf(m_sllBuffer, UINT64_HEX_BUF_LEN, "%016lx", n);
#else	
    snprintf(m_sllBuffer, UINT64_HEX_BUF_LEN, "%016llx", n);
#endif
    Write(m_sllBuffer, UINT64_HEX_BUF_LEN);

    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(int64_t n)
{
    memset(m_sllBuffer, 0, sizeof(m_sllBuffer));
#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64)	
    snprintf(m_sllBuffer, UINT64_HEX_BUF_LEN, "%016lx", static_cast<uint64_t>(n));
#else	
    snprintf(m_sllBuffer, UINT64_HEX_BUF_LEN, "%016llx", static_cast<uint64_t>(n));
#endif
    Write(m_sllBuffer, UINT64_HEX_BUF_LEN);

    return *this;
}

template <class ConvertorType>
template<size_t SIZE>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(std::bitset<SIZE>& v)
{
	//SIZE必须大于等于0
	uint32_t dwSize = (SIZE==v.size()?SIZE:0);
    (*this) << dwSize;
	for(uint32_t i =0; i< dwSize; i++)
	{
        if(!m_bWriteGood) 
        {
            return *this;
        }
		uint8_t c = (v[i] ? 1 : 0);
		Write(&c, sizeof(uint8_t));
	}
    return *this;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(std::vector<DATA>& v)
{
	uint32_t sz = v.size();
	(*this) << sz;
	for (uint32_t i = 0; i < sz; ++i)
	{
        if(!m_bWriteGood) 
        {
            return *this;
        }
		(*this) << v[i];
	}
	return *this;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(std::list<DATA>& v)
{
	uint32_t sz = v.size();
	(*this) << sz;
	typename std::list<DATA>::iterator it = v.begin();
	for (; it != v.end(); ++it)
	{
        if(!m_bWriteGood) 
        {
            return *this;
        }
		(*this) << (*it);
	}
	return *this;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(std::set<DATA>& v)
{
	uint32_t sz = v.size();
	(*this) << sz;
	typename std::set<DATA>::const_iterator it;
	for (it = v.begin(); it != v.end() ; ++it)
    {
        if(!m_bWriteGood) 
        {
            return *this;
        }
		DATA& val = (*const_cast<DATA*>(&(*it)));
		(*this) << val;
	}
	return *this;
}

template <class ConvertorType>
template <class DATA1, class DATA2>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(std::map<DATA1, DATA2>& v)
{
	uint32_t sz = v.size();
	(*this) << sz;
	typename std::map<DATA1, DATA2>::const_iterator it;
	for (it = v.begin(); it != v.end() ; ++it)
	{
        if(!m_bWriteGood) 
        {
            return *this;
        }
		DATA1& key = (*const_cast<DATA1*>(&(*it).first));
		DATA2& val = (*const_cast<DATA2*>(&(*it).second));
		(*this) << key;
		(*this) << val;
	}	
	return *this;
}


template <class ConvertorType>
template <class DATA1, class DATA2>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(std::multimap<DATA1, DATA2>& v)
{
	uint32_t sz = v.size();
	(*this) << sz;
	typename std::multimap<DATA1, DATA2>::const_iterator it;
	for (it = v.begin(); it != v.end() ; ++it)
	{
        if(!m_bWriteGood) 
        {
            return *this;
        }
		DATA1& key = (*const_cast<DATA1*>(&(*it).first));
		DATA2& val = (*const_cast<DATA2*>(&(*it).second));
		(*this) << key;
		(*this) << val;
	}	
	return *this;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator<<(DATA& v)
{
	v.Serialize(*this);
	return *this;
}
////////////////////////////////////////////////////////////////
template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(int8_t& c)
{
    Read(&c, sizeof(int8_t));
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(uint8_t& c)
{
    Read(&c, sizeof(uint8_t));
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(bool& b)
{
	uint8_t c = 0;
    Read(&c, sizeof(uint8_t));
	b = ((c != 0) ? true : false);
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(int16_t& n)
{
    return *this >> (uint16_t&)n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(uint16_t& n)
{
    Read(&n, sizeof(uint16_t));
    ConvertorType::Network2Host(n);
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(int32_t& n)
{
    return *this >> (uint32_t&)n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(uint32_t& n)
{
    Read(&n, sizeof(uint32_t));
    ConvertorType::Network2Host(n);
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(std::string& str)
{
	//str.resize(0);
    uint32_t nLen = 0;
    (*this) >> nLen;

	if(0 == nLen && !str.empty())
		str = "";
    
    if (nLen > 0) 
    {
        assignStdString(str, nLen);
    }
    return *this;
}

//add by wendyhu 2010-12-22 
template <class ConvertorType>
template<size_t SIZE>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(std::bitset<SIZE>& v)
{
    uint32_t nLen = 0;;
    (*this) >> nLen;
	
	for(uint32_t i= 0; i < nLen; i++)
	{
        if(!m_bReadGood)
        {
            return *this;
        }
		uint8_t c = 0;
		Read(&c, sizeof(uint8_t));
		if( i<SIZE && c)
		{	
			v.set( i );
		}
   }
   
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(uint64_t& n)
{
    memset(m_sllBuffer, 0, sizeof(m_sllBuffer));
    Read(m_sllBuffer, UINT64_HEX_BUF_LEN);
#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64)	
    sscanf(m_sllBuffer, "%016lx", &n);
#else
    sscanf(m_sllBuffer, "%016llx", &n);
#endif	
	return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(int64_t& n)
{
    memset(m_sllBuffer, 0, sizeof(m_sllBuffer));
    Read(m_sllBuffer, UINT64_HEX_BUF_LEN);
	uint64_t m = 0;
#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64)	
    sscanf(m_sllBuffer, "%016lx", &m);
#else
    sscanf(m_sllBuffer, "%016llx", &m);
#endif	

	n = static_cast<int64_t>(m);
	return *this;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(std::vector<DATA>& v)
{
	uint32_t sz = 0;
	(*this) >> sz;
    if(sz >= MAX_STD_CONTAINER_LEN)
        v.resize(MAX_STD_CONTAINER_LEN);
    else
    	v.resize(sz);	
	if(0 == sz)
		return *this;
	for (uint32_t i = 0; i < sz; ++i)
	{
        if(!m_bReadGood)
        {
            return *this;
        }
		(*this) >> v[i];
	}
	return *this;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(std::list<DATA>& v)
{
	uint32_t sz = 0;
	(*this) >> sz;
	if(0 == sz)
		return *this;
	for (uint32_t i = 0; i < sz; ++i)
	{
        if(!m_bReadGood)
        {
            return *this;
        }
        DATA data;
		(*this) >> data;
		v.push_back(data);
	}
	return *this;
}


template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(std::set<DATA>& v)
{
	uint32_t sz = 0;
	(*this) >> sz;
	if(0 == sz)
		return *this;

	for (uint32_t i = 0; i < sz; ++i)
	{
        if(!m_bReadGood)
        {
            return *this;
        }
		DATA val;
		(*this) >> val;
		v.insert(val);
	}
	return *this;
}

template <class ConvertorType>
template <class DATA1, class DATA2>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(std::map<DATA1, DATA2>& v)
{
	uint32_t sz = 0;
	(*this) >> sz;
	if(0 == sz)
		return *this;

	for(uint32_t i = 0; i < sz; ++i)	
	{
        if(!m_bReadGood)
        {
            return *this;
        }
		DATA1 key;
		DATA2 val;
		(*this) >> key;
		(*this) >> val;
		v[key] = val;
	}

	return *this;
}


template <class ConvertorType>
template <class DATA1, class DATA2>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(std::multimap<DATA1, DATA2>& v)
{
	uint32_t sz = 0;
	(*this) >> sz;
	if(0 == sz)
		return *this;

	for(uint32_t i = 0; i < sz; ++i)	
	{
        if(!m_bReadGood)
        {
            return *this;
        }
		DATA1 key;
		DATA2 val;
		(*this) >> key;
		(*this) >> val;
        v.insert(std::pair<DATA1,DATA2>(key,val));
	}

	return *this;
}


template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator>>(DATA& v)
{
	v.Serialize(*this);
	return *this;
}

template <class ConvertorType>
inline
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::mmap(void** pAddr, uint32_t nLen)
{
    if (m_bReadGood)
    {
        if(nLen > m_nReadBufLenLeft)
        {
            m_bReadGood = false;
            return *this;
        }
        (*pAddr)=m_pStreamBuf;
        m_nReadBufLenLeft -= nLen;
        m_pStreamBuf += nLen;
    }
    return *this;
}


template <class ConvertorType>
inline 
bool CByteStreamT<ConvertorType>::isGood()
{
    if (m_bWriteGood && m_bReadGood)
        return true;
    else
        return false;
}

template <class ConvertorType>
inline 
uint32_t CByteStreamT<ConvertorType>::getWrittenLength()
{
    return m_nBufLen - m_nWriteBufLenLeft;
}

template <class ConvertorType>
inline 
uint32_t CByteStreamT<ConvertorType>::getReadLength()
{
    return m_nBufLen - m_nReadBufLenLeft;
}

template <class ConvertorType>
inline
uint32_t CByteStreamT<ConvertorType>::getRemainLength2Read()
{
    return m_nReadBufLenLeft;
}

template <class ConvertorType>
inline
uint32_t CByteStreamT<ConvertorType>::getRemainLength2Write()
{
    return m_nWriteBufLenLeft;
}

template <class ConvertorType>
inline
char* CByteStreamT<ConvertorType>::getRawBufStart()
{
    return m_pBufStart;
}

template <class ConvertorType>
inline
char* CByteStreamT<ConvertorType>::getRawBufCur()
{
	if(m_bStore)
		return (m_pBufStart + (m_nBufLen - m_nWriteBufLenLeft));

	return (m_pBufStart + (m_nBufLen - m_nReadBufLenLeft));
}

template <class ConvertorType>
inline 
bool CByteStreamT<ConvertorType>::GetRemainData(char *pszbuff, uint32_t &dwLen)
{
	if (dwLen < m_nReadBufLenLeft)
	{
		dwLen = 0;
		return false;
	}

	memcpy(pszbuff, m_pStreamBuf, m_nReadBufLenLeft);
	dwLen = m_nReadBufLenLeft;
	m_nReadBufLenLeft = 0;
	m_pStreamBuf += m_nReadBufLenLeft;

	return true;
}

template <class ConvertorType>
inline 
void CByteStreamT<ConvertorType>::goForward(uint32_t dwOffset)
{
	if(m_bStore)
    {
        if(dwOffset > m_nWriteBufLenLeft)
        {
            m_bWriteGood = false;
            //return *this;
        }
        
        m_nWriteBufLenLeft -= dwOffset;
        m_pStreamBuf += dwOffset;
	}
	else
	{
        if(dwOffset > m_nReadBufLenLeft)
        {
            m_bReadGood = false;
            //return *this;
        }
        
        m_nReadBufLenLeft -= dwOffset;
        m_pStreamBuf += dwOffset;
    }
    //return *this;
}

template <class ConvertorType>
inline 
void CByteStreamT<ConvertorType>::goBackward(uint32_t dwOffset)
{
	if(m_bStore)
    {
        if(dwOffset > (m_nBufLen - m_nWriteBufLenLeft))
        {
            m_bWriteGood = false;
            //return *this;
        }
        
        m_nWriteBufLenLeft += dwOffset;
        m_pStreamBuf -= dwOffset;
	}
	else
	{
        if(dwOffset > (m_nBufLen - m_nReadBufLenLeft))
        {
            m_bReadGood = false;
            //return *this;
        }
        
        m_nReadBufLenLeft += dwOffset;
        m_pStreamBuf -= dwOffset;
    }
    //return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::Read(void *pvDst, uint32_t nLen)
{
    if (m_bReadGood) 
    {
        if(nLen > m_nReadBufLenLeft)
        {
            m_bReadGood = false;
            return *this;
        }
        
        memcpy(pvDst, m_pStreamBuf, nLen);
        m_nReadBufLenLeft -= nLen;
        m_pStreamBuf += nLen;
    }
    return *this;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::Write(const void *pvSrc, uint32_t nLen)
{
    if(!m_bRealWrite)
    {
        m_nWriteBufLenLeft -= nLen;
        return *this;
    }

    if(m_bWriteGood) 
    {
        if(nLen > m_nWriteBufLenLeft)
        {
            m_bWriteGood = false;
            return *this;
        }
        
        memcpy(m_pStreamBuf, pvSrc, nLen);
        m_nWriteBufLenLeft -= nLen;
        m_pStreamBuf += nLen;
    }
    return *this;
}

template <class ConvertorType>
inline 
void CByteStreamT<ConvertorType>::assignStdString(std::string& str, uint32_t nLen)
{
    if (m_bReadGood) 
    {
        if(nLen > m_nReadBufLenLeft)
        {
            m_bReadGood = false;
            return;
        }
        
        //str.resize(0);
        //str.resize(nLen);
        str.assign(m_pStreamBuf, nLen);
        
        m_nReadBufLenLeft -= nLen;
        m_pStreamBuf += nLen;
    }
}


/////////////////////// Read or Write ////////////////////////
template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (int8_t& c)
{
    if(m_bStore)
        return *this << c;

    return *this >> c;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (uint8_t& c)
{
    if(m_bStore)
        return *this << c;

    return *this >> c;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (bool& b)
{
    if(m_bStore)
        return *this << b;

    return *this >> b;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::operator & (int16_t& n)
{
    if(m_bStore)
        return *this << n;

    return *this >> n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::operator & (uint16_t& n)
{
    if(m_bStore)
        return *this << n;

    return *this >> n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::operator & (int32_t& n)
{
    if(m_bStore)
        return *this << n;

    return *this >> n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::operator & (uint32_t& n)
{
    if(m_bStore)
        return *this << n;

    return *this >> n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::operator & (std::string& str)
{
    if(m_bStore)
        return *this << str;

    return *this >> str;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::operator & (uint64_t& n)
{
    if(m_bStore)
        return *this << n;

    return *this >> n;
}

template <class ConvertorType>
inline 
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::operator & (int64_t& n)
{
    if(m_bStore)
        return *this << n;

    return *this >> n;
}

template <class ConvertorType>
template<size_t SIZE>
inline
CByteStreamT<ConvertorType>&
CByteStreamT<ConvertorType>::operator & (std::bitset<SIZE>& v)
{
	if(m_bStore)
		return *this << v;

    return *this >> v;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (std::vector<DATA>& v)
{
    if(m_bStore)
        return *this << v;

    return *this >> v;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (std::list<DATA>& v)
{
    if(m_bStore)
        return *this << v;

    return *this >> v;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (std::set<DATA>& v)
{
    if(m_bStore)
        return *this << v;

    return *this >> v;
}

template <class ConvertorType>
template <class DATA1, class DATA2>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (std::map<DATA1, DATA2>& v)
{
    if(m_bStore)
        return *this << v;

    return *this >> v;
}


template <class ConvertorType>
template <class DATA1, class DATA2>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (std::multimap<DATA1, DATA2>& v)
{
    if(m_bStore)
        return *this << v;

    return *this >> v;
}

template <class ConvertorType>
template <class DATA>
inline
CByteStreamT<ConvertorType>& 
CByteStreamT<ConvertorType>::operator & (DATA& v)
{
    if(m_bStore)
        return *this << v;

    return *this >> v;
}
/////////////////////// Type Definition ////////////////////////
typedef CByteStreamT<CHostNetworkConvertorNormal> CByteStreamNetwork;
typedef CByteStreamT<CHostNetworkConvertorNull> CByteStreamMemory;

#endif /* BYTE_STREAM_H */

