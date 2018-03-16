// socket
// connect
#include <stdio.h>
#include <string.h>
#include <boost/asio.hpp>

using namespace boost;
using namespace boost::asio::ip;

int main()
{
	try
	{
		asio::io_service io_service;

		tcp::socket s(io_service);
		tcp::resolver resolver(io_service);

		asio::connect(s, resolver.resolve({"127.0.0.1", "5000"}));
		printf("connected...\n");

		char buf[512];
		while (scanf("%s", buf) == 1)
		{
			int len = strlen(buf) + 1;
			asio::write(s, asio::buffer(buf, len));

			asio::read(s, asio::buffer(buf, len));	
			printf("%s\n", buf);
		}

		io_service.run();
	} 
	catch (std::exception& e)
	{
		printf("error: %s\n", e.what());
	}
}
