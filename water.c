#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 1000
#define MINDEG 10
#define LACKWATER 0
#define WATER_100 100
#define COUNTRESET 0
#define ROW_LOCK_NUMBER 6
#define ROW_WATER_NUMBER 16
#define ROW_WATERS_NUMBER 11
#define COLUMN_NUMBER 80
#define DISP_LOCKON "｜　｜　〇　｜　    ｜　　　｜　　　｜　　　｜　　｜\n"
#define DISP_LOCKOFF "｜　｜　\x1b[31m●\x1b[39m　｜　    ｜　　　｜　　　｜　　　｜　　｜\n"

extern int nowWater;
extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];
extern int nowDeg;

char waters[ROW_WATERS_NUMBER][COLUMN_NUMBER] = {
	"｜　　　　　水位：□□□□□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■\x1b[39m□□□□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■\x1b[39m□□□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■■\x1b[39m□□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■■■\x1b[39m□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■■■■\x1b[39m□□□□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■■■■■\x1b[39m□□□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■■■■■■\x1b[39m□□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■■■■■■■\x1b[39m□□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■■■■■■■■\x1b[39m□　　　　　　｜\n",
	"｜　　　　　水位：\x1b[34m■■■■■■■■■■\x1b[39m　　　　　　｜\n"
};

/// <summary>
/// 水位が1000になるまで水をいれる
/// </summary>
void addWater() {
	messageReset();
	printf("\rAltキー長押しで水を入れてください。(アプリ終了:q)");

	// 水位が1000になるまで、水を入れるためのアナウンスを続ける
	do
	{
		// Altキーを押し続ける間、0.5秒毎に水位を100上昇させる
		while (GetKeyState(VK_MENU) & 0x8000) {
			if (nowWater < MAXWATER) {
				nowWater += WATER_100;
			}
			else {
				break;
			}

			strcpy(display[ROW_WATER_NUMBER], waters[nowWater / WATER_100]);
			changeDisplay();
			printf("\r注水中");

			Sleep(500);
		}

		printf("\rAltキー長押しで水を入れてください。(アプリ終了:q)");

		if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

	} while (nowWater != MAXWATER);

	messageReset();
	printf("\r水が満タンになりました。");
	Sleep(2000);
}

/// <summary>
/// 給湯を行う。
/// 一定時間何も行わない場合、給湯をロックする
/// </summary>
void drainWater() {
	
	int lockCount = COUNTRESET;
	lockOff();
	changeDisplay();
	printf("\rお湯を出すにはSHIFTキーを押し続けてください。給湯ロック：r");

	do
	{
		// Shiftキーを押し続ける間、100ずつ水位を減少させる
		while (GetKeyState(VK_SHIFT) & 0x8000) {
			int lockCount = 0;
			if (nowWater >= WATER_100) {
				nowWater -= WATER_100;
			}
			else {
				break;
			}

			strcpy(display[16], waters[nowWater / WATER_100]);
			changeDisplay();
			printf("\r給湯中");

			Sleep(500);
		}

		// 水位が0になるとお湯が無くなったことのアナウンスを行う。
		// 水位が０ではなく、Shiftキーを押していない時は、押すためのアナウンスを行う。
		if (nowWater == LACKWATER) {
			strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
			nowDeg = MINDEG;
			reflectDeg();
			changeDisplay();
			printf("\rお湯が無くなりました。");
			Sleep(2000);
			break;
		}
		
		messageReset();
		printf("\rお湯を出すにはSHIFTキーを押し続けてください。給湯ロック：r");
		Sleep(100);
		lockCount++;

		// ｒキーを押すと給湯をロックする
		if (GetKeyState('R') & 0x8000) {
			lockOn();
			break;
		}

	} while (lockCount < 100);

	// 操作をせずに10秒経過すると給湯がロックされる
	if (lockCount >= 100) {
		lockOn();
	}

	lockCount = COUNTRESET;
}