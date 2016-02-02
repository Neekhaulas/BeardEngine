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

class PacketChecking : public PacketHeader
{
public:
	PacketChecking() : PacketHeader(C2S_CHECK){};
	int version;
	int idUser;
};

class PacketWaitingForStart : public PacketHeader
{
public:
	PacketWaitingForStart() : PacketHeader(S2C_WAITFORSTART) {};
};

class PacketSendGameInfos : public PacketHeader
{
public:
	PacketSendGameInfos() : PacketHeader(S2C_GAMEINFOS){};
	int map;
	int team;
};

class PacketDisconnect : public PacketHeader
{
public:
	PacketDisconnect() : PacketHeader(S2C_DISCONNECT) {};
	int reason;
};

class PacketInput : public PacketHeader
{
public:
	PacketInput() : PacketHeader(C2S_INPUT) {};
	short lerp;
	float horizontalMove;
	float angle;
	int button;
};

class PacketSync : public PacketHeader
{

};

class PacketLoading : public PacketHeader
{
public:
	PacketLoading() : PacketHeader(C2S_COMMAND){}
};

class PacketSnapshot : public PacketHeader
{
public:
	PacketSnapshot() : PacketHeader(S2C_SNAPSHOT) {};
	snapshot snapshot;
};

#endif