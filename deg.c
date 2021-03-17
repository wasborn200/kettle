#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define KEEPDEG1 "｜　入力ｈ　｜選　択｜　　\x1b[31m●\x1b[39m　〇　〇　　　　　　　｜\n"
#define KEEPDEG2 "｜　入力ｈ　｜選　択｜　　〇　\x1b[31m●\x1b[39m　〇　　　　　　　｜\n"
#define KEEPDEG3 "｜　入力ｈ　｜選　択｜　　〇　〇　\x1b[31m●\x1b[39m　　　　　　　｜\n"

extern int nowDeg;
extern int maxDeg;
extern int keepDegFlag;
extern int dropDegCount;
int raiseDegCount;
int tempDeg;
char deg[20];
char temp[20];
char displayDig1[100] = "｜　｜　　　｜　　　｜ \x1b[31m";
char displayDig2[100] = "\x1b[39m｜　　　｜給　湯｜　　｜\n";

/// <summary>
/// 水を加熱させる
/// </summary>
void raiseDeg() {
	
	messageReset();
	printf("\r加熱を開始します。");
	Sleep(2000);
	strcpy(str[13], KEEPDEG1);

	// 0.5秒毎に10度ずつ加熱する
	while (nowDeg < maxDeg) {
		Sleep(100);
		raiseDegCount++;
		if (raiseDegCount == 5) {
			if ((tempDeg = maxDeg - nowDeg) <= 5) {
				nowDeg += tempDeg;
			}
			else {
				nowDeg += 5;
			}
			changeDisplayDeg();
			changeDisplay();
			raiseDegCount = 0;
		}
		printf("\r加熱中（保温温度変更：h）");
		
		// hキーを入力することで最高温度を変更する
        if (GetKeyState('H') & 0x8000) {
			changeMaxDeg();
		}
	}

	changeDisplay();
	printf("\rお湯が沸きました。");
	Sleep(2000);
}

/// <summary>
/// 温度表示部分を変更する
/// </summary>
void changeDisplayDeg() {

	strcpy(str[5], "");

	sprintf(temp, "%3d", nowDeg);

	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		if (i == 0 || i == 2 || i == 4) {
			deg[i] = temp[j];
			if (nowDeg == 10)
			{
				deg[i] = '-';
			}
			j++;
		}
		else {
			deg[i] = ' ';
		}
	}
	deg[5] = '\0';
	strcat(str[5], displayDig1);
	strcat(str[5], deg);
	strcat(str[5], displayDig2);
}

void changeMaxDeg() {
	
	if (keepDegFlag != 2) {
		keepDegFlag++;
	}
	else {
		keepDegFlag = 0;
	}

	switch (keepDegFlag) {
	case 0:
		maxDeg = 98;
		strcpy(str[13], KEEPDEG1);
		break;
	case 1:
		maxDeg = 90;
		strcpy(str[13], KEEPDEG2);
		break;
	case 2:
		maxDeg = 70;
		strcpy(str[13], KEEPDEG3);
		break;
	}
	changeDisplay();
}

void downDeg() {

	if (nowDeg != maxDeg) {
		nowDeg -= 1;
		changeDisplayDeg();
		changeDisplay();
	}
	dropDegCount = 0;
}