// Boost
//   => Header only
//   => Header + library => boost_system

// : Template Library
//   소스파일과 헤더파일을 분리할 수 없다.
//   => 모든 구현을 헤더파일로 제공해야 한다.
//      h + cpp = hpp

// 문제점: C++을 잘 알아야 합니다.
// node.js: 비동기

// g++ 1.cpp -lboost_system
#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// boost의 모든 클래스는 boost의 이름 공간에 존재합니다.
using namespace boost;
using namespace boost::asio;

// 아래의 함수는 동기적으로 동작합니다.
// 동기(Synchronous: 동시에 일어나는)
//  : 요청과 결과가 한 자리에 일어난다.
//    설계가 단순하고, 직관적이다.
//    결과가 주어질 때까지 대기해야 한다. - 비효율

// 비동기(Asynchronous: 동시에 일어나지 않는)
//  : 요청한 그 자리에서 결과가 주어지지 않는다.
//    설계가 복잡하지만, 결과가 주어지는 동안 시간이 걸리더라도
//    다른 작업을 수행할 수 있다.         - 효율

int main()
{
	// io_service 
	// 최신버전의 Asio 에서는 io_context 라는 이름으로 변경되었습니다.

	io_service io;  // !
	deadline_timer t(io, posix_time::seconds(5));

	t.wait();
	printf("Hello, Asio...\n");
}












