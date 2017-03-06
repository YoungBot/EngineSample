//==========================================================
//NetPacket.cpp
//==========================================================
#include "NetPacket.hpp"


NetPacket::NetPacket()
	:messageCount(0)
	, connectionID(0xff)
{
	ByteBuffer::init(buffer, PACKET_MTUU);
}

NetPacket::NetPacket(void *data, size_t data_len, sockaddr* saddr, size_t addrlen)
	: messageCount(0)
	, connectionID(0xff)
{
	ByteBuffer::init(buffer, PACKET_MTUU);
	write_bytes(data, data_len);
	addr.init(saddr, addrlen);
	//unsigned short ack = 0xffff;
	//write_bytes(&ack, 2);
	//write_bytes(&messageCount, 1);

}

NetPacket::NetPacket(sockaddr* saddr, size_t addrlen)
	:messageCount(0)
	, connectionID(0xff)
{
	ByteBuffer::init(buffer, PACKET_MTUU);
	addr.init(saddr, addrlen);
	unsigned short ack = 0xffff;
	write_bytes(&connectionID, 1);
	write_bytes(&ack, 2);
	write_bytes(&messageCount, 1);
}

NetPacket::NetPacket(unsigned short ackID, sockaddr* saddr, size_t addrlen)
	:messageCount(0)
	, connectionID(0xff)
{
	ByteBuffer::init(buffer, PACKET_MTUU);
	addr.init(saddr, addrlen);
	unsigned short ack = ackID;
	write_bytes(&connectionID, 1);
	write_bytes(&ack, 2);
	write_bytes(&messageCount, 1);
}

NetPacket::NetPacket(unsigned char connectID, unsigned short ackID, sockaddr* saddr, size_t addrlen)
	:messageCount(0)
	, connectionID(connectID)
{
	ByteBuffer::init(buffer, PACKET_MTUU);
	addr.init(saddr, addrlen);
	unsigned short ack = ackID;
	write_bytes(&connectionID, 1);
	write_bytes(&ack, 2);
	write_bytes(&messageCount, 1);
}

byte_t* NetPacket::get_buffer()
{
	return buffer;
}

bool NetPacket::AddMessage(NetMessage& newMessage)
{
	unsigned short messageSize = (unsigned short)newMessage.m_size + 3;
	if (newMessage.GetMessageDefinition()->IsReliable() || newMessage.GetMessageDefinition()->IsInOrder())
	{
		messageSize += 2;
	}
	write_bytes(&messageSize, 2);
	byte_t messageType = (byte_t)newMessage.m_type;
	write_bytes(&messageType, 1);
	if (newMessage.GetMessageDefinition()->IsReliable() || newMessage.GetMessageDefinition()->IsInOrder())
	{
		unsigned short reliableID = newMessage.m_reliableID;
		write_bytes(&reliableID, 2);
	}
	
	
	if (write_bytes(newMessage.m_buffer, newMessage.m_size))
	{
		messageCount++;
		return true;
	}	
	else
		return false;
	//write_bytes(newMessage.get_buffer(), newMessage.m_size+3);
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetPacket::FinalizePackage()
{
	m_buffer[0] = connectionID;
	m_buffer[3] = messageCount;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

std::string NetPacket::GetIPv4FromPacket()
{
	unsigned char ipInt[6];
	std::string ipString;
	char ipChar[10];
	for (int i = 0; i < 6; i++)
	{
		unsigned char ip = addr.addr.__ss_pad1[i];
		ipInt[i] = ip;
	}
	for (int i = 2; i < 6; i++)
	{	
		_itoa_s(ipInt[i], ipChar,10);
		ipString.append(ipChar);
		if (i!=5)
		{
			ipString.push_back('.');
		}
	}
	ipString.push_back(':');
	unsigned short portShort = ipInt[0] * 256 + ipInt[1];
	char port[10];
	_itoa_s(portShort, port, 10);
	ipString.append(port);
	return ipString;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetPacket::ReadHeader(packet_header_t& header)
{
	read_bytes(&header.connection_idx, 1);
	read_bytes(&header.ack, 2);
	read_bytes(&header.msg_count, 1);
}

NetMessage* NetPacket::ReadNextMessageFromPacket()
{
	unsigned short messageLength;
	unsigned char messageType;
	//m_currentReadPosition = m_buffer + 4;

	if (m_currentReadPosition + (byte_t)2 - m_buffer > m_size)
	{
		return nullptr;
	}

	read_bytes(&messageLength, 2);
	read_bytes(&messageType, 1);
	NetMessage* message = new NetMessage((MessageType)messageType);
	if (message->m_definition->IsReliable() || message->m_definition->IsInOrder())
	{
		read_bytes(&message->m_reliableID, 2);
		void* data = message->buffer;
		size_t data_len = messageLength - 5;
		read_bytes(data, data_len);
		message->write_bytes(data, data_len);
	}
	else
	{
		void* data = message->buffer;
		size_t data_len = messageLength - 3;
		read_bytes(data, data_len);
		message->write_bytes(data, data_len);
	}
	return message;
}
