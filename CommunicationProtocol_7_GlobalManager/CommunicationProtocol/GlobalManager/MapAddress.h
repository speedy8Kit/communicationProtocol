#pragma once

#include "StructsForMessage.h"
#include "MessageManager.h"

/// <summary>
/// сопоставляет менеджер конкретному адресу
/// </summary>
struct  SElementMapAddress
{
	MessageManager* exlNTF;
	SAddress* address;
};


/// <summary>
/// Список всех MessageManager подключенных к определенным адрессам
/// С этим списком работает GlobalManager, чтобы менеджер мог опросить все компоненты
/// </summary>
class MapAddress
{
public:
	MapAddress();
	~MapAddress();

	void add(SAddress* addr, MessageManager* exlNTF);
/// <summary>
/// ищет менеджер прикрепленный к следующему адресу переберая весь массив
/// </summary>
/// <param name="addr"></param>
/// <returns> может быть nullptr если такого адреса нет</returns>
	MessageManager* findExchangeInterface(SAddress addr);

	SElementMapAddress* getElementMap(unsigned int number);
	unsigned int getLenghtMap();

private:
	SElementMapAddress** m_map = new SElementMapAddress*[32];
	unsigned int m_length_map;

};


