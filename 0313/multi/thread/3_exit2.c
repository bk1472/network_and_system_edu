#include <pthread.h>
#include <stdio.h>

// goto
//  1. 이중 루프를 한번에 빠져나올 때
//  2. 에러 루틴을 한곳에 모아서 처리할 수 있다.

// register
//  : 컴파일러가 웬만한 개발자보다 영리하다.
// for (int i = 0 ; i < 100 ; ++i)


// 아래의 코드는 최적화 컴파일시 제대로 동작하지 않습니다.
//  => 메모리 가시성의 문제
//   : 변수의 값이 메모리에서 변경되었음애도 불구하고
//     관찰하지 못하는 현상
//  => volatile(제한자)
//   : 반드시 해당 변수의 값을 메모리로부터 읽거나 써야 한다.

// C언어의 제한자 3개
//  cvr 제한자
//  1. const
//  2. volatile
//  3. restrict(c99)
//    -> memcpy, memmove
//   : 중첩된 영역에 대해서는 제대로 동작하지 않는다.
//   => CPU 명령의 최적화
//      연속된 영역에 대한 복사 처리에 최적화
//      : restrict

//   => memmove는 뒤에서부터 복사를 수행하기 때문에
//      중첩된 영역에 대해서 사용할 수 있다.

// C언어 캐스팅 연산자 1개
// C++   캐스팅 연산자 4개
// 1. static_cast
// 2. dynamic_cast
// 3. reintepret_cast
// 4. const_cast
//   : const를 제거할 때 사용
//    cvr 제한자를 제거하는 용도로 사용할 수 있다.

// const 함수
//  : GCC 컴파일러

// Modern Programming Language
//  => C14 / C++11/14 / Java8
//  => Functional Programming

// 순수 함수(pure function)
__attribute__((__const__))int foo(int a, int b)
{
	return a + b;
}


void* foo(void* p)
{
	volatile int* pn = (void*)p;

	while (*pn)
	{
		// ...
	}

	printf("foo end...\n");
	return 0;
}

int main()
{
	int n = 1;

	pthread_t thread;
	pthread_create(&thread, 0, &foo, &n);

	getchar();
	n = 0;

	pthread_join(thread, 0);
	printf("progam end..\n");
}
