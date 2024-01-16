#pragma once

#pragma pack(push, 1)

typedef struct _Data
{
	int FirstNumber;
	int SecondNumber;
	char Operator;
} Data;

typedef struct _Header
{
	u_short Code;
	u_short Size;
} Header;

#pragma pack(pop)
