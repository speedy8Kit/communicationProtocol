#pragma once

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "MapAddress.h"


class GlobalManager
{
public:
	GlobalManager(std::ifstream* file_config, std::ofstream* file_log);
	~GlobalManager();

	int routing();

/// <summary>
/// открывет все порты из файла конфигураций, если они уже окрывались, закрывает старые
/// </summary>
	void openAllConnections();
	void closeAllConnections();

private:
/// <summary>
/// программа не расчитана на неоднократный вызов функции чтения конфигураций
/// </summary>
	void readConfigFile();
	void registerMsgMngr(SAddress* addr, MessageManager* exclNTF);
	void addToLog(Message& msg);

	std::ifstream* m_config_file;
	std::ofstream* m_log_file;

// список возможных подключений, он создается на основании конфигурационного файла (m_config_file)
	MessageManager** m_msg_mngr_list = new MessageManager * [32];
	int m_length_msg_mngr_list;

	SAddress m_current_addres;
	MapAddress* m_map_address;
	Message* m_last_msg;


};