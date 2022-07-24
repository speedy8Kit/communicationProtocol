#pragma once

#include <iostream>
#include <bitset>
#include <string>
#include <ctime> 
#include <fstream>


#include "Message.h"
#include "ACExchangeInterface.h"
#include "UDP.h"
#include "MessageManager.h"
#include "QueueMessage.h"
#include "GlobalManager.h"


using namespace std;

void testFunc(char* str, int len)
{
    for (int i = 0; i < len; i++)
        cout << str[i] << endl;
}

void myTest1()
{

    SKinematicParams ken_param2{ NULL };

    cout << sizeof(ken_param2) << endl;

    ken_param2.position = { 1, 2, 3, 4, 5, 6 };
    ken_param2.velocity = { 7, 8, 9, 10, 11, 12 };
    ken_param2.acceleration = { 13, 14, 15, 16, 17, 18 };

    char* m_buff = new char[sizeof(ken_param2)];

    memcpy(m_buff, &ken_param2, sizeof(ken_param2));

    SKinematicParams ken_param3;

    memcpy(&ken_param3, m_buff, sizeof(ken_param2));
    NavigContent navig_content2(ken_param3);

    for (size_t i = 0; i < sizeof(ken_param2); i++)
    {
        cout << m_buff[i];
    }
    cout << endl;

    cout << navig_content2.toString();
}

void createRES_NAVIG(ostream& file)
{

    SKinematicParams ken_param;

    ken_param.position = { 1, 2, 3, 4, 5, 6 };
    ken_param.velocity = { 7, 8, 9, 10, 11, 12 };
    ken_param.acceleration = { 13, 14, 15, 16, 17, 18 };
    NavigContent* navig_content = new NavigContent(ken_param);

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };
    ETypeMsg type_mess = ETypeMsg::RES_NAVIG;

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, navig_content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createRES_TARGET(ostream& file)
{

    SKinematicParams ken_param;

    ken_param.position = { 1, 2, 3, 4, 5, 6 };
    ken_param.velocity = { 7, 8, 9, 10, 11, 12 };
    ken_param.acceleration = { 13, 14, 15, 16, 17, 18 };
    TargetContent* navig_content = new TargetContent(ken_param);

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };
    ETypeMsg type_mess = ETypeMsg::RES_TARGET;

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, navig_content);
    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createRES_WORKABILITY(ostream& file)
{

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::RES_WORKABILITY;
    EWorkability workability = EWorkability::NOT_OK;
    WorkabilityContent* content = new WorkabilityContent(workability);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createRES_ADDRESS_LIST(ostream& file)
{

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::RES_ADDRESS_LIST;
    int* addr_list = new int[3];
    addr_list[0] = 1;
    addr_list[1] = 6;
    addr_list[2] = 5;

    AddrListContent* content = new AddrListContent(addr_list, 3);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createRES_MSG_TYPE_LIST(ostream& file)
{

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::RES_MSG_TYPE_LIST;
    ETypeMsg* msg_type_list = new ETypeMsg[3];
    msg_type_list[0] = ETypeMsg::CMD_CHANGE_POINT;
    msg_type_list[1] = ETypeMsg::ERR;
    msg_type_list[2] = ETypeMsg::REQ_ADDRESS_LIST;
    MsgTypeListContent* content = new MsgTypeListContent(msg_type_list, 3);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createRES_POINT_LIST(ostream& file)
{

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::RES_POINT_LIST;

    SPoint point_list[POINTS_OF_LIST]{ NULL };
    for (int i = 0; i < POINTS_OF_LIST; i++)
    {
        point_list[i] = { 1 , 2, 3 };
    }

    PointListContent* content = new PointListContent(point_list);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createRES_CURRENT_COMMAND_PERFORM(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::RES_CURRENT_COMMAND_PERFORM;

    SCurrentCmd current_cmd{ ETypeMsg(NULL) };
    current_cmd.msg_type = ETypeMsg::CMD_SET_PATH;
    current_cmd.percent = 3;
    CurrentCmdContent* content = new CurrentCmdContent(current_cmd);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createCMD_SET_POINT_LIST(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::RES_POINT_LIST;

    SPoint point_list[POINTS_OF_LIST]{ NULL };
    for (int i = 0; i < POINTS_OF_LIST; i++)
    {
        point_list[i] = { 1 , 2, 3 };
    }
    PointListContent* content = new PointListContent(point_list);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createCMD_CHANGE_POINT(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::CMD_CHANGE_POINT;

    SChangePoint change_point = { {1, 2, 3}, 1 };

    ChangePointContent* content = new ChangePointContent(change_point);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createCMD_MOVE_TO_POS(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::CMD_MOVE_TO_POS;

    SMoveToPos move_to_pos = {};
    move_to_pos.position = { 5, 6, 7, 8, 9, 10 };
    move_to_pos.v = { 5 };
    MoveToPosContent* content = new MoveToPosContent(move_to_pos);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createSRV_MISSION_COMPLITE(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::SRV_MISSION_COMPLITE;
    bool target_reached = true;

    MissionCompleteContent* content = new MissionCompleteContent(target_reached);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createSRV_SET_PID_PARAMS(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::SRV_SET_PID_PARAMS;

    SPIDParams params = { 13, 12, 15 };

    PIDParamsContent* content = new PIDParamsContent(params);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createSRV_SET_TIME(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::SRV_SET_TIME;

    double time = 9.8;

    SetTimeContent* content = new SetTimeContent(time);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createSRV_REGISTER_ME(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::SRV_REGISTER_ME;

    std::string str = "im Kit";

    RegisterContent* content = new RegisterContent(str);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createCMD_SET_PATH(ostream& file)
{

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::CMD_SET_PATH;

    SPath* path = new SPath[3];
    path[0] = { 54, 23, ETrajType::LINE };
    path[1] = { 76, 42, ETrajType::SPLINE_ERMITH };
    path[2] = { 99, 12, ETrajType::TO_POINT };


    PathContent* content = new PathContent(path, 3);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}
void createEMPTY(ostream& file)
{
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::ERR;

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess);

    Message message2(message.getBuffMsg());

    message.logingNameHead(file);

    message.loging(file);
    message2.loging(file);
}

void testAllCmd(ostream& file)
{
    createRES_NAVIG(file);
    file << ";" << endl;
    createRES_TARGET(file);
    file << ";" << endl;
    createRES_WORKABILITY(file);
    file << ";" << endl;
    createRES_ADDRESS_LIST(file);
    file << ";" << endl;
    createRES_MSG_TYPE_LIST(file);
    file << ";" << endl;
    createRES_POINT_LIST(file);
    file << ";" << endl;
    createRES_CURRENT_COMMAND_PERFORM(file);
    file << ";" << endl;
    createCMD_SET_POINT_LIST(file);
    file << ";" << endl;
    createCMD_CHANGE_POINT(file);
    file << ";" << endl;
    createCMD_MOVE_TO_POS(file);
    file << ";" << endl;
    createSRV_MISSION_COMPLITE(file);
    file << ";" << endl;
    createSRV_SET_PID_PARAMS(file);
    file << ";" << endl;
    createSRV_SET_TIME(file);
    file << ";" << endl;
    createSRV_REGISTER_ME(file);
    file << ";" << endl;
    createCMD_SET_PATH(file);
    file << ";" << endl;
    createEMPTY(file);
    file << ";" << endl;

}


void testUDPSrever(ostream& file) {
    file << "norm";
    char ip[] = "127.0.0.1";
    UDP* server = new UDPServer(ip, 5600);
    server->open();
    char m_buff[1024];

    while (true) {
        int len = server->readBuff(m_buff);
        if (len > 0) {
            std::cout << len << "\n";
            for (size_t i = 0; i < len; i++)
            {
                std::cout << m_buff[i];
            }
            cout << "\n";
            server->writeBuff("norm", 4);
        }
    }
}

void testUDPClient(ostream& file) {
    char m_buff[1024];
    time_t time = std::time(nullptr);
    file << "norm";
    char ip[] = "127.0.0.1";
    ACExchangeInterface* client = new UDPClient(ip, 5600);
    client->open();

    while ((std::time(nullptr) - time) < 2)
    {
        client->writeBuff("hellow", 7);
        int len = client->readBuff(m_buff);
        if (len > 0) {
            std::cout << len << "\n";
            for (size_t i = 0; i < len; i++)
            {
                std::cout << m_buff[i];
            }
            cout << "\n";
        }
    }
}


void testQueueMessage(ostream& file)
{
    QueueMessage* queue = new QueueMessage();

    for (size_t i = 0; i < 6; i++)
    {
        EPriority priority = EPriority::NORM;
        switch (i)
        {
        case (0):
            priority = EPriority::LOW;
            break;
        case 1:
            priority = EPriority::CRITICAL;
            break;
        case 2:
            priority = EPriority::NORM;
            break;
        case 3:
            priority = EPriority::NORM;
            break;
        case 4:
            priority = EPriority::CRITICAL;
            break;
        case 5:
            priority = EPriority::CRITICAL;
            break;
        default:
            priority = EPriority::CRITICAL;
            break;
        }

        EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
        SAddress adr_sender = { 1, 2, 3 };
        SAddress adr_recipient = { 4, 5, 6 };

        ETypeMsg type_mess = ETypeMsg::SRV_REGISTER_ME;

        char* data = new char[9];
        data[0] = 'i';
        data[1] = 'm';
        data[2] = ' ';
        data[3] = 'K';
        data[4] = 'i';
        data[5] = 't';
        data[6] = ':';
        data[7] = ' ';
        data[8] = char(i) + 48;

        RegisterContent* content = new RegisterContent(data, 9);

        Message* message = new Message(priority, confirm, adr_sender, adr_recipient,
            type_mess, content);

        queue->addMessage(message);

    }
    int len = queue->getLen();
    for (size_t i = 0; i < 6; i++) {
        Message* msg = queue->getMessage();
        msg->logingNameHead(file);
        msg->loging(file);
    }



}


void testMessageManagerServer(ostream& file) {
    char m_buff[1024]{};
    char ip[] = "127.0.0.1";
    ACExchangeInterface* server = new UDPServer(ip, 5600);

    MessageManager* msg_manager = new MessageManager(server);
    server = nullptr;

    msg_manager->openExchangeInterface();
    Message* msg_recive;

    while (true) {
        msg_recive = msg_manager->getNextMessage();
        if (msg_recive) {
            msg_recive->logingNameHead(file);
            msg_recive->loging(file);
            file << msg_manager->getCountMsgInQueue() << "\n";
            file << "\n";
            //server->writeBuff("norm", 4);
            delete msg_recive;
            msg_recive = nullptr;
        }
    }
}

void testMessageManagerClient_1(ostream& file) {
    char m_buff[1024]{};
    for (size_t i = 0; i < 1024; i++)
    {
        m_buff[i] = '0';
    }
    char ip[] = "127.0.0.1";
    ACExchangeInterface* client = new UDPClient(ip, 5600);
    MessageManager* msg_manager = new MessageManager(client);
    client = nullptr;

    msg_manager->openExchangeInterface();

    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::SRV_REGISTER_ME;

    std::string data = "hhhhh";
    //data += to_string(i++);
    RegisterContent* content = new RegisterContent(data);

    std::string data2 = "hhhhh";
    //data += to_string(i++);
    RegisterContent* content2 = new RegisterContent(data2);

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess, content);

    Message message2(priority, confirm, adr_sender, adr_recipient,
        type_mess, content2);

    msg_manager->sendMessage(message);
    msg_manager->sendMessage(message2);

    for (size_t i = 0; i < message.getBuffSize(); i++)
    {
        file << message.getBuffMsg()[i];
    }
    file << ";\n";

    for (size_t i = 0; i < message2.getBuffSize(); i++)
    {
        file << message2.getBuffMsg()[i];
    }
    file << ";\n";
}
void testMessageManagerClient_2(ostream& file) {
    char m_buff[1024];
    time_t time = std::time(nullptr);
    char ip[] = "127.0.0.1";
    ACExchangeInterface* client = new UDPClient(ip, 5600);
    MessageManager* msg_manager = new MessageManager(client);

    msg_manager->openExchangeInterface();
    Message* msg_recive;
    int i = 0;
    while ((std::time(nullptr) - time) < 2)
    {

        EPriority priority = EPriority::LOW;
        EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
        SAddress adr_sender = { 1, 2, 3 };
        SAddress adr_recipient = { 4, 5, 6 };

        ETypeMsg type_mess = ETypeMsg::SRV_REGISTER_ME;

        std::string data = "heloo; ";
        data += to_string(i++);
        RegisterContent* content = new RegisterContent(data);

        Message message(priority, confirm, adr_sender, adr_recipient,
            type_mess, content);

        /*
    EPriority priority = EPriority::LOW;
    EConfirm confirm = EConfirm::NOT_REQUIRE_CONFIRM;
    SAddress adr_sender = { 1, 2, 3 };
    SAddress adr_recipient = { 4, 5, 6 };

    ETypeMsg type_mess = ETypeMsg::ERR;

    Message message(priority, confirm, adr_sender, adr_recipient,
        type_mess);

*/
        msg_manager->sendMessage(message);

        message.loging(file);

        msg_recive = msg_manager->getNextMessage();
        if (msg_recive) {
            file << Message::toStringETypeMsg(msg_recive->getTypeMsg()) << "\n";
            delete msg_recive;
        }
    }

}

void testMapAddress(ostream& file)
{
    MapAddress* map_addres = new MapAddress();
    for (size_t i = 0; i < 4; i++)
    {
        char ip[] = "127.0.0.1";
        ACExchangeInterface* server = new UDPServer(ip, 5600+i);

        MessageManager* msg_manager = new MessageManager(server);
        file << "mngr" << i << ":; " << msg_manager << ";\n";
        SAddress* addr = new SAddress();
        addr->MIDDLE = i;
        addr->HIGH   = i;
        addr->LOW    = i;
        map_addres->add(addr, msg_manager);
    }
    SAddress addr{};
    addr.HIGH   = 1;
    addr.MIDDLE = 1;
    addr.LOW    = 1;
    MessageManager* mngr = map_addres->findExchangeInterface(addr);
    file << "findExchangeInterface:; " << mngr << ";\n";

    file << "getElementMap:; " << map_addres->getElementMap(1)->exlNTF << ";\n";
    file << "getLenghtMap:; " << map_addres->getLenghtMap() << ";\n";

}

void testGlobalManager(ostream& file) 
{
    ifstream* config_file = new ifstream();
    ofstream* log_file = new ofstream();

    config_file->open("config.json");
    log_file->open("log.txt");

    GlobalManager  global_manager(config_file, log_file);
    
    while (true)
    {
        //std::cout << "OK\n";
        global_manager.routing();
    }
}
