// multi thread programming
//  => 멀티 스레드 상에서 동적 메모리 할당(malloc) 연산은
//     비효율적이다.

// malloc vs tcmalloc(Thread Cache Malloc)
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>

// tcmalloc을 적용하기 위해서 코드를 수정할 필요가 없습니다.
// => 라이브러리만 링크 해주면 됩니다.
// $ sudo apt install libgoogle-perftools-dev

// 적용 방법 2가지
// 1. 컴파일시 라이브러리를 링크한다.
//   $ gcc 6_TLS4.c -ltcmalloc
// 2. LD_PRELOAD
//   $ LD_PRELOAD=/usr/lib/libtcmalloc.so ./a.out

// malloc의 양대 산맥
// tcmalloc - Google
//   : Google PerfTools
//     => Heap Cheacker

// jemalloc - Facebook
// TBB malloc - Intel

// malloc:     2205
// tcmalloc:   912

int timestamp()
{
	struct timeval tv;
	gettimeofday(&tv, 0);

	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main()
{
	void* p;
	int n = 32;

	int start = timestamp();
	while (n <= 1024)
	{
		for (int i = 0 ; i < 10000000; ++i)
		{
			p = malloc(n);
			free(p);
		}

		n *= 2;
	}
	printf("ms: %d\n", timestamp() - start);
}
