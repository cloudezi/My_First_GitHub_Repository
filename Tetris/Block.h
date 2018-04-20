#include"AllDefine.h"
//基础方块
class BasicBlock
{	
public:
	Position m_FourPos[4];//由4块组成
	bool m_bMove;//可否移动
	BasicBlock()//构造函数——默认可移动
	{
		m_bMove = true;
	}
	void Fall()//下落
	{
		for( int i=0;i<4;i++ )
		{	
			m_FourPos[i].m_iY++;
		}
	}
	void Move( char cInput )//移动
	{
		int iMove=0;
		if( 'A' == cInput || 'a' == cInput )
		{
			iMove = -1;
		}
		else if( 'D' == cInput || 'd' == cInput )
		{
			iMove = 1;
		}
		if( iMove != 0 )
		{
			for( int i=0;i<4;i++ )
			{	
				m_FourPos[i].m_iX += iMove;
			}
		}
	}
	void Transfrom( Position Center )//绕指定中心点旋转90°变形
	{
		int rx0 = Center.m_iX;
		int ry0 = Center.m_iY;
		for( int i=0;i<4;i++ )
		{	
			int x = m_FourPos[i].m_iX;
			int y = m_FourPos[i].m_iY;
			m_FourPos[i].m_iX = (x - rx0)*0 - (y - ry0)*1 + rx0;
			m_FourPos[i].m_iY = (x - rx0)*1 + (y - ry0)*0 + ry0;
		}
	}
	//坐标中任意点(x,y)，绕一个坐标点(rx0,ry0)逆时针旋转a角度后的新的坐标设为(x0, y0)，有公式：
	//x0= (x - rx0)*cos(a) - (y - ry0)*sin(a) + rx0 ;    y0= (x - rx0)*sin(a) + (y - ry0)*cos(a) + ry0 ;
};
class I_Block : public BasicBlock
{
public:
	I_Block()
	{
		m_FourPos[0].m_iX = MAP_WIDTH/2 -2;
		m_FourPos[0].m_iY = 0;

		m_FourPos[1].m_iX = MAP_WIDTH/2 -1;
		m_FourPos[1].m_iY = 0;

		m_FourPos[2].m_iX = MAP_WIDTH/2;
		m_FourPos[2].m_iY = 0;

		m_FourPos[3].m_iX = MAP_WIDTH/2 +1;
		m_FourPos[3].m_iY = 0;
	}
};
class L_Block : public BasicBlock
{
public:
	L_Block()
	{
		m_FourPos[0].m_iX = MAP_WIDTH/2;
		m_FourPos[0].m_iY = 0;

		m_FourPos[1].m_iX = MAP_WIDTH/2;
		m_FourPos[1].m_iY = 1;

		m_FourPos[2].m_iX = MAP_WIDTH/2;
		m_FourPos[2].m_iY = 2;

		m_FourPos[3].m_iX = MAP_WIDTH/2 +1;
		m_FourPos[3].m_iY = 2;
	}
};
class J_Block : public BasicBlock
{
public:
	J_Block()
	{
		m_FourPos[0].m_iX = MAP_WIDTH/2;
		m_FourPos[0].m_iY = 0;
				  
		m_FourPos[1].m_iX = MAP_WIDTH/2;
		m_FourPos[1].m_iY = 1;
				  
		m_FourPos[2].m_iX = MAP_WIDTH/2;
		m_FourPos[2].m_iY = 2;
				  
		m_FourPos[3].m_iX = MAP_WIDTH/2 -1;
		m_FourPos[3].m_iY = 2;
	}
};
class S_Block : public BasicBlock
{
public:
	S_Block()
	{
		m_FourPos[0].m_iX = MAP_WIDTH/2;
		m_FourPos[0].m_iY = 0;
				  
		m_FourPos[1].m_iX = MAP_WIDTH/2 +1;
		m_FourPos[1].m_iY = 0;
				  
		m_FourPos[2].m_iX = MAP_WIDTH/2 -1;
		m_FourPos[2].m_iY = 1;
				  
		m_FourPos[3].m_iX = MAP_WIDTH/2;
		m_FourPos[3].m_iY = 1;
	}
};
class Z_Block : public BasicBlock
{
public:
	Z_Block()
	{
		m_FourPos[0].m_iX = MAP_WIDTH/2 -1;
		m_FourPos[0].m_iY = 0;
				  
		m_FourPos[1].m_iX = MAP_WIDTH/2;
		m_FourPos[1].m_iY = 0;
				  
		m_FourPos[2].m_iX = MAP_WIDTH/2;
		m_FourPos[2].m_iY = 1;
				  
		m_FourPos[3].m_iX = MAP_WIDTH/2 +1;
		m_FourPos[3].m_iY = 1;
	}
};
class T_Block : public BasicBlock
{
public:
	T_Block()
	{
		m_FourPos[0].m_iX = MAP_WIDTH/2 -1;
		m_FourPos[0].m_iY = 0;
				  
		m_FourPos[1].m_iX = MAP_WIDTH/2;
		m_FourPos[1].m_iY = 0;
				  
		m_FourPos[2].m_iX = MAP_WIDTH/2 +1;
		m_FourPos[2].m_iY = 0;
				  
		m_FourPos[3].m_iX = MAP_WIDTH/2;
		m_FourPos[3].m_iY = 1;
	}
};
class O_Block : public BasicBlock
{
public:
	O_Block()
	{
		m_FourPos[0].m_iX = MAP_WIDTH/2 -1;
		m_FourPos[0].m_iY = 0;
				  
		m_FourPos[1].m_iX = MAP_WIDTH/2;
		m_FourPos[1].m_iY = 0;
				  
		m_FourPos[2].m_iX = MAP_WIDTH/2 -1;
		m_FourPos[2].m_iY = 1;
				  
		m_FourPos[3].m_iX = MAP_WIDTH/2;
		m_FourPos[3].m_iY = 1;
	}
};