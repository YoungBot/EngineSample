//==========================================================
//NetPacketQueue.cpp
//==========================================================
#include "NetPacketQueue.hpp"
#include "NetPacket.hpp"
void NetPacketQueue::enqueue_write(NetPacket *packet)
{
	outgoing.Enqueue(packet);
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void NetPacketQueue::enqueue_write(byte_t *buffer, size_t len, sockaddr* addr, size_t addr_len)
{
	NetPacket *packet = new NetPacket(buffer, len, addr, addr_len);
	packet->set_length(len);
	enqueue_write(packet);
}
///----------------------------------------------------------
///
///----------------------------------------------------------
NetPacket* NetPacketQueue::dequeue_write()
{
	NetPacket *packet = nullptr;
	if (outgoing.Dequeue(&packet))
	{
		return packet;
	}
	return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void NetPacketQueue::enqueue_read(NetPacket *packet)
{
	incoming.Enqueue(packet);
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void NetPacketQueue::enqueue_read(byte_t *buffer, size_t len, sockaddr* addr, size_t addr_len)
{
	NetPacket *packet = new NetPacket(buffer, len, addr, addr_len);
	packet->set_length(len);
	enqueue_read(packet);
}
///----------------------------------------------------------
///
///----------------------------------------------------------
NetPacket* NetPacketQueue::dequeue_read()
{
	NetPacket* packet = nullptr;
	if (incoming.Dequeue(&packet))
	{
		return packet;
	}
	return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NetPacket* NetPacketQueue::createPingPack(sockaddr* addr)
{
	//NetPacket* pac = new NetPacket("1234", 4, (sockaddr*)(&addr), sizeof(addr));
	NetPacket* pac = new NetPacket(0xff,1,addr, sizeof(sockaddr_in));
	NetMessage* msg = new NetMessage(MESSAGE_TYPE_PING);
	pac->AddMessage(*msg);
	pac->FinalizePackage();
	return pac;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NetPacket* NetPacketQueue::createPongPack(sockaddr* addr)
{
	NetPacket* pac = new NetPacket(addr, sizeof(sockaddr_in));
	NetMessage* msg = new NetMessage(MESSAGE_TYPE_PONG);
	pac->AddMessage(*msg);
	pac->FinalizePackage();
	return pac;
}

NetPacket* NetPacketQueue::createPackTest(sockaddr* addr)
{
	NetMessage* msg = new NetMessage("YoungBot", 8);

	NetPacket* pac = new NetPacket(0xff,0,addr, sizeof(sockaddr_in));
	pac->AddMessage(*msg);
	//msg = new NetMessage("Hello", 5);
	//pac->AddMessage(*msg);
	//msg = new NetMessage("I AM MAL'GANIS! I AM ETERNAL!!", 30);
	//pac->AddMessage(*msg);
	pac->FinalizePackage();
	return pac;
}

NetPacket* NetPacketQueue::createPack(NetMessage& message, sockaddr* addr)
{
	NetPacket* pac = new NetPacket(addr, sizeof(sockaddr_in));
	pac->AddMessage(message);
	pac->FinalizePackage();
	return pac;
}
