//==========================================================
//NetSession.cpp
//==========================================================
#include "NetSession.hpp"
#include "NetSystem.hpp"
#include "NetPacket.hpp"
#include "Engine/Time/Time.hpp"
#include "NetConnection.hpp"
NetSession* g_gameSession = nullptr;
extern std::vector<std::string>* g_messages = nullptr;
class CThreadNetSession : public CThread
{
public:
	CThreadNetSession();
protected:
	virtual void Run();
private:
};
///----------------------------------------------------------
///
///----------------------------------------------------------

CThreadNetSession::CThreadNetSession()
{
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void CThreadNetSession::Run()
{
	//CreateSocket
	//SetNonblocking
	//while(haveSocket)
	//{
	//	SendOutgoing
	//	processIncoming
	//}
	//close
}

NetSession::NetSession()
	:m_frequency(0.0f)
{
	m_listening = false;
}
bool NetSession::Host(short port)
{
	UDPSocket *sock = g_netSystem->create_udp_socket(&packet_queue,port);
	sockets.push_back(sock);
	m_lastTimeRecv = GetCurrentSeconds();
	return true;
}

void NetSession::Listen(bool listening)
{
	m_listening = listening;
}

void NetSession::Shutdown()
{
	for (unsigned int i = 0; i < sockets.size(); ++i) {
		UDPSocket *sock = sockets[i];
		g_netSystem->free_socket(sock);
	}
	sockets.clear();

	m_listening = false;
}

void NetSession::Tick(std::vector<std::string>& messages)
{
	messages;
	NetPacket* currentPack = nullptr;
	currentPack = packet_queue.dequeue_read();
	while (currentPack!=nullptr)
	{
		if (CheckPacket(currentPack))
		{
			//std::string ip = "Message From: ";
			//ip.append(currentPack->GetIPv4FromPacket());
			//messages.push_back(ip);
			currentPack->m_currentReadPosition = currentPack->m_buffer;
			ProcessPacket(currentPack);
		}
		currentPack = packet_queue.dequeue_read();
		m_lastTimeRecv = GetCurrentSeconds();
	}
}

std::string NetSession::GetAddressString()
{
	return "hello";
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool NetSession::CheckPacket(NetPacket* packet)
{
	unsigned char ID;
	packet->read_bytes(&ID, 1);
	unsigned short ack;
	packet->read_bytes(&ack, 2);
	unsigned char messageCount;
	packet->read_bytes(&messageCount, 1);
	unsigned short totalLength = 4;
	for (unsigned char i = 0; i < messageCount; i ++)
	{
		unsigned short messageSize;
		packet->read_bytes(&messageSize, 2);
		totalLength += messageSize;
		packet->m_currentReadPosition += messageSize -2;
	}
	if (totalLength == packet->get_length())
		return true;
	else 
		return false;

	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetSession::SendPacket(NetPacket* packet)
{
	packet_queue.enqueue_write(packet);
}

void NetSession::SetSendFrequency(float hz)
{
	hz;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool NetSession::CanProcessMessage(net_sender_t &sender, NetMessage& msg)
{
	// Message Option:  CONNECTIONLESS
	if (!msg.m_definition->IsConnectionless() && sender.connection == nullptr) {
		return false;
	}

	// Message Option: RELIABLE
	if (msg.m_definition->IsReliable()) {
		NetConnection *cp = sender.connection;
		if (cp != nullptr) {
			if (cp->m_receivedReliableIDs.Get(msg.m_reliableID) == true) {
				return false;
			}
		}
	}

	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetSession::ProcessPacket(NetPacket* packet)
{
	
	packet_header_t header;
	packet->ReadHeader(header);


	net_sender_t sender;
	sender.connection = NetConnection::FindConnectionByAddress(&packet->addr);
	sender.session = this;
	sender.address = &packet->addr;
	bool shouldAck = false;
	shouldAck;
	if (sender.connection==nullptr)
	{
		NetConnection* connection = new NetConnection((sockaddr*)&packet->addr.addr);
		connection->m_connectionID = (uint8_t)g_netConnections.size();
		g_netConnections.push_back(connection);
		sender.connection = connection;
	}

	NetMessage* message = packet->ReadNextMessageFromPacket();
	bool track_ack = false;
	while (message!=nullptr)
	{
		ProcessMessage(sender.connection, message);
	
		track_ack = track_ack || (( (message->m_definition->IsReliable() || message->m_definition->IsInOrder()) && sender.connection != nullptr));

		
		delete message;
		message = packet->ReadNextMessageFromPacket();
	}

	if (track_ack && (header.ack != 0xffff/*invalidAck*/)) {
		if (sender.connection->m_trackedAcks.size() < 0xff) {
			sender.connection->m_trackedAcks.push_back(header.ack);
		}
	}
	//for (unsigned char i = 0; i < header.msg_count; i++)
	//{
	//	unsigned short messageSize;
	//	packet->read_bytes(&messageSize, 2);
	//	MessageType messageType;
	//	packet->read_bytes(&messageType, 1);
	//	if (messageType == MESSAGE_TYPE_PING)
	//	{
	//		continue;
	//	}
	//	if (messageType == MESSAGE_TYPE_PONG)
	//	{			
	//		continue;
	//	}
	//	if (messageType == MESSAGE_TYPE_ACCEPT)
	//	{
	//
	//		sender.connection->m_connectionID = 1;
	//		continue;
	//	}
	//	char mssg[1000];
	//	//currentPack->read_bytes(mssg, messageSize - 3);
	//	//mssg[messageSize - 3] = '\0';
	//	//std::string msg(mssg);
	//	//
	//	//messages.push_back(msg);
	//}

	

}

///----------------------------------------------------------
///
///----------------------------------------------------------

void NetSession::ProcessMessage(NetConnection* connection, NetMessage* msg)
{
	msg->m_definition->m_cb(connection, *msg);

}

void PingCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	connection->m_willBeDestroied = true;
	g_messages->push_back("a ping");
	return;
}
void PongCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	connection->m_willBeDestroied = true;
	g_messages->push_back("a pong");
	return;
}
void HeartbeatCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	connection;
	Beep(1000, 100);
	//g_messages->push_back("a heart beat");
	//connection->m_lastTimeSent = GetCurrentSeconds();
}
void AckCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	unsigned char acksNum;
	msg.read_bytes(&acksNum, 1);
	if (acksNum ==0)
	{
		return;
	}
	unsigned short* acks = new unsigned short[acksNum];
	memcpy(acks, msg.m_currentReadPosition, 2 * acksNum);
	for (int i = 0; i < acksNum; i++)
	{
		unsigned short currentAck = acks[i];
		ReliableTracker* currentTracker  = connection->FindAndRemoveTracker(currentAck);
		if (currentTracker!=nullptr)
		{
			connection->MarkReliableID(currentTracker);
			
		}
	}
	
	delete acks;
	g_messages->push_back("an ack");
	return;
}
void JoinRequestCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	//unsigned char reason = NetSession::CheckCanBeJoin();
	if (1)//ACCEPT
	{
		if (connection->m_connectionID==0)
		{
			return;
		}
		std::string requestName = "";
		unsigned char character;
		msg.read_bytes(&character, 1);
		while (character!='\0')
		{
			requestName.push_back(character);
			msg.read_bytes(&character, 1);
		}
		
		connection->m_connectionName = requestName;

		NetMessage* message = new NetMessage(MESSAGE_TYPE_ACCEPT);
		unsigned char maxConnection = 8;
		unsigned char myConnectionIndex = g_netConnections[0] ->m_connectionID;
		std::string hostName = g_netConnections[0]->m_connectionName;
		connection->m_connectionID = g_netConnections[0]->m_connectionID;
		//message->write_bytes(&connection->m_nextReliableID, 2);
		message->write_bytes(&maxConnection, 1);
		message->write_bytes(&connection->m_connectionID, 1);	
		message->write_bytes(&myConnectionIndex, 1);
		message->write_bytes((void*)hostName.c_str(), hostName.size()+1);
		connection->AddMessage(message);
		g_messages->push_back("a join request from someone");
	}
	//else
	//{
	//	NetMessage* message = new NetMessage(MESSAGE_TYPE_DENY);
	//	message->write_bytes(&reason, 1);
	//	NetPacket* pac = new NetPacket(0xff, 0xffff, (sockaddr*)&connection->m_netAddress->addr, sizeof(sockaddr_in));	
	//	pac->AddMessage(*message);
	//	pac->FinalizePackage();
	//	NetPacketQueue* queue = g_gameSession->GetOutGoingQueue();
	//	queue->enqueue_write(pac);
	//}

	return;
}
void JoinAcceptCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	unsigned char maxConnections;
	msg.read_bytes(&maxConnections, 1);
	unsigned char myConnectionIndex;
	msg.read_bytes(&myConnectionIndex, 1);
	connection->m_connectionID = myConnectionIndex;
	g_messages->push_back("a join accept");
	//msg.
	//connection->m_connectionID = 
	return;
}
void JoinDenyCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	for (std::vector<NetConnection*>::iterator connectionIter = g_netConnections.begin(); connectionIter != g_netConnections.end(); ++connectionIter)
	{
		if (*connectionIter == connection)
		{
			g_netConnections.erase(connectionIter);
			break;
		}
	}
	unsigned char reason;
	msg.read_bytes(&reason, 1);
	char numString[5];
	
	_itoa_s(reason,numString,1);
	std::string output = "a join deny reason: ";
	output.append(numString);
	g_messages->push_back(output);
	return;
}
void LeaveCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	for (std::vector<NetConnection*>::iterator connectionIter = g_netConnections.begin(); connectionIter != g_netConnections.end(); ++connectionIter)
	{
		if (*connectionIter == connection)
		{
			g_netConnections.erase(connectionIter);
			break;
		}
	}
	g_messages->push_back("a leave");
	return;
}

void StartTestCallback(NetConnection* connection, NetMessage& msg)
{
	connection;
	msg;
}
void InOrderCallback(NetConnection* connection, NetMessage& msg)
{
	msg;
	unsigned short inOrderID;
	msg.read_bytes(&inOrderID, 2);
	unsigned int value;
	msg.read_bytes(&value, 4);
	inOrderMessage newOrder(inOrderID, value);
	if (connection->CheckInorderID(inOrderID))
	{
		connection->m_inOrders.push_back(newOrder);
	}

	//std::string output = "an inOrder message, ID :";
	//char numString[10];
	//itoa(inOrderID, numString, 10);
	//output.append(numString);
	//output.append("value : ");
	//itoa(value, numString, 10);
	//output.append(numString);
	//g_messages->push_back(output);
}
void ForceTestCallback(NetConnection* connection, NetMessage& msg)
{
	connection;
	msg;
}

void NetSession::RegisterAllEngineNetMessages()
{
	NetMessage::NetMessageRegister(MESSAGE_TYPE_PING, PingCallback, eNMO_Connectionless);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_PONG, PongCallback, eNMO_Connectionless);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_HEARTBEAT, HeartbeatCallback, eNMO_Connectionless);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_ACK, AckCallback, eNMO_Connectionless);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_JOIN, JoinRequestCallback, eNMO_Reliable);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_ACCEPT, JoinAcceptCallback, eNMO_Reliable);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_DENY, JoinDenyCallback, eNMO_Connectionless);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_LEAVE, LeaveCallback, eNMO_Connectionless);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_START_TEST, StartTestCallback, eNMO_Reliable);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_INORDER_TEST, InOrderCallback, eNMO_InOrder);
	NetMessage::NetMessageRegister(MESSAGE_TYPE_FORCE_TEST, ForceTestCallback, eNMO_Reliable);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

unsigned char NetSession::CheckCanBeJoin()
{
	
	if (g_netConnections.size()<=0)
	{		
		return 0;//no connection
	}
	NetConnection* myConnection = NetConnection::FindConnectionByID(0);
	if (myConnection!=nullptr && myConnection->m_isJoinable ==false)
	{
		return 0;//no host
	}
	if (g_netConnections.size()>8)
	{
		return 1;//max connection
	}
	return 2;
}

