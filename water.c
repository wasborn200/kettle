#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 2000
#define LIMITWATER 200
#define MINDEG 10
#define LACKWATER 0
#define WATER_200 200
#define COUNTRESET 0
#define ROW_STATUS_NUMBER 8
#define ROW_WATERS_NUMBER 11
#define ROW_LOCK_NUMBER 13
#define ROW_WATER_NUMBER 16
#define COLUMN_NUMBER 80
#define MSG_RESET_ON 1
#define MSG_RESET_OFF 0
#define DISP_STATUS_DEFAULT "｜　　　　　　　　　｜　〇　　　　〇｜　　　　　　　　　　｜\n"

extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];
extern int nowDeg;

char waters[ROW_WATERS_NUMBER][COLUMN_NUMBER] = {
	"｜　　ーーー　　水位：□□□□□□□□□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■\x1b[39m□□□□□□□□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■\x1b[39m□□□□□□□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■\x1b[39m□□□□□□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■\x1b[39m□□□□□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■\x1b[39m□□□□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■\x1b[39m□□□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■■\x1b[39m□□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■■■\x1b[39m□□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■■■■\x1b[39m□　　入力Ｌ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■■■■■\x1b[39m　　入力Ｌ　　　｜\n"
};

/// <summary>
/// 水位がMAXになるまで水をいれる
/// </summary>
int addWater(int nowWater) {
	int msgResetFlag = MSG_RESET_OFF;

	messageReset();
	printf("\r給水(入力Ｗ)後、加熱ボタン(入力Ｈ)を押してください。");

	// 水位MAXになるまで、水を入れるためのアナウンスを続ける
	do
	{
		// T入力：保温温度変更
		// H入力：加熱モードへ移行（水位が制限水位以上の時）
		// Q入力：アプリ終了
		// W入力：給水
		if (GetKeyState('T') & 0x8000) {
			changeTargetDeg();
			msgResetFlag = MSG_RESET_ON;
		}
		else if (GetKeyState('H') & 0x8000) {
			if (nowWater >= LIMITWATER) {
				break;
			}
		}
		else if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

		// Altキーを押し続ける間、0.5秒毎に水位を200上昇させる
		while (GetKeyState('W') & 0x8000) {
			if (nowWater < MAXWATER) {
				nowWater += WATER_200;
				nowDeg = MINDEG;

				strcpy(display[ROW_WATER_NUMBER], waters[nowWater / WATER_200]);
				changeDisplay();
				printf("\r給水中");
				msgResetFlag = MSG_RESET_ON;
				Sleep(500);
			}
			else {
				break;
			}
		}

		if (msgResetFlag == MSG_RESET_ON) {
			messageReset();
			printf("\r給水(入力Ｗ)後、加熱ボタン(入力Ｈ)を押してください。");
			msgResetFlag = MSG_RESET_OFF;
		}

	} while (nowWater < MAXWATER);

	if (nowWater == MAXWATER) {
		messageReset();
		printf("\r水が満杯になりました。");
		Sleep(2000);
	}

	return nowWater;
}

/// <summary>
/// 給湯を行う。
/// 一定時間何も行わない場合、給湯をロックする
/// </summary>
int drainWater(int nowWater, int* loc) {
	int msgResetFlag = MSG_RESET_OFF;
	int lockCount = COUNTRESET;

	messageReset();
	printf("\r給湯(入力Ａ)を行ってください。再ロック(入力Ｌ)");

	do {
		if (GetKeyState('L') & 0x8000 || lockCount >= 100) {
			lockOn(loc);
			break;
		}

		// Aキーを押し続ける間、200ずつ水位を減少させる
		while (GetKeyState('A') & 0x8000) {
			lockCount = COUNTRESET;
			nowWater -= WATER_200;

			strcpy(display[ROW_WATER_NUMBER], waters[nowWater / WATER_200]);
			changeDisplay();
			printf("\r給湯中");
			msgResetFlag = MSG_RESET_ON;
			Sleep(500);

			if (nowWater == LACKWATER) {
				break;
			}

		}

		if (msgResetFlag == MSG_RESET_ON) {
			messageReset();
			printf("\r給湯(入力Ａ)を行ってください。再ロック(入力Ｌ)");
			msgResetFlag = MSG_RESET_OFF;
		}

		Sleep(100);
		lockCount++;

	} while (nowWater != LACKWATER);

	if (nowWater == LACKWATER) {
		strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_DEFAULT);
		strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
		nowDeg = MINDEG;
		reflectDeg();
		changeDisplay();
		printf("\rお湯が無くなりました。");
		Sleep(2000);
	}

	return nowWater;
}