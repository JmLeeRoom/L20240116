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

	// 파일 열기
	// 파일 입출력
	FILE* image;
	

	// 파일 열기
	image = fopen("chicken.jpg", "rb");
	if (image)
	{
		std::cout << "이미지 읽기 성공" << std::endl;
	}
	// 파일 열기 실패 처리
	if (image == NULL) {
		perror("Error opening file");
		return -1;
	}

	

	

	// WinSock 초기화
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 서버의 리스닝 소켓 생성
	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 소켓 주소 구조체 정의
	struct sockaddr_in ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));

	//소켓 주소 설정
	ListenSockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(ListenSockAddr.sin_addr.s_addr));
	ListenSockAddr.sin_port = htons(5001);

	// 지정된 주소에 소켓을 바인딩함
	bind(ListenSocket, (struct sockaddr*)&ListenSockAddr, sizeof(ListenSockAddr));

	// 클라이언트 연결을 기다리는 상태로 소켓을 설정
	listen(ListenSocket, 5);


	// 소켓 주소 구조체 정의
	struct sockaddr_in ClinetSockAddr;
	memset(&ClinetSockAddr, 0, sizeof(ClinetSockAddr));
	int ClientSockAddrLength = sizeof(ClinetSockAddr);

	//클라이언트의 연결 수락
	SOCKET ClientSocket = accept(ListenSocket, (struct sockaddr*)&ClinetSockAddr, &ClientSockAddrLength);

	
	//이미지 파일 읽고 전송
	char Buffer[1024] = { 0, };
	while (!feof(image)) {
		int bytes_read = fread(Buffer, 1, 1024, image);
		send(ClientSocket, Buffer, bytes_read, 0);
	}

	printf("Image file sent successfully\n");
	fclose(image);

	// 데이터 전송
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

	//	// 수신 데이터를 저장하기 위한 버퍼
	//	char Buffer[1024] = { 0, };
	//	//클라이언트로 부터 데이터를 저장 받어서 RecvByte에 저장
	//	int RecvByte = recv(ClientSocket, Buffer, 1024, 0);
	//	if (RecvByte <= 0)
	//	{
	//		break;
	//	}

	//	// 수신된 결과를 저장할 변수 선인 및 초기화
	//	long long Result = 0;

	//	// 수신된 데이터를 Result 복사
	//	memcpy(&Result, Buffer, sizeof(Result));
	//	cout << Result << endl;
	//}

	//소켓 종료 및 정리
	closesocket(ClientSocket);
	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}