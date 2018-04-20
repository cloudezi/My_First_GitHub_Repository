#include"Block.h"
class Game//游戏类
{
private:
	int m_pMap[MAP_WIDTH*MAP_HEIGHT];//地图
	BasicBlock * m_pBlock;//方块指针
	int m_iBlockType;//方块类型
	Position m_Center;//变形中心点
	int m_iSpeed;//下落速度
	int m_iScore;//当前分值
	Game()
	{
		InitGame();
	}
public:
	void InitGame()
	{
		memset(m_pMap,0,MAP_WIDTH*MAP_HEIGHT);
		for( int y=0;y<MAP_HEIGHT;y++ )
		{
			for( int x=0;x<MAP_WIDTH;x++ )
			{
				if( 0 == x || MAP_WIDTH-1 == x || MAP_HEIGHT-1 == y )
				{
					m_pMap[y*MAP_WIDTH + x] = WALL;
				}
			}
		}
		m_pBlock = NULL;
		m_iBlockType = -1;
		m_Center.m_iX = MAP_WIDTH/2;
		m_Center.m_iY = 0;
		m_iSpeed = 20;
		m_iScore = 0;
	}
	static Game * GetInstance()
	{
		static Game a;//创建一个局部静态游戏变量
		return &a;//返回其指针
	}
	void PrintMap();//显示地图
	void Start();//开始界面
	void PrintScore();//显示分数

	void CreatBlock();//创建新方块
	void PrintBlock();//显示方块

	void DeleteBlock();//判断并消除整行

	bool JudgeFall();//判断是否可下落
	void FallBlock();//方块下落

	bool JudgeMove( char cInput );//判断是否可移动
	bool JudgeTrans();//判断是否可变形
	void Operate();//操作模块	

	bool JudgeOver();//判断是否结束	
	void RunGame()//运行游戏
	{
		srand((unsigned int)time(0));
		Start();//游戏开始
		int iCount = 0;//计算帧数
		while( JudgeOver() )//判定游戏是否结束
		{
			if( m_iScore >= 50 &&  m_iScore < 100 )//根据分数增加难度
			{
				m_iSpeed = 15;
			}
			else if( m_iScore >= 100 &&  m_iScore < 200 )
			{
				m_iSpeed = 10;
			}
			else if( m_iScore >= 200 &&  m_iScore < 500 )
			{
				m_iSpeed = 5;
			}
			CreatBlock();//生成方块
			PrintScore();//显示当前分数
			if( iCount == m_iSpeed )//若帧数达到规定数
			{
				FallBlock();//执行下落程序
				iCount = 0;//计算帧归零
			}
			Operate();//玩家操作
			PrintBlock();//显示方块			
			iCount++;//帧数+1
			Sleep(25);//25毫秒为1帧
		}
	}
};