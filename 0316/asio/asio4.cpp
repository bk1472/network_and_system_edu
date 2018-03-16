#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;

class printer
{
public:
	// ASIO를 통해 동작하는 클래스는 반드시 io_service가 필요하다.
	printer(asio::io_service& io) 
		: timer_(io, posix_time::seconds(1)), count_(0) 
	{
		timer_.async_wait(boost::bind(&printer::print, this));
		// print(printer* this) 
	}

	// 일반 함수가 아닌 멤버 함수를 콜백으로 사용하고 싶다.
	void print()
	{
		if (count_ < 5)
		{
			printf("count: %d\n", count_);
			++count_;

			timer_.expires_at(timer_.expires_at() + posix_time::seconds(1));
			timer_.async_wait(boost::bind(&printer::print, this));
		}
	}

private:
	asio::deadline_timer timer_;
	int count_;
};


int main()
{
	asio::io_service io_service;
	printer p(io_service);

	io_service.run();
}




















