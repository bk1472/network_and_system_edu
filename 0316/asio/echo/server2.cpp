#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost;
using namespace boost::asio::ip;

// 콜백을 등록하기 위해서, 매번 함수를 만드는 것은
// 번거로운 일입니다.
//  => C++11 lambda를 사용하면 좋다.
class session : public enable_shared_from_this<session>
{
public:
	typedef shared_ptr<session> pointer;

	static pointer new_session(asio::io_service& io_service)
	{
		return shared_ptr<session>(new session(io_service));
	}

	session(asio::io_service& io) : socket_(io) {}
	~session() { printf("~session()\n"); }

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		do_read();
	}
	
	// 람다를 통해서 콜백의 로직을 작성할 때 주의할 점
	//  => 참조 계수를 반드시 증가할 수 있도록 작성해야 합니다.
	void do_read()
	{
		auto self(shared_from_this());
		socket_.async_read_some(asio::buffer(data_, 1024),
			[this, self](const system::error_code& e, std::size_t bytes_transferred) {

			if (!e)
			{
				printf("do_read: %ld\n", bytes_transferred);
				do_write(bytes_transferred);
			}
		});
	}

	void do_write(std::size_t length)
	{
		auto self(shared_from_this());
		async_write(socket_, asio::buffer(data_, length),
			[this, self](const system::error_code& e, std::size_t bytes_transferred) {
			if (!e)
			{
				printf("do_write: %ld\n", bytes_transferred);
				do_read();
			}
		});
	}

private:
	tcp::socket socket_;
	char data_[1024];    // buf
};

class server
{
public:
	server(asio::io_service& io, short port)
		: io_service_(io),
		  acceptor_(io, tcp::endpoint(tcp::v4(), port))
	{
		do_accept();
	}
	
	void do_accept()
	{
		// session* s = new session(io_service_);
		auto s = session::new_session(io_service_);

		acceptor_.async_accept(s->socket(),
			[s, this](const system::error_code& e) {

			printf("handle accept...\n");
			if (!e)
			{
				s->start();
				do_accept();
			}
		});
	}

private:
	asio::io_service& io_service_;
	tcp::acceptor acceptor_;
};


int main()
{
	try 
	{
		asio::io_service io_service;
		server server(io_service, 5000);

		io_service.run();
	}
	catch (std::exception& e)
	{
		printf("error: %s\n", e.what());
	}
}
