/**********************************
 * File: InetAddr.h
 * Author: ponlee
 * Version: 1.0
 * Date:  2015-08
 * Desc: ÍøÂçµØÖ·ip:port·â×°Àà
***********************************/

#ifndef _INET_ADDR_H
#define _INET_ADDR_H

#include <string>
#include <stdint.h>

class CInterAddr
{
public:
    CInterAddr();
    CInterAddr(uint32_t dwIpAddress, uint16_t wPort);
    CInterAddr(const std::string& strIpAddress, uint16_t wPort);
	CInterAddr(const CInterAddr &);
	CInterAddr operator =(const CInterAddr&);

    void InitAddr(uint32_t dwIpAddress, uint16_t wPort);
    uint32_t getAddress() const;
    const char *getHost() const;
    uint16_t getPort() const;
    
	bool operator ==(const CInterAddr& right) const
    {
	return (*this).getAddress() == right.getAddress() &&
	    (*this).getPort() == right.getPort();
    }

private:
    char m_sBuffer[20];
    uint32_t m_dwIpAddress;
    uint16_t m_wPort;
};


#endif

