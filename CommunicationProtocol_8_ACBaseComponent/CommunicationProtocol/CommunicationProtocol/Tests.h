#pragma once

#include <iostream>
#include <bitset>
#include <string>
#include <ctime> 
#include <fstream>



#include "ACBaseComponent.h"
#include "MessageManager.h"
#include "UDP.h"


using namespace std;
using namespace std::chrono;

void testBaseComponent(ostream& file)
{

    char m_buff[1024]{};
    for (size_t i = 0; i < 1024; i++)
    {
        m_buff[i] = '0';
    }
    char ip[] = "127.0.0.1";
    ACExchangeInterface* client = new UDPClient(ip, 10000);
    MessageManager* msg_manager = new MessageManager(client);
    client = nullptr;

    msg_manager->openExchangeInterface();

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::REQUIRE_NOT_CONFIRM;
    SAddress adr_sender = { 1, 1, 3 };
    SAddress adr_recipient = { 1, 1, 0 };

    ETypeMsg type_mess = ETypeMsg::SRV_REGISTER_ME;

    std::string data = "im Kit";
    //data += to_string(i++);
    RegisterContent* content = new RegisterContent(data);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    msg_manager->sendMessage(message);
    std::cout << "sendMessage\n";

    Message* msg_recive;
    while (true)
    {
        msg_recive = msg_manager->getNextMessage();
        if (msg_recive) {
            msg_recive->loging(file);
            delete msg_recive;
        }

    }

}