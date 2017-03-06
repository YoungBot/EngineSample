//==========================================================
//NetAddress.hpp
//==========================================================
#pragma once
#ifndef _NETADDRESS_HPP_
#define _NETADDRESS_HPP_

#include <WinSock2.h>

class NetAddress
{
public:
	sockaddr_storage addr;
	size_t length;
	void init(sockaddr* address,size_t len)
	{
		memcpy(&addr, address, len);
		length = len;
	}
	bool operator == (const NetAddress& addrToEqual) const
	{
		for (int i = 0; i < 6; i++)
		{
			if (addr.__ss_pad1[i] != addrToEqual.addr.__ss_pad1[i])
			{
				return false;
			}
			
		}
		return true;
	}
};





#endif
