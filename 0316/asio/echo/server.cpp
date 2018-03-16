
#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost;
using namespace boost::asio::ip;

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
		socket_.async_read_some(asio::buffer(data_, 1024),
			bind(&session::handle_read, shared_from_this(), 
				asio::placeholders::error,
				asio::placeholders::bytes_transferred));
	}

	void handle_read(const system::error_code& e, size_t bytes_transferred)
	{
		printf("handle_read: %ld\n", bytes_transferred);
		if (!e)
		{
			async_write(socket_, asio::buffer(data_, bytes_transferred),
				bind(&session::handle_write, shared_from_this(), 
					asio::placeholders::error,
					asio::placeholders::bytes_transferred));
		}
	}

	void handle_write(const system::error_code& e, size_t bytes_transferred)
	{
		printf("handle_write: %ld\n", bytes_transferred);
		if (!e)
		{
			socket_.async_read_some(asio::buffer(data_, 1024),
					bind(&session::handle_read, shared_from_this(), 
						asio::placeholders::error,
						asio::placeholders::bytes_transferred));
		}
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
			bind(&server::handle_accept, this, s, asio::placeholders::error));
	}

	void handle_accept(session::pointer s, const system::error_code& e)
	{
		printf("handle accept\n");
		if (!e)
		{
			s->start();
			do_accept();
		}
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
