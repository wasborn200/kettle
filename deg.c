#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define DEG_1 1
#define DEG_5 5
#define MINDEG 10
#define TARGETDEG_98 98
#define TARGETDEG_90 90
#define TARGETDEG_70 70
#define ROW_DISPLAYDEG_NUMBER 5
#define ROW_TARGETDEG_NUMBER 13
#define DISP_TARGETDEG_98 "｜　入力ｈ　｜選　択｜　　\x1b[31m●\x1b[39m　〇　〇　　　　　　　｜\n"
#define DISP_TARGETDEG_90 "｜　入力ｈ　｜選　択｜　　〇　\x1b[31m●\x1b[39m　〇　　　　　　　｜\n"
#define DISP_TARGETDEG_70 "｜　入力ｈ　｜選　択｜　　〇　〇　\x1b[31m●\x1b[39m　　　　　　　｜\n"
#define COUNTRESET 0

extern int nowDeg;
extern int targetDeg;
extern int keepDegFlag;
extern int dropDegCount;
int raiseDegCount;
int tempDeg;
char deg[20];
char temp[20];
char displayDeg1[80] = "｜　｜　　　｜　　　｜ \x1b[31m";
char displayDeg2[80] = "\x1b[39m｜　　　｜給　湯｜　　｜\n";

/// <summary>
/// 保温温度まで水を加熱させる
/// </summary>
void raiseDeg() {
	
	messageReset();
	printf("\r加熱を開始します。");
	Sleep(2000);
	
	// 初回は98度のランプを点灯させる
	if (targetDeg == TARGETDEG_98) {
		strcpy(display[ROW_TARGETDEG_NUMBER], DISP_TARGETDEG_98);
	}

	// 0.5秒毎に10度ずつ加熱する
	while (nowDeg < targetDeg) {
		Sleep(100);
		raiseDegCount++;
		if (raiseDegCount == DEG_5) {
			if ((tempDeg = targetDeg - nowDeg) <= DEG_5) {
				nowDeg += tempDeg;
			}
			else {
				nowDeg += DEG_5;
			}
			reflectDeg();
			changeDisplay();
			raiseDegCount = COUNTRESET;
		}
		printf("\r加熱中（保温温度変更：h）");
		
		// hキーを入力することで最高温度を変更する
        if (GetKeyState('H') & 0x8000) {
			changeTargetDeg();
		}
	}

	changeDisplay();
	printf("\rお湯が沸きました。");
	Sleep(2000);
}

/// <summary>
/// 時間経過により温度を減少させる（保温設定温度以下にはならない）
/// </summary>
void downDeg() {

	if (nowDeg != targetDeg) {
		nowDeg -= DEG_1;
		reflectDeg();
		changeDisplay();
	}
	dropDegCount = COUNTRESET;
}


/// <summary>
/// 温度表示部分を変更する
/// </summary>
void reflectDeg() {

	strcpy(display[ROW_DISPLAYDEG_NUMBER], "");

	// 現在の温度を文字にして、間にスペースを入れる
	// 最低温度の時は'-'で表示する
	sprintf(temp, "%3d", nowDeg);
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		if (i == 0 || i == 2 || i == 4) {
			deg[i] = temp[j];
			if (nowDeg == MINDEG)
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

	strcat(display[ROW_DISPLAYDEG_NUMBER], displayDeg1);
	strcat(display[ROW_DISPLAYDEG_NUMBER], deg);
	strcat(display[ROW_DISPLAYDEG_NUMBER], displayDeg2);
}

/// <summary>
/// 保温温度を変更する
/// </summary>
void changeTargetDeg() {
	
	// 保温温度を98→90→70の順でループする
	if (keepDegFlag != 2) {
		keepDegFlag++;
	}
	else {
		keepDegFlag = 0;
	}

	switch (keepDegFlag) {
	case 0:
		targetDeg = TARGETDEG_98;
		strcpy(display[13], DISP_TARGETDEG_98);
		break;
	case 1:
		targetDeg = TARGETDEG_90;
		strcpy(display[13], DISP_TARGETDEG_90);
		break;
	case 2:
		targetDeg = TARGETDEG_70;
		strcpy(display[13], DISP_TARGETDEG_70);
		break;
	}
	changeDisplay();
	Sleep(500);
}