//==========================================================
//UDPSocket.cpp
//==========================================================
#include "UDPSocket.hpp"
#include "Engine/Network/NetSystem.hpp"
#include "Engine/Network/NetPacketQueue.hpp"
#include "Engine/Network/NetAddress.hpp"
#include "Engine/Network/NetPacket.hpp"
UDPSocket::UDPSocket(NetPacketQueue *queue, short port)
{
	m_running = true;
	m_service_thread = new SocketThread();
	m_service_thread->init(this, queue, port);
	m_service_thread->Start("serviceThread");
}

void UDPSocket::close() 
{ 
	m_running = false; 
}

// Blocks on this socket until it's thead is finished
void UDPSocket::join()
{
	close();
	m_service_thread->Join();
}
bool UDPSocket::is_running() 
{ 
	return m_running; 
}

void SocketThread::CreateAndBindSocket()
{
	m_socket = INVALID_SOCKET;
	SOCKET sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	FATAL_ASSERTION(sock != INVALID_SOCKET, "FAILED");

	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(m_port);
	addr.sin_family = AF_INET;

	int status = bind(sock, (sockaddr*)&addr, sizeof(addr));
	if (status == SOCKET_ERROR)
	{
		//FATAL_ASSERTION(sock != INVALID_SOCKET, "FAILED TO BIND ADDRESS : i%", WSAGetLastError());
		closesocket(sock);
		return;
	}

	m_socket = sock;

	unsigned long non_blocking = 1;
	ioctlsocket(m_socket, FIONBIO, &non_blocking);
}

void SocketThread::ServiceSocket()
{

	while (m_owner->is_running()) {
		// Try to recv data, read until nothing there
		// or it errored out
		ProcessIncoming();
		ProcessOutgoing();

		ThreadYield();
	}

}

void SocketThread::ProcessIncoming()
{
	byte_t buffer[PACKET_MTU];
	sockaddr_storage their_addr;
	bool close_self = false;
	while (!close_self)
	{
		size_t addrlen = sizeof(their_addr);
		int recvd = recvfrom(m_socket,   // socket we're reading on
			(char*)buffer,                    // buffer to read into 
			PACKET_MTU,                // max size of buffer
			0,                         // options
			(sockaddr*)&their_addr,    // Address we received from on success
			(int*)&addrlen);

		if (recvd > 0)
		{
			m_queue->enqueue_read(buffer, recvd, (sockaddr*)&their_addr, addrlen);
		}
		else if (recvd < 0)
		{
			int error = WSAGetLastError();
			switch (error)
			{
			case WSAEWOULDBLOCK:
			case WSAEMSGSIZE:
				break;
			default:
				m_owner->close();
			};
			return;
		}
		else
		{
			m_owner->close();
		}

	}
}

void SocketThread::ProcessOutgoing()
{
	NetPacket *packet = m_queue->dequeue_write();
	while (nullptr != packet) {
		const NetAddress *address = packet->get_address();
		sendto(m_socket,
			(const char*)packet->get_buffer(),
			packet->get_length(),
			0,
			(sockaddr*)&address->addr,
			address->length);

		delete packet;
		packet = m_queue->dequeue_write();
	}
}