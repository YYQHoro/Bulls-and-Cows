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
	printf("���ڳ����� л�� ���֡�����\n");
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	addrServer.sin_addr.S_un.S_addr=inet_addr(addr);
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(6000);
	if(connect(sockClient,(SOCKADDR*)&addrServer,sizeof(SOCKADDR))!=0)
	{
		printf("����ʧ�ܡ�\n");
	}else{
		printf("�ɹ���л���������ӡ�����\n");
	}
	send(sockClient,"�������ѳɹ����ӡ�\n",strlen("�������ѳɹ����ӡ�\n")+1,0);
	while(1)
	{
		recv(sockClient, recvBuf, 100, 0);
		printf("л����%s\n",recvBuf);

		printf("�����죺");
		scanf("%s",sendBuf);
		send(sockClient,sendBuf,strlen(sendBuf)+1,0);
		if(strcmp(sendBuf,"q")==0)
			break;
		
	}
	closesocket(sockClient);
	WSACleanup();
}
