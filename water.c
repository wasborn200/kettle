#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 1000

extern int nowWater;
extern char str[13][80];
extern int nowDeg;
extern char degs[11][80];

char waters[11][80] = {
	"｜　　　　　水位：□□□□□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：■□□□□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：■■□□□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：■■■□□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：■■■■□□□□□□　　　　　　｜\n",
	"｜　　　　　水位：■■■■■□□□□□　　　　　　｜\n",
	"｜　　　　　水位：■■■■■■□□□□　　　　　　｜\n",
	"｜　　　　　水位：■■■■■■■□□□　　　　　　｜\n",
	"｜　　　　　水位：■■■■■■■■□□　　　　　　｜\n",
	"｜　　　　　水位：■■■■■■■■■□　　　　　　｜\n",
	"｜　　　　　水位：■■■■■■■■■■　　　　　　｜\n"
};

/// <summary>
/// 水位が1000になるまで水をいれる
/// </summary>
void addWater() {
	messageReset();
	printf("\r水がありません。水を入れるにはAltキーを押し続けてください。");

	// 水位が1000になるまで、水を入れるためのアナウンスを続ける
	do
	{
		// Altキーを押し続ける間、0.5秒毎に水位を100上昇させる
		while (GetKeyState(VK_MENU) & 0x8000) {
			if (nowWater < MAXWATER) {
				nowWater += 100;
			}
			else {
				break;
			}

			strcpy(str[11], waters[nowWater / 100]);
			changeDisplay();
			printf("\r注水中");

			Sleep(500);
		}

		printf("\r水がありません。水を入れるにはAltキーを押し続けてください。");

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
	
	int lockCount = 0;
	strcpy(str[6], "｜　｜　●　｜　    ｜　　　｜　　　｜　　　｜　　｜\n");
	changeDisplay();
	printf("\rお湯を出すにはSHIFTキーを押し続けてください。");

	do
	{
		// Shiftキーを押し続ける間、100ずつ水位を減少させる
		while (GetKeyState(VK_SHIFT) & 0x8000) {
			int lockCount = 0;
			if (nowWater >= 100) {
				nowWater -= 100;
			}
			else {
				break;
			}

			strcpy(str[11], waters[nowWater / 100]);
			changeDisplay();
			printf("\r給湯中");

			Sleep(500);
		}

		// 水位が0になるとお湯が無くなったことのアナウンスを行う。
		// Shiftキーを押していないだけなら、押すためのアナウンスを行う。
		if (nowWater < 100) {
			nowDeg = 10;
			strcpy(str[5], degs[0]);
			changeDisplay();
			printf("\rお湯が無くなりました。");
			Sleep(2000);
			break;
		}
		else {
			printf("\r　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
			printf("\rお湯を出すにはSHIFTキーを押し続けてください。");
		}
		Sleep(1000);
		lockCount++;

	} while (lockCount < 10);

	// lockCountが10になると給湯がロックされる
	if (lockCount >= 10) {
		strcpy(str[6], "｜　｜　〇　｜　    ｜　　　｜　　　｜　　　｜　　｜\n");
		changeDisplay();
		printf("\r給湯がロックされました。");
		Sleep(2000);
	}

	lockCount = 0;
}