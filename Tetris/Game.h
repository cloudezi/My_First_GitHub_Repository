#include"Block.h"
class Game//��Ϸ��
{
private:
	int m_pMap[MAP_WIDTH*MAP_HEIGHT];//��ͼ
	BasicBlock * m_pBlock;//����ָ��
	int m_iBlockType;//��������
	Position m_Center;//�������ĵ�
	int m_iSpeed;//�����ٶ�
	int m_iScore;//��ǰ��ֵ
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
		static Game a;//����һ���ֲ���̬��Ϸ����
		return &a;//������ָ��
	}
	void PrintMap();//��ʾ��ͼ
	void Start();//��ʼ����
	void PrintScore();//��ʾ����

	void CreatBlock();//�����·���
	void PrintBlock();//��ʾ����

	void DeleteBlock();//�жϲ���������

	bool JudgeFall();//�ж��Ƿ������
	void FallBlock();//��������

	bool JudgeMove( char cInput );//�ж��Ƿ���ƶ�
	bool JudgeTrans();//�ж��Ƿ�ɱ���
	void Operate();//����ģ��	

	bool JudgeOver();//�ж��Ƿ����	
	void RunGame()//������Ϸ
	{
		srand((unsigned int)time(0));
		Start();//��Ϸ��ʼ
		int iCount = 0;//����֡��
		while( JudgeOver() )//�ж���Ϸ�Ƿ����
		{
			if( m_iScore >= 50 &&  m_iScore < 100 )//���ݷ��������Ѷ�
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
			CreatBlock();//���ɷ���
			PrintScore();//��ʾ��ǰ����
			if( iCount == m_iSpeed )//��֡���ﵽ�涨��
			{
				FallBlock();//ִ���������
				iCount = 0;//����֡����
			}
			Operate();//��Ҳ���
			PrintBlock();//��ʾ����			
			iCount++;//֡��+1
			Sleep(25);//25����Ϊ1֡
		}
	}
};