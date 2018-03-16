#if 0
$ g++ server.cpp calculator.grpc.pb.cc calculator.pb.cc -o server -std=c++11 -lprotobuf -lpthread -lgrpc++ -lgrpc -lgrpc++_reflection -ldl -L/usr/local/lib

#endif


#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "calculator.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using calculator::Request;
using calculator::Response;
using calculator::Calculator;

// Stub - 실제 서비스의 구현체
// final: 상속 금지
class CalculatorServiceImpl final  : public Calculator::Service {

	Status Plus(ServerContext* context, 
				    const Request* request,
				    Response* response) override {
		int lhs = request->lhs();
		int rhs = request->rhs();

		response->set_result(lhs + rhs);
		return Status::OK;
	}

	Status Minus(ServerContext* context, 
				    const Request* request,
				    Response* response) override {
		int lhs = request->lhs();
		int rhs = request->rhs();

		response->set_result(lhs - rhs);
		return Status::OK;
	}

};

void RunServer()
{
	std::string address("0.0.0.0:5000");
	CalculatorServiceImpl service;


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
