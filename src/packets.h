#ifndef __PACKETS_H
#define __PACKETS_H

class PacketHeader
{
public:
	unsigned char cmd;
	PacketHeader(int cmd){
		this->cmd = cmd;
	}
};

class PacketSync : public PacketHeader
{

};

class PacketLoading : public PacketHeader
{
public:
	PacketLoading() : PacketHeader(C2S_COMMAND)
	{

	}

};

#endif