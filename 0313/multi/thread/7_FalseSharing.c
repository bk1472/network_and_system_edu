// False Sharing(가짜 공유 문제)

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#include <stdio.h>

int timestamp()
{
	struct timeval tv;
	gettimeofday(&tv, 0);

	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

//------------------------------------
// 아래의 코드는 멀티 코어 상에서 성능상의 이슈가 발생합니다.
//  1. 같은 캐시 라인을 공유하게 되고, 각 코어는 캐시라인 데이터를
//     변경할 때마다 무효화 신호를 보낸다.
//  2. 캐시를 적절하게 사용할 수 없고, 반드시 메모리로부터 접근해야 하는
//     문제가 발생한다. 

#if 0
struct data
{
	long a;
	// char padding[64];
	long b;
};
#endif

struct data
{
	// 같은 캐시라인을 공유하지 않도록 한다.
	long a __attribute__((aligned(64)));
	long b __attribute__((aligned(64)));
};

static struct data data = { 0, 0 };

void* foo(void* p)
{
	for (int i = 0 ; i < 500000000 ; ++i)
	{
		data.a += 1;
	}

	return (void*)data.a;
}

void* goo(void* p)
{
	for (int i = 0 ; i < 500000000 ; ++i)
	{
		data.b += 1;
	}

	return (void*)data.b;
}

int main()
{
	pthread_t thread[2];

	int start = timestamp();
	pthread_create(&thread[0], 0, &foo, 0);
	pthread_create(&thread[1], 0, &goo, 0);

	for (int i = 0 ; i < 2; ++i)
	{
		void* status;
		pthread_join(thread[i], &status);

		printf("status: %ld\n", (long)status);
	}
	printf("ms: %d\n", timestamp() - start);
}
