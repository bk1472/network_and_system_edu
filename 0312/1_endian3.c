
// 컴퓨터마다 CPU가 다르기 때문에
// 엔디안의 차이가 발생한다.
// 네트워크를 통해 데이터를 교환하는 방식에 대한
// 약속이 필요하다.
//  => Big Endian
//   : 네트워크로 전송하는 데이터에 대해서 빅 엔디안으로 전환
//     해야 하고, 네트워크를 통해 전송 받은 데이터에 대해서도
//     각각의 CPU에 맞게 변환해서 사용해야 한다. 

#include <stdio.h>
#include <arpa/inet.h>

void printByteOrder(void* value, int size)
{
	char* p = (char*)value;
	for (int i = 0 ; i < size ; ++i)
		printf("%x ", p[i]);
	putchar('\n');
}

// 16 >> 1
//-16 >> 1

// >> 오른쪽 쉬프트
// 1. 산술 쉬프트
//   => signed type(부호 비트), >>
// 2. 논리 쉬프트
//   => unsigned type(0),       >>>

// 0x78 56 34 12
int int32ToBigEndian(unsigned int value)
{
#if BYTE_ORDER == LITTLE_ENDIAN
	return (value & 0xff000000) >> 24 |
		   (value & 0xff0000)   >> 8  |
		   (value & 0xff00)     << 8  |
		   (value & 0xff)       << 24;
#else
	return value;
#endif
}

int main()
{
	int value = 0x12345678;
	printByteOrder(&value, sizeof value);

	value = ntohl(value);
	// value = int32ToBigEndian(value);
	//      htonl -> host to network: 송신
	//      ntohl -> network to host: 수신
    //      htons
    //      ntohs 
    //  : long(4) / short(2)
	
	printByteOrder(&value, sizeof value);
}
