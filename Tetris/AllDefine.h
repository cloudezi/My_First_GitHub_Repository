#pragma once
#include<iostream>
#include<windows.h>
#include<time.h>
using namespace std;
//显示类型枚举
enum
{
	SPACE,
	MOVE_BLOCK,
	STOP_BLOCK,
	WALL,
};
//方块种类枚举
enum
{
	I_BLOCK,
	L_BLOCK,
	J_BLOCK,
	S_BLOCK,
	Z_BLOCK,
	T_BLOCK,
	O_BLOCK,
	MAX_BLOCK_NUM,
};
#define MAP_WIDTH  19//地图宽
#define MAP_HEIGHT 22//地图高
//2维坐标点
struct Position
{
	int m_iX;
	int m_iY;
	Position()
	{
		m_iX = -1;
		m_iY = -1;
	}
	Position( int X, int Y )
	{
		m_iX = X;
		m_iY = Y;
	}
};
void Erasure( int iX, int iY );