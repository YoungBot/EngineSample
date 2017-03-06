//==========================================================
//NetSystem.cpp
//==========================================================
#include "NetSystem.hpp"
#include <WS2tcpip.h>
#include "NetSession.hpp"
#include "UDPSocket.hpp"
#include <iostream>
#include "Engine/Console/console_command.hpp"

#pragma comment(lib,"ws2_32.lib")
NetSystem* g_netSystem = nullptr;
bool NetSystem::init()
{
	g_netSystem = this;
	WSADATA wsa_data;
	int error = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (error == 0) {
		//local_host_name = AllocLocalHostName();
		return true;
	}
	else {
		std::cout << "Failed to initialize WinSock.  Error[%u]: %s\n" << error;
		return false;
	}
}

UDPSocket* NetSystem::create_udp_socket(NetPacketQueue *queue, short port)
{
	UDPSocket *sock = new UDPSocket(queue, port);
	return sock;
}

void NetSystem::deinit()
{
	WSACleanup();
}

NetSession* NetSystem::create_session()
{
	return new NetSession();
}

void NetSystem::destroy_session(NetSession* session)
{
	free(session);
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void* NetSystem::NetAddressForHost(size_t outbuf_len, char const* hostName, char const* portName, bool bindable)
{
	bindable;
	outbuf_len;
	//char portname[16];

	addrinfo* address = AllocAddressesForHost(hostName, portName);
	
	//size_t c = 0;
	//addr = address->ai_addr;
	
	return address->ai_addr;
}

addrinfo* NetSystem::AllocAddressesForHost(const char* hostName, const char* portname)
{

	addrinfo hints;
	addrinfo *addr;


	memset(&hints, 0, sizeof(hints));

	// Which network layer it's using - usually want to UNSPEC, since it doesn't matter.  But since we're hard coding
	// the client sides connection, we will likely want to use AF_INET when we want to bind an address
	hints.ai_family = AF_UNSPEC;

	hints.ai_socktype = SOCK_STREAM; // STREAM based, determines transport layer (TCP)
	hints.ai_flags = AI_PASSIVE; // used for binding/listening

	int status = getaddrinfo(hostName, portname, &hints, &addr);
	status;
	return addr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void NetSystem::GetHostIP(char* buffer)
{
	gethostname(buffer, 256);
}
