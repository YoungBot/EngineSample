//==========================================================
//NetPacketQueue.hpp
//==========================================================

#pragma once
#ifndef _NETPACKETQUEUE_HPP_
#define _NETPACKETQUEUE_HPP_
#include "Engine/Thread/ThreadSafeQueue.hpp"
#include "Engine/Network/NetMessage.hpp"
typedef unsigned char byte_t;
struct sockaddr;

class NetPacket;
class NetPacketQueue
{
private:
	CThreadSafeQueue<NetPacket*> incoming;
	CThreadSafeQueue<NetPacket*> outgoing;
public: 
	void enqueue_write(NetPacket *packet);
	
	void enqueue_write(byte_t *buffer, size_t len, sockaddr* addr, size_t addr_len);
	
	
	NetPacket* dequeue_write();
	
		
	void enqueue_read(NetPacket *packet);
	
	///----------------------------------------------------------
	///
	///----------------------------------------------------------
	
	void enqueue_read(byte_t *buffer, size_t len, sockaddr* addr, size_t addr_len);
	

	NetPacket* dequeue_read();
	
	static NetPacket* createPingPack(sockaddr* addr);
	static NetPacket* createPongPack(sockaddr* addr);
	//static NetPacket* createHeartbeatPack(sockaddr* addr);
	static NetPacket* createPackTest(sockaddr* addr);
	static NetPacket* createPack(NetMessage& message, sockaddr* addr);
};

#endif