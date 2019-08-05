#include "Net.h"

#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")

char sendBuf[100]="HelloSocket!";
char recvBuf[100]={""};

void NetConnect(char * addr)
{
	WSADATA wsaData;
	SOCKET sockClient;
	SOCKADDR_IN addrServer;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	printf("正在尝试与 谢康 握手。。。\n");
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	addrServer.sin_addr.S_un.S_addr=inet_addr(addr);
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(6000);
	if(connect(sockClient,(SOCKADDR*)&addrServer,sizeof(SOCKADDR))!=0)
	{
		printf("连接失败。\n");
	}else{
		printf("成功与谢康电脑连接。。。\n");
	}
	send(sockClient,"杨宇庆已成功连接。\n",strlen("杨宇庆已成功连接。\n")+1,0);
	while(1)
	{
		recv(sockClient, recvBuf, 100, 0);
		printf("谢康：%s\n",recvBuf);

		printf("杨宇庆：");
		scanf("%s",sendBuf);
		send(sockClient,sendBuf,strlen(sendBuf)+1,0);
		if(strcmp(sendBuf,"q")==0)
			break;
		
	}
	closesocket(sockClient);
	WSACleanup();
}
