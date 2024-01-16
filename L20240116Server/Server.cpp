#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Server.h"
using namespace std;

#pragma comment(lib, "ws2_32")


int main()
{
	srand((u_int)(time(nullptr)));

	// ���� ����
	// ���� �����
	FILE* image;
	

	// ���� ����
	image = fopen("chicken.jpg", "rb");
	if (image)
	{
		std::cout << "�̹��� �б� ����" << std::endl;
	}
	// ���� ���� ���� ó��
	if (image == NULL) {
		perror("Error opening file");
		return -1;
	}

	

	

	// WinSock �ʱ�ȭ
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ������ ������ ���� ����
	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// ���� �ּ� ����ü ����
	struct sockaddr_in ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));

	//���� �ּ� ����
	ListenSockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(ListenSockAddr.sin_addr.s_addr));
	ListenSockAddr.sin_port = htons(5001);

	// ������ �ּҿ� ������ ���ε���
	bind(ListenSocket, (struct sockaddr*)&ListenSockAddr, sizeof(ListenSockAddr));

	// Ŭ���̾�Ʈ ������ ��ٸ��� ���·� ������ ����
	listen(ListenSocket, 5);


	// ���� �ּ� ����ü ����
	struct sockaddr_in ClinetSockAddr;
	memset(&ClinetSockAddr, 0, sizeof(ClinetSockAddr));
	int ClientSockAddrLength = sizeof(ClinetSockAddr);

	//Ŭ���̾�Ʈ�� ���� ����
	SOCKET ClientSocket = accept(ListenSocket, (struct sockaddr*)&ClinetSockAddr, &ClientSockAddrLength);

	
	//�̹��� ���� �а� ����
	char Buffer[1024] = { 0, };
	while (!feof(image)) {
		int bytes_read = fread(Buffer, 1, 1024, image);
		send(ClientSocket, Buffer, bytes_read, 0);
	}

	printf("Image file sent successfully\n");
	fclose(image);

	// ������ ����
	//while (true)
	//{
	//	//char Message[9] = { 0, };

	//	Data Packet;
	//	// 0 ~ 9999
	//	Packet.FirstNumber = (rand() % 20000) - 10000;
	//	// 1 ~ 9999
	//	Packet.SecondNumber = (rand() % 20000) - 10000;
	//	/*Packet.SecondNumber == 0 ? 1 : Packet.SecondNumber;*/
	//	if (Packet.SecondNumber == 0)
	//	{
	//		Packet.SecondNumber = 1;
	//	}
	//	////[0][0][0][0][][][][][]
	//	//memcpy(&Message[0], &FirstNumber, sizeof(int));
	//	////[0][0][0][0][1][1][1][1][]
	//	//memcpy(&Message[4], &SecondNumber, sizeof(int));
	//	////[0][0][0][0][1][1][1][1][2]
	//	Packet.Operator = rand() % 5;

	//	send(ClientSocket, (char*)&Packet, (u_int)sizeof(Packet), 0);

	//	// ���� �����͸� �����ϱ� ���� ����
	//	char Buffer[1024] = { 0, };
	//	//Ŭ���̾�Ʈ�� ���� �����͸� ���� �޾ RecvByte�� ����
	//	int RecvByte = recv(ClientSocket, Buffer, 1024, 0);
	//	if (RecvByte <= 0)
	//	{
	//		break;
	//	}

	//	// ���ŵ� ����� ������ ���� ���� �� �ʱ�ȭ
	//	long long Result = 0;

	//	// ���ŵ� �����͸� Result ����
	//	memcpy(&Result, Buffer, sizeof(Result));
	//	cout << Result << endl;
	//}

	//���� ���� �� ����
	closesocket(ClientSocket);
	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}