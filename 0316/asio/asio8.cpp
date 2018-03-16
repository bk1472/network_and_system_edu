#include <time.h>

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost;
using namespace boost::asio::ip;

std::string make_daytime_string()
{
	time_t now = time(0);
	return ctime(&now);
}

// 1. enable_shared_from_this 를 상속 받는다.
class session : public enable_shared_from_this<session>
{
public:
	typedef shared_ptr<session> pointer;

	session(asio::io_service& io)
		: socket_(io)
	{}

	~session() 
	{
		printf("session destroyed\n");
	}

	// 2. 정적 팩토리 함수를 제공한다.
	static pointer new_session(asio::io_service& io_service)
	{
		return shared_ptr<session>(new session(io_service));
	}

	void start()
	{
		printf("session start\n");
		message_ = make_daytime_string();

		// 비동기의 함수 호출이 참조 계수를 증가하는 형태로 동작하도록
		// 해야 한다.
#if 0
		asio::async_write(socket_, asio::buffer(message_),
			bind(&session::handle_write, this, 
				asio::placeholders::error,
				asio::placeholders::bytes_transferred));
#endif

		// this -> shared_from_this()
		asio::async_write(socket_, asio::buffer(message_),
			bind(&session::handle_write, shared_from_this(),
				asio::placeholders::error,
				asio::placeholders::bytes_transferred));
	}

	void handle_write(const system::error_code& e, size_t s)
	{
		if (!e)
			printf("session write - bytes transferred: %ld\n", s);

		// delete this;
		// 연결을 종료하기 위해서는 session의 객체를 파괴하면 된다.
		// => socket도 파괴된다.
		// => 연결이 종료된다.
	}

	tcp::socket& socket() 
	{
		return socket_;
	}

private:
	tcp::socket socket_;
	std::string message_;
};


class server
{
public:
	server(asio::io_service& io)
		: acceptor_(io, tcp::endpoint(tcp::v4(), 5000))
	{
		do_accept();
	}

	void do_accept()
	{
		// session* s = new session(acceptor_.get_io_service());
		auto s = session::new_session(acceptor_.get_io_service());
		
		acceptor_.async_accept(s->socket(), 
			bind(&server::handle_accept, this, s, asio::placeholders::error)); 
	}

	void handle_accept(session::pointer s, const system::error_code& e)
	{
		// 에러의 발생 여부를 체크해야 합니다.
		if (!e)
		{
			printf("handle_accept()\n");
			// 에러가 발생하지 않았을 때
			s->start();
			do_accept();
		}

#if 0
		else 
		{
			// 에러가 발생하였을 때
			delete s;
		}
#endif
	}

private:
	tcp::acceptor acceptor_;
};


int main()
{
	try
	{
		asio::io_service io_service;
		server s(io_service);

		io_service.run();
	}
	catch (std::exception& e)
	{
		printf("error: %s\n", e.what());
	}

}

















