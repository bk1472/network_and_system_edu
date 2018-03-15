// Multi Process/Thread Programming
//  => 어떤 하드웨어를 사용하고 있느냐에 따라서
//     최적화된 스레드의 개수가 다르다.

// Core 4: 8  ~ 16
// Core 8: 16 ~ 32
//   : 일반화되어 있지 않다.

// => 스레드를 통한 병렬 프로그래밍이 아닌
//    Task 기반의 병렬 프로그래밍을 해야 한다.

// Task(추상화)
//   : 이제 작업을 정의하면, 해당 작업을 몇개의 스레드로 동작할지는
//     병렬 라이브러리가 판단한다.

// 병렬 라이브러리
// Apple: GCD
// Microsoft: PPL(C++)
//  C++: TBB, C++11(Task)
//  Java: JDK5 - Concurrent Package
//           8 - Stream API

// 배열 안에 있는 소수의 합을 구하는 프로그램.
//  1. 싱글 스레드 기반 검증
//  2. 병렬화

// 선언적인 형태로 코드를 작성해야지만, 병렬화가 쉽다.
// 1. 명령형 프로그래밍
// 2. 선언적 프로그래밍
#include <sys/time.h>

int timestamp()
{
	struct timeval tv;
	gettimeofday(&tv, 0);

	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#include <stdio.h>

#include <array>
#include <numeric>

#include <algorithm> // for_each
using namespace std;

bool is_prime(int n)
{
	if (n < 2)
		return false;

	for (int i = 2 ; i < n ; ++i)
		if (n % i == 0)
			return false;

	return true;
}

#if 0
long sum = 0;
void prime_sum(int n)
{
	sum += is_prime(n) ? arr[i] : 0;
}
#endif

int main()
{
	long sum = 0;

	array<int, 200000> arr;
	iota(arr.begin(), arr.end(), 1);   // numeric

	int start = timestamp();

#if 1
	// 1. 명령형 프로그래밍
	for (int i = 0 ; i < 200000; ++i)
		sum += is_prime(arr[i]) ? arr[i] : 0;
#endif

#if 0
	// 2. 선언형 프로그래밍 
	//  => 쉽게 병렬화가 가능하다.
	//     병렬 라이브러리를 이용하면 
	for_each(arr.begin(), arr.end(), [&](int n) {
		sum += is_prime(n) ? n : 0;
	});
#endif
	
	printf("timestamp: %dms\n", timestamp() - start);
	printf("sum: %ld\n", sum);
}



































