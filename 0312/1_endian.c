// #1. Endian
//   정의: CPU가 데이터를 저장하고 해석하는 방식

// 리틀 엔디안: 시작 주소에 하위 바이트부터 기록하는 방식
//  Intel / AMD CPU

// 빅 엔디안  : 시작 주소에 상위 바이트부터 기록하는 방식
//  ARM: Little / Big 조정 가능하다.
//  Java

// 0x12345678
//    Big:  12 34 56 78
// Little:  78 56 34 12

// 0x3344
//     B: 33 44
//     L: 44 33

// Socket Programming - IPC(Inter Process Communication)
//  => Network Programming
//    : 빅 엔디안 

#include <stdio.h>

void printByteOrder(void* value, int size)
{
	char* p = (char*)value;
	for (int i = 0 ; i < size ; ++i)
		printf("%x ", p[i]);
	putchar('\n');
}

int main()
{
	int value = 0x12345678;
	printByteOrder(&value, sizeof value);
}




