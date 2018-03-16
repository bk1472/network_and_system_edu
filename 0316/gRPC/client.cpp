#include <stdio.h>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using helloworld::Request;
using helloworld::Response;
using helloworld::Greeter;

// Remote Proxy
//  : 원격에 있는 객체를 마치 로컬에 있는 것처럼 사용할 수 있다.
// => Remote Proxy는 서비스 개발자가 제공한다.
class GreeterClient {
public:
	GreeterClient(std::shared_ptr<Channel> channel) 
		: stub_(Greeter::NewStub(channel)) {}		

	//-----
	std::string SayHello(const std::string& name) 
	{
		// SayHello의 기능은 서버에 구현되어 있다.
		// 서버에 요청해야 한다.
		Request request;
		request.set_name(name);

		Response response;
		ClientContext context;
		Status status = stub_->SayHello(&context, request, &response);

		if (status.ok())
		{
			return response.message();
		}
		else
		{
			printf("error: %d, message: %s\n",
				status.error_code(), status.error_message().c_str());
			return "";
		}
	}

	//-----
private:
	std::unique_ptr<Greeter::Stub> stub_;
};


int main()
{
	GreeterClient greeter(grpc::CreateChannel(
		"localhost:5000", grpc::InsecureChannelCredentials()));

	std::string message = greeter.SayHello("Tom");
	printf("response: %s\n", message.c_str());
}
