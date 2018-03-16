// g++ 2.cpp -lboost_system
#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// 객체의 수명을 관리 - Ref Count
using namespace boost;
// using namespace boost::asio;
// using namespace boost::system;

// 결과가 완료되는 시점에 호출되는 함수 - 콜백
//  => 콜백 함수 설계의 특징
//    : 비동기 요청의 결과를 반드시 받아야 한다.
//      첫번째 인자 또는 마지막 인자로 설계하는 것이 일반적이다.
void print(const system::error_code& e)
{
	printf("Hello, Async Asio..\n");
}

int main()
{
	asio::io_service io;  // !
	asio::deadline_timer t(io, posix_time::seconds(5));

	t.async_wait(&print);

	// 모든 비동기의 요청이 완료되기 전까지 프로그램은 종료하면 안된다.
	io.run();
}
















