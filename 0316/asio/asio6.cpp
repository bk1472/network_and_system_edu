
#include <time.h>

#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace boost;
using namespace boost::asio::ip;

// BSD API
// socket
// bind
// listen
// accept -> socket

// 서버는 클라이언트가 접속하면, 현재 시간을 알려주는 서비스
std::string make_daytime_string()
{
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try 
	{
		asio::io_service io_service;

		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 5000));

		while (1)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			std::string message = make_daytime_string();

			system::error_code err;
			asio::write(socket, asio::buffer(message), err);
		}

	} 
	catch (std::exception& e)
	{
		printf("error: %s\n", e.what());
	}
}





