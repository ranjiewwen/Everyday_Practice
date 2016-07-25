
#include "Cping.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#define ICMP_ECHO 8  // 定义回显报文代码
#define ICMP_ECHOREPLY 0
#define ICMP_MIN 8  // 最小8字节ICMP包
#define MAX_ICMP_PACKET 1024 // 最大ICMP大小


#pragma pack(4)
// IP头首部结构
struct IpHeader
{
	unsigned int h_len : 4;   // 首部长度
	unsigned int version : 4;   // IP版本
	unsigned char tos;    // 服务类型
	unsigned short total_len;  // 包总长度
	unsigned short ident;   // 标识符
	unsigned short frag_and_flags; // 标志
	unsigned char ttl;    // 生存周期
	unsigned char proto;   // protocol (TCP, UDP etc) 协议类型
	unsigned short checksum;  // IP检验和
	unsigned int sourceIP;   // 源地址IP
	unsigned int destIP;   // 目的地址IP
};
// ICMP 首部结构
struct IcmpHeader
{
	BYTE i_type; // 类型
	BYTE i_code; // 代码类型
	USHORT i_cksum; // 检验和
	USHORT i_id; // 地址
	USHORT i_seq; // 发送顺序
	// 增加一个时间戳
	ULONG timestamp;
};
CPing::CPing(void)
{
	m_socketRaw = INVALID_SOCKET;
	m_bPrintInfo = false;
	Init();
}

CPing::~CPing(void)
{
	FInit();
}
bool CPing::Init()
{
	WSADATA wsaData = { 0 };
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0)
		return false;
	//创建发送套接字
	// 注：为了使用发送接收超时设置(即设置SO_RCVTIMEO, SO_SNDTIMEO)，
	// 必须将标志位设为WSA_FLAG_OVERLAPPED !
	m_socketRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_socketRaw == INVALID_SOCKET)
		return false;

	// 设置一个有接收时限的套接字
	int nTimeout = 1000;
	int nResult = setsockopt(m_socketRaw, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeout, sizeof(nTimeout));
	if (nResult == SOCKET_ERROR)
		return false;
	//设置一个有发送时限的套接字
	nTimeout = 1000;
	nResult = setsockopt(m_socketRaw, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeout, sizeof(nTimeout));
	if (nResult == SOCKET_ERROR)
		return false;

	return true;
}
bool CPing::FInit()
{
	WSACleanup();
	return true;
}
bool CPing::PingHelper(const char* pDscAddr, int nPackNum, int nDataSize)
{
	if (pDscAddr == NULL || nPackNum <= 0)
		return false;

	// 进行域名解析
	sockaddr_in addrDsc = { 0 };
	hostent* pHostent = gethostbyaddr(pDscAddr, strlen(pDscAddr), AF_INET);
	if (pHostent != NULL)
	{
		addrDsc.sin_family = AF_INET;
		addrDsc.sin_addr.S_un.S_addr = inet_addr(pDscAddr);
	}
	else
	{
		pHostent = gethostbyname(pDscAddr);
		if (pHostent == NULL)
			return false;
		addrDsc.sin_family = pHostent->h_addrtype;
		memcpy(&(addrDsc.sin_addr), pHostent->h_addr, pHostent->h_length);
	}
	if (m_bPrintInfo)
	{
		std::cout << "Pinging " << inet_ntoa(addrDsc.sin_addr);
		std::cout << " with " << nDataSize << " bytes of data:" << std::endl << std::endl;
	}

	char szIcmpData[MAX_ICMP_PACKET] = { 0 };
	char szRecvBuff[MAX_ICMP_PACKET] = { 0 };
	ConstructIcmpMessage(szIcmpData, nDataSize);
	IcmpHeader* pIcmpHeader = reinterpret_cast<IcmpHeader*>(szIcmpData);
	int nPackSize = nDataSize + sizeof(IcmpHeader);
	int nSeqNO = 0;
	int nRet = 0;
	sockaddr_in addrSrc = { 0 };
	int nRecvPacket = 0;
	for (int i = 0; i < nPackNum; ++i)
	{
		pIcmpHeader->i_cksum = 0; // 先把ICMP的检验和置零
		pIcmpHeader->i_seq = nSeqNO++; // 发送顺序加一
		pIcmpHeader->timestamp = GetTickCount(); // 记录时间
		pIcmpHeader->i_cksum = CheckSum((USHORT*)szIcmpData, nPackSize);// 计算检验和
		nRet = sendto(m_socketRaw, szIcmpData, nPackSize, 0, (sockaddr*)&addrDsc, sizeof(addrDsc));
		if (nRet == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT) // 发送超时
			{
				if (m_bPrintInfo)
				{
					std::cout << "Request timed out." << std::endl;
				}
				continue;
			}
			return false;
		}
		int nSrcLen = sizeof(addrSrc);
		nRet = recvfrom(m_socketRaw, szRecvBuff, sizeof(szRecvBuff), 0, (sockaddr*)&addrSrc, &nSrcLen);
		if (nRet == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT) // 接收超时
			{
				if (m_bPrintInfo)
				{
					std::cout << "Request timed out." << std::endl;
				}
				continue;
			}
			return false;
		}
		if (DecodeIpPacket(szRecvBuff, nRet, &addrSrc))
			++nRecvPacket;
		if (m_bPrintInfo)
			Sleep(1000);
	}
	if (m_bPrintInfo)
	{
		std::cout << std::endl << "Packets: Sent = " << nPackNum;
		std::cout << ", Received = " << nRecvPacket;
		std::cout << ", Lost = " << nPackNum - nRecvPacket;
		std::cout << " (" << (nPackNum - nRecvPacket) * 100 / nPackNum;
		std::cout << "% loss)" << std::endl;
	}

	return nRecvPacket > 0;
}
bool CPing::ConstructIcmpMessage(char* pDataBuff, int nDataSize)
{
	if (pDataBuff == NULL)
		return false;
	IcmpHeader* pIcmpHeader = (IcmpHeader*)pDataBuff;
	pIcmpHeader->i_type = ICMP_ECHO;     // 设置回显报文
	pIcmpHeader->i_code = 0;
	pIcmpHeader->i_id = (USHORT)GetCurrentProcessId();// 获取当前进程ID
	pIcmpHeader->i_cksum = 0;       // 初始化检验和为0
	pIcmpHeader->i_seq = 0;       // 顺序符
	char* pDataPart = pDataBuff + sizeof(IcmpHeader);  // 给数据区赋地址
	memset(pDataPart, 'E', nDataSize);      // 把数据区初始化
	return true;
}
// 计算校验和
USHORT CPing::CheckSum(USHORT* pBuff, int nSize)
{
	unsigned long ulChkSum = 0; // 给检验和置0
	while (nSize > 1)
	{
		ulChkSum += *pBuff++; // 把所有IP数据报的数据都加到一起
		nSize -= sizeof(USHORT);// 每次计算两个十二位二进制和 （每次减两个字节）
	}
	if (nSize != 0)
	{
		ulChkSum += *(UCHAR*)pBuff; // 判断当只剩下一个字节没有加到检验和时在这里加上
	}
	ulChkSum = (ulChkSum >> 16) + (ulChkSum & 0XFFFF); // 先按32bit计算二进制和得到cksum，然后把高位低位相加
	//得到16bit的和。
	ulChkSum += (ulChkSum >> 16); // 把高16位和低16位相加溢出的进位再加到校验和中
	return (USHORT)(~ulChkSum);  // 取反得到检验和
}
bool CPing::DecodeIpPacket(char* pBuff, int nBuffSize, sockaddr_in* pAddr)
{
	if (pBuff == NULL || nBuffSize <= 0)
		return false;
	IpHeader* pIpHeader = (IpHeader*)pBuff;
	unsigned short usIpHeaderLen = (pIpHeader->h_len) * 4; //计算IP首部的长度
	IcmpHeader* pIcmpHeader = (IcmpHeader*)(pBuff + usIpHeaderLen);
	//判断是否是回显应答报文
	if (pIcmpHeader->i_type != ICMP_ECHOREPLY)
		return false;
	// 判断是否是当前进程的IP地址，确认是此次的回显报文。
	if (pIcmpHeader->i_id != (USHORT)GetCurrentProcessId())
		return false;
	if (nBuffSize < usIpHeaderLen + ICMP_MIN)
		return false;
	if (m_bPrintInfo)
	{
		std::cout << "Reply from " << inet_ntoa(pAddr->sin_addr);
		std::cout << ": bytes=" << nBuffSize - usIpHeaderLen - ICMP_MIN;
		std::cout << " time=" << GetTickCount() - pIcmpHeader->timestamp;
		std::cout << "ms TTL=" << pIpHeader->ttl << std::endl;
	}
	return true;
}
bool CPing::CanPing(const char* pDscAddr)
{
	m_bPrintInfo = false;
	return PingHelper(pDscAddr);
}
void CPing::Ping(const char* pDscAddr, int nPackNum, int nPackSize)
{
	m_bPrintInfo = true;
	PingHelper(pDscAddr, nPackNum, nPackSize);
}

//使用代码示例：
//CPing ping;
//ping.Ping("www.baidu.com");