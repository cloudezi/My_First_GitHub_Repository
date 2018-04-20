#include"Game.h"
void main()
{
	Game::GetInstance()->RunGame();	
}
void Erasure( int iX, int iY )
//此函数的含义，是将输出光标移动到坐标点（iX,iY）并等待在此坐标后输出；
{
	COORD Pos = { iX,iY };
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取标准输出设备句柄
	SetConsoleCursorPosition(Handle,Pos);			 //设置光标位置
	CONSOLE_CURSOR_INFO CurSor;
	GetConsoleCursorInfo(Handle, &CurSor);			 //获取光标信息
	CurSor.bVisible = false;						 //使光标不可见
	SetConsoleCursorInfo(Handle, &CurSor);			 //设置光标信息
}