#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define ROW_LOCK_NUMBER 6
#define ROW_MAX_NUMBER 18
#define COLUMN_NUMBER 80
#define DISP_LOCKON "｜　｜　〇　｜　    ｜　　　｜　　　｜　　　｜　　｜\n"
#define DISP_LOCKOFF "｜　｜　\x1b[31m●\x1b[39m　｜　    ｜　　　｜　　　｜　　　｜　　｜\n"

extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];

/// <summary>
/// 画面表示のリセット及び再表示
/// </summary>
void changeDisplay() {
	system("cls");
	for (int i = 0; i < ROW_MAX_NUMBER; i++)
	{
		printf(display[i]);
	}
}

/// <summary>
/// メッセージのリセット
/// </summary>
void messageReset() {
	printf("\r　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
}

/// <summary>
/// 給湯をロックする
/// </summary>
void lockOn() {
	strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
	changeDisplay();
	printf("\r給湯がロックされました。");
	Sleep(1000);
}

/// <summary>
/// 給湯ロックを解除する
/// </summary>
void lockOff() {
	strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKOFF);
	changeDisplay();
	printf("\r給湯ロックが解除されました。");
	Sleep(1000);
}