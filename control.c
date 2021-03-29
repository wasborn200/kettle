#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define ROW_LOCK_NUMBER 13
#define ROW_MAX_NUMBER 21
#define COLUMN_NUMBER 80
#define LOCK_ON 0
#define LOCK_OFF 1
#define DISP_LOCKON "｜　　ーーー　　　　　ーーーーーーー　　　　｜　〇　｜　　｜\n"
#define DISP_LOCKOFF "｜　　ーーー　　　　　ーーーーーーー　　　　｜　\x1b[31m●\x1b[39m　｜　　｜\n"

extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];
extern int lock;

/// <summary>
/// 画面表示のリセット及び再表示
/// </summary>
void changeDisplay() {
	system("cls");
	int i;
	for (i = 0; i < ROW_MAX_NUMBER; i++)
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
void lockOn(int* loc) {
	*loc = LOCK_ON;
	strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
	changeDisplay();
	printf("\r給湯がロックされました。");
	Sleep(1000);
}

/// <summary>
/// 給湯ロックを解除する
/// </summary>
void lockOff(int* loc) {
	*loc = LOCK_OFF;
	strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKOFF);
	changeDisplay();
	printf("\r給湯ロックが解除されました。");
	Sleep(1000);
}