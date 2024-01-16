#pragma once // 해당 헤더 파일이 컴파일 과정에서 한번만 포함되도록 보장하는 명령어

#pragma pack(push, 1) // 구조체의 패딩을 제어하는 지시어 구조체의 모든 멤버가 1바이트 경계에 정렬되도록 설정

// 구조체 선언
typedef struct _Data
{
	int FirstNumber;
	int SecondNumber;
	char Operator;
} Data;

#pragma pack(pop) // 이전의 패킹 설정을 복원
