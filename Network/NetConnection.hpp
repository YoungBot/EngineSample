#pragma once
//==========================================================
//NetConnection.hpp
//==========================================================

#pragma once
#ifndef _NETCONNECTION_HPP_
#define _NETCONNECTION_HPP_
#include <vector>
#include <queue>
#include "Engine/Network/BitArray.hpp"
class NetAddress;
class NetMessage;
class NetSession;
class NetPacket;
class ReliableTracker;
class NetConnection;

int const CONNECTION_RELIABLE_WINDOWSIZE = 4096;
int const CONNECTION_MAXRELIABLEID = 0xffff;

enum eConnectionState
{
	eConnectionState_Connected,
	eConnectionState_Disconnected,
};

struct net_sender_t
{
	NetSession* session;
	NetAddress* address;
	NetConnection* connection;
};
struct inOrderMessage
{
	uint16_t m_id;
	uint32_t m_value;
	inOrderMessage(uint16_t id,uint32_t value)
	{
		m_id = id;
		m_value = value;
	}
};

class NetConnection
{
public:
	NetConnection();
	NetConnection(void* addr);
	NetConnection(void* addr,NetSession* session);
	~NetConnection();
	//////////////////////////////////////////////////////////////////////////
	NetAddress* m_netAddress;
	unsigned short m_ackID;
	//unsigned short m_nextReliableID;
	double m_timeLastReceivedPacket;
	eConnectionState m_state;
	std::vector<NetMessage*> m_unsentUnreliablesMessages;
	std::vector<NetMessage*> m_unsentReliablesMessages;
	std::vector<NetMessage*> m_sentReliablesMessages;
	uint8_t m_connectionID;
	uint16_t m_oldestUsedReliableID;
	uint16_t m_nextReliableID;
	uint16_t m_nextOutgoingOrderID;
	uint16_t m_nextIncomingOrderID;
	TBitArray<CONNECTION_MAXRELIABLEID> m_sentReliablesIDs;
	TBitArray<CONNECTION_MAXRELIABLEID> m_receivedReliableIDs;
	std::vector<ReliableTracker*> m_trackers;
	std::vector<uint16_t> m_trackedAcks;
	std::vector<inOrderMessage> m_inOrders;
	std::string m_connectionName;
	uint16_t m_inOrderTestNumber;
	bool m_isHosting;
	bool m_isJoinable;
	bool m_willBeDestroied;
	//TBitArray<>
	//std::vector<NetMessage*> m_;
	float m_lastTimeSent;
	NetSession* m_session;
	//////////////////////////////////////////////////////////////////////////
	void SetNetAddress(NetAddress& address);
	void AddMessage(NetMessage* msg);
	void Tick();
	void CheckForDisconnect();
	void SendPacket();
	void IncrementAck(unsigned short m_ackID);
	NetPacket* PacketAllocate(unsigned short ackID);
	void SetState(eConnectionState state){ m_state = state; }
	eConnectionState IsConnected(){ return m_state; }
	bool ShouldSendHeartbeat();
	void SendHeartbeat();
	bool CanUseReliableID(uint16_t reliable_id);
	void SetSession(NetSession* session);
	void IncrementReliableID(uint16_t nextReliableID);
	void NetSessionSendPacket(NetSession* session, NetPacket* packet);
	void CleanupTrackers();
	void ProcessMessage();
	void ProcessPacket(NetPacket& packet);
	void MarkReliableID(ReliableTracker* tracker);
	bool CheckInorderID(uint16_t id);
	void SortInorders();
	NetMessage* CreateAckMessage();
	ReliableTracker* FindAndRemoveTracker(uint16_t ack);
	static NetConnection* FindConnectionByID(uint8_t ID);
	static NetConnection* FindConnectionByAddress(NetAddress* address);
	//bool IsMe() const { return m_session->me; }
	

};
extern std::vector<NetConnection*> g_netConnections;

#endif