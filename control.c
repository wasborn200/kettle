#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define LINE_LOCK_NUMBER 6
#define LINE_MAX_NUMBER 18
#define COLUMN_NUMBER 80
#define DISP_LOCKON "｜　｜　〇　｜　    ｜　　　｜　　　｜　　　｜　　｜\n"
#define DISP_LOCKOFF "｜　｜　\x1b[31m●\x1b[39m　｜　    ｜　　　｜　　　｜　　　｜　　｜\n"

extern char display[LINE_MAX_NUMBER][COLUMN_NUMBER];

/// <summary>
/// 画面表示のリセット及び再表示
/// </summary>
void changeDisplay() {
	system("cls");
	for (int i = 0; i < LINE_MAX_NUMBER; i++)
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

void lockOn() {
	strcpy(display[LINE_LOCK_NUMBER], DISP_LOCKON);
	changeDisplay();
	printf("\r給湯がロックされました。");
	Sleep(1000);
}

void lockOff() {
	strcpy(display[LINE_LOCK_NUMBER], DISP_LOCKOFF);
	changeDisplay();
	printf("\r給湯ロックが解除されました。");
	Sleep(1000);
}