#include "MapAddress.h"

MapAddress::MapAddress():
	m_length_map{ 0 }
{

}

MapAddress::~MapAddress()
{
	// ������� ����� ������� ������ ��������� � ����������� � ������ � ��� ������ ����������
	for (size_t i = 0; i < m_length_map; i++)
	{
		delete m_map[i];
	}
	delete[] m_map;
}

void MapAddress::add(SAddress* addr, MessageManager* exlNTF)
{
	// �� m_map ��������� ���������� � ��� ������������ ������������ ������ (32),
	// �� ���������� ������� ������� � �������� �����(�������������) ������� 
	SElementMapAddress* ell = new SElementMapAddress();
	ell->address = addr;
	ell->exlNTF = exlNTF;
	m_map[m_length_map] = ell;

	m_length_map++;
}


MessageManager* MapAddress::findExchangeInterface(SAddress addr)
{
	for (size_t i = 0; i < m_length_map; i++)
	{
		SAddress temp_addr = *(m_map[i]->address);
		if (temp_addr.LOW    == addr.LOW    &&
			temp_addr.MIDDLE == addr.MIDDLE &&
			temp_addr.HIGH   == addr.HIGH     )
		{
			return m_map[i]->exlNTF;
		}
	}
	return nullptr;
}

SElementMapAddress* MapAddress::getElementMap(unsigned int number)
{
	return m_map[number];
}

unsigned int MapAddress::getLenghtMap()
{
	return m_length_map;
}
