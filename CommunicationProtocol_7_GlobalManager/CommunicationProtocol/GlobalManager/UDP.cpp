# include "UDP.h"
using namespace std;
UDP::UDP() {
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int err = WSAStartup(version, &data);
	if (err != 0)
	{
		cout << "Can't start Winsock!" << err;
	}

	m_addr = SOCKADDR_IN();
	m_addr_linked = SOCKADDR_IN();
	m_soket = SOCKET();
}

UDP::~UDP()
{
	WSACleanup();
}


UDPClient::UDPClient(const char ip_server_linked[16], u_short port_server_linked) : UDP()
{
	m_addr_linked.sin_addr.s_addr = inet_addr(ip_server_linked);
	m_addr_linked.sin_port = htons(port_server_linked);
	m_addr_linked.sin_family = AF_INET;
}

UDPClient::~UDPClient()
{
}

int UDPClient::open()	
{
	// create socket
	m_soket = socket(AF_INET, SOCK_DGRAM, NULL);
	if (m_soket == INVALID_SOCKET) {
		std::cout << "Socket error: " << WSAGetLastError();
		WSACleanup();
		return INVALID_SOCKET;
	}
	else {
		BOOL l = true;
		int err = ioctlsocket(m_soket, FIONBIO, (unsigned long*)&l);
		if (err != NO_ERROR)
			printf("ioctlsocket failed with error: %ld\n", err);
		else
		{
			cout << "create client!\n";
		}
		return 0;
	}
}

UDPServer::UDPServer(const char ip[16], u_short port) : UDP()
{
	m_addr.sin_addr.s_addr = inet_addr(ip);
	m_addr.sin_port = htons(port);
	m_addr.sin_family = AF_INET;
}


UDPServer::~UDPServer()
{
}

int UDPServer::open()
{

	// create socket
	m_soket = socket(AF_INET, SOCK_DGRAM, NULL);
	if (m_soket == INVALID_SOCKET) {
		std::cout << "Socket error: " << WSAGetLastError();
		WSACleanup();
		return INVALID_SOCKET;
	}
	else 
	{
		BOOL l = true;
		int err = ioctlsocket(m_soket, FIONBIO, (unsigned long*)&l);
		if (err != NO_ERROR){
			printf("ioctlsocket failed with error: %ld\n", err);
			return err;
		}
		else {
			//Bind soket to ip address and 
			err = bind(m_soket, (sockaddr*)&m_addr, sizeof(m_addr));
			if (err == SOCKET_ERROR)
			{
				cout << "Can't bind socket! " << WSAGetLastError() << endl;
				return err;
			}
			else {
				cout << "create server!\n";
			}
		}
	}
	
	return 0;
}

int UDP::close()
{
	closesocket(m_soket);
	int res = WSACleanup();
	return res;
}

int UDP::readBuff(char* m_buff)
{
	int m_maxBuffLen = 1024;
	int bsize;
	int m_addr_linked_size = sizeof(m_addr_linked);
	bsize = recvfrom(m_soket, m_buff, m_maxBuffLen, 0, (sockaddr*)&m_addr_linked, &m_addr_linked_size);
	return bsize;
}

int UDP::writeBuff(const char* m_buff, unsigned int len_buf)
{	
	int sendOK = sendto(m_soket, m_buff, len_buf, 0, (sockaddr*)&m_addr_linked, sizeof(m_addr_linked));
	if (sendOK == SOCKET_ERROR)
	{
		cout << "That didn't work!" << WSAGetLastError() << endl;
		return 1;
	}
	return 0;
}
