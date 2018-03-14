#include <sys/time.h>
#include <tbb/tbb.h>
using namespace tbb;

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

array<int, 2000000> arr;
int main()
{
	// long sum = 0;
	iota(arr.begin(), arr.end(), 1);   // numeric

	int start = timestamp();

	combinable<long> sum;
	parallel_for_each(arr.begin(), arr.end(), [&](int n) {
			sum.local() += is_prime(n) ? n : 0;
	});

	printf("timestamp: %dms\n", timestamp() - start);
	printf("sum: %ld\n", sum.combine(plus<long>()));
}


// 규모 확장
//  1. scale up: C/C++
//   => 컴퓨터의 사양을 올린다.
//   => 확장이 어렵다.

//  2. scale out: node.js: Single Thread
//   => 컴퓨터의 개수를 늘린다.
//   => 모든 데이터가 공유될 수 있도록하는 방법을 제공해야 한다.
//      Redis / Memchached
//     : 데이터베이스
















