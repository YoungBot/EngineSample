//==========================================================
//NetMessage.hpp
//==========================================================
#pragma once
#ifndef _NETMESSAGE_HPP_
#define _NETMESSAGE_HPP_
#include <assert.h>
#include <vector>
#include <string>
typedef unsigned char unit8_t;
typedef unsigned char byte_t;
typedef unsigned int uint_t;
size_t const MESSAGE_MTU = 128;
size_t const PACKET_MTUU = 1400;
class NetConnection;
class NetMessage;
typedef void(*NetMessageCallback)(NetConnection* connection, NetMessage& msg);
class ByteBuffer
{
public:

	byte_t *m_buffer;
	byte_t *m_endOfBuffer;
	byte_t *m_currentReadPosition;
	size_t m_size;
	size_t m_maxSize;
	size_t read_idx;

	void init(void* buffer, size_t max_size);


	// When you write, you write to the end of the buffer
	// @return 
	//    true:  Was enough room and was written
	//    false: Not enough room, and was not written.
	bool write_bytes(void *data, size_t size);


	// Reads from buffer, copying data up to size into data
	// @return 
	//    number of bytes read, should equal size on success
	//    If less than size, there was not enough data.  
	//    Advanced read index either way.
	size_t read_bytes(void *out_data, size_t size);


	size_t get_length() const
	{
		return m_size;
	}

	void set_length(size_t len)
	{
		//assert(len <= m_size);
		m_size = len;
	}

	template<typename Tx>
	bool write(Tx const &v)
	{
		write_bytes(&v, sizeof(Tx));
	}

	template<typename Tx>
	bool read(Tx const &v)
	{
		return (read_bytes(&v, sizeof(Tx)) == sizeof(Tx));
	}
};
enum MessageType
{
	MESSAGE_TYPE_INVALID = -1,
	MESSAGE_TYPE_PING,
	MESSAGE_TYPE_PONG,
	MESSAGE_TYPE_HEARTBEAT,
	MESSAGE_TYPE_ACK,
	MESSAGE_TYPE_JOIN,
	MESSAGE_TYPE_ACCEPT,
	MESSAGE_TYPE_DENY,
	MESSAGE_TYPE_LEAVE,
	MESSAGE_TYPE_START_TEST,
	MESSAGE_TYPE_INORDER_TEST,
	MESSAGE_TYPE_FORCE_TEST,
	MESSAGE_TYPE_NUM
};
///----------------------------------------------------------
///
///----------------------------------------------------------
enum eNetMessageOptions
{
	eNMO_Reliable = (1 << 0),
	eNMO_Connectionless = (1<<1),
	eNMO_InOrder = (1<<2),

};
struct NetMessageDefinition
{
	NetMessageDefinition(MessageType id, NetMessageCallback cb, eNetMessageOptions options)
	{
		m_type = id;
		m_cb = cb;
		m_options = options;
	}
	MessageType m_type;
	NetMessageCallback m_cb;
	eNetMessageOptions m_options;

	bool IsConnectionless()
	{
		if (m_options == eNMO_Connectionless)
			return true;
		else
			return false;
	}
	bool IsReliable()
	{
		if (m_options == eNMO_Reliable)
			return true;
		else
			return false;
	}
	bool IsInOrder()
	{
		if (m_options == eNMO_InOrder)
			return true;
		else
			return false;
	}
};


//
//NetMessageRegister(eNetMessage_JoinRequest, OnJoinRequest, eNMO_Reliable);
//NetMessageRegister(eNetMessage_Ping, OnJoinRequest, eNMO_Connectionless);
//NetMessageRegister(eNetMessage_Pong, OnJoinRequest, eNMO_Connectionless);
//NetMessageRegister(eNetMessage_Heartbeat, OnJoinRequest, eNMO_Connectionless);

//void OnJoinRequest(net_sender_t const &from, NetMessage &msg);
//
//void NetJoin(NetAddress &addr)
//{
//	NetSession * sp = new NetSession();
//	sp->Start();
//	sp->Join(addr);
//}
///----------------------------------------------------------
///
///----------------------------------------------------------

class NetMessage : public ByteBuffer
{
public:
	byte_t buffer[MESSAGE_MTU];
	NetMessage();
	NetMessage(void *data, size_t data_len);
	NetMessage(MessageType type);
	NetMessage(MessageType type, void* data);
	bool AddMessage(void* newMessage, unsigned short messageLength);
	byte_t* get_buffer();
	MessageType GetType() { return m_type; }
	static void NetMessageRegister(MessageType id, NetMessageCallback cb, eNetMessageOptions options);
	void SetDefinitionsByType();
	NetMessageDefinition* GetMessageDefinition();
	//bool GetDefinition
	MessageType m_type;
	uint16_t m_reliableID;
	double m_lastTime;
	NetMessageDefinition* m_definition;

};
extern std::vector<NetMessageDefinition*> s_messageDefinitions;
#endif