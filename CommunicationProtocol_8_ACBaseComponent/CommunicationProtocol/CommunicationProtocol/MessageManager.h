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
	/// определяет самое приоритетное сообщение и достает его из очереди
	/// </summary>
	/// <returns> указатель сообщение или nullptr если очередь пуста</returns>
	Message* getNextMessage();
	int getCountMsgInQueue();

	void sendMessage(Message &msg);

	void changeExchangeInterface(ACExchangeInterface* exchange_interface);

	// для сокрытия интерфейса создадим отдельные методы открытия и закрытия

	void openExchangeInterface();
	void closeExchangeInterface();

private:

	// число показывающее количество нераспарсенных элементов
	int m_buff_nuber_of_unchecked_bytes = 0;
	// начиная с этого элемента буфера дольнейшие элементы не парсились
	int m_buff_first_unchecked_byte = 0;

	/// <summary>
	/// проверяет m_buff на наличие сообщений и добавляет их в m_queue_message
	/// </summary>
	/// <returns> 
	/// ошибка поиска сообщения: 
	/// 0 - сообщение найдено;
	///	1 - сообщение неполное (массив пустой);
	/// 2 - поврежденное сообщения;
	/// 3 - неизвестная ошибка.
	/// </returns>
	int findMsgInTheBuff();
	/// <summary>
	/// считывает все сообщения из буфера и добавляет их в очередь
	/// </summary>
	void findAllMsgInTheBuff();

	enum errfFindMsgInTheBuff
	{
		OK,						// сообщение найдено;
		ERR_INCOMPLETE_MSG,		// сообщение неполное (массив пустой);
		ERR_CRC,				// поврежденное сообщения;
		ERR						// неизвестная ошибка.
	};

	QueueMessage* m_queue_message;	
	ACExchangeInterface* m_exchange_interfacce;
	int m_len_buff = 1024 * 8;
	const int m_max_len_msg = 1033;
	char* m_buff = new char[m_len_buff];
};
