
#include <pthread.h>
#include <stdio.h>

// 스레드의 장점
//  => 같은 주소 공간에서 동작하기 때문에
//     데이터 공유가 쉽다.

// => 스레드를 통해서 전달받은 데이터가 유효한지
//    주의해야 한다.
//   : 공유 되는 변수의 수명을 참조 계수로 관리하는 것이 좋다.
void* goo(void* p)
{
	int* arr = (int*)p;
	int sum = 0;

	for (int i = 0 ; i < 10 ; ++i)
		sum += arr[i];

	printf("sum: %d\n", sum);
	return 0;
}

// void* foo(void* p)
// main 함수 내의 지역 변수는 프로그램이 시작되었을 때 생성되고,
// 프로그램이 종료할 때 파괴된다.

// 스레드는 자신만의 스택을 가진다.
// => 스레드는 함수를 실행하는 흐름.
// => 스레드가 가지는 스택의 크기는 얼마입니까?
//    Windows: 1MB
//    Linux  : 8MB
//      -> ulimit -a

int main()
{ 
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	pthread_t thread;
	pthread_create(&thread, 0, &goo, arr);
	pthread_detach(thread);

	return 0;
}

/*
int main()
{
	pthread_t thread;
	pthread_create(&thread, 0, &foo, 0);
	pthread_join(thread, 0);

	printf("program end...\n");
	getchar();
}
*/
