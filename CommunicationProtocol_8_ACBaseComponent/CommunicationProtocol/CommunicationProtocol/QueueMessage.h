#pragma once
#include "Message.h"

struct ElementQeueMessage
{
	Message* data;
	ElementQeueMessage* next = nullptr;
	ElementQeueMessage* prev = nullptr;
};

class QueueMessage
{
public:
	QueueMessage();
	~QueueMessage();

	void addMessage(Message* msg);
	Message* getMessage();

	unsigned int getLen();

private:
	ElementQeueMessage* m_start;
	ElementQeueMessage* m_end;
	unsigned int m_size_content = 0;

	void addMessageByIndex(Message* msg, const unsigned int index);
};
