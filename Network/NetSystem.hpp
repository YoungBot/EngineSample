//==========================================================
//NetSystem.hpp
//==========================================================
#pragma once
#ifndef _NETSYSTEM_HPP_
#define _NETSYSTEM_HPP_
//#include "Engine/Console/console_command.hpp"

//#include <WinSock2.h>

typedef unsigned char byte_t;

size_t const PACKET_MTU = 1400; // maximum transmission unit
struct addrinfo;
class NetPacketQueue;
class NetSession;
class UDPSocket;
class NetSystem
{
public:
	//NetSession *m_session;

	bool init(); // WSAStartup
	void deinit();
	UDPSocket* create_udp_socket(NetPacketQueue *queue, short port);
	

	void free_socket(UDPSocket*) {};

	NetSession* create_session();
	

	void destroy_session(NetSession* session );
	
	static void* NetAddressForHost(size_t outbuf_len, char const* hostName, char const* portName, bool bindable);
	static addrinfo* AllocAddressesForHost(const char* hostName, const char* portname);
	static void GetHostIP(char* buffer);
	
};

extern NetSystem* g_netSystem;



#endif