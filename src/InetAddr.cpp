#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "InetAddr.h"

void CInterAddr::InitAddr(uint32_t dwIpAddress, uint16_t wPort)
{
    m_dwIpAddress = dwIpAddress;
    m_wPort       = wPort;
    memset(this->m_sBuffer, 0, sizeof(m_sBuffer));

    struct in_addr in;
	in.s_addr = dwIpAddress;

	char IPdotdec[20]={0};
	const char *p = inet_ntop(AF_INET,(void *)&in,IPdotdec,16);
	if (p != NULL)
    {
        snprintf(m_sBuffer, sizeof(m_sBuffer), "%s", IPdotdec);
    }
}


CInterAddr::CInterAddr()
{
    InitAddr(0, 0);
}

CInterAddr::CInterAddr(uint32_t dwIpAddress, uint16_t wPort)
{
    InitAddr(dwIpAddress, wPort);
}

CInterAddr::CInterAddr(const std::string& strIpAddress, uint16_t wPort)
{
    uint32_t dwIpAddress = inet_addr(strIpAddress.c_str());
    InitAddr(dwIpAddress, wPort);
}

uint32_t CInterAddr::getAddress() const
{
    return this->m_dwIpAddress;
}

const char *CInterAddr::getHost() const
{

    return m_sBuffer;
}

uint16_t CInterAddr::getPort() const
{
    return m_wPort;
}

CInterAddr::CInterAddr(const CInterAddr &rhs)
{
    m_dwIpAddress = rhs.getAddress();
    m_wPort       = rhs.getPort();
    snprintf(m_sBuffer, sizeof(m_sBuffer), "%s", rhs.getHost());
}

CInterAddr CInterAddr::operator =(const CInterAddr &rhs)
{
    if (this != &rhs)
    {
        m_dwIpAddress = rhs.getAddress();
        m_wPort       = rhs.getPort();
        snprintf(m_sBuffer, sizeof(m_sBuffer), "%s", rhs.getHost());
        return *this;
    }
    return rhs;
}

