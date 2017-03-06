//==========================================================
//NetMessage.cpp
//==========================================================
#include "NetMessage.hpp"
std::vector<NetMessageDefinition*> s_messageDefinitions;
void ByteBuffer::init(void* buffer, size_t max_size)
{
	
	m_maxSize = max_size;
	m_buffer = (byte_t*)buffer;
	m_endOfBuffer = m_buffer;
	m_currentReadPosition = m_buffer;
	m_size = 0;
	read_idx = 0;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
bool ByteBuffer::write_bytes(void *data, size_t size)
{
	if (size + m_size > m_maxSize)
	{
		return false;
	}
	else
	{
		memcpy(m_endOfBuffer, data, size);
		m_size += size;
		m_endOfBuffer += size;
		return true;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------
size_t ByteBuffer::read_bytes(void *out_data, size_t size)
{
	
	if (size < m_size)
	{
		memcpy(out_data, m_currentReadPosition, size);
		m_currentReadPosition += size;
		return size;
	}
	else
	{
		memcpy(out_data,m_buffer, m_size);
		return m_size;
	}

}
///----------------------------------------------------------
///
///----------------------------------------------------------

NetMessage::NetMessage()
	:m_type(MESSAGE_TYPE_PING)
	,m_definition(nullptr)
{
	init(buffer, PACKET_MTUU);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NetMessage::NetMessage(void *data, size_t data_len)
	:m_type(MESSAGE_TYPE_JOIN)
	, m_definition(nullptr)
{
	init(buffer, PACKET_MTUU);
	//AddMessage(data, data_len);
	m_reliableID = 0;
	//write_bytes(&m_reliableID, 2);
	write_bytes(data, data_len);
	char null = '\0';
	write_bytes(&null, 1);
	SetDefinitionsByType();
}

NetMessage::NetMessage(MessageType type)
	:m_type(type)
	,m_definition(nullptr)
	,m_reliableID(0)
{
	init(buffer, PACKET_MTUU);
	SetDefinitionsByType();
	SetDefinitionsByType();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NetMessage::NetMessage(MessageType type, void* data)
	:m_type(type)
	, m_definition(nullptr)
{
	init(buffer, PACKET_MTUU);
	//AddMessage(data, data_len);
	m_reliableID = 0;
	byte_t* currentPosition = (byte_t*)data;

	unsigned short messageSize;
	memcpy(&messageSize, currentPosition, 2);
	currentPosition += 2;

	MessageType messageType;
	memcpy(&messageType, currentPosition, 1);
	currentPosition++;
	memcpy(&m_reliableID, currentPosition, 2);

	write_bytes(&m_reliableID, 2);
	
	char null = '\0';
	write_bytes(&null, 1);
	SetDefinitionsByType();
}

///----------------------------------------------------------
///
///----------------------------------------------------------

bool NetMessage::AddMessage(void* newData, unsigned short messageLength)
{
	newData;
	messageLength;
	return true;
	
}

byte_t* NetMessage::get_buffer()
{
	//buffer[0] = m_size>>8 + 2; //right shift 8
	//buffer[1] = m_size & 0xffff;
	//buffer[2] = 1; //type
	//memcpy(&buffer[3], m_buffer, m_size);
	return buffer;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void NetMessage::NetMessageRegister(MessageType id, NetMessageCallback cb, eNetMessageOptions options)
{
	NetMessageDefinition* newDefinition = new NetMessageDefinition(id, cb, options);
	s_messageDefinitions.push_back(newDefinition);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetMessage::SetDefinitionsByType()
{
	for (unsigned int i = 0; i < s_messageDefinitions.size(); i++)
	{
		if (s_messageDefinitions[i]->m_type == m_type)
		{
			m_definition = s_messageDefinitions[i];
			return;
		}
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NetMessageDefinition* NetMessage::GetMessageDefinition()
{
	return m_definition;
}

