#pragma once
#include <cstdint>
#include <WinSock2.h>
#include <memory>

class SocketAddress
{
public:
	SocketAddress(uint32_t inAddress,uint16_t inPort)
	{
		//IPV4
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
		GetAsSockAddrIn()->sin_port = htons(inPort);
	}

	SocketAddress(const sockaddr& inSocketAddr)
	{
		memcpy(&mSockAddr, &inSocketAddr, sizeof(sockaddr));
	}

private:
	sockaddr mSockAddr;

	sockaddr_in* GetAsSockAddrIn()
	{
		return reinterpret_cast<sockaddr_in*>(&mSockAddr);
	}
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;
