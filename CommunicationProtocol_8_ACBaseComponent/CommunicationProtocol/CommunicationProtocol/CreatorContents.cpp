#include "CreatorContents.h"

// класс фабрика отвечающий за определение класса содержания сообщения
ACBaseContent *CreatorContents::createContent(ETypeMsg msg_type, const char *buf, unsigned int size)
{
	{
		switch (msg_type)
		{
			// пустое сообщение. Запросы
		case ETypeMsg::REQ_NAVIG:
		case ETypeMsg::REQ_TARGET:
		case ETypeMsg::REQ_WORKABILITY:
		case ETypeMsg::REQ_ADDRESS_LIST:
		case ETypeMsg::REQ_MSG_TYPE_LIST:
		case ETypeMsg::REQ_POINT_LIST:
		case ETypeMsg::REQ_CURRENT_COMMAND_PERFORM:
			return new EmptyContent();

			// ответы
		case ETypeMsg::RES_NAVIG:
			return new NavigContent(buf);
		case ETypeMsg::RES_TARGET:
			return new TargetContent(buf);
		case ETypeMsg::RES_WORKABILITY:
			return new WorkabilityContent(buf);
		case ETypeMsg::RES_ADDRESS_LIST:
			return new AddrListContent(buf, size);
		case ETypeMsg::RES_MSG_TYPE_LIST:
			return new MsgTypeListContent(buf, size);
		case ETypeMsg::RES_POINT_LIST:
			return new PointListContent(buf);
		case ETypeMsg::RES_CURRENT_COMMAND_PERFORM:
			return new CurrentCmdContent(buf);

			// команды
		case ETypeMsg::CMD_SET_POINT_LIST:
			break;
		case ETypeMsg::CMD_CHANGE_POINT:
			return new ChangePointContent(buf);
		case ETypeMsg::CMD_SET_PATH:
			return new PathContent(buf, size);
		case ETypeMsg::CMD_MOVE_TO_POS:
			return new MoveToPosContent(buf);

			// пустые сервисные сообщения.
		case ETypeMsg::SRV_START_MISSION:
		case ETypeMsg::SRV_STOP_MISSION:
			return new EmptyContent();

			// сервисные
		case ETypeMsg::SRV_MISSION_COMPLITE:
			return new MissionCompleteContent(buf);
		case ETypeMsg::SRV_SET_PID_PARAMS:
			return new PIDParamsContent(buf);
		case ETypeMsg::SRV_SET_TIME:
			return new SetTimeContent(buf);
		case ETypeMsg::SRV_REGISTER_ME:
			return new RegisterContent(buf, size);
			
			//ошибки
		case ETypeMsg::ERR:
			return new EmptyContent();
		default:
			std::cout << "ERRRRROOOOORRRRR!!!! (CreatorContents::createContent)";
			return new EmptyContent();
		}
	}
}
