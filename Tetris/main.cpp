#include"Game.h"
void main()
{
	Game::GetInstance()->RunGame();	
}
void Erasure( int iX, int iY )
//�˺����ĺ��壬�ǽ��������ƶ�������㣨iX,iY�����ȴ��ڴ�����������
{
	COORD Pos = { iX,iY };
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ��׼����豸���
	SetConsoleCursorPosition(Handle,Pos);			 //���ù��λ��
	CONSOLE_CURSOR_INFO CurSor;
	GetConsoleCursorInfo(Handle, &CurSor);			 //��ȡ�����Ϣ
	CurSor.bVisible = false;						 //ʹ��겻�ɼ�
	SetConsoleCursorInfo(Handle, &CurSor);			 //���ù����Ϣ
}