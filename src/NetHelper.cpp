#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stropts.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/tcp.h>

#include "NetHelper.h"

static char g_CharMap[][4]={
	"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16",
	"17","18","19","20","21","22","23","24","25","26","27","28","29","30","31",
	"32","33","34","35","36","37","38","39","40","41","42","43","44","45","46",
	"47","48","49","50","51","52","53","54","55","56","57","58","59","60","61",
	"62","63","64","65","66","67","68","69","70","71","72","73","74","75","76",
	"77","78","79","80","81","82","83","84","85","86","87","88","89","90","91",
	"92","93","94","95","96","97","98","99","100","101","102","103","104","105"
	,"106","107","108","109","110","111","112","113","114","115","116","117","118","119",
	"120","121","122","123","124","125","126","127","128","129","130","131","132","133",
	"134","135","136","137","138","139","140","141","142","143","144","145","146","147",
	"148","149","150","151","152","153","154","155","156","157","158","159","160","161",
	"162","163","164","165","166","167","168","169","170","171","172","173","174","175",
	"176","177","178","179","180","181","182","183","184","185","186","187","188","189",
	"190","191","192","193","194","195","196","197","198","199","200","201","202","203",
	"204","205","206","207","208","209","210","211","212","213","214","215","216","217",
	"218","219","220","221","222","223","224","225","226","227","228","229","230","231",
	"232","233","234","235","236","237","238","239","240","241","242","243","244","245",
	"246","247","248","249","250","251","252","253","254","255"
};

void NetHelper::HtoP(unsigned int unIP,char *pIP){
	NetHelper::INET_NTOA(htonl(unIP),pIP);
}

bool NetHelper::IsCPULittleEndian(){
	const int n = 1; 
	return *((char*)&n) ? true : false;
}

bool NetHelper::IsIpAddr(char* pHostStr){
	bool isIPAddr = true;
	int tmp1,tmp2,tmp3,tmp4,i;
	while(1){
		i = sscanf(pHostStr,"%d.%d.%d.%d",&tmp1,&tmp2,&tmp3,&tmp4);
		if( i != 4){
			isIPAddr = false;
			break;
		}
		if( (tmp1 > 255) || (tmp2 > 255) || (tmp3 > 255) || (tmp4 > 255)){
			isIPAddr = false;
			break;
		}
		for( const char *pChar = pHostStr; *pChar != '\0'; pChar++){
			if( (*pChar != '.') && ((*pChar < '0') || (*pChar > '9'))) {
				isIPAddr = false;
				break;
			}
		}
		break;
	}
	return isIPAddr;
}

u_int64_t NetHelper::NTOHL64(u_int64_t N){
	if(!NetHelper::IsCPULittleEndian())
		return N;
		
	u_int64_t	H = 0;
	u_int32_t iTmp = 0;
		
	iTmp = ntohl((u_int32_t)(N>>32));
	memcpy(&H,&iTmp,sizeof(u_int32_t));
		
	iTmp = ntohl((u_int32_t)(N));
	memcpy(((char*)&H)+sizeof(u_int32_t),&iTmp,sizeof(u_int32_t));
		
	return H;
}

u_int64_t NetHelper::HTONL64(u_int64_t H) {
	if(!NetHelper::IsCPULittleEndian())
		return H;
		
	u_int64_t	N = 0;
	u_int32_t iTmp = 0;
		
	iTmp = htonl((u_int32_t)(H>>32));
	memcpy(&N,&iTmp,sizeof(u_int32_t));
		
	iTmp = htonl((u_int32_t)(H));
	memcpy(((char*)&N)+sizeof(u_int32_t),&iTmp,sizeof(u_int32_t));
		
	return N;
}

void NetHelper::INET_NTOA(unsigned int unIP,char *pIP){
	strcpy((char*)(pIP),g_CharMap[*(unsigned char*)&(unIP)]);\
	strcat((char*)(pIP),".");\
	strcat((char*)(pIP),g_CharMap[*((unsigned char*)&(unIP)+1)]);\
	strcat((char*)(pIP),".");\
	strcat((char*)(pIP),g_CharMap[*((unsigned char*)&(unIP)+2)]);\
	strcat((char*)(pIP),".");	\
	strcat((char*)(pIP),g_CharMap[*((unsigned char*)&(unIP)+3)]);\
}

std::string NetHelper::GetLocalHostIp()
{
	int fd, intrface;
	long ip = -1;
	char szBuf[128] = {0};
	struct ifreq buf[16];
	struct ifconf ifc;

	if((fd=socket (AF_INET, SOCK_DGRAM, 0)) >= 0)
	{
		ifc.ifc_len = sizeof buf;
		ifc.ifc_buf = (caddr_t) buf;
		if (!ioctl(fd, SIOCGIFCONF, (char*)&ifc))
		{
			intrface = ifc.ifc_len / sizeof(struct ifreq);
			while(intrface-- > 0)
			{
				if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface])))
				{
					ip=inet_addr(inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr));
					break;
				}
			}
		}
		close (fd);
	}

	// 转换为点分十进制格式
	unsigned char* pIp = (unsigned char*)(&ip);
	snprintf(szBuf, sizeof(szBuf), "%u.%u.%u.%u", pIp[0], pIp[1], pIp[2], pIp[3]);

	return szBuf;
}

int32_t NetHelper::ParseUrl( const char* pszUrl,std::string& host,std::string& uri,int &servicePort,int& protocol )
{
	const char* start = NULL;
	const char* end = NULL;

	if (strncasecmp(pszUrl, "http://", 7) == 0)
	{
		protocol = 0;
		servicePort = 80;
		start = pszUrl + 7;
	}
	else if (strncasecmp(pszUrl, "https://", 8) == 0) 
	{
		protocol = 1;
		servicePort = 443;
		start = pszUrl + 8;
	}
	else 
	{
		protocol = 0;
		servicePort = 80;
		start = pszUrl;
	}

	end = strchr(start, '/');
	std::string strHost;

	if (end == NULL)
	{
		uri = "/";
		strHost = start;
	}
	else
	{
		uri = end;
		strHost = std::string(start, end - start);
	}
	size_t pos;
	if( (pos=strHost.find(":")) == std::string::npos )
	{
		host = strHost;
	}
	else
	{
		host = strHost.substr(0,pos);
		servicePort = atoi(strHost.substr(pos+1).c_str());
	}
	if (servicePort == 0)
	{
		return -1;
	}
	return 0;
}

int32_t NetHelper::Url2IP( const std::string &url,std::string& ip,std::string &errMsg )
{
	ip = "" ;
	struct hostent *hostinfo;
	if((hostinfo = gethostbyname(url.c_str())) == NULL)
	{
		errMsg = "Url2IP fail to convert url:" + url;
		return -1;
	}
	char IPstr[20]={0};
	if(inet_ntop(AF_INET,*hostinfo->h_addr_list,IPstr,sizeof(IPstr))==NULL)
	{
		errMsg = "Url2IP fail to convert url:" + url;
		return -1;
	}
	ip = IPstr ;

	return 0;
}

int32_t NetHelper::NetSetNonBlock( int32_t fd )
{
	int flags;
	
	/** fcntl(2) for F_GETFL and F_SETFL 不能被信号中断 **/
	if ((flags = fcntl(fd, F_GETFL)) == -1) {
		errmsg = "fcntl(F_GETFL):";
		errmsg.append( strerror(errno) );
		return -1;
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
		errmsg = "fcntl(F_SETFL):";
		errmsg.append( strerror(errno) );
		return -1;
	}
	return 0;
}

int32_t NetHelper::NetSetTcpNoDelay( int32_t fd, int32_t val )
{
	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val)) == -1)
	{
		errmsg = "setsockopt TCP_NODELAY: ";
		errmsg.append( strerror(errno) );
		return -1;
	}

	return 0;
}

int32_t NetHelper::NetSetSendBuffer( int32_t fd, int32_t buffsize )
{
	if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buffsize, sizeof(buffsize)) == -1)
	{
		errmsg = "setsockopt SO_SNDBUF: ";
		errmsg.append( strerror(errno) );
		return -1;
	}
	return 0;
}

int32_t NetHelper::NetSetTcpKeepAlive( int32_t fd )
{
	int yes = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(yes)) == -1) {
		errmsg = "setsockopt SO_KEEPALIVE: ";
		errmsg.append( strerror(errno) );
		return -1;
	}

	return 0;
}

int32_t NetHelper::NetPeerToString( int32_t fd, CInterAddr& netAddr )
{
	struct sockaddr_in sa;
	socklen_t salen = sizeof(sa);

	if (getpeername(fd,(struct sockaddr*)&sa,&salen) == -1) {
		netAddr = CInterAddr("?\0", 0);
		return -1;
	}
	netAddr = CInterAddr( inet_ntoa(sa.sin_addr), ntohs(sa.sin_port) );
	return 0;
}

int32_t NetHelper::NetGetSockName( int32_t fd, CInterAddr& netAddr )
{
	struct sockaddr_in sa;
	socklen_t salen = sizeof(sa);

	if (getsockname(fd,(struct sockaddr*)&sa,&salen) == -1) {
		netAddr = CInterAddr("?\0", 0);
		return -1;
	}
	netAddr = CInterAddr( inet_ntoa(sa.sin_addr), ntohs(sa.sin_port) );
	return 0;
}
