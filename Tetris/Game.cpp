#include"Game.h"
void Game::PrintMap()//显示地图
{
	system("cls");
	for( int y=0;y<MAP_HEIGHT;y++ )
	{
		for( int x=0;x<MAP_WIDTH;x++ )
		{
			if( m_pMap[y*MAP_WIDTH + x] == SPACE )
			{
				cout<<"  ";
			}
			else if( m_pMap[y*MAP_WIDTH + x] == WALL )
			{
				cout<<"※";
			}
		}
		cout<<"\n";
	}
}
void Game::Start()//开始界面
{
	cout<<"    《俄罗斯方块》\nAD控制左右移动，S加速下落，W变形\n 即将开始游戏：\n";
	system("pause");
	PrintMap();
}
void Game::PrintScore()//显示分数
{
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取标准输出设备句柄
	SetConsoleTextAttribute(Handle,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );//还原控制台颜色
	Erasure( 0, MAP_HEIGHT );
	cout<<"当前分数为："<<m_iScore<<"  \n";
}
void Game::CreatBlock()//创建新方块
{
	if( NULL == m_pBlock )//若没有方块
	{
		m_iBlockType = rand()%MAX_BLOCK_NUM;//随机生成一个方块
		//m_iBlockType = I_BLOCK;
		switch( m_iBlockType )
		{
		case I_BLOCK:
			{
				m_pBlock = new I_Block;
				break;
			}
		case L_BLOCK:
			{
				m_pBlock = new L_Block;
				break;
			}
		case J_BLOCK:
			{
				m_pBlock = new J_Block;
				break;
			}
		case S_BLOCK:
			{
				m_pBlock = new S_Block;
				break;
			}
		case Z_BLOCK:
			{
				m_pBlock = new Z_Block;
				break;
			}
		case T_BLOCK:
			{
				m_pBlock = new T_Block;
				break;
			}
		case O_BLOCK:
			{
				m_pBlock = new O_Block;
				break;
			}
		}
		for( int i=0;i<4;i++ )//给地图数组赋值,变形中心点回位
		{
			m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
		}
		m_Center.m_iX = MAP_WIDTH/2;
		m_Center.m_iY = 0;
		return;
	}
	else
		return;
}
void Game::PrintBlock()//显示方块
{
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取标准输出设备句柄
	if( m_pBlock != NULL )
	{
		switch( m_iBlockType )
		{
		case I_BLOCK:
			{
				SetConsoleTextAttribute(Handle,FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				break;
			}
		case L_BLOCK:
			{
				SetConsoleTextAttribute(Handle,FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			}
		case J_BLOCK:
			{
				SetConsoleTextAttribute(Handle,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			}
		case S_BLOCK:
			{
				SetConsoleTextAttribute(Handle,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			}
		case Z_BLOCK:
			{
				SetConsoleTextAttribute(Handle,FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				break;
			}
		case T_BLOCK:
			{
				SetConsoleTextAttribute(Handle,FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				break;
			}
		case O_BLOCK:
			{
				SetConsoleTextAttribute(Handle,FOREGROUND_BLUE );
				break;
			}
		}
		for( int i=0;i<4;i++ )
		{
			Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
			cout<<"■";
		}		
	}
}

bool Game::JudgeFall()
//判断是否可下落
{
	if( m_pBlock == NULL )//没有活动方块
	{
		return false;
	}
	for( int i=0;i<4;i++ )//4个方块都要判断
	{	//若任意方块下面有固定方块或者墙（到底了），则不能下落
		if( m_pMap[(m_pBlock->m_FourPos[i].m_iY +1 )*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] == STOP_BLOCK || m_pMap[(m_pBlock->m_FourPos[i].m_iY +1 )*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] == WALL )
		{	
			return false;
		}
	}
	return true;
}
void Game::DeleteBlock()//判断并消除整行
{
	int n = 0;//消除了n行
	for( int y=MAP_HEIGHT-2;y>1;y-- )//从下往上数
	{
		bool bScore = true;
		for( int x = MAP_WIDTH-2; x>0; x-- )
		{
			if( STOP_BLOCK != m_pMap[y*MAP_WIDTH + x] )//若该行未满，不能消除本行；跳出本行的判断；
			{
				bScore = false;
				break;
			}
		}
		if( true == bScore )//若该行已满
		{
			n++;//计1行
			for( int y1 = y; y1>1; y1-- )//该行以上全部往下落1格；
			{
				for( int x1 = MAP_WIDTH-2; x1>0; x1-- )
				{
					m_pMap[y1*MAP_WIDTH +x1] = m_pMap[(y1-1)*MAP_WIDTH +x1];
					m_pMap[(y1-1)*MAP_WIDTH +x1] = SPACE;
					Erasure( x1*2, y1-1 );
					cout<<"  ";
					Erasure( x1*2, y1);
					if( SPACE == m_pMap[y1*MAP_WIDTH +x1] )
					{
						cout<<"  ";
					}
					else if( STOP_BLOCK == m_pMap[y1*MAP_WIDTH +x1] )
					{
						cout<<"■";
					}
				}
			}
			y++;//重新从此行起再次开始判定；
		}		
	}
	m_iScore += n*n;//分数增加；
	return;
}
void Game::FallBlock()//方块下落
{
	if( m_pBlock == NULL )//没有活动方块
	{
		return;
	}
	if( JudgeFall() )//若可以下落
	{
		for( int i=0;i<4;i++ )//擦去原方块，更新MAP
		{
			Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
			cout<<"  ";
			m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = SPACE;
		}
		for( int i=0;i<4;i++ )//给方块赋新坐标值,更新MAP
		{
			m_pBlock->m_FourPos[i].m_iY++;
			m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
		}
		PrintBlock();//显示新方块；
		m_Center.m_iY++;//变形中心点也下落一点
	}
	else//若无法下落
	{
		for( int i=0;i<4;i++ )//方块变成固定方块，更新MAP
		{
			m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = STOP_BLOCK;			
		}
		delete m_pBlock;//删除原方块，等待生成新方块；
		m_pBlock = NULL;
		DeleteBlock();//判断并消除整行；
	}
}

bool Game::JudgeMove( char cInput )//判断是否可移动
{
	if( m_pBlock == NULL )//没有活动方块
	{
		return false;
	}
	if( 'A' == cInput || 'a' == cInput )//左移动
	{
		for( int i=0;i<4;i++ )//4个方块都要判断
		{	//若任意方块左边有固定方块或者墙，则不能
			if( m_pMap[(m_pBlock->m_FourPos[i].m_iY )*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX -1)] == STOP_BLOCK || m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX -1)] == WALL )
			{	
				return false;
			}
		}
	}
	else if( 'D' == cInput || 'd' == cInput )//右移动
	{
		for( int i=0;i<4;i++ )//4个方块都要判断
		{	//若任意方块右边有固定方块或者墙，则不能
			if( m_pMap[(m_pBlock->m_FourPos[i].m_iY )*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX +1)] == STOP_BLOCK || m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX +1)] == WALL )
			{	
				return false;
			}
		}
	}
	return true;
}
bool Game::JudgeTrans()//判断是否可变形
{
	if( NULL != m_pBlock )
	{
		if( m_iBlockType == O_BLOCK )
		{
			return false;
		}
		Position Trans[4];//定义变形后的坐标组
		int rx0 = m_Center.m_iX;
		int ry0 = m_Center.m_iY;
		for( int i=0;i<4;i++ )//绕中心点90°得到变形坐标组；
		{	
			int x = m_pBlock->m_FourPos[i].m_iX;
			int y = m_pBlock->m_FourPos[i].m_iY;
			Trans[i].m_iX = (x - rx0)*0 - (y - ry0)*1 + rx0;
			Trans[i].m_iY = (x - rx0)*1 + (y - ry0)*0 + ry0;
		}
		for( int i=0;i<4;i++ )//4个变形后的点都要判断
		{	//若4个点中有任意点为固定方块或墙，则不能变形
			if( m_pMap[ Trans[i].m_iY*MAP_WIDTH + Trans[i].m_iX] == STOP_BLOCK || m_pMap[ Trans[i].m_iY*MAP_WIDTH + Trans[i].m_iX] == WALL )
			{	
				return false;
			}
			else if( Trans[i].m_iY < 0 || Trans[i].m_iX > (MAP_WIDTH-1) )//若变形点超限，不能变形
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
	return true;
}
void Game::Operate()//操作模块
{
	if( m_pBlock == NULL )//没有活动方块
	{
		return;
	}
	if( GetAsyncKeyState('A') & 1 )
	{
		if( JudgeMove('A') )//若可移动
		{
			for( int i=0;i<4;i++ )//擦去原方块，更新MAP
			{
				Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
				cout<<"  ";
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = SPACE;
			}
			m_pBlock->Move('A');//移动方块
			for( int i=0;i<4;i++ )//更新MAP
			{
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
			}
			PrintBlock();//显示新方块；
			m_Center.m_iX--;//变形中心点也左移一格
		}
	}
	else if( GetAsyncKeyState('D') & 1 )
	{
		if( JudgeMove('D') )//若可移动
		{
			for( int i=0;i<4;i++ )//擦去原方块，更新MAP
			{
				Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
				cout<<"  ";
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = SPACE;
			}
			m_pBlock->Move('D');//移动方块
			for( int i=0;i<4;i++ )//更新MAP
			{
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
			}
			PrintBlock();//显示新方块；
			m_Center.m_iX++;//变形中心点也左移一格
		}
	}
	else if( GetAsyncKeyState('W') & 1 )
	{
		if( JudgeTrans() )//若可变形
		{
			for( int i=0;i<4;i++ )//擦去原方块，更新MAP
			{
				Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
				cout<<"  ";
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = SPACE;
			}
			m_pBlock->Transfrom(m_Center);//变形
			for( int i=0;i<4;i++ )//更新MAP
			{
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
			}
			PrintBlock();//显示新方块；
		}
	}
	else if( GetAsyncKeyState('S') & 1 )
	{
		FallBlock();
	}
	return;
}

bool Game::JudgeOver()//判断是否结束
{
	for( int x = MAP_WIDTH/2 -2; x< MAP_WIDTH/2 +3; x++ )//若顶层的指定区域也有固定块，则游戏结束
	{
		if( m_pMap[x] == STOP_BLOCK )
		{
			HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取标准输出设备句柄
			SetConsoleTextAttribute(Handle,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );//还原控制台颜色
			Erasure( 0, MAP_HEIGHT+1 );
			cout<<"GAME OVER\n";
			system("pause");
			return false;
		}
	}
	return true;
}