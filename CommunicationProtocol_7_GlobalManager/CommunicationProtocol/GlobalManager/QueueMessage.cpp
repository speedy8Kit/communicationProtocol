#include "QueueMessage.h"


void QueueMessage::addMessage(Message* msg)
{
	ElementQeueMessage* el = m_start;
	if (m_size_content == 0) {
		ElementQeueMessage* new_el = new ElementQeueMessage();
		new_el->data = msg;
		m_end = new_el;
		m_start = new_el;
		m_size_content++;
	}
	else
	{
		// если добавить нужно в начало списка те самый высокий приоритет
		if (msg->getPriority() == EPriority::CRITICAL)
		{
			this->addMessageByIndex(msg, 0);
		}
		// если добавить нужно в конец списка те самый низкий приоритет
		else if (msg->getPriority() == EPriority::LOW)
		{
			this->addMessageByIndex(msg, m_size_content);
		}
		// остальные случаи
		else for (int i = 0; i < m_size_content; i++)
		{
			if (int(msg->getPriority()) > int(el->data->getPriority())) {
				addMessageByIndex(msg, i);
				break;
			}
			else if (i >= m_size_content - 1) { // если элементов больше нетдобавляем в конец
				addMessageByIndex(msg, m_size_content);
				break;
			}
			else
			{
				el = el->next;
			}
		}
	}
}

Message* QueueMessage::getMessage()
{
	if (m_size_content == 0) {
		return nullptr;
	}
	else if (m_size_content == 1)
	{
		Message* result = m_start->data;
		delete m_start;
		m_start = nullptr;
		m_end = nullptr;
		m_size_content--;
		return result;
	}
	else
	{
		Message* result = m_start->data;
		m_start = m_start->next;
		delete m_start->prev;
		m_start->prev = nullptr;
		m_size_content--;
		return result;
	}
}

void QueueMessage::addMessageByIndex(Message* msg, const unsigned int index)
{
	ElementQeueMessage* new_el = new ElementQeueMessage();
	new_el->data = msg;
	if (index == 0) { // в начало
		new_el->next = m_start;
		m_start->prev = new_el;
		m_start = new_el;
	}
	else if (index >= m_size_content) // в конец
	{
		 new_el->prev = m_end;
		 m_end->next = new_el;
		 m_end = new_el;
	}
	else
	{
		ElementQeueMessage* el = m_start;
		for (size_t i = 0; i < index; i++) el = el->next;

		new_el->prev = el->prev;
		new_el->next = el;
		el->prev->next = new_el;
		el->prev = new_el;

	}
	m_size_content++;
}
unsigned int QueueMessage::getLen()
{
	return m_size_content;
}
QueueMessage::QueueMessage()
{
	m_start = m_end = nullptr;
}

QueueMessage::~QueueMessage()
{
	for (size_t i = 0; i < m_size_content; i++) {
		m_start = m_start->next;
		delete m_start->prev;
	}
	delete m_end;
}
