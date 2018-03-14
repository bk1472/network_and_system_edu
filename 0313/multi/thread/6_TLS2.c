// 1. Reentrant(재진입) 불가능하다?
// => 함수가 상태를 가지고 있다.
//    함수가 내부 정적 변수나 전역 변수에 의존하고 있다.
//   1) 재귀적으로 사용하는 것이 불가능하다.
//   2) 스레드에 안전하지 않다.

// 2. 재진입이 가능하다 != 스레드에 안전하다

// 3. 재진입이 불가능한 함수의 대표적인 예 - strtok

// strtok
// 멀티 스레드 상에서
//  1. linux 에서는 제대로 동작하지 않습니다.
//     : strtok_r
//     => 재진입 가능한 별도의 버전을 제공한다.

//  2. windows 에서는 제대로 동작합니다.
//     - libc-mt(2005)
//     : C의 표준 라이브러리에 TLS를 적용하였습니다.
//     => 재진입 불가능한 함수는 스레드 안전하게 만드는 방법.

// Modern Programming
//  1. Object   => Immutable
//  2. Function => Pure

#include <unistd.h>

#include <stdio.h>
#include <string.h>

#include <pthread.h>

#if 0
void* foo(void* a)
{
	char* name = (char*)a;
	char s[] = "hello world show me the money";

	char* sp;
	
	for (char* p = strtok_r(s, " ", &sp) ; p != NULL 
		; p = strtok_r(NULL, " ", &sp))
	{
		printf("%s: %s\n", name, p);
		usleep(10);
	}
	return 0;
}
#endif

// Bionic - Android C Library
char* xstrtok(char* s, const char* d)
{
	static __thread char* sp; // TLS
	return strtok_r(s, d, &sp);
}

#if 1
void* foo(void* a)
{
	char* name = (char*)a;
	char s[] = "hello world show me the money";
	
	for (char* p = xstrtok(s, " ") ; p != NULL ; p = xstrtok(NULL, " "))
	{
		printf("%s: %s\n", name, p);
		usleep(10);
	}
	return 0;
}
#endif


#if 1
int main()
{
	pthread_t thread[2];
	pthread_create(&thread[0], 0, &foo, "A");
	pthread_create(&thread[1], 0, &foo, "B");

	for (int i = 0 ; i < 2; ++i)
		pthread_join(thread[i], 0);
}
#endif


