#ifndef __MASSAGE_H__
#define __MASSAGE_H__

#include "CreatorContents.h"
#include "StructsForMessage.h"
#include <bitset>

#include <iostream>
#include <string>
using namespace std;
// сообщение которое отправляется либо получатся от других компонентов
// оно содержит загаловок из 9 байт и текст сообщения
class Message
{

public:
    // конструктор позволяющий создать сообщение зная данные заголовка
    Message(EPriority priority, EConfirm confirm, SAddress adr_sender, SAddress adr_recipient,
            ETypeMsg type_msg, ACBaseContent *content = nullptr);

    // конструктор позволяющий создать объект сообщения на основании получееного набора байт
    // с учетом корректности полученного сообщения
    Message(const char *m_buff, bool check_crc = true);

    ~Message();


    /// <summary>
    /// выводит все данные сообщения через ";"
    /// </summary>
    /// <param name="out_stream"> поток в который будет выводиться информация </param>
    void loging(ostream &out_stream);


    /// <summary>
    /// выводит все названия данных сообщения через ";"
    /// </summary>
    /// <param name="out_stream"> поток в который будет выводиться информация </param>
    void logingNameHead(ostream &out_stream);

    /// <summary>
    /// генерерирует 16 битную контрольную сумму путем последовательного использования операций and и xor
    /// </summary>
    /// <param name="mess"> - массив на основании которого формируется контольная сумма </param>
    /// <param name="len_mess"> - длина массива </param>
    /// <param name="controlSum"> строка в которую записывается crc (два элемета) </param>
    static void createCrc(const char* mess, unsigned int len, char* controlSum);


    auto getPriority()      -> EPriority;
    auto getConfirm()       -> EConfirm;
    auto getAdrSender()     -> SAddress;
    auto getAdrRecipient()  -> SAddress;
    auto getTypeMsg()       -> ETypeMsg;
    auto getBuffSize()      -> int;
    auto getContent()       -> ACBaseContent *;
    auto getBuffMsg()       -> char *;


    //обязадельный байт в начале каждого сообщения по нему ищется начало сообщения
    // положение - 0..8 (8 бит)
    static const char start_byte = 0b01010011;
    
    // обязаnельный маркер в каждом сообщении
    // положение - 12..16 (4 бита)
    static const char control_marker = 0b0110;

    static std::string toStringETypeMsg(ETypeMsg msg_type);
private:
    // положение - 0..8 (8 бит)
    // start_byte

    // устанавливает очередность обработки сообщений
    // положение - 8..10 (2 бита)
    EPriority m_priority;

    // определяет необходимость ответа на сообщение и является ли оно само ответом
    // положение - 10..12 (2 бита)
    EConfirm m_confirm;

    // положение - 12..16 (4 бита)
    // control_markey

    // определяет адрес получателя
    // положение - 16..28 (12 бит)
    SAddress m_adr_sender;

    // определяет адрес отправителя
    // положение - 28..40 (12 бит)
    SAddress m_adr_recipient;

    // определяет тип сообщения
    // положение - 40..46 (6 бит)
    ETypeMsg m_type_msg;

    // определяет длинну всего сообщение с зоголовком и содержанием
    // положение - 46..56 (10 бит)
    int m_buff_msg_len;

    ACBaseContent *m_content;

    // число необходимое для проверки корректности полученного собщения,
    // проверяется по закону ...
    // положение - -16..0 (последние 16 бит)
    // m_crc;

    // все сообщение с зоголовком и содержанием в виде байтов
    char *m_buff_msg = new char[1033];

    // представляет данные заголовка сообщения в виде массива 7 байтов
    void packHead();

    // представляет сообщение в виде массива байтов
    void puckMessage();

    // распаковывает все сообщение предпологая, что оно уже корректное
    void unpackMessage(const char* buff_recived);
    // распаковывает заголовок из 7 байт и записывает значения данных в свойства объекта
    void unpackHead(const char *buff_recived);


};

#endif // __MESSAGE_H__
