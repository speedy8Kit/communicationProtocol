#ifndef __CONTENTS_H__
#define __CONTENTS_H__

#include <cstring>
#include <iostream>
#include <string>

#include "StructsForContents.h"
#include "StructsForMessage.h"

// у менеджера нижнего уровня максимум 32 компонента
#define MAX_COMPONENTS_OF_MANAGER 32
// максимальное количество точек в маршруте 64
#define POINTS_OF_LIST 64
// хз
#define MAX_LEN_DESCRIPTION_COMPONENT 64

// основной класс наследниками которого являяются все содержания сообщений
// с его помощью и класса фабрики CreatorsComponents реализуется патерн фабрика классов

class ACBaseContent
{
protected:
	unsigned int m_size_content = 0;

public:
	virtual void marshall(char *m_buff) = 0;
	virtual void unmarshall(const char *m_buff) = 0;

	// вставляется как заголовок для наглядности, подписывает значение каждого столбца
	virtual std::string toStringHeaders() = 0;
	// представляет все данные в виде строки, разделенные знаком ";"
	virtual std::string toString() = 0;

	unsigned int get_size() { return m_size_content; }
};

//  ###############################################################################
//  /////////////////////////// CONCRET_CONTENTS //////////////////////////////////
//  ###############################################################################

// ////////////////////////////// NavigContent ////////////////////////////////////

class EmptyContent : public ACBaseContent
{
public:
	virtual void marshall(char *m_buff) {}
	virtual void unmarshall(const char *m_buff) {}
	std::string toStringHeaders() { return ""; };
	std::string toString() { return ""; }
	EmptyContent(){};
};

// ////////////////////////////// NavigContent ////////////////////////////////////

class NavigContent : public ACBaseContent
{
	SKinematicParams m_navig_data;

public:
	void marshall(char *m_buff);
	void unmarshall(const char *m_buff);
	NavigContent(SKinematicParams navig_data);
	NavigContent(const char *m_buff);
	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// TargetContent ////////////////////////////////////

class TargetContent : public ACBaseContent
{
private:
	SKinematicParams m_target_data;

public:
	TargetContent(SKinematicParams target_data);
	TargetContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// WorkabilityContent ////////////////////////////////////

class WorkabilityContent : public ACBaseContent
{
private:
	EWorkability m_workability;

public:
	WorkabilityContent(EWorkability alive);
	WorkabilityContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// AddrListContent ////////////////////////////////////

class AddrListContent : public ACBaseContent
{
private:
	unsigned int m_len_addr_list;
	int *m_addr_list; // int[MAX_COMPONENTS_OF_MANAGER];

public:
	AddrListContent(int *addr_list, unsigned int len_addr_list);
	AddrListContent(const char *buf, unsigned int size);
	~AddrListContent();

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// MsgTypeListContent ////////////////////////////////////

class MsgTypeListContent : public ACBaseContent
{
private:
	ETypeMsg* m_msg_type_list; // new ETypeMsg[int(ETypeMsg::MAX_TYP_MSG)];
	unsigned int m_len_msg_type_list;

public:
	MsgTypeListContent(ETypeMsg *msg_type_list, unsigned int len_msg_type_list);
	MsgTypeListContent(const char *buf, unsigned int size);
	~MsgTypeListContent();

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// PointListContent ////////////////////////////////////

class PointListContent : public ACBaseContent
{
private:
	SPoint m_point_list[POINTS_OF_LIST];

public:
	PointListContent(SPoint point_list[POINTS_OF_LIST]);
	PointListContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// CurrentCmdContent ////////////////////////////////////

class CurrentCmdContent : public ACBaseContent
{
private:
	SCurrentCmd m_current_cmd;

public:
	CurrentCmdContent(SCurrentCmd current_cmd);
	CurrentCmdContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// ChangePointContent ////////////////////////////////////

class ChangePointContent : public ACBaseContent
{
private:
	SChangePoint m_change_point;

public:
	ChangePointContent(SChangePoint change_point);
	ChangePointContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// SET_PATHContent ////////////////////////////////////

class PathContent : public ACBaseContent
{
private:
	SPath *m_path;
	unsigned int m_len_path;
public:
	PathContent(SPath* path, unsigned int len_path);
	PathContent(const char* buf, unsigned int size);
	~PathContent();

	void marshall(char* buf);
	void unmarshall(const char* buf);

	std::string toStringHeaders();
	std::string toString();
};


// ////////////////////////////// MoveToPosContent ////////////////////////////////////

class MoveToPosContent : public ACBaseContent
{
private:
	SMoveToPos m_move_to_pos;

public:
	MoveToPosContent(SMoveToPos move_to_pos);
	MoveToPosContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// MissionCompleteContent ////////////////////////////////////

class MissionCompleteContent : public ACBaseContent
{
private:
	bool m_target_reached;

public:
	MissionCompleteContent(bool target_reached);
	MissionCompleteContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// PIDParamsContent ////////////////////////////////////

class PIDParamsContent : public ACBaseContent
{
private:
	SPIDParams m_pid;

public:
	PIDParamsContent(SPIDParams pid);
	PIDParamsContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// SetTimeContent ////////////////////////////////////

class SetTimeContent : public ACBaseContent
{
private:
	double m_time;

public:
	SetTimeContent(double time);
	SetTimeContent(const char *buf);

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

// ////////////////////////////// RegisterContent ////////////////////////////////////

class RegisterContent : public ACBaseContent
{
private:
	char* m_description_component;
	unsigned int m_len_description_component;

public:
	RegisterContent(std::string description_component);
	RegisterContent(const char *buf, unsigned int size);
	~RegisterContent();

	void marshall(char *buf);
	void unmarshall(const char *buf);

	std::string toStringHeaders();
	std::string toString();
};

#endif // __CONTENTS_H__
