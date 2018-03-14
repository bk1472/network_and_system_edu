#ifndef PACKET_H
#define PACKET_H

#include <arpa/inet.h>

struct Packet
{
	char* start;
	char* current;

	Packet(char* buf) : start(buf), current(buf) {}
	
	char readByte()
	{
		char ret = *current;
		current += sizeof ret;
		return ret;
	}

	int readInt32() 
	{
		int ret = *(int*)current;
		current += sizeof ret;
		return ntohl(ret);
	}

	void writeByte(char v)
	{
		*current = v;	
		current += sizeof v;
	}

	void writeInt32(int v)
	{
		*(int*)current = htonl(v);
		current += sizeof v;
	}

	int length()
	{
		return current - start;
	}
};

#endif
