#include <winsock2.h>
#include <stdio.h>
#include "ping.h"

int main(void)
{
	CPing objPing;

	char *szDestIP = "123.0.0.1";
	PingReply reply;
	memset(&reply,0,sizeof(reply));
	printf("Pinging %s with %d bytes of data:\n", szDestIP, DEF_PACKET_SIZE);
	while (TRUE)
	{
		objPing.Ping(szDestIP, &reply);
		if (reply.m_dwBytes == 0)
		{
			printf("³¬Ê±£¬Î´pingÍ¨.....\n");
		}
		else
		{
			printf("Reply from %s: bytes=%d time=%ldms TTL=%ld\n", szDestIP, reply.m_dwBytes, reply.m_dwRoundTripTime, reply.m_dwTTL);
		}
		Sleep(500);
	}

	return 0;
}