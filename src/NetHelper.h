/**********************************
 * File: NetHelper.h
 * Author:ponlee
 * Version:1.0
 * Desc:基本网络操作的封装类
***********************************/

#ifndef _NET_BASE_HPP_
#define _NET_BASE_HPP_

#include <string>
#include <cstdio>

#include "InetAddr.h"

class NetHelper
{
public:
	NetHelper(){};
	~NetHelper(){};

public:
	/**
		* FUNC: 二进制IP转化为点分十进制IP格式
	**/
	static void HtoP (unsigned int unIP,char *pIP);
	/**
		* FUNC: 大小端判断
	**/
	static bool IsCPULittleEndian();
	/**
		* FUNC: 判断是否为正确的IP地址
	**/
	static bool IsIpAddr(char* pHostStr);
	/**
		* FUNC: 网络2主机字节序(64位),32位使用htonl
	**/
	static u_int64_t NTOHL64(u_int64_t N);
	/**
		* FUNC: 主机2网络字节序(64位)，32位使用ntohl
	**/
	static u_int64_t HTONL64(u_int64_t H);
	/**
		* FUNC: 得到本地主机IP地址
	**/
	static std::string GetLocalHostIp();
	/**
		* FUNC: Http Url 分割接口
	**/
	static int32_t ParseUrl( const char* pszUrl, std::string& host, std::string& uri, int &servicePort, int& protocol);

	/**
		* FUNC: Url 到 Ip 转化接口
	**/
	static int32_t Url2IP( const std::string &url, std::string& ip, std::string &errMsg );

	/***************************************************
	** @DESC 设置套接字为非阻塞
	** @RESULT
	**		-1->设置失败， 0->成功
	****************************************************/
	static int32_t NetSetNonBlock( int32_t fd );
	
	/***************************************************
	** @DESC 设置套接字fd是否取消 nagle
	** @PARAM	
	**		fd => 套接字fd； 
	**		val => 是否设置TcpNoDelay， 1 表示设置， 0 表示不设置
	** @RESULT
	**		-1->设置失败， 0->成功
	****************************************************/
	static int32_t NetSetTcpNoDelay( int32_t fd, int32_t val );

	/***************************************************
	** @DESC 设置套接字的发送buff
	** @RESULT
	**		-1->设置失败， 0->成功
	****************************************************/
	static int32_t NetSetSendBuffer( int32_t fd, int32_t buffsize );

	/***************************************************
	** @DESC 设置TCP的 KeepAlive
	** @RESULT
	**		-1->设置失败， 0->成功
	****************************************************/
	static int32_t NetSetTcpKeepAlive( int32_t fd );

	/***************************************************
	** @DESC 获取与套接字fd 相连的对端地址ip:port对
	** @RESULT
	**		-1->设置失败， 0->成功
	****************************************************/
	static int32_t NetPeerToString( int32_t fd, CInterAddr& netAddr );

	/***************************************************
	** @DESC 获取与套接字 fd  相连的本地地址ip:port对
	** @RESULT
	**		-1->设置失败， 0->成功
	****************************************************/
	static int32_t NetGetSockName( int32_t fd, CInterAddr& netAddr );

	static std::string&	GetErrMsg(){ return errmsg; }

private:
	static void INET_NTOA(unsigned int unIP,char *pIP);	

private:
	static std::string	errmsg;
};

#endif
