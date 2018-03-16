#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "calculator.pb.h"

using namespace boost;
using namespace boost::asio::ip;

// asio::async_read
//   => readn(socket, buf, len);

// socket_.async_read.some
//   => read(socket, buf, sizeof buf);

// client(Request)  -> {len(2)}char[] -> server
// server(Response) -> {len(2)}char[] -> client
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
		do_read_header();
	}

	void do_read_header()
	{
		auto self(shared_from_this());
		asio::async_read(socket_, 
			asio::buffer(&header_length_, sizeof(header_length_)),
			[self, this](const system::error_code& ec, size_t len) {
				printf("do_read_header()\n");

				if (!ec)
				{
					do_read_body();
				}

			});
	}

	void do_read_body()
	{
		auto self(shared_from_this());
		asio::async_read(socket_,
			asio::buffer(data_, header_length_),
			[self, this](const system::error_code& ec, size_t len) {
			
				if (!ec)
				{
					Request request;
					request.ParseFromArray(data_, len);
					int lhs = request.lhs();
					int rhs = request.rhs();

					int result = lhs + rhs;
					printf("do_read_body - lhs: %d, rhs: %d\n", lhs, rhs);
					do_write(result);
				}
			});
	}

	void do_write(int result)
	{
		printf("result: %d\n", result);
		auto self(shared_from_this());

		Response response;
		response.set_result(result);

		short header = response.ByteSize();

		memcpy(data_, &header, sizeof header);
		response.SerializeToArray(data_ + sizeof(header), header);

		asio::async_write(socket_, 
			asio::buffer(data_, header + sizeof(header)),
			[self, this](const system::error_code& ec, size_t len) {
				printf("do_write: %ld\n", len);
				if (!ec)
					do_read_header();
			});
	}

private:
	tcp::socket socket_;
	char  data_[1024]; 
	short header_length_;
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
