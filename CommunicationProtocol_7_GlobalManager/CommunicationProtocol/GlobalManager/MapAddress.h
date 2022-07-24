#pragma once

#include "StructsForMessage.h"
#include "MessageManager.h"

/// <summary>
/// ������������ �������� ����������� ������
/// </summary>
struct  SElementMapAddress
{
	MessageManager* exlNTF;
	SAddress* address;
};


/// <summary>
/// ������ ���� MessageManager ������������ � ������������ ��������
/// � ���� ������� �������� GlobalManager, ����� �������� ��� �������� ��� ����������
/// </summary>
class MapAddress
{
public:
	MapAddress();
	~MapAddress();

	void add(SAddress* addr, MessageManager* exlNTF);
/// <summary>
/// ���� �������� ������������� � ���������� ������ ��������� ���� ������
/// </summary>
/// <param name="addr"></param>
/// <returns> ����� ���� nullptr ���� ������ ������ ���</returns>
	MessageManager* findExchangeInterface(SAddress addr);

	SElementMapAddress* getElementMap(unsigned int number);
	unsigned int getLenghtMap();

private:
	SElementMapAddress** m_map = new SElementMapAddress*[32];
	unsigned int m_length_map;

};


