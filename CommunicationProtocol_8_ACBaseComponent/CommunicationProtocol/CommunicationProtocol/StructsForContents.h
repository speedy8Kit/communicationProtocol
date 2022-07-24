#pragma once

#include "StructsForMessage.h"

struct SCordinates
{
    float x, y, z, phi, thetta, psi;
};


struct SKinematicParams // для NAVIG и TARGET
{
	SCordinates position{ NULL };
    SCordinates velocity{ NULL };
    SCordinates acceleration{ NULL };
};


enum class EWorkability
{
	IS_OK = 0,
	NOT_OK = 1
};

struct SPoint
{
	float x, y, z;
};

struct SPointList
{
	SPoint point[64];
	//	SPoint* point = new SPoint[64];
};

enum class ETrajType
{
	TO_POINT,
	LINE,
	SPLINE_ERMITH
};

struct SPath {
	char point;
	float v;
	ETrajType traj_type;
};

enum class ETargetPointAchieve
{
	YES,
	NO
};

struct SCurrentCmd
{
	ETypeMsg msg_type{ ETypeMsg(NULL) };
	char percent{ NULL };
};

struct SChangePoint
{
	SPoint point;
	char number;
};

struct SMoveToPos
{
	SCordinates position;
	float v;
};

struct SPIDParams
{
	float k_p, k_i, k_d;
};

