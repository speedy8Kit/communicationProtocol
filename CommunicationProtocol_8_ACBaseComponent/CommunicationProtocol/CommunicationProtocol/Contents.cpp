#include "Contents.h"

/////////////////////////////////////////////////////////////////////////////////{

NavigContent::NavigContent(SKinematicParams navig_data)
{
	m_navig_data = navig_data;
	m_size_content = sizeof(SKinematicParams);
}
NavigContent::NavigContent(const char *buf)
{
	m_size_content = sizeof(SKinematicParams);
	unmarshall(buf);
}
void NavigContent::marshall(char *buf)
{
	memcpy(buf, &m_navig_data, m_size_content);
}
void NavigContent::unmarshall(const char *buf)
{
	memcpy(&m_navig_data, buf, m_size_content);
}
std::string NavigContent::toStringHeaders()
{
	std::string str;
	str += "PosX; PosY; PosZ; PosPhi; PosTheta; PosPsi;";
	str += "VelX; VelY; VelZ; VelPhi; VelTheta; VelPsi;";
	str += "AccX; AccY; AccZ; AccPhi; AccTheta; AccPsi;";
	return str;
}
std::string NavigContent::toString()
{
	std::string str;

	str += std::to_string(m_navig_data.position.x) + ";";
	str += std::to_string(m_navig_data.position.y) + ";";
	str += std::to_string(m_navig_data.position.z) + ";";
	str += std::to_string(m_navig_data.position.phi) + ";";
	str += std::to_string(m_navig_data.position.thetta) + ";";
	str += std::to_string(m_navig_data.position.psi) + ";";

	str += std::to_string(m_navig_data.velocity.x) + ";";
	str += std::to_string(m_navig_data.velocity.y) + ";";
	str += std::to_string(m_navig_data.velocity.z) + ";";
	str += std::to_string(m_navig_data.velocity.phi) + ";";
	str += std::to_string(m_navig_data.velocity.thetta) + ";";
	str += std::to_string(m_navig_data.velocity.psi) + ";";

	str += std::to_string(m_navig_data.acceleration.x) + ";";
	str += std::to_string(m_navig_data.acceleration.y) + ";";
	str += std::to_string(m_navig_data.acceleration.z) + ";";
	str += std::to_string(m_navig_data.acceleration.phi) + ";";
	str += std::to_string(m_navig_data.acceleration.thetta) + ";";
	str += std::to_string(m_navig_data.acceleration.psi) + ";";

	return str;
}

/////////////////////////////////////////////////////////////////////////////////

TargetContent::TargetContent(SKinematicParams target_data)
{
	m_target_data = target_data;
	m_size_content = sizeof(SKinematicParams);
}
TargetContent::TargetContent(const char *buf)
{
	m_size_content = sizeof(SKinematicParams);
	unmarshall(buf);
}
void TargetContent::marshall(char *buf)
{
	memcpy(buf, &m_target_data, m_size_content);
}
void TargetContent::unmarshall(const char *buf)
{
	memcpy(&m_target_data, buf, m_size_content);
}
std::string TargetContent::toStringHeaders()
{
	std::string str;
	str += "Pos_X; Pos_Y; Pos_Z; Pos_Phi; Pos_Thetta; Pos_Psi;";
	str += "Vel_X; Vel_Y; Vel_Z; Vel_Phi; Vel_Thetta; Vel_Psi;";
	str += "Acc_X; Acc_Y; Acc_Z; Acc_Phi; Acc_Thetta; Acc_Psi;";
	return str;
}
std::string TargetContent::toString()
{
	std::string str;
	str = "( ";
	str += std::to_string(m_target_data.position.x) + ";";
	str += std::to_string(m_target_data.position.y) + ";";
	str += std::to_string(m_target_data.position.z) + ";";
	str += std::to_string(m_target_data.position.phi) + ";";
	str += std::to_string(m_target_data.position.thetta) + ";";
	str += std::to_string(m_target_data.position.psi) + ";";

	str += std::to_string(m_target_data.velocity.x) + ";";
	str += std::to_string(m_target_data.velocity.y) + ";";
	str += std::to_string(m_target_data.velocity.z) + ";";
	str += std::to_string(m_target_data.velocity.phi) + ";";
	str += std::to_string(m_target_data.velocity.thetta) + ";";
	str += std::to_string(m_target_data.velocity.psi) + ";";

	str += std::to_string(m_target_data.acceleration.x) + ";";
	str += std::to_string(m_target_data.acceleration.y) + ";";
	str += std::to_string(m_target_data.acceleration.z) + ";";
	str += std::to_string(m_target_data.acceleration.phi) + ";";
	str += std::to_string(m_target_data.acceleration.thetta) + ";";
	str += std::to_string(m_target_data.acceleration.psi) + ";";
	return str;

	////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////

WorkabilityContent::WorkabilityContent(EWorkability alive)
{
	m_workability = alive;
	m_size_content = sizeof(EWorkability);
}
WorkabilityContent::WorkabilityContent(const char *buf)
{
	m_size_content = sizeof(EWorkability);
	unmarshall(buf);
}
void WorkabilityContent::marshall(char *buf)
{
	memcpy(buf, &m_workability, m_size_content);
}
void WorkabilityContent::unmarshall(const char *buf)
{
	memcpy(&m_workability, buf, m_size_content);
}
std::string WorkabilityContent::toStringHeaders()
{
	std::string str;
	str += "Workability;";
	return str;
}
std::string WorkabilityContent::toString()
{
	std::string str;
	str += std::to_string((short)m_workability) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

AddrListContent::AddrListContent(int *addr_list, unsigned int len_addr_list)
{
	if (len_addr_list > MAX_COMPONENTS_OF_MANAGER) {}
	m_len_addr_list = len_addr_list;
	m_addr_list = addr_list;
	m_size_content = sizeof(int) * m_len_addr_list;
}
AddrListContent::AddrListContent(const char *buf, unsigned int size)
{
	m_size_content = size;
	m_len_addr_list = m_size_content / sizeof(int);
	m_addr_list = new int[m_len_addr_list];
	unmarshall(buf);
}
AddrListContent::~AddrListContent()
{
	delete[] m_addr_list;
}
void AddrListContent::marshall(char *buf)
{
	memcpy(buf, m_addr_list, m_size_content);
}
void AddrListContent::unmarshall(const char *buf)
{
	memcpy(m_addr_list, buf, m_size_content);
}
std::string AddrListContent::toStringHeaders()
{
	std::string str;
	for (int i = 0; i < m_len_addr_list; i++)
		str += "Addr_" + std::to_string(i) + ";";
	return str;
}
std::string AddrListContent::toString()
{
	std::string str;
	for (int i = 0; i < m_len_addr_list; i++)
		str += std::to_string(m_addr_list[i]) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

MsgTypeListContent::MsgTypeListContent(ETypeMsg *msg_type_list, unsigned int len_msg_type_list)
{
	if (len_msg_type_list > int(ETypeMsg::MAX_TYP_MSG)) {}

	m_len_msg_type_list = len_msg_type_list;
	m_msg_type_list = msg_type_list;
	m_size_content = sizeof(ETypeMsg) * len_msg_type_list;
}
MsgTypeListContent::MsgTypeListContent(const char *buf, unsigned int size)
{
	m_size_content = size;
	m_len_msg_type_list = int(m_size_content / sizeof(ETypeMsg));
	m_msg_type_list = new ETypeMsg[m_len_msg_type_list];
	unmarshall(buf);
}
MsgTypeListContent::~MsgTypeListContent()
{
	delete[] m_msg_type_list;
}
void MsgTypeListContent::marshall(char *buf)
{
	memcpy(buf, m_msg_type_list, m_size_content);
}
void MsgTypeListContent::unmarshall(const char *buf)
{
	memcpy(m_msg_type_list, buf, m_size_content);
}
std::string MsgTypeListContent::toStringHeaders()
{
	std::string str;
	for (int i = 0; i < m_len_msg_type_list; i++)
		str += "MsgType_" + std::to_string(i) + ";";
	return str;
}
std::string MsgTypeListContent::toString()
{
	std::string str;
	for (int i = 0; i < m_len_msg_type_list; i++)
		str += std::to_string((char)m_msg_type_list[i]) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

PointListContent::PointListContent(SPoint point_list[POINTS_OF_LIST])
{
	for (int i = 0; i < POINTS_OF_LIST; i++)
	{
		m_point_list[i] = point_list[i];
	}

	m_size_content = sizeof(SPoint) * POINTS_OF_LIST;
}
PointListContent::PointListContent(const char *buf)
{
	m_size_content = sizeof(SPoint) * POINTS_OF_LIST;
	unmarshall(buf);
}
void PointListContent::marshall(char *buf)
{
	memcpy(buf, m_point_list, m_size_content);
}
void PointListContent::unmarshall(const char *buf)
{
	memcpy(m_point_list, buf, m_size_content);
}
std::string PointListContent::toStringHeaders()
{
	std::string str;
	for (int i = 0; i < POINTS_OF_LIST; i++)
	{
		str += "Pos_X_" + std::to_string(i) + ";";
		str += "Pos_Y_" + std::to_string(i) + ";";
		str += "Pos_Z_" + std::to_string(i) + ";";
	}
	return str;
}
std::string PointListContent::toString()
{
	std::string str;
	for (int i = 0; i < POINTS_OF_LIST; i++)
	{
		str += std::to_string(m_point_list[i].x) + ";";
		str += std::to_string(m_point_list[i].y) + ";";
		str += std::to_string(m_point_list[i].z) + ";";
	}
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

CurrentCmdContent::CurrentCmdContent(SCurrentCmd current_cmd)
{
	m_current_cmd = current_cmd;
	m_size_content = sizeof(SCurrentCmd);
}
CurrentCmdContent::CurrentCmdContent(const char *buf)
{
	m_size_content = sizeof(SCurrentCmd);
	unmarshall(buf);
}
void CurrentCmdContent::marshall(char *buf)
{
	memcpy(buf, &m_current_cmd, m_size_content);
}
void CurrentCmdContent::unmarshall(const char *buf)
{
	memcpy(&m_current_cmd, buf, m_size_content);
}
std::string CurrentCmdContent::toStringHeaders()
{
	std::string str;
	str += "CurCmd; %;";
	return str;
}
std::string CurrentCmdContent::toString()
{
	std::string str;
	str += std::to_string((char)m_current_cmd.msg_type) + ";";
	str += std::to_string(m_current_cmd.percent) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

ChangePointContent::ChangePointContent(SChangePoint change_point)
{
	m_change_point = change_point;
	m_size_content = sizeof(SChangePoint);
}
ChangePointContent::ChangePointContent(const char *buf)
{
	m_size_content = sizeof(SChangePoint);
	unmarshall(buf);
}
void ChangePointContent::marshall(char *buf)
{
	memcpy(buf, &m_change_point, m_size_content);
}
void ChangePointContent::unmarshall(const char *buf)
{
	memcpy(&m_change_point, buf, m_size_content);
}
std::string ChangePointContent::toStringHeaders()
{
	std::string str;
	str += "PointX; PointY; PointZ; number;";
	return str;
}
std::string ChangePointContent::toString()
{
	std::string str;
	str += std::to_string(m_change_point.point.x) + ";";
	str += std::to_string(m_change_point.point.y) + ";";
	str += std::to_string(m_change_point.point.z) + ";";
	str += std::to_string(m_change_point.number) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

MoveToPosContent::MoveToPosContent(SMoveToPos move_to_pos)
{
	m_move_to_pos = move_to_pos;
	m_size_content = sizeof(SMoveToPos);
}
MoveToPosContent::MoveToPosContent(const char *buf)
{
	m_size_content = sizeof(SMoveToPos);
	unmarshall(buf);
}
void MoveToPosContent::marshall(char *buf)
{
	memcpy(buf, &m_move_to_pos, m_size_content);
}
void MoveToPosContent::unmarshall(const char *buf)
{
	memcpy(&m_move_to_pos, buf, m_size_content);
}
std::string MoveToPosContent::toStringHeaders()
{
	std::string str;
	str += "Pos_X; Pos_Y; Pos_Z; Pos_phi; Pos_thetta; Pos_psi; v;";
	return str;
}
std::string MoveToPosContent::toString()
{
	std::string str;
	str += std::to_string(m_move_to_pos.position.x) + ";";
	str += std::to_string(m_move_to_pos.position.y) + ";";
	str += std::to_string(m_move_to_pos.position.z) + ";";
	str += std::to_string(m_move_to_pos.position.phi) + ";";
	str += std::to_string(m_move_to_pos.position.thetta) + ";";
	str += std::to_string(m_move_to_pos.position.psi) + ";";
	str += std::to_string(m_move_to_pos.v) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

MissionCompleteContent::MissionCompleteContent(bool target)
{
	m_target_reached = target;
	m_size_content = sizeof(bool);
}
MissionCompleteContent::MissionCompleteContent(const char *buf)
{
	m_size_content = sizeof(bool);
	unmarshall(buf);
}
void MissionCompleteContent::marshall(char *buf)
{
	memcpy(buf, &m_target_reached, m_size_content);
}
void MissionCompleteContent::unmarshall(const char *buf)
{
	memcpy(&m_target_reached, buf, m_size_content);
}
std::string MissionCompleteContent::toStringHeaders()
{
	std::string str;
	str += "TargAchv;";
	return str;
}
std::string MissionCompleteContent::toString()
{
	std::string str;
	str += std::to_string(m_target_reached) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

PIDParamsContent::PIDParamsContent(SPIDParams pid)
{
	m_pid = pid;
	m_size_content = sizeof(SPIDParams);
}
PIDParamsContent::PIDParamsContent(const char *buf)
{
	m_size_content = sizeof(SPIDParams);
	unmarshall(buf);
}
void PIDParamsContent::marshall(char *buf)
{
	memcpy(buf, &m_pid, m_size_content);
}
void PIDParamsContent::unmarshall(const char *buf)
{
	memcpy(&m_pid, buf, m_size_content);
}
std::string PIDParamsContent::toStringHeaders()
{
	std::string str;
	str += "k_p; k_i; k_d;";
	return str;
}
std::string PIDParamsContent::toString()
{
	std::string str;
	str += std::to_string(m_pid.k_p) + ";";
	str += std::to_string(m_pid.k_i) + ";";
	str += std::to_string(m_pid.k_d) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

SetTimeContent::SetTimeContent(double time)
{
	m_time = time;
	m_size_content = sizeof(double);
}
SetTimeContent::SetTimeContent(const char *buf)
{
	m_size_content = sizeof(double);
	unmarshall(buf);
}
void SetTimeContent::marshall(char *buf)
{
	memcpy(buf, &m_time, m_size_content);
}
void SetTimeContent::unmarshall(const char *buf)
{
	memcpy(&m_time, buf, m_size_content);
}
std::string SetTimeContent::toStringHeaders()
{
	std::string str;
	str += "Time;";
	return str;
}
std::string SetTimeContent::toString()
{
	std::string str;
	str += std::to_string(m_time) + ";";
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

RegisterContent::RegisterContent(std::string description_component)
{
	m_len_description_component = description_component.length();
	m_description_component = new char[m_len_description_component];
	for (size_t i = 0; i < m_len_description_component; i++)
	{
		m_description_component[i] = description_component[i];
	}
	m_size_content = sizeof(char) * m_len_description_component;

}
RegisterContent::RegisterContent(const char *buf, unsigned int size)
{
	m_size_content = size;
	m_len_description_component = int(size / sizeof(char));
	m_description_component = new char[m_len_description_component];
	unmarshall(buf);
}
RegisterContent::~RegisterContent()
{
	delete[] m_description_component;
}
void RegisterContent::marshall(char *buf)
{
	memcpy(buf, m_description_component, m_size_content);
}
void RegisterContent::unmarshall(const char *buf)
{
	memcpy(m_description_component, buf, m_size_content);
}
std::string RegisterContent::toStringHeaders()
{
	std::string str;
	str += "RegCmp;";
	return str;
}
std::string RegisterContent::toString()
{
	std::string str;
	for (int i = 0; i < m_len_description_component; i++)
		str += m_description_component[i];
	str += ";";
	return str;
}


//////////////////////////////////////////////////////////////////////////////////

PathContent::PathContent(SPath* path, unsigned int len_path) {
	m_len_path = len_path;
	m_size_content = sizeof(SPath) * len_path;
	m_path = path;
}

PathContent::PathContent(const char* buf, unsigned int size) {
	m_size_content = size;
	m_len_path = int(size / sizeof(SPath));
	m_path = new SPath[m_len_path];
	unmarshall(buf);
}
PathContent::~PathContent() {
	delete[] m_path;
}
void PathContent::marshall(char* buf)
{
	memcpy(buf, m_path, m_size_content);
}
void PathContent::unmarshall(const char* buf)
{
	memcpy(m_path, buf, m_size_content);
}

std::string PathContent::toStringHeaders(){
	std::string str;
	for (int i = 0; i < m_len_path; i++)
	{
		str += "pointt_" + std::to_string(i) + ";";
		str += "velocity_" + std::to_string(i) + ";";
		str += "traj_" + std::to_string(i) + ";";
	}
	return str;
}
std::string PathContent::toString(){
	std::string str;
	for (int i = 0; i < m_len_path; i++)
	{
		str += std::to_string(m_path[i].point) + ";";
		str += std::to_string(m_path[i].v) + ";";
		switch (m_path[i].traj_type)
		{
		case ETrajType::LINE:
			str += "LINE;";
			break;
		case ETrajType::SPLINE_ERMITH:
			str += "SPLINE_ERMITH;";
			break;
		case ETrajType::TO_POINT:
			str += "TO_POINT;";
			break;
		default:
			break;
		}
	}
	return str;
}