#pragma once
#include<iostream>
#include<windows.h>
#include<time.h>
using namespace std;
//��ʾ����ö��
enum
{
	SPACE,
	MOVE_BLOCK,
	STOP_BLOCK,
	WALL,
};
//��������ö��
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
#define MAP_WIDTH  19//��ͼ��
#define MAP_HEIGHT 22//��ͼ��
//2ά�����
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