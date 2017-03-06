//==========================================================
//NetSession.hpp
//==========================================================
#pragma once
#ifndef _NETSESSION_HPP_
#define _NETSESSION_HPP_

#include <vector>
#include <string>
#include "NetPacketQueue.hpp"
#include "Engine/Thread/Thread.hpp"
//#include <WS2tcpip.h>

class UDPSocket;
class CThreadNetSession;
class NetMessage;
class NetConnection;
struct net_sender_t;

class NetSession
{
public:
	NetSession();
	bool Host(short port);
	void Listen(bool listening);
	void Shutdown();
	void Tick(std::vector<std::string>& messages);
	//char const *get_host_addr_name() const {return};
	std::string GetAddressString();
	NetPacketQueue* GetOutGoingQueue() { return &packet_queue; }
	bool CheckPacket(NetPacket* packet);
	void SendPacket(NetPacket* packet);
	void SetSendFrequency(float hz);
	double GetLastTimeRecv() { return m_lastTimeRecv; }
	bool CanProcessMessage(net_sender_t &sender, NetMessage& msg);
	void ProcessPacket(NetPacket* packet);
	void ProcessMessage(NetConnection* connection, NetMessage *msg);
	static void RegisterAllEngineNetMessages();
	static unsigned char CheckCanBeJoin();
private:
	NetPacketQueue packet_queue;
	std::vector<UDPSocket*> sockets;
	CThreadNetSession* m_thread;
	bool m_listening;
	float m_frequency;
	double m_lastTimeRecv;
};
extern NetSession* g_gameSession;
extern std::vector<std::string>* g_messages;
#endif