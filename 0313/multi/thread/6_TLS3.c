#include <stdio.h>
#include <string.h>

int* foo()
{
	// static int a;
	// return &a;

	return malloc(sizeof(int));
}	

// C++은new를 통한 생성한다.
//  => delete 를 해야 한다.
//  => 스마트 포인터를 이용해야 한다.
#if 0
shared_ptr<int> goo() {
	return make_shared(42);
}
#endif

// 함수에서 주소를 반환할 경우
//  1. 지역 변수의 주소를 반환하면 안됩니다.

//  2. static int a
//    => 스레드 안전하지 않다.

//  3. malloc(sizeof(int));
//    => 스레드 안전하다.
//    => 반드시 free를 해야 한다.

// 특정한 함수가 포인터를 반환할 경우
//  어떤 방법을 통해서 반환하고 있는지를 확인하는 방법. - 90%
//  1) _r 버전을 같이 제공하고 있다.
//     static
//  2) _r 버전을 제공하고 있지 않다.
//     malloc

// strdup
// getpwnam

int main()
{
	char* s = "hello";
	
	// char* p = malloc(strlen(s) + 1);
	// strcpy(p, s);
	char* p = strdup(s);

	p[0] = 'x';
	free(p);
}
