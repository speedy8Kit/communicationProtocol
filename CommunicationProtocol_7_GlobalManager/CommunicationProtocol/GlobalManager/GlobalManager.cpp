#include "GlobalManager.h"
#include "UDP.h"
GlobalManager::GlobalManager(std::ifstream* file_config, std::ofstream* file_log):
	m_config_file{ file_config },
	m_log_file{ file_log },

	m_last_msg{ nullptr },
	m_length_msg_mngr_list{ 0 }
{
	m_map_address = new MapAddress();
	readConfigFile();
}

GlobalManager::~GlobalManager()
{
	delete m_map_address;

	for (int i = 0; i < m_length_msg_mngr_list; i++) {
		delete m_msg_mngr_list[i];
	}
	delete[] m_msg_mngr_list;
	delete m_last_msg;
	
	m_config_file->close();
	m_log_file->close();

	delete m_config_file;
	delete m_log_file;
}

int GlobalManager::routing()
{	
	for (size_t i = 0; i < m_length_msg_mngr_list; i++)
	{
		Message* msg = m_msg_mngr_list[i]->getNextMessage();
		if (msg) 
		{
			msg->loging(std::cout);
			if (msg->getTypeMsg() == ETypeMsg::SRV_REGISTER_ME &&
				msg->getConfirm() == EConfirm::REQUIRE_NOT_CONFIRM)
			{
				// проверяем подходит ли адрес для подключения
				if ( (msg->getAdrRecipient().MIDDLE == msg->getAdrRecipient().MIDDLE && 
					msg->getAdrRecipient().HIGH == msg->getAdrRecipient().HIGH) )
				{
					SAddress* adr_recip = new SAddress(msg->getAdrRecipient());
					registerMsgMngr(adr_recip, m_msg_mngr_list[i]);

					Message msg_reg(msg->getPriority(), EConfirm::NOT_REQUIRE_CONFIRM, m_current_addres,
						*adr_recip, msg->getTypeMsg());

					//Message msg_reg(msg->getPriority(), EConfirm::NOT_REQUIRE_CONFIRM, msg->getAdrRecipient(),
					//	msg->getAdrSender(), msg->getTypeMsg());

					m_msg_mngr_list[i]->sendMessage(msg_reg);
				}
				else // отправляем сообщение об ошибке
				{
					EPriority priority = EPriority::LOW;
					EConfirm confirm = EConfirm::NOT_REQUIRE_NOT_CONFIRM;
					SAddress adr_sender = msg->getAdrRecipient();
					delete msg;
					ETypeMsg type_mess = ETypeMsg::ERR;

					Message message_err(priority, confirm, adr_sender, m_current_addres,
						type_mess);
					m_msg_mngr_list[i]->sendMessage(message_err);
				}

			}
			else
			{
				MessageManager* msg_mngr =
					m_map_address->findExchangeInterface(SAddress(msg->getAdrSender()));
				if (msg_mngr) 
				{
					msg_mngr->sendMessage((Message&)msg);
					delete msg;
				}
				else
				{
					EPriority priority = EPriority::LOW;
					EConfirm confirm = EConfirm::NOT_REQUIRE_NOT_CONFIRM;
					SAddress adr_sender = msg->getAdrRecipient();
					delete msg;
					ETypeMsg type_mess = ETypeMsg::ERR;

					Message message_err(priority, confirm, adr_sender, m_current_addres,
						type_mess);
					msg_mngr->sendMessage(message_err);
					return 1;
				}
			}

		}
	}
	return 0;
}

void GlobalManager::openAllConnections()
{
	if (m_msg_mngr_list != nullptr)
	{
		closeAllConnections();
	}
	readConfigFile();
	for (size_t i = 0; i < m_length_msg_mngr_list; i++)
	{
		m_msg_mngr_list[i]->openExchangeInterface();
	}
}

void GlobalManager::closeAllConnections()
{
	for (size_t i = 0; i < m_length_msg_mngr_list; i++)
	{
		m_msg_mngr_list[i]->closeExchangeInterface();
	}
	delete m_map_address;
	m_map_address = new MapAddress();
	for (int i = 0; i < m_length_msg_mngr_list; i++) {
		delete m_msg_mngr_list[i];


	}

	m_length_msg_mngr_list = 0;
}

void GlobalManager::readConfigFile()
{
// дисериализация файла json
	std::string config_text;
	if (m_config_file->is_open())
	{
		std::string temp;
		while (getline(*m_config_file, temp))
		{
			config_text += temp;
		}
	}
	else {
		std::cout << "no config";
	}

	json config_json = json::parse(config_text);

	//##################################  m_msg_mngr_list  ##################################

// перебрать все виды доступных интерфейсов передачи данных
// 
// из-за отсутствия необходимости удобной модернизации, не выведенно в отдельную функцию
	for (auto element : config_json["UDPServer"]) 
	{
		std::string ip = element["IP"].get<std::string>();
		int port = element["port"].get<int>();

		ACExchangeInterface* temp_exi = new UDPServer(ip.c_str(), port);
		m_msg_mngr_list[m_length_msg_mngr_list] = new MessageManager(temp_exi);
		m_msg_mngr_list[m_length_msg_mngr_list]->openExchangeInterface();
		m_length_msg_mngr_list++;
	}
	for (auto element : config_json["UDPClient"])
	{
		std::string ip = element["IP"].get<std::string>();
		int port = element["port"].get<int>();

		ACExchangeInterface* temp_exi = new UDPClient(ip.c_str(), port);
		m_msg_mngr_list[m_length_msg_mngr_list] = new MessageManager(temp_exi);
		m_msg_mngr_list[m_length_msg_mngr_list]->openExchangeInterface();
		m_length_msg_mngr_list++;
	}
// при необходимости повторить аналогичные действия после цикла не для UDP
/*
for (auto element : config_json["INTERFACE"]) {
	создание ACExchangeInterface и добавление его в список.
}
*/

	//##################################  addres  ##################################

	m_current_addres.HIGH	=		config_json["address"]["HIGH"].get<int>();
	m_current_addres.MIDDLE =		config_json["address"]["MIDLE"].get<int>();
	m_current_addres.LOW	=		config_json["address"]["LOW"].get<int>();
}

void GlobalManager::registerMsgMngr(SAddress* addr, MessageManager* exclNTF)
{
		m_map_address->add(addr, exclNTF);
}

void GlobalManager::addToLog(Message& msg)
{
	 msg.logingNameHead(*m_log_file);
	 msg.loging(*m_log_file);
	 *m_log_file << ";\n";
}
