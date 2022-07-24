#ifndef __STRUCTS_FOR_MESSAGE_H__
#define __STRUCTS_FOR_MESSAGE_H__

struct SAddress
{
    //3 бита
    unsigned char HIGH;
    //4 бита
    unsigned char MIDDLE;
    // 5 битов
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


    // компонент отправляет весь набор (16 чисел) навигационных данных
    RES_NAVIG = 10,
    // компонент отправляет весь набор (16 чисел) данных о целе
    RES_TARGET,
    // компонент подтверждает свою работоспособность
    RES_WORKABILITY,
    // менеджер отправляет список адресов компонентов подключенных к нему
    RES_ADDRESS_LIST,
    // компонент отправляет список команд с которыми может работать
    RES_MSG_TYPE_LIST,
    // компонент отправляет список точек по которым должен перемещаться робот
    RES_POINT_LIST,
    // модуль отправляет команду которая сейчас выполняется
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