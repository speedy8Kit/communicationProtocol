#pragma once

#include "QueueMessage.h"
#include "Message.h"
#include "ACExchangeInterface.h"
#include <iostream>
class MessageManager
{
public:
	MessageManager(ACExchangeInterface* exchange_interface);
	~MessageManager();
	/// <summary>
	/// ���������� ����� ������������ ��������� � ������� ��� �� �������
	/// </summary>
	/// <returns> ��������� ��������� ��� nullptr ���� ������� �����</returns>
	Message* getNextMessage();
	int getCountMsgInQueue();

	void sendMessage(Message &msg);

	void changeExchangeInterface(ACExchangeInterface* exchange_interface);

	// ��� �������� ���������� �������� ��������� ������ �������� � ��������

	void openExchangeInterface();
	void closeExchangeInterface();

private:

	// ����� ������������ ���������� �������������� ���������
	int m_buff_nuber_of_unchecked_bytes = 0;
	// ������� � ����� �������� ������ ���������� �������� �� ���������
	int m_buff_first_unchecked_byte = 0;

	/// <summary>
	/// ��������� m_buff �� ������� ��������� � ��������� �� � m_queue_message
	/// </summary>
	/// <returns> 
	/// ������ ������ ���������: 
	/// 0 - ��������� �������;
	///	1 - ��������� �������� (������ ������);
	/// 2 - ������������ ���������;
	/// 3 - ����������� ������.
	/// </returns>
	int findMsgInTheBuff();
	/// <summary>
	/// ��������� ��� ��������� �� ������ � ��������� �� � �������
	/// </summary>
	void findAllMsgInTheBuff();

	enum errfFindMsgInTheBuff
	{
		OK,						// ��������� �������;
		ERR_INCOMPLETE_MSG,		// ��������� �������� (������ ������);
		ERR_CRC,				// ������������ ���������;
		ERR						// ����������� ������.
	};

	QueueMessage* m_queue_message;	
	ACExchangeInterface* m_exchange_interfacce;
	int m_len_buff = 1024 * 8;
	const int m_max_len_msg = 1033;
	char* m_buff = new char[m_len_buff];
};
