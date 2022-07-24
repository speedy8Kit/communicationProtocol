#pragma once
#include "MessageManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <chrono>
#include <thread>


class ACBaseComponent
{
public:
	ACBaseComponent(ofstream* m_log_file, ifstream* m_config_file,
					const long int update_time_millis = 50);
	~ACBaseComponent();

	virtual int init() = 0;
	int mainLoop();
	void addToLog(Message* msg);
private:
	clock_t m_start_time;
	clock_t m_last_time;

	long int m_update_time_mills;

	SAddress m_addr_curent;
	SAddress m_addr_manager;

	Message* m_last_msg;

	MessageManager* m_message_manager;

	std::ofstream* m_log_file;
	std::ifstream* m_config_file;
/// <summary>
/// программа не расчитана на неоднократный вызов функции чтения конфигураций
/// </summary>
	void readConfigFile();
	bool isUpdateTime(const long int delay_micro_seconds = 500);

	virtual void timerWork() {};
	virtual long int messageProcessing(Message* msg) = 0;
};
