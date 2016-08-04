
//#pragma comment (lib,"ws2_32.lib")
//#include <Winsock2.h>
//#include <stdio.h>


//////udp Server
//void main()
//{
//	//版本协商
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//	wVersionRequested = MAKEWORD(1, 1);
//	err = WSAStartup(wVersionRequested, &wsaData);
//	if (err != 0) {
//		/* Tell the user that we could not find a usable */
//		/* WinSock DLL.                                  */
//		return;
//	}
//	/* Confirm that the WinSock DLL supports 2.2.*/
//	/* Note that if the DLL supports versions greater    */
//	/* than 2.2 in addition to 2.2, it will still return */
//	/* 2.2 in wVersion since that is the version we      */
//	/* requested.                                        */
//	if (LOBYTE(wsaData.wVersion) != 1 ||
//		HIBYTE(wsaData.wVersion) != 1) {
//		/* Tell the user that we could not find a usable */
//		/* WinSock DLL.                                  */
//		WSACleanup();
//		return;
//	}
//	/* The WinSock DLL is acceptable. Proceed. */
//	//创建数据报套接字
//	SOCKET svr = socket(AF_INET, SOCK_DGRAM, 0);
//	//创建本地地址信息
//	SOCKADDR_IN addr;
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(6000);
//	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	int len = sizeof(sockaddr);
//	bind(svr, (sockaddr*)&addr, len);
//	//创建客户端地址对象
//	SOCKADDR_IN addrClient;
//	char recvBuf[128];
//	char sendBuf[128];
//	char tempBuf[256];
//	while (true)
//	{
//		//接收数据
//		printf("wait receive client message :\n");
//		recvfrom(svr, recvBuf, 128, 0, (sockaddr*)&addrClient, &len);
//		char* ipClient = inet_ntoa(addrClient.sin_addr);
//		sprintf(tempBuf, "%s said: %s\n", ipClient, recvBuf);
//		printf("%s", tempBuf);
//		gets(sendBuf);
//		//发送数据
//		sendto(svr, sendBuf, strlen(sendBuf) + 1, 0, (sockaddr*)&addrClient, len);
//	}
//	closesocket(svr);
//	WSACleanup();
//}

////TCP server
//
//#pragma comment(lib, "ws2_32.lib")
//#include <Winsock2.h>
//#include <stdio.h>
//void main()
//{
//	//版本协商
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//	wVersionRequested = MAKEWORD(1, 1); //0x0101
//	err = WSAStartup(wVersionRequested, &wsaData);
//	if (err != 0)
//	{
//		return;
//	}
//	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)  //wsaData.wVersion!=0x0101
//	{
//		WSACleanup();
//		return;
//	}
//	//创建Socket
//	SOCKET sockSvr = socket(AF_INET, SOCK_STREAM, 0);
//	//创建IP地址和端口
//	SOCKADDR_IN addrSvr;
//	addrSvr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	addrSvr.sin_family = AF_INET;
//	addrSvr.sin_port = htons(6000);
//	//绑定端口监听
//	bind(sockSvr, (SOCKADDR*)&addrSvr, sizeof(SOCKADDR));
//	listen(sockSvr, 5);
//	sockaddr_in addrClient;
//	int len = sizeof(sockaddr);
//	while (true)
//	{
//		//阻塞方法，获得一个客户Socket连接
//		SOCKET sockConn = accept(sockSvr, (sockaddr*)&addrClient, &len);
//		char sendbuffer[128];
//		sprintf(sendbuffer, "Welcom %s!", inet_ntoa(addrClient.sin_addr));
//		//向客户Socket发送数据
//		send(sockConn, sendbuffer, strlen(sendbuffer) + 1, 0);
//		char recvbuffer[128];
//		//从客户Soc接受数据
//		recv(sockConn, recvbuffer, 128, 0);
//		printf("%s\n", recvbuffer);
//		//关闭Socket
//		closesocket(sockConn);
//	}
//	closesocket(sockSvr);
//	//释放Winsock资源
//	WSACleanup();
//}



//tcp server select
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "WS2_32")	

int main()
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);

	USHORT nPort = 4567;	// 此服务器监听的端口号

	// 创建监听套节字
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	// 绑定套节字到本地机器
	if (::bind(sListen, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf(" Failed bind() \n");
		return -1;
	}
	// 进入监听模式
	::listen(sListen, 5);

	// select模型处理过程
	// 1）初始化一个套节字集合fdSocket，添加监听套节字句柄到这个集合
	fd_set fdSocket;		// 所有可用套节字集合
	FD_ZERO(&fdSocket);
	FD_SET(sListen, &fdSocket);
	while (TRUE)
	{
		// 2）将fdSocket集合的一个拷贝fdRead传递给select函数，
		// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回。
		fd_set fdRead = fdSocket;
		int nRet = ::select(0, &fdRead, NULL, NULL, NULL);
		if (nRet > 0)
		{
			// 3）通过将原来fdSocket集合与select处理过的fdRead集合比较，
			// 确定都有哪些套节字有未决I/O，并进一步处理这些I/O。
			for (int i = 0; i < (int)fdSocket.fd_count; i++)
			{
				if (FD_ISSET(fdSocket.fd_array[i], &fdRead))
				{
					if (fdSocket.fd_array[i] == sListen)		// （1）监听套节字接收到新连接
					{
						if (fdSocket.fd_count < FD_SETSIZE)
						{
							sockaddr_in addrRemote;
							int nAddrLen = sizeof(addrRemote);
							SOCKET sNew = ::accept(sListen, (SOCKADDR*)&addrRemote, &nAddrLen);   //用于接收到来的链接
							FD_SET(sNew, &fdSocket);
							printf("接收到连接（%s）\n", ::inet_ntoa(addrRemote.sin_addr));
						}
						else
						{
							printf(" Too much connections! \n");
							continue;
						}
					}
					else
					{
						char szText[256];
						int nRecv = ::recv(fdSocket.fd_array[i], szText, strlen(szText), 0);
						if (nRecv > 0)						// （2）可读
						{
							szText[nRecv] = '\0';
							printf("接收到数据：%s \n", szText);
						}
						else								// （3）连接关闭、重启或者中断
						{
							::closesocket(fdSocket.fd_array[i]);
							printf("链接关闭,,,");
							FD_CLR(fdSocket.fd_array[i], &fdSocket);
						}
					}
				}
			}
		
		else
		{
			printf(" Failed select() \n");
			break;
		}
	}

	WSACleanup();
	return 0;
}