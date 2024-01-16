#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Client.h"
using namespace std;

#pragma comment(lib, "ws2_32")




int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(ServerSockAddr.sin_addr.s_addr));
	ServerSockAddr.sin_port = htons(5001);

	connect(ServerSocket, (struct sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));
	
	FILE* image;
	// 이미지 파일 생성
	image = fopen("chicken.jpg", "wb");
	if (image == NULL) {
		perror("Error in creating image file.");
		closesocket(ServerSocket);
		WSACleanup();
		return 1;
	}

	// 서버로부터 데이터 수신 및 파일 쓰기
	char Buffer[1024] = { 0, };
	int bytesReceived;
	while ((bytesReceived = recv(ServerSocket, Buffer, 1024, 0)) > 0) {
		fwrite(Buffer, 1, bytesReceived, image);
	}

	if (bytesReceived < 0) {
		printf("recv failed: %d", WSAGetLastError());
	}

	printf("Image file received successfully\n");




	//
	//while (true)
	//{
	//	char Buffer[1024] = { 0, };
	//	int RecvByte = recv(ServerSocket, Buffer, 1024, 0);
	//	if (RecvByte <= 0)
	//	{
	//		break;
	//	}

	//	//int FirstNumber = 0;
	//	//int SecondNumber = 0;
	//	//char Operator = 0;
	//	Data Packet;
	//	memcpy(&Packet, Buffer, sizeof(Packet));

	//	//memcpy(&FirstNumber, &Buffer[0], sizeof(int));
	//	//memcpy(&SecondNumber, &Buffer[4], sizeof(int));
	//	//Operator = Buffer[8];
	//	long long Result = 0;

	//	cout << Packet.FirstNumber << " ";


	//	switch (Packet.Operator)
	//	{
	//	case 0:
	//		Result = Packet.FirstNumber + Packet.SecondNumber;
	//		cout << " + ";
	//		break;
	//	case 1:
	//		Result = Packet.FirstNumber - Packet.SecondNumber;
	//		cout << " - ";
	//		break;
	//	case 2:
	//		Result = Packet.FirstNumber * Packet.SecondNumber;
	//		cout << " * ";
	//		break;
	//	case 3:
	//		Result = Packet.FirstNumber / Packet.SecondNumber;
	//		cout << " / ";
	//		break;
	//	case 4:
	//		Result = Packet.FirstNumber % Packet.SecondNumber;
	//		cout << " % ";
	//		break;
	//	default:
	//		Result = Packet.FirstNumber + Packet.SecondNumber;
	//		cout << " + ";
	//		break;
	//	}
	//	cout << Packet.SecondNumber << " = ";

	//	cout << Result << endl;

	//	char Message[8] = { 0, };
	//	memcpy(Message, &Result, sizeof(Result));

	//	send(ServerSocket, Message, (u_int)sizeof(Message), 0);
	//}
	fclose(image);
	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}