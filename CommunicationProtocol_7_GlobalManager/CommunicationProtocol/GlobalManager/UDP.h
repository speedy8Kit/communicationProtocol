#pragma once
#include "ACExchangeInterface.h"

#include <iostream>

#include <string>
#include <cmath>
#include <ctime>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class UDP : public ACExchangeInterface
{
public:
	UDP();
	~UDP();

	virtual int open() = 0;
	
	int close();
	/// <summary>
	/// ��������� ������ �� ������ ������������ ������ 
	/// </summary>
	/// <param name="buf"> ������ ���� ������������ ������ �� ������ </param>
	/// <returns>����������� ���� ��������� � ������ buf </returns>
	int readBuff(char* buf);
	/// <summary>
	/// ��������� ������ � ����� ���������� ���������� � �����������
	/// </summary>
	/// <param name="m_buff"> ������ � ������� ������� ������� ��������� </param>
	/// <param name="len_buf"></param>
	/// <returns></returns>
	int writeBuff(const char* m_buff, unsigned int len_buf);

protected:
	SOCKET m_soket;

	SOCKADDR_IN m_addr;
	SOCKADDR_IN m_addr_linked;
};

class UDPClient : public UDP
{
public:
	UDPClient(const char ip_srever_linked[16], u_short port_server_linked);
	~UDPClient();

	int open();
};

class UDPServer : public UDP
{
public:
	UDPServer(const char ip[16], u_short port);
	~UDPServer();

	int open();
};

