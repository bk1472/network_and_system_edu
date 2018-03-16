#include <time.h>

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// LLVM(경량 VM)
//  => clang, clang++

// gcc
// LLVM clang: Apple, Google

// 1.c   ->    1.o 
// 1.c         ->    I.L    ->    1.o 


// Asio의 객체의 수명을 관리하는 기술
//   => C++ 스마트 포인터
//   => raw pointer를 직접 관리하는 것은 어렵다.
//     1) 메모리 누수 - delete를 잊는다.
//     2) 잘못된 참조 - 이미 파괴된 메모리를 참조한다. 

// 소유권(ownership)
//    : 복사의 정책
//   1) unique_ptr<>: 소유권을 독점
//   2) shared_ptr<>: 소유권을 공유

// a = b;                unique_ptr<> 복사 금지
// a = std::move(b);     소유권 이전

// a = b;                shared_ptr<> 참조 계수
using namespace boost;
using namespace boost::asio::ip;

std::string make_daytime_string()
{
	time_t now = time(0);
	return ctime(&now);
}

// shared_ptr: 참조 계수의 모델로 관리하는 것이 좋다.
//  1. 비동기의 함수가 호출되는 도중 session의 객체가 유효하다는 것이
//     보장된다.
//  2. 더이상 참조하는 포인터가 없을 경우,
//     자동으로 파괴된다.

// 참조 계수 모델의 문제점
// 1. 성능의 저하가 다소 있다.
//   => 참조 계수의 증감은 원자적 연산으로 수행된다.
// 2. 메모리 누수가 발생할 수 있다.
//   => 상호 참조에 의해서


class session
{
public:
	session(asio::io_service& io)
		: socket_(io)
	{}

	~session() 
	{
		printf("session destroyed\n");
	}

	void start()
	{
		printf("session start\n");
		message_ = make_daytime_string();

		asio::async_write(socket_, asio::buffer(message_),
			bind(&session::handle_write, this, 
				asio::placeholders::error,
				asio::placeholders::bytes_transferred));
	}

	void handle_write(const system::error_code& e, size_t s)
	{
		if (!e)
			printf("session write - bytes transferred: %ld\n", s);

		delete this;
		// 연결을 종료하기 위해서는 session의 객체를 파괴하면 된다.
		// => socket도 파괴된다.
		// => 연결이 종료된다.
	}

	tcp::socket& socket() 
	{
		return socket_;
	}

private:
	tcp::socket socket_;
	std::string message_;
};


class server
{
public:
	server(asio::io_service& io)
		: acceptor_(io, tcp::endpoint(tcp::v4(), 5000))
	{
		do_accept();
	}

	void do_accept()
	{
		session* s = new session(acceptor_.get_io_service());
		
		acceptor_.async_accept(s->socket(), 
			bind(&server::handle_accept, this, s, asio::placeholders::error)); 
	}

	void handle_accept(session* s, const system::error_code& e)
	{
		// 에러의 발생 여부를 체크해야 합니다.
		if (!e)
		{
			printf("handle_accept()\n");
			// 에러가 발생하지 않았을 때
			s->start();
			do_accept();
		}
		else 
		{
			// 에러가 발생하였을 때
			delete s;
		}
	}

private:
	tcp::acceptor acceptor_;
};


int main()
{
	try
	{
		asio::io_service io_service;
		server s(io_service);

		io_service.run();
	}
	catch (std::exception& e)
	{
		printf("error: %s\n", e.what());
	}

}

















