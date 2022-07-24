#include "MessageManager.h"

MessageManager::MessageManager(ACExchangeInterface* exhange_interface):
	m_exchange_interfacce{ exhange_interface }
{
	m_queue_message = new QueueMessage();
}

MessageManager::~MessageManager()
{
	delete m_queue_message;
	delete m_exchange_interfacce;
	delete[] m_buff;
}

Message* MessageManager::getNextMessage()
{

	int res = m_exchange_interfacce->readBuff(m_buff + m_buff_nuber_of_unchecked_bytes);
	// считываем сообщения пока они не закончатся в буфере итерфейса передачи данных
	while (res > 0)
	{
		m_buff_nuber_of_unchecked_bytes += res;
		// если места остаось меньше чем на одну максимальную посылку
		// если в конце осталось неполное сообщение, то его переносим в начало буфера и продолжаем уже после него
		if ((m_len_buff - (m_buff_first_unchecked_byte + m_buff_nuber_of_unchecked_bytes)) < m_max_len_msg)
		{
			findAllMsgInTheBuff();
		}
		res = m_exchange_interfacce->readBuff(m_buff + m_buff_nuber_of_unchecked_bytes);
	}
	findAllMsgInTheBuff();
	return m_queue_message->getMessage();
}

int MessageManager::getCountMsgInQueue()
{
	return m_queue_message->getLen();
}

void MessageManager::sendMessage(Message& msg)
{
	m_exchange_interfacce->writeBuff(msg.getBuffMsg(), msg.getBuffSize());
}

void MessageManager::changeExchangeInterface(ACExchangeInterface* exchange_interface)
{
	delete m_exchange_interfacce;
	m_exchange_interfacce = exchange_interface;
}

void MessageManager::openExchangeInterface()
{
	m_exchange_interfacce->open();
}

void MessageManager::closeExchangeInterface()
{
	m_exchange_interfacce->open();
}


int MessageManager::findMsgInTheBuff()
{
	// искать сообщение пока не найдется или не будет доказано, что это невозможно
	while (m_buff_nuber_of_unchecked_bytes > 0)
	{
		// проверяем можно ли найти заголовок соощения
		if (m_buff_nuber_of_unchecked_bytes > 8)
		{
			// нахоим старт байт, контрольный маркер и проверяем находися ли все сообщение в буфере
			if (m_buff[m_buff_first_unchecked_byte] == Message::start_byte and
				(m_buff[m_buff_first_unchecked_byte + 1] & 0b00001111) == Message::control_marker)
			{
				// проверяем полное ли сообщение
				int msg_buff_size = ((m_buff[m_buff_first_unchecked_byte + 5] & 0b0000000011) << 8) |
					(m_buff[m_buff_first_unchecked_byte + 6] & 0b0011111111);
				if (msg_buff_size <= m_buff_nuber_of_unchecked_bytes)
				{
					// распаковка сообщения проводится только после проверки crc
					char crc[2] = { '0','0' };
					Message::createCrc(m_buff + m_buff_first_unchecked_byte, msg_buff_size - 2, crc);
					
					int err_crc = 
						((((m_buff[msg_buff_size + m_buff_first_unchecked_byte - 2] ^ crc[0]) & 0b0000000011111111) << 8) |
						 (((m_buff[msg_buff_size + m_buff_first_unchecked_byte - 1] ^ crc[1]) & 0b0000000011111111) << 0)
						);

					if (!err_crc) {
						Message* msg = new Message(m_buff + m_buff_first_unchecked_byte, false);
						m_buff_first_unchecked_byte += msg_buff_size;
						m_buff_nuber_of_unchecked_bytes -= msg_buff_size;
						m_queue_message->addMessage(msg);
						return OK;
					}
					else {
						return ERR_CRC;
					}
				}
				else  // если сообщение неполное, то прекращаем искать
				{
					break;
				}
			}
			else // если не найден старт байт, то движемся дальше по сообщению
			{
				m_buff_first_unchecked_byte++;
				m_buff_nuber_of_unchecked_bytes--;
			}
		}
		else // невозможно обрабатывать без возможности определить длину сообщения
		{
			break;
		}
	}
	// хвостик переносим в начало
	// проверяем не находится ли он уже в начале. Такой вариант может оказаться,
	// когда первое сообщение отправляется медленно и буфер интерфейса успевает простаивать пустым
	if (m_buff_first_unchecked_byte != 0)
	{
		memcpy(m_buff, m_buff + m_buff_first_unchecked_byte, m_buff_nuber_of_unchecked_bytes);
	}
	m_buff_first_unchecked_byte = 0;
	return ERR_INCOMPLETE_MSG;
}

void MessageManager::findAllMsgInTheBuff()
{
	int err_check = OK;
	// проверяем массив, пока не будет доказано, что больше сообщений не обнаружится
	while (err_check == OK || err_check == ERR_CRC)
	{
		err_check = this->findMsgInTheBuff();
		if (err_check == ERR_CRC) {
			cout << "ERR_CRC \n";
		}
	}
}
