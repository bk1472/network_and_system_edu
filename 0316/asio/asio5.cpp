
// 비동기의 이벤트는 순서를 제어하기 힘듭니다. - 동기화 이슈
//  strand
// TR1 - C++
#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;

class printer
{
public:
	printer(asio::io_service& io)
		: strand_(io),
		  timer1_(io, posix_time::seconds(1)),
		  timer2_(io, posix_time::seconds(1)),
		  count_(0)
	{
		// timer1_.async_wait(bind(&printer::print1, this));
		// timer2_.async_wait(bind(&printer::print2, this));
		timer1_.async_wait(strand_.wrap(bind(&printer::print1, this)));
		timer2_.async_wait(strand_.wrap(bind(&printer::print2, this)));
	}

	void print1()
	{
		if (count_ < 10)
		{
			printf("timer1: %d\n", count_);
			++count_;

			timer1_.expires_at(timer1_.expires_at() + posix_time::seconds(1));
			timer1_.async_wait(strand_.wrap(bind(&printer::print1, this)));
			/// timer1_.async_wait(bind(&printer::print1, this));
		}
	}

	void print2()
	{
		if (count_ < 10)
		{
			printf("timer2: %d\n", count_);
			++count_;

			timer2_.expires_at(timer2_.expires_at() + posix_time::seconds(1));
			timer2_.async_wait(strand_.wrap(bind(&printer::print2, this)));
			// timer2_.async_wait(bind(&printer::print2, this));
		}
	}

private:
	asio::io_service::strand strand_;
	asio::deadline_timer  timer1_;
	asio::deadline_timer  timer2_;

	int count_;
};

// ASIO의 성능을 끌어올리는 방법
//   => io_service.run()을 여러개의 스레드를 통해 처리한다.
//   : 여러개의 비동기 작업이 실제 동시에 수행되기 때문에
//     동기화에 대해서 고려해야 한다. 

// asio::strand를 통해서 수행되는 비동기작업은 
// 동시에 수행되지 않고 순차적으로 수행된다.
int main()
{
	asio::io_service io_service;
	printer p(io_service);

	// 별도의 스레드를 통해 io_service.run()을 수행한다.
	thread t(bind(&asio::io_service::run, &io_service));

	// io_service가 하나의 스레드(메인 스레드)를 통해서 동작한다.
	io_service.run();
}




