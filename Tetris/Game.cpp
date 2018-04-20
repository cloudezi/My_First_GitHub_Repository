#include"Game.h"
void Game::PrintMap()//��ʾ��ͼ
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
				cout<<"��";
			}
		}
		cout<<"\n";
	}
}
void Game::Start()//��ʼ����
{
	cout<<"    ������˹���顷\nAD���������ƶ���S�������䣬W����\n ������ʼ��Ϸ��\n";
	system("pause");
	PrintMap();
}
void Game::PrintScore()//��ʾ����
{
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ��׼����豸���
	SetConsoleTextAttribute(Handle,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );//��ԭ����̨��ɫ
	Erasure( 0, MAP_HEIGHT );
	cout<<"��ǰ����Ϊ��"<<m_iScore<<"  \n";
}
void Game::CreatBlock()//�����·���
{
	if( NULL == m_pBlock )//��û�з���
	{
		m_iBlockType = rand()%MAX_BLOCK_NUM;//�������һ������
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
		for( int i=0;i<4;i++ )//����ͼ���鸳ֵ,�������ĵ��λ
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
void Game::PrintBlock()//��ʾ����
{
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ��׼����豸���
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
			cout<<"��";
		}		
	}
}

bool Game::JudgeFall()
//�ж��Ƿ������
{
	if( m_pBlock == NULL )//û�л����
	{
		return false;
	}
	for( int i=0;i<4;i++ )//4�����鶼Ҫ�ж�
	{	//�����ⷽ�������й̶��������ǽ�������ˣ�����������
		if( m_pMap[(m_pBlock->m_FourPos[i].m_iY +1 )*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] == STOP_BLOCK || m_pMap[(m_pBlock->m_FourPos[i].m_iY +1 )*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] == WALL )
		{	
			return false;
		}
	}
	return true;
}
void Game::DeleteBlock()//�жϲ���������
{
	int n = 0;//������n��
	for( int y=MAP_HEIGHT-2;y>1;y-- )//����������
	{
		bool bScore = true;
		for( int x = MAP_WIDTH-2; x>0; x-- )
		{
			if( STOP_BLOCK != m_pMap[y*MAP_WIDTH + x] )//������δ���������������У��������е��жϣ�
			{
				bScore = false;
				break;
			}
		}
		if( true == bScore )//����������
		{
			n++;//��1��
			for( int y1 = y; y1>1; y1-- )//��������ȫ��������1��
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
						cout<<"��";
					}
				}
			}
			y++;//���´Ӵ������ٴο�ʼ�ж���
		}		
	}
	m_iScore += n*n;//�������ӣ�
	return;
}
void Game::FallBlock()//��������
{
	if( m_pBlock == NULL )//û�л����
	{
		return;
	}
	if( JudgeFall() )//����������
	{
		for( int i=0;i<4;i++ )//��ȥԭ���飬����MAP
		{
			Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
			cout<<"  ";
			m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = SPACE;
		}
		for( int i=0;i<4;i++ )//�����鸳������ֵ,����MAP
		{
			m_pBlock->m_FourPos[i].m_iY++;
			m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
		}
		PrintBlock();//��ʾ�·��飻
		m_Center.m_iY++;//�������ĵ�Ҳ����һ��
	}
	else//���޷�����
	{
		for( int i=0;i<4;i++ )//�����ɹ̶����飬����MAP
		{
			m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = STOP_BLOCK;			
		}
		delete m_pBlock;//ɾ��ԭ���飬�ȴ������·��飻
		m_pBlock = NULL;
		DeleteBlock();//�жϲ��������У�
	}
}

bool Game::JudgeMove( char cInput )//�ж��Ƿ���ƶ�
{
	if( m_pBlock == NULL )//û�л����
	{
		return false;
	}
	if( 'A' == cInput || 'a' == cInput )//���ƶ�
	{
		for( int i=0;i<4;i++ )//4�����鶼Ҫ�ж�
		{	//�����ⷽ������й̶��������ǽ������
			if( m_pMap[(m_pBlock->m_FourPos[i].m_iY )*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX -1)] == STOP_BLOCK || m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX -1)] == WALL )
			{	
				return false;
			}
		}
	}
	else if( 'D' == cInput || 'd' == cInput )//���ƶ�
	{
		for( int i=0;i<4;i++ )//4�����鶼Ҫ�ж�
		{	//�����ⷽ���ұ��й̶��������ǽ������
			if( m_pMap[(m_pBlock->m_FourPos[i].m_iY )*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX +1)] == STOP_BLOCK || m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX +1)] == WALL )
			{	
				return false;
			}
		}
	}
	return true;
}
bool Game::JudgeTrans()//�ж��Ƿ�ɱ���
{
	if( NULL != m_pBlock )
	{
		if( m_iBlockType == O_BLOCK )
		{
			return false;
		}
		Position Trans[4];//������κ��������
		int rx0 = m_Center.m_iX;
		int ry0 = m_Center.m_iY;
		for( int i=0;i<4;i++ )//�����ĵ�90��õ����������飻
		{	
			int x = m_pBlock->m_FourPos[i].m_iX;
			int y = m_pBlock->m_FourPos[i].m_iY;
			Trans[i].m_iX = (x - rx0)*0 - (y - ry0)*1 + rx0;
			Trans[i].m_iY = (x - rx0)*1 + (y - ry0)*0 + ry0;
		}
		for( int i=0;i<4;i++ )//4�����κ�ĵ㶼Ҫ�ж�
		{	//��4�������������Ϊ�̶������ǽ�����ܱ���
			if( m_pMap[ Trans[i].m_iY*MAP_WIDTH + Trans[i].m_iX] == STOP_BLOCK || m_pMap[ Trans[i].m_iY*MAP_WIDTH + Trans[i].m_iX] == WALL )
			{	
				return false;
			}
			else if( Trans[i].m_iY < 0 || Trans[i].m_iX > (MAP_WIDTH-1) )//�����ε㳬�ޣ����ܱ���
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
void Game::Operate()//����ģ��
{
	if( m_pBlock == NULL )//û�л����
	{
		return;
	}
	if( GetAsyncKeyState('A') & 1 )
	{
		if( JudgeMove('A') )//�����ƶ�
		{
			for( int i=0;i<4;i++ )//��ȥԭ���飬����MAP
			{
				Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
				cout<<"  ";
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = SPACE;
			}
			m_pBlock->Move('A');//�ƶ�����
			for( int i=0;i<4;i++ )//����MAP
			{
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
			}
			PrintBlock();//��ʾ�·��飻
			m_Center.m_iX--;//�������ĵ�Ҳ����һ��
		}
	}
	else if( GetAsyncKeyState('D') & 1 )
	{
		if( JudgeMove('D') )//�����ƶ�
		{
			for( int i=0;i<4;i++ )//��ȥԭ���飬����MAP
			{
				Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
				cout<<"  ";
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = SPACE;
			}
			m_pBlock->Move('D');//�ƶ�����
			for( int i=0;i<4;i++ )//����MAP
			{
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
			}
			PrintBlock();//��ʾ�·��飻
			m_Center.m_iX++;//�������ĵ�Ҳ����һ��
		}
	}
	else if( GetAsyncKeyState('W') & 1 )
	{
		if( JudgeTrans() )//���ɱ���
		{
			for( int i=0;i<4;i++ )//��ȥԭ���飬����MAP
			{
				Erasure( (m_pBlock->m_FourPos[i].m_iX)*2, (m_pBlock->m_FourPos[i].m_iY) );
				cout<<"  ";
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = SPACE;
			}
			m_pBlock->Transfrom(m_Center);//����
			for( int i=0;i<4;i++ )//����MAP
			{
				m_pMap[(m_pBlock->m_FourPos[i].m_iY)*MAP_WIDTH + (m_pBlock->m_FourPos[i].m_iX)] = MOVE_BLOCK;
			}
			PrintBlock();//��ʾ�·��飻
		}
	}
	else if( GetAsyncKeyState('S') & 1 )
	{
		FallBlock();
	}
	return;
}

bool Game::JudgeOver()//�ж��Ƿ����
{
	for( int x = MAP_WIDTH/2 -2; x< MAP_WIDTH/2 +3; x++ )//�������ָ������Ҳ�й̶��飬����Ϸ����
	{
		if( m_pMap[x] == STOP_BLOCK )
		{
			HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ��׼����豸���
			SetConsoleTextAttribute(Handle,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );//��ԭ����̨��ɫ
			Erasure( 0, MAP_HEIGHT+1 );
			cout<<"GAME OVER\n";
			system("pause");
			return false;
		}
	}
	return true;
}