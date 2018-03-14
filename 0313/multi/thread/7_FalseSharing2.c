#include <stdio.h>
#include <stdlib.h>

// 2. 동적 메모리 할당(malloc)
// => 동적 메모리 할당시 64바이트의 배수로 할당해서 사용해야 한다.
int main()
{
	unsigned long pa = (unsigned long)malloc(64);
	unsigned long pb = (unsigned long)malloc(64);

	int diff = abs(pa - pb);
	printf("diff: %d\n", diff);
}


#if 0
// 1. 전역 변수도 발생 가능성이 높다.
int a __attribute__((aligned(64)));
int b __attribute__((aligned(64)));

int main()
{
	unsigned long pa = (unsigned long)&a;
	unsigned long pb = (unsigned long)&b;

	int diff = abs(pa - pb);
	printf("diff: %d\n", diff);
}
#endif


