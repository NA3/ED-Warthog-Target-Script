#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <Winsock2.h>
#include <fstream>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

#pragma comment(lib, "ws2_32.lib")

int main()
{
// Read and Parse file
	//initialize vector that will contain the desired info

	//Load the file
	std::ifstream ED_API("Users/tomdu/Saved Games/Frontier Developments/Elite Dangerous/Statustest.json");
	try {
		json::parse(ED_API);
	}
	catch (json::parse_error &e)
	{
		std::cerr << e.what() << std::endl;
	}
	

	//Retreive Parsed Value



// Send Data
	char buf[128];
	sockaddr_in addr;

	WSADATA WSAData;
	WSAStartup(2, &WSAData);
	gethostname(buf, sizeof(buf));
	hostent *server = gethostbyname(buf);
	if (server)
	{
		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s != INVALID_SOCKET)
		{
			memcpy(&addr.sin_addr, server->h_addr, server->h_length);
			addr.sin_family = server->h_addrtype;
			addr.sin_port = htons(1000); // use TCP port 1000, the same as the one in TARGET script
			if (!connect(s, (sockaddr*)&addr, sizeof(addr)))
			{
				*(unsigned short*)buf = 2 + 19;		// data size = 21 bytes (packet length + data)
				strcpy(buf + 2, "Send to TARGET TEST");		// 19 bytes of data (can be anything)
				send(s, buf, *(unsigned short*)buf, 0);	// send (packet length + data) bytes of data
			}
			closesocket(s);
		}
	}
	WSACleanup();
}

