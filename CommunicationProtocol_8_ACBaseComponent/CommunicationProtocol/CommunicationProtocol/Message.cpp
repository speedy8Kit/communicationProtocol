#include "Message.h"

// ######################################  конструкторы ###########################################

Message::Message(EPriority priority, EConfirm confirm, SAddress adr_sender, SAddress adr_recipient,
                 ETypeMsg type_msg, ACBaseContent *content)
{
    m_priority = priority;
    m_confirm = confirm;

    m_adr_sender = adr_sender;
    m_adr_recipient = adr_recipient;

    m_type_msg = type_msg;
    m_content = content;

    m_buff_msg_len = 9;
    if (!m_content) m_content = new EmptyContent();
    m_buff_msg_len += m_content->get_size();

    // добавляем сгенерированный заголовок в итоговое сообщение

    this->puckMessage();
}

Message::Message(const char* buff_received, bool check_crc)
{

    // полная распаковка сообщения проводится только после проверки crc
    if (check_crc) {
        m_buff_msg_len = ((buff_received[5] & 0b0000000011) << 8) | (buff_received[6] & 0b0011111111);
        createCrc(buff_received, m_buff_msg_len - 2, m_buff_msg + m_buff_msg_len - 2);

        int err_crc = ((((buff_received[m_buff_msg_len - 2] ^ m_buff_msg[m_buff_msg_len - 2]) & 0b0000000011111111) << 8) |
                   (((buff_received[m_buff_msg_len - 1] ^ m_buff_msg[m_buff_msg_len - 1]) & 0b0000000011111111) << 0));
        
        if (err_crc) {
            cout << "ERR crc from Message.cpp/Message(): " << err_crc << "\n";
        }
    }
    this->unpackMessage(buff_received);
}

Message::~Message()
{
    delete[] this->m_buff_msg;
    delete this->m_content;
}

// ############################################## функции #########################################

void Message::loging(ostream &out_stream)
{
    out_stream << toStringETypeMsg(this->getTypeMsg()) << ";";

    switch (m_priority)
    {
    case EPriority::LOW:
        out_stream << "LOW";
        break;
    case EPriority::NORM:
        out_stream << "NORM";
        break;
    case EPriority::HIGH:
        out_stream << "HIGH";
        break;
    case EPriority::CRITICAL:
        out_stream << "CRITICAL";
        break;
    default:
        out_stream << "ERR";
        break;
    }

    out_stream << "; ";

    switch (m_confirm)
    {
    case EConfirm::NOT_REQUIRE_NOT_CONFIRM:
        out_stream << "NOT_REQUIRE_NOT_CONFIRM";
        break;
    case EConfirm::NOT_REQUIRE_CONFIRM:
        out_stream << "NOT_REQUIRE_CONFIRM";
        break;
    case EConfirm::REQUIRE_NOT_CONFIRM:
        out_stream << "REQUIRE_NOT_CONFIRM";
        break;
    default:
        out_stream << "ERR";
        break;
    }

    out_stream << "; ";

    out_stream << (int)m_adr_sender.HIGH << "-" << (int)m_adr_sender.MIDDLE << "-" << (int)m_adr_sender.LOW;

    out_stream << "; ";

    out_stream << (int)m_adr_recipient.HIGH << "-" << (int)m_adr_recipient.MIDDLE << "-" << (int)m_adr_recipient.LOW;

    out_stream << "; ";

    out_stream << m_buff_msg_len;

    out_stream << "; ";

    bitset<8> bit_set1(m_buff_msg[m_buff_msg_len - 2]);
    bitset<8> bit_set2(m_buff_msg[m_buff_msg_len - 1]);
    out_stream << bit_set1 << " " << bit_set2;

    out_stream << "; ";

    out_stream << m_content->toString();

    out_stream << "\n";
}

void Message::logingNameHead(ostream &out_stream)
{
    out_stream << "message_type;"
               << "priority; "
               << "confirm; "
               << "adr_sender; "
               << "adr_recipient; "
               << "buff_size; "
               << "crc; "
               << m_content->toStringHeaders()
               << endl;
}

// /////////////////////////////////////////// pack_unpack ////////////////////////////////////////

void Message::puckMessage()
{
    this->packHead();
    m_content->marshall(m_buff_msg + 7);

    createCrc(m_buff_msg, m_buff_msg_len - 2, m_buff_msg + m_buff_msg_len - 2);
}

void Message::packHead()
{
    m_buff_msg[0] = start_byte;

    m_buff_msg[1]  = ((char)m_priority       << 6 & 0b11000000);
    m_buff_msg[1] |= ((char)m_confirm        << 4 & 0b00110000);
    m_buff_msg[1] |= (control_marker              & 0b00001111);

    m_buff_msg[2]  = (m_adr_sender.HIGH      << 5 & 0b11100000);
    m_buff_msg[2] |= (m_adr_sender.MIDDLE    << 1 & 0b00011110);
    m_buff_msg[2] |= (m_adr_sender.LOW       >> 4 & 0b00000001);

    m_buff_msg[3]  = (m_adr_sender.LOW       << 4 & 0b11110000);
    m_buff_msg[3] |= (m_adr_recipient.HIGH   << 1 & 0b00001110);
    m_buff_msg[3] |= (m_adr_recipient.MIDDLE >> 3 & 0b00000001);

    m_buff_msg[4]  = (m_adr_recipient.MIDDLE << 5 & 0b11100000);
    m_buff_msg[4] |= (m_adr_recipient.LOW         & 0b00011111);

    m_buff_msg[5]  = ((char)m_type_msg       << 2 & 0b11111100);
    m_buff_msg[5] |= (m_buff_msg_len         >> 8 & 0b00000011);

    m_buff_msg[6]  = (m_buff_msg_len              & 0b11111111);
}

void Message::unpackMessage(const char* buff_received)
{
    this->unpackHead(buff_received);
    m_content = CreatorContents::createContent(m_type_msg, buff_received + 7, m_buff_msg_len - 9);

    memcpy(m_buff_msg, buff_received, m_buff_msg_len);
}

void Message::unpackHead(const char *buff_received)
{
    m_priority              = EPriority((buff_received[1] & 0b11000000) >> 6);
    m_confirm               = EConfirm((buff_received[1] & 0b00110000) >> 4);

    m_adr_sender.HIGH       =  (buff_received[2] & 0b11100000) >> 5;
    m_adr_sender.MIDDLE     =  (buff_received[2] & 0b00011110) >> 1;
    m_adr_sender.LOW        = ((buff_received[2] & 0b00000001) << 4) |
                                    ((buff_received[3] & 0b11110000) >> 4);

    m_adr_recipient.HIGH    =  (buff_received[3] & 0b00001110) >> 1;
    m_adr_recipient.MIDDLE  = ((buff_received[3] & 0b00000001) << 3) |
                                    ((buff_received[4] & 0b11100000) >> 5);
    m_adr_recipient.LOW     =  (buff_received[4] & 0b00011111);

    m_type_msg              = ETypeMsg((buff_received[5] & 0b11111100) >> 2);
    m_buff_msg_len          = ((buff_received[5] & 0b0000000011) << 8) |
                                     (buff_received[6] & 0b0011111111);
}

std::string Message::toStringETypeMsg(ETypeMsg msg_type)
{
    std::string str;
    switch (msg_type)
    {
    case ETypeMsg::REQ_NAVIG:
        str = "REQ_NAVIG";
        break;
    case ETypeMsg::REQ_TARGET:
        str = "REQ_TARGET";
        break;
    case ETypeMsg::REQ_WORKABILITY:
        str = "REQ_WORKABILITY";
        break;
    case ETypeMsg::REQ_ADDRESS_LIST:
        str = "REQ_ADDRESS_LIST";
        break;
    case ETypeMsg::REQ_MSG_TYPE_LIST:
        str = "REQ_MSG_TYPE_LIST";
        break;
    case ETypeMsg::REQ_POINT_LIST:
        str = "REQ_POINT_LIST";
        break;
    case ETypeMsg::REQ_CURRENT_COMMAND_PERFORM:
        str = "REQ_CURRENT_COMMAND_PERFORM";
        break;
    case ETypeMsg::RES_NAVIG:
        str = "RES_NAVIG";
        break;
    case ETypeMsg::RES_TARGET:
        str = "RES_TARGET";
        break;
    case ETypeMsg::RES_WORKABILITY:
        str = "RES_WORKABILITY";
        break;
    case ETypeMsg::RES_ADDRESS_LIST:
        str = "RES_ADDRESS_LIST";
        break;
    case ETypeMsg::RES_MSG_TYPE_LIST:
        str = "RES_MSG_TYPE_LIST";
        break;
    case ETypeMsg::RES_POINT_LIST:
        str = "RES_POINT_LIST";
        break;
    case ETypeMsg::RES_CURRENT_COMMAND_PERFORM:
        str = "RES_CURRENT_COMMAND_PERFORM";
        break;
    case ETypeMsg::CMD_SET_POINT_LIST:
        str = "CMD_SET_POINT_LIST";
        break;
    case ETypeMsg::CMD_CHANGE_POINT:
        str = "CMD_CHANGE_POINT";
        break;
    case ETypeMsg::CMD_SET_PATH:
        str = "CMD_SET_PATH";
        break;
    case ETypeMsg::CMD_MOVE_TO_POS:
        str = "CMD_MOVE_TO_POS";
        break;
    case ETypeMsg::SRV_START_MISSION:
        str = "SRV_START_MISSION";
        break;
    case ETypeMsg::SRV_STOP_MISSION:
        str = "SRV_STOP_MISSION";
        break;
    case ETypeMsg::SRV_MISSION_COMPLITE:
        str = "SRV_MISSION_COMPLITE";
        break;
    case ETypeMsg::SRV_SET_PID_PARAMS:
        str = "SRV_SET_PID_PARAMS";
        break;
    case ETypeMsg::SRV_SET_TIME:
        str = "SRV_SET_TIME";
        break;
    case ETypeMsg::SRV_REGISTER_ME:
        str = "SRV_REGISTER_ME";
        break;
    case ETypeMsg::ERR:
        str = "ERR";
        break;
    default:
        str = "Error type!";
        break;
    }

    return str;
}


void Message::createCrc(const char *mess, unsigned int len_mess, char *controlSum)
{
    unsigned short crc = 0xFFFF;
    while (len_mess--)
    {
        crc ^= *mess++ << 8;

        for (int i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    for (int i = 0; i < 2; i++)
    {
        crc ^= 0b0000'0000 << 8;
        for (int i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }

    controlSum[0] = (crc & 0b1111'1111'0000'0000) >> 8;
    controlSum[1] = crc & 0b1111'1111;
}

EPriority Message::getPriority()
{
    return m_priority;
}
EConfirm Message::getConfirm()
{
    return m_confirm;
}
SAddress Message::getAdrSender()
{
    return m_adr_sender;
}
SAddress Message::getAdrRecipient()
{
    return m_adr_recipient;
}
ETypeMsg Message::getTypeMsg()
{
    return m_type_msg;
}
int Message::getBuffSize()
{
    return m_buff_msg_len;
}
auto Message::getContent() -> ACBaseContent *
{
    return m_content;
}
char *Message::getBuffMsg()
{
    return m_buff_msg;
}
