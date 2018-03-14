// C++98/03 - C++ 
// C++11/14 - C++ 2 / Modern C++
// C++17/20 - C++ 3 - ASIO, Coroutine
// => Boost Library

// $ g++ 1_thread.cpp -std=c++11 -lpthread
#include <stdio.h>

#include <thread>

// 스레드 종료 API가 존재하지 않습니다.
// => Java/C# Thread API - Thread.stop() deprecated
//    Windows Thread 를 종료할 때 절대 반환말고 다른 방법을
//   사용하면 안됩니다.

void foo()
{
	printf("foo thread..\n");
}

int main()
{
	std::thread t(&foo);   // 시작한다.
	t.join();
}	
