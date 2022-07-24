#include "ACBaseComponent.h"


using json = nlohmann::json;

ACBaseComponent::ACBaseComponent(ofstream* log_file,
	ifstream* config_file, const long int update_time_millis) :
	m_message_manager{ nullptr },
	m_log_file{ log_file },
	m_config_file{ config_file }
{

	m_start_time = clock();
	m_update_time_mills = update_time_millis;
	readConfigFile();

}



ACBaseComponent::~ACBaseComponent()
{
	delete m_config_file;
	delete m_log_file;
	delete m_message_manager;
}

int ACBaseComponent::mainLoop()
{
	if (isUpdateTime())
		timerWork();
	Message* msgPtr = m_message_manager->getNextMessage();
	if (msgPtr != nullptr)
	{
		messageProcessing(msgPtr);
		delete msgPtr;
	}
	return 0;
}
void ACBaseComponent::addToLog(Message* msg)
{
	msg->logingNameHead((ostream&)m_log_file);
	msg->loging((ostream&)m_log_file);
}

void ACBaseComponent::readConfigFile()
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

	m_addr_manager.HIGH = config_json["address"]["HIGH"];
	m_addr_manager.MIDDLE = config_json["address"]["MIDLE"];
	m_addr_manager.LOW = config_json["address"]["LOW"];
}

bool ACBaseComponent::isUpdateTime(const long int delay_micro_seconds)
{
	if (clock() - m_last_time > m_update_time_mills)
	{
		m_last_time = clock();
		return true;
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::microseconds(delay_micro_seconds));
		return false;
	}
}
