
// 스레드 프로그래밍 장점
//  => 스레드 간 데이터의 공유가 쉽다.
//  => 데이터 레이스 컨디션을 처리해야 한다.

#include <unistd.h>

#include <stdio.h>
#include <pthread.h>


#if 0
// C++은 아래처럼 사용하면 데드락의 위험이 있다.
// C언어: 반환값을 에러를 처리한다.
// C++  : 예외를 통해서 에러를 처리한다. 
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct Mutex
{
	pthread_mutex_t mutex;
public:
	Mutex()  { pthread_mutex_init(&mutex, NULL);    }
	~Mutex() { pthread_mutex_destroy(&mutex); }

	void lock() { pthread_mutex_lock(&mutex); }
	void unlock() { pthread_mutex_unlock(&mutex); }

	struct AutoLock
	{
		Mutex* m;
	public:
		AutoLock(Mutex* p) : m(p) { m->lock();   }
		~AutoLock()               { m->unlock(); }
	};
};

// C++ 표준에는 
// 예외가 발생하면 지역 객체의 소멸자 호출은 보장된다.
// => RAII(Resource Acqusion Is Initializer)
// => 예외 안정성
#endif

#include <mutex>
using namespace std;

void* foo(void* p)
{
	static int x;
	// static Mutex m;
	static std::mutex m;
	
	for (int i = 0 ; i < 5000 ; ++i)
	{
		lock_guard<mutex> al(m);
		// Mutex::AutoLock al(&m);
		// m.lock();
		x = 100;
		usleep(10);
		x += 1;
		printf("%s: %d\n", (char*)p, x);
		// m.unlock();
	}
}


int main()
{
	pthread_t thread[3];
	pthread_create(&thread[0], 0, &foo, (void*)"A");
	pthread_create(&thread[1], 0, &foo, (void*)"  B");
	pthread_create(&thread[2], 0, &foo, (void*)"     C");

	for (int i = 0 ; i < 3 ; ++i)
		pthread_join(thread[i], 0);

	printf("program end..\n");
}
