#ifndef __STRUCTS_FOR_MESSAGE_H__
#define __STRUCTS_FOR_MESSAGE_H__

struct SAddress
{
    //3 ����
    unsigned char HIGH;
    //4 ����
    unsigned char MIDDLE;
    // 5 �����
    unsigned char LOW;

};

enum class EPriority
{
    LOW,
    NORM,
    HIGH,
    CRITICAL
};

enum class EConfirm
{
    NOT_REQUIRE_NOT_CONFIRM,
    REQUIRE_NOT_CONFIRM,
    NOT_REQUIRE_CONFIRM
};

enum class ETypeMsg
{
    REQ_NAVIG = 0,
    REQ_TARGET,
    REQ_WORKABILITY,
    REQ_ADDRESS_LIST,
    REQ_MSG_TYPE_LIST,
    REQ_POINT_LIST,
    REQ_CURRENT_COMMAND_PERFORM,


    // ��������� ���������� ���� ����� (16 �����) ������������� ������
    RES_NAVIG = 10,
    // ��������� ���������� ���� ����� (16 �����) ������ � ����
    RES_TARGET,
    // ��������� ������������ ���� �����������������
    RES_WORKABILITY,
    // �������� ���������� ������ ������� ����������� ������������ � ����
    RES_ADDRESS_LIST,
    // ��������� ���������� ������ ������ � �������� ����� ��������
    RES_MSG_TYPE_LIST,
    // ��������� ���������� ������ ����� �� ������� ������ ������������ �����
    RES_POINT_LIST,
    // ������ ���������� ������� ������� ������ �����������
    RES_CURRENT_COMMAND_PERFORM,


    CMD_SET_POINT_LIST = 20,
    CMD_CHANGE_POINT,
    CMD_SET_PATH,
    CMD_MOVE_TO_POS,

    SRV_START_MISSION = 40,
    SRV_STOP_MISSION,
    SRV_MISSION_COMPLITE,
    SRV_SET_PID_PARAMS,
    SRV_SET_TIME,
    SRV_REGISTER_ME,

    ERR = 50,
    MAX_TYP_MSG = 64
};



#endif //__STRUCTS_FOR_MESSAGE_H__