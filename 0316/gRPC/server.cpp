#if 0
$ g++ server.cpp helloworld.grpc.pb.cc helloworld.pb.cc -o server -std=c++11 -lprotobuf -lpthread -lgrpc++ -lgrpc -lgrpc++_reflection -ldl -L/usr/local/lib


#endif


#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using helloworld::Request;
using helloworld::Response;
using helloworld::Greeter;

// Stub - 실제 서비스의 구현체
// final: 상속 금지
class GreeterServiceImpl final  : public Greeter::Service {

	Status SayHello(ServerContext* context, 
				    const Request* request,
				    Response* response) override {
		printf("SayHello \n");

		std::string prefix("Hello, ");
		response->set_message(prefix + request->name());

		return Status::OK;
	}
};

void RunServer()
{
	std::string address("0.0.0.0:5000");
	GreeterServiceImpl service;


	ServerBuilder builder;
	builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	std::unique_ptr<Server> server(builder.BuildAndStart());
	printf("Server listening on %s\n", address.c_str());

	server->Wait();
}

int main()
{
	RunServer();
	return 0;
}
