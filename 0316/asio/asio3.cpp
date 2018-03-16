#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp> 
// C++11 표준에도 존재합니다.
// => 함수형 프로그래밍의 부분 적용 기술

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;

void print(const system::error_code& ec, 
		   asio::deadline_timer* t, int* count)
{
	if (*count < 5)
	{
		printf("%d\n", *count);
		++(*count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(print, asio::placeholders::error, t, count));
	}
}

int main()
{
	asio::io_service io_service;

	int count = 0;
	asio::deadline_timer t(io_service, boost::posix_time::seconds(1));

	// t.async_wait(&print);
	t.async_wait(boost::bind(print, asio::placeholders::error, &t, &count));
	io_service.run();

	return 0;
}
