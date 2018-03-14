
// TLS
// : 매우 중요합니다.

// 스레드간에 공유되지 않는 전역변수나 정적 변수가 필요할 때
// => TLS(Thread Local Storage)
//    TSS(Thread Specific Storage)

// 1. 만드는 방법 2가지
//   1) 정적 TLS: 컴파일 타임에 결정하는 방법
//       => 컴파일러 명령(GCC, clang)
//   2) 동적 TLS: 런타임에 함수 호출을 통해 생성하는 방법
//       => pthread_setspecific
//          pthread_getspecific

#include <stdio.h>
#include <pthread.h>

int next3times()
{
	static __thread int n = 0;
	n += 3;

	return n;
}

void* foo(void* p)
{
	char* s = (char*)p;
	printf("%s: %d\n", s, next3times());
	printf("%s: %d\n", s, next3times());
	printf("%s: %d\n", s, next3times());
}

int main()
{
	pthread_t thread[2];
	pthread_create(&thread[0], 0, &foo, (void*)"A");
	pthread_create(&thread[1], 0, &foo, (void*)"B");

	for (int i = 0 ; i < 2; ++i)
		pthread_join(thread[i], 0);
}
