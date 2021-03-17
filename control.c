#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

extern char str[13][80];

/// <summary>
/// 画面表示のリセット及び再表示
/// </summary>
void changeDisplay() {
	system("cls");
	for (int i = 0; i < 13; i++)
	{
		printf(str[i]);
	}
}

/// <summary>
/// メッセージのリセット
/// </summary>
void messageReset() {
	printf("\r　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
}