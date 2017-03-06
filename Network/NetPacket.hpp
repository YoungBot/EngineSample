//==========================================================
//NetPacket.hpp
//==========================================================
#pragma once
#ifndef _NETPACKET_HPP_
#define _NETPACKET_HPP_

#include "NetAddress.hpp"
#include "NetMessage.hpp"
//#include "NetSystem.hpp"
#include <assert.h>
#include <string>
struct packet_header_t 
{ 
	uint16_t ack; 
	uint8_t connection_idx; 
	uint8_t msg_count; 
};

class NetPacket : public ByteBuffer
{
public:
	byte_t buffer[PACKET_MTUU];
	NetAddress addr;
	unsigned char messageCount;
	unsigned char connectionID;
	NetPacket();
	NetPacket(sockaddr* saddr, size_t addrlen);
	NetPacket(void *data, size_t data_len, sockaddr* saddr, size_t addrlen);
	NetPacket(unsigned short ackID, sockaddr* saddr, size_t addrlen);
	NetPacket(unsigned char connectID, unsigned short ackID, sockaddr* saddr, size_t addrlen);

	byte_t* get_buffer();
	bool AddMessage(NetMessage& newMessage);
	inline NetAddress const* get_address() const { return &addr; }
	void FinalizePackage();
	std::string GetIPv4FromPacket();
	void ReadHeader(packet_header_t& header);
	NetMessage* ReadNextMessageFromPacket();
};


#endif