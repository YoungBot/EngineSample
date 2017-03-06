//==========================================================
//UDPSocket.hpp
//==========================================================
#pragma once
#ifndef _UDPSOCKET_HPP_
#define _UDPSOCKET_HPP_

#include <WinSock2.h>


#include "Engine/Thread/Thread.hpp"
#include "Engine/Utility/Utility.hpp"


class NetPacketQueue;
class SocketThread;
class UDPSocket
{
private:
	bool m_running;
	SocketThread* m_service_thread;
	//SOCKET socket;
	//NetPacketQueue *queue;

public:
	UDPSocket(NetPacketQueue *queue, short port);

	void close();

	// Blocks on this socket until it's thead is finished
	void join();

	bool is_running();
	
};

class SocketThread: public CThread
{
private:
	SOCKET m_socket;
	short m_port;
	UDPSocket *m_owner;
	NetPacketQueue *m_queue;

	void CreateAndBindSocket();
	void ServiceSocket();
	void ProcessIncoming();
	void ProcessOutgoing();
	
protected:
	virtual void Run()
	{
		CreateAndBindSocket();
		if (m_socket != INVALID_SOCKET)
		{
			ServiceSocket();
			closesocket(m_socket);
		}
	}
	///----------------------------------------------------------
	///
	///----------------------------------------------------------
	public:
		SocketThread() {}
		void init(UDPSocket* owner, NetPacketQueue *queue, short port)
		{
			this->m_owner = owner;
			this->m_socket = INVALID_SOCKET;
			this->m_port = port;
			this->m_queue = queue;
		}
	
};

#endif
