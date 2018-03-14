// 현재 시스템의 엔디안을 확인하는 방법
// => 매크로로 제공하고 있습니다.
#include <stdio.h>

int main()
{
#if BYTE_ORDER == LITTLE_ENDIAN
	printf("litten endian\n");
#elif BYTE_ORDER == BIG_ENDIAN
	printf("big endian\n");
#endif
}
