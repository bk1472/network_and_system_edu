#include <stdio.h>
#include <string.h>
#include <boost/asio.hpp>

#include "calculator.pb.h"

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

		int lhs = 10;
		int rhs = 32;
		for (int i = 0 ; i < 1000 ; ++i)
		{
			Request request;
			request.set_lhs(lhs);
			request.set_rhs(rhs);

			short header = request.ByteSize();
			memcpy(buf, &header, sizeof header);
			request.SerializeToArray(buf + sizeof(header), header);

			asio::write(s, asio::buffer(buf, header + sizeof header));
			//-----------

			asio::read(s, asio::buffer(&header, sizeof header));
			asio::read(s, asio::buffer(buf, header));

			Response response;
			response.ParseFromArray(buf, header);

			printf("%3d: result: %d\n", i, response.result());
		}

		io_service.run();
	} 
	catch (std::exception& e)
	{
		printf("error: %s\n", e.what());
	}
}









