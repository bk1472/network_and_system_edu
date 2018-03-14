#include <stdio.h>
#include <pthread.h>

// concurrent vs parallel
// concurrent(병행):
//   동시에 수행되는 것처럼 보이지만, 순차적으로 수행될 수도 있다.
// parallel(병렬):  
//   동시에 수행된다.
//    : '병렬 컴퓨터'가 필요합니다.


// 정수의 값의 연산하는 부분에 대해서 뮤텍스를 이용한다면
// 성능의 저하가 너무 심하다.
// => 정수의 연산을 안전하게 수행하는 CPU의 명령셋
// => 원자적 연산(Atomic Operations);
//   Windows: Windows API
//   Linux: pthread API에 존재하지 않고,
//          GCC 제공하는 연산을 사용해야 합니다.

// 원자적 연산의 대표적인 예제
//  => 참조 계수를 통한 객체의 수명 관리

// CLONE_VM
// copy_mm

// struct file
typedef struct {
	    int counter;
} atomic_t;

atomic_t x = {0 };
#define LOCK_PREFIX "\n\tlock; "
static inline void atomic_inc(atomic_t *v)
{
	asm volatile(LOCK_PREFIX "incl %0"
		     : "+m" (v->counter));
}

void* foo(void* p)
{
	for (int i = 0 ; i < 100000 ; ++i)
	{
		// ++x;
		// __sync_fetch_and_add(&x, 1);
		atomic_inc(&x);
	}

	return 0;
}


int main()
{
	pthread_t thread[3];
	for (int i = 0 ; i < 3 ; ++i)
		pthread_create(&thread[i], 0, &foo, 0);

	for (int i = 0 ; i < 3; ++i)
		pthread_join(thread[i], 0);

	printf("x: %d\n", x.counter);
}
