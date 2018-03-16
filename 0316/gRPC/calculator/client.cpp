#include <stdio.h>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "calculator.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using calculator::Request;
using calculator::Response;
using calculator::Calculator;

class CalculatorClient {
public:
	CalculatorClient(std::shared_ptr<Channel> channel) 
		: stub_(Calculator::NewStub(channel)) {}		

	//-----
	int Plus(int a, int b) 
	{
		Request request;
		request.set_lhs(a);
		request.set_rhs(b);
		
		Response response;
		ClientContext context;
		Status status = stub_->Plus(&context, request, &response);
		if (status.ok())
			return response.result();
		else
			return -1;
	}

	int Minus(int a, int b) 
	{
		Request request;
		request.set_lhs(a);
		request.set_rhs(b);
		
		Response response;
		ClientContext context;
		Status status = stub_->Minus(&context, request, &response);
		if (status.ok())
			return response.result();
		else
			return -1;
	}
	//-----
private:
	std::unique_ptr<Calculator::Stub> stub_;
};


int main()
{
	CalculatorClient calc(grpc::CreateChannel(
		"localhost:5000", grpc::InsecureChannelCredentials()));

	printf("Plus(10, 20): %d\n", calc.Plus(10, 20));
	printf("Minus(10, 20): %d\n", calc.Minus(10, 20));
}













