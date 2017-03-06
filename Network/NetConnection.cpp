//==========================================================
//NetConnection.cpp
//==========================================================
#include "NetConnection.hpp"
#include "NetAddress.hpp"
#include "NetPacket.hpp"
#include "NetSession.hpp"
#include "Engine/Time/Time.hpp"

double const CONNECTION_TIMEFORDISCONNECT = 30.0f;
double const CONNECTION_HEARTBEATTIME = 3.0f;
float const TRACKER_MAX_AGE = 10.0f;
float const NETMESSAGE_RESEND_TIME = 0.1f;
std::vector<NetConnection*> g_netConnections;


class ReliableTracker
{
public:
	ReliableTracker(uint16_t ack, size_t count)
	{
		m_timeCreated = GetCurrentSeconds();
		m_packetAck = ack;
		m_reliableIDs.reserve(count);
	}
	double m_timeCreated;
	uint16_t m_packetAck;
	std::vector<uint16_t> m_reliableIDs;

};

NetConnection::NetConnection()
	:m_ackID(0)
	,m_lastTimeSent((float)GetCurrentSeconds())
	, m_timeLastReceivedPacket((float)GetCurrentSeconds())
	, m_state(eConnectionState_Disconnected)
	,m_session(g_gameSession)
	, m_connectionID(0xff)
	, m_nextReliableID(0)
	, m_oldestUsedReliableID(0)
	, m_connectionName("")
	, m_isHosting(false)
	, m_isJoinable(false)
	, m_willBeDestroied(false)
	,m_nextOutgoingOrderID(0)
	,m_nextIncomingOrderID(0)
{
	m_unsentUnreliablesMessages.clear();
}

NetConnection::NetConnection(void* addr)
	: m_ackID(0)
	, m_lastTimeSent((float)GetCurrentSeconds())
	,m_timeLastReceivedPacket((float)GetCurrentSeconds())
	, m_state(eConnectionState_Disconnected)
	,m_session(g_gameSession)
	, m_connectionID(0xff)
	, m_nextReliableID(0)
	, m_oldestUsedReliableID(0)
	, m_connectionName("")
	, m_isHosting(false)
	, m_isJoinable(false)
	, m_willBeDestroied(false)
	, m_nextOutgoingOrderID(0)
	, m_nextIncomingOrderID(0)
{
	m_unsentUnreliablesMessages.clear();
	NetAddress* address = new NetAddress();
	address->init((sockaddr*)addr, sizeof(sockaddr));
	m_netAddress = address;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NetConnection::NetConnection(void* addr, NetSession* session)
	: m_ackID(0)
	, m_lastTimeSent((float)GetCurrentSeconds())
	, m_timeLastReceivedPacket((float)GetCurrentSeconds())
	, m_state(eConnectionState_Disconnected)
	, m_session(session)
	, m_connectionID(0xff)
	,m_nextReliableID(0)
	,m_oldestUsedReliableID(0)
	, m_connectionName("")
	, m_isHosting(false)
	, m_isJoinable(false)
	, m_willBeDestroied(false)
	, m_nextOutgoingOrderID(0)
	, m_nextIncomingOrderID(0)
{
	m_unsentUnreliablesMessages.clear();
	NetAddress* address = new NetAddress();
	address->init((sockaddr*)addr, sizeof(sockaddr));
	m_netAddress = address;
}
NetConnection::~NetConnection()
{
	// CLEAN UP MEMORY STILL IN THESE QUEUES //
	/*
	queue<NetMessage*> m_unsentReliables;
	queue<NetMessage*> m_sentReliables;
	vector<NetMessage*> m_unsentUnreliables;
	queue<ReliableTracker*> m_trackers;
	*/
}

void NetConnection::SetNetAddress(NetAddress& address)
{
	NetAddress* myAddress = new NetAddress(address);
	m_netAddress = myAddress;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::AddMessage(NetMessage* msg)
{
	//NetMessage* newMessage = new NetMessage(*msg);
	NetMessageDefinition *defn= msg->GetMessageDefinition();
	if(defn->m_options & eNMO_Reliable || defn->m_options & eNMO_InOrder)
		m_unsentReliablesMessages.push_back(msg);
	else
		m_unsentUnreliablesMessages.push_back(msg);
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::Tick()
{
	m_timeLastReceivedPacket = g_gameSession->GetLastTimeRecv();
	this->CheckForDisconnect();
	if (!this->IsConnected() ==  eConnectionState_Disconnected)
	{
		return;
	}

	if (ShouldSendHeartbeat())
	{
		SendHeartbeat();
	}

	CleanupTrackers();
	
	SendPacket();
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::CheckForDisconnect()
{
	double currentTime = GetCurrentSeconds();
	double age = currentTime - this->m_timeLastReceivedPacket;
	if (age > CONNECTION_TIMEFORDISCONNECT)
	{
		SetState(eConnectionState_Disconnected);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::IncrementAck(unsigned short ackID)
{
	ackID;
	++m_ackID;
	if (m_ackID == 0) {
		++m_ackID;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::SendPacket()
{
	NetPacket* packet = PacketAllocate(m_ackID);
	packet->connectionID = g_netConnections[0]->m_connectionID;
	IncrementAck(m_ackID);

	//std::vector<NetMessage*> reliablesSentThisFrame;
	std::queue<NetMessage*> reliablesSentThisFrame;

	while (m_sentReliablesMessages.size() > 0)
	{
		NetMessage *msg = m_sentReliablesMessages.front();

		if (m_sentReliablesIDs.Get(msg->m_reliableID) == false)
		{
			m_sentReliablesMessages.erase(m_sentReliablesMessages.begin());//DEQUEUE
			//delete msg;
		}
		else
		{
			// Resend if it has passed resend age
			float age = (float)(GetCurrentTime() - msg->m_lastTime);
			if (age >= NETMESSAGE_RESEND_TIME) {
				if (packet->AddMessage(*msg)) {
					m_sentReliablesMessages.erase(m_sentReliablesMessages.begin());
					reliablesSentThisFrame.push(msg);
				}
				else
				{
					break;
				}
			}
			else {
				break;
			}
		}
	}

		while (m_unsentReliablesMessages.size() > 0)
		{
			NetMessage* msg = m_unsentReliablesMessages.front();
			uint16_t reliable_id = m_nextReliableID;
			if (!CanUseReliableID(m_nextReliableID))
			{
				break;
			}
			msg->m_reliableID = reliable_id;
			if (packet->AddMessage(*msg))
			{
				IncrementReliableID(m_nextReliableID);
				m_unsentReliablesMessages.pop_back();
				reliablesSentThisFrame.push(msg);
				m_sentReliablesIDs.Set(msg->m_reliableID);
			}
			else
				break;
		}

		if (m_trackedAcks.size() != 0)
		{
			NetMessage* message = CreateAckMessage();
			packet->AddMessage(*message);
			m_trackedAcks.clear();
		}

		for (unsigned int i = 0; i < m_unsentUnreliablesMessages.size(); i++)
		{
			packet->AddMessage(*m_unsentUnreliablesMessages[i]);
		}

		NetSessionSendPacket(m_session, packet);

		if (reliablesSentThisFrame.size() > 0)
		{
			ReliableTracker * tracker = new ReliableTracker(m_ackID, reliablesSentThisFrame.size());
			while (reliablesSentThisFrame.size() > 0)
			{
				NetMessage* msg = reliablesSentThisFrame.front();
				reliablesSentThisFrame.pop();
				tracker->m_reliableIDs.push_back(msg->m_reliableID);
				m_trackers.push_back(tracker);
				msg->m_lastTime = GetCurrentSeconds();
				m_sentReliablesMessages.push_back(msg);
			}
		}
	
}


NetPacket* NetConnection::PacketAllocate(unsigned short ackID)
{
	NetPacket* pack = new NetPacket(m_connectionID,ackID,(sockaddr*)&m_netAddress->addr,m_netAddress->length);
	return pack;
}



bool NetConnection::ShouldSendHeartbeat()
{
	if (m_connectionID==0xff)
	{
		return false;
	}
	double current_time = GetCurrentSeconds();
	double age = current_time - this->m_lastTimeSent;
	if ( age > CONNECTION_HEARTBEATTIME)
	{
		m_lastTimeSent = (float)GetCurrentSeconds();
		return true;
	}
	return false;
}

void NetConnection::SendHeartbeat()
{
	NetMessage msg(MESSAGE_TYPE_HEARTBEAT);
	NetPacket* packet = new NetPacket(m_connectionID,m_ackID,(sockaddr*)(&m_netAddress->addr), m_netAddress->length);
	packet->AddMessage(msg);
	packet->FinalizePackage();
	g_gameSession->SendPacket(packet);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool NetConnection::CanUseReliableID(uint16_t reliable_id)
{
	if (reliable_id < m_oldestUsedReliableID)
	{
		reliable_id += CONNECTION_MAXRELIABLEID;
	}
	uint16_t distance =reliable_id - m_oldestUsedReliableID;
	return distance < CONNECTION_RELIABLE_WINDOWSIZE;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::SetSession(NetSession* session)
{
	m_session = session;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::IncrementReliableID(uint16_t nextReliableID)
{
	nextReliableID;
	++m_nextReliableID;
	if (CONNECTION_MAXRELIABLEID == m_nextReliableID) {
		++m_nextReliableID;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::NetSessionSendPacket(NetSession* session, NetPacket* packet)
{
	packet->FinalizePackage();
	if (packet->messageCount>0)
	{
		session->SendPacket(packet);
	}
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::CleanupTrackers()
{
	while (m_trackers.size()>0)
	{
		ReliableTracker* tracker = m_trackers.front();
		
		if (tracker != nullptr)
		{
			float age = (float)GetCurrentSeconds() - (float)tracker->m_timeCreated;
			if (age >= TRACKER_MAX_AGE)
			{
				m_trackers.pop_back();//pop
				//delete tracker;
			}
			else
			{
				return;
			}
		}
	}
}

void NetConnection::ProcessPacket(NetPacket& packet)
{
	packet;
	m_timeLastReceivedPacket = GetCurrentTime();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::MarkReliableID(ReliableTracker* currentTracker)
{
	for (unsigned int i = 0; i < currentTracker->m_reliableIDs.size(); i++)
	{
		m_sentReliablesIDs.Unset(currentTracker->m_reliableIDs[i]);
	}

}

bool NetConnection::CheckInorderID(uint16_t id)
{
	for (unsigned int i = 0; i < m_inOrders.size(); i++)
	{
		if (m_inOrders[i].m_id == id)
		{
			return false;
		}
	}
	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetConnection::SortInorders()
{
	for (unsigned int i = 0; i < m_inOrders.size()-1; i++)
	{
		for (unsigned int j = i + 1; j < m_inOrders.size(); j++)
		{
			if (m_inOrders[i].m_id > m_inOrders[j].m_id)
			{
				inOrderMessage temp(m_inOrders[i]);
				m_inOrders[i] = m_inOrders[j];
				m_inOrders[j] = temp;
			}
		}
	}
}

///----------------------------------------------------------
///
///----------------------------------------------------------

NetMessage* NetConnection::CreateAckMessage()
{
	NetMessage* message = new NetMessage(MESSAGE_TYPE_ACK);
	unsigned char acksNum = (unsigned char)m_trackedAcks.size();
	message->write_bytes(&acksNum, 1);
	for (unsigned int i = 0; i < m_trackedAcks.size(); i++)
	{
		message->write_bytes(&m_trackedAcks[i],2);
	}
	return message;
}

///----------------------------------------------------------
///
///----------------------------------------------------------

ReliableTracker* NetConnection::FindAndRemoveTracker(uint16_t ack)
{
	for (std::vector<ReliableTracker*>::iterator trackerIter = m_trackers.begin(); trackerIter != m_trackers.end();++trackerIter)
	{
		ReliableTracker* tracker = *trackerIter;
		if (tracker->m_packetAck == ack)
		{
			m_trackers.erase(trackerIter);
			return tracker;
		}
	}
	return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
NetConnection* NetConnection::FindConnectionByID(uint8_t ID)
{
	for (unsigned int i = 0; i < g_netConnections.size(); i++)
	{
		if (g_netConnections[i]->m_connectionID == ID)
		{
			return g_netConnections[i];
		}
	}
	return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NetConnection* NetConnection::FindConnectionByAddress(NetAddress* address)
{
	for (unsigned int i = 0; i < g_netConnections.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (address->addr.__ss_pad1[j] != g_netConnections[i]->m_netAddress->addr.__ss_pad1[j])
			{
				goto returnNull;
			}		
		}
		return g_netConnections[i];
	returnNull:;
	}
	return nullptr;
}

///----------------------------------------------------------
///
///----------------------------------------------------------
// OnProcessAck
// net_sender_t &from
// NetMessage &msg
// 0 options - requires connection, and it is NOT reliable
//NET_MESSAGE(eMessageType_Ack)
//{
//	NetConnection *cp = from.connection;
//	if (cp == nullptr) {
//		return;
//	}
//
//	uint8_t ack_count;
//	msg.read<uint8_t>(&ack_count);
//
//	while (ack_count > 0) {
//		uint16_t ack;
//		msg.read<uint16_t>(&ack);
//
//		ReliableTracker *tracker = cp->FindAndRemoveTracker(ack);
//			if (tracker != nullptr) {
//				for (int i = 0; i < tracker->m_reliableIDs.size(); ++i) {
//					uint16_t reliable_id = tracker->m_reliableIDs[i];
//					cp->m_sentReliablesIDs.unset(reliable_id);
//				}
//
//				delete tracker;
//			}
//		--ack_count;
//	}
//}

//
