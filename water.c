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

extern int nowWater;
extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];
extern int nowDeg;
extern int msgResetFlag;

char waters[ROW_WATERS_NUMBER][COLUMN_NUMBER] = {
	"｜　　ーーー　　水位：□□□□□□□□□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■\x1b[39m□□□□□□□□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■\x1b[39m□□□□□□□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■\x1b[39m□□□□□□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■\x1b[39m□□□□□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■\x1b[39m□□□□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■\x1b[39m□□□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■■\x1b[39m□□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■■■\x1b[39m□□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■■■■\x1b[39m□　　入力Ｒ　　　｜\n",
	"｜　　ーーー　　水位：\x1b[34m■■■■■■■■■■\x1b[39m　　入力Ｒ　　　｜\n"
};

/// <summary>
/// 水位がMAXになるまで水をいれる
/// </summary>
void addWater() {
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
			}
			else {
				break;
			}

			strcpy(display[ROW_WATER_NUMBER], waters[nowWater / WATER_200]);
			changeDisplay();
			printf("\r給水中");
			msgResetFlag = MSG_RESET_ON;

			Sleep(500);
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
}

/// <summary>
/// 給湯を行う。
/// 一定時間何も行わない場合、給湯をロックする
/// </summary>
void drainWater() {
	
	int lockCount = COUNTRESET;
	changeDisplay();
	printf("\r給湯(入力Ａ)を行ってください。再ロック(入力Ｒ)");

	do
	{
		// R入力：ロック
		// Q入力：アプリ終了
		if (GetKeyState('R') & 0x8000) {
			lockOn();
			break;
		}
		else if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

		// Aキーを押し続ける間、200ずつ水位を減少させる
		while (GetKeyState('A') & 0x8000) {
			int lockCount = 0;
			if (nowWater >= WATER_200) {
				nowWater -= WATER_200;
			}
			else {
				break;
			}

			strcpy(display[16], waters[nowWater / WATER_200]);
			changeDisplay();
			printf("\r給湯中");
			msgResetFlag = MSG_RESET_ON;

			Sleep(500);
		}

		// 水位が0になるとお湯が無くなったことのアナウンスを行う。
		if (nowWater == LACKWATER) {
			strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_DEFAULT);
			strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
			nowDeg = MINDEG;
			reflectDeg();
			changeDisplay();
			printf("\rお湯が無くなりました。");
			Sleep(2000);
			break;
		}
		
		if (msgResetFlag == MSG_RESET_ON) {
			messageReset();
			printf("\r給湯(入力Ａ)を行ってください。再ロック(入力Ｒ)");
			msgResetFlag = MSG_RESET_OFF;
		}


		Sleep(100);
		lockCount++;

	} while (lockCount < 100);

	// 操作をせずに10秒経過すると給湯がロックされる
	if (lockCount >= 100) {
		lockOn();
	}

	lockCount = COUNTRESET;
}