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
#define ROW_TARGETDEG_NUMBER 11
#define ROW_STATUS_NUMBER 8
#define DISP_TARGETDEG_98 "｜　｜温　度｜　　　｜　\x1b[31m●\x1b[39m　〇　〇　｜　　　｜解　除｜　　｜\n"
#define DISP_TARGETDEG_90 "｜　｜温　度｜　　　｜　〇　\x1b[31m●\x1b[39m　〇　｜　　　｜解　除｜　　｜\n"
#define DISP_TARGETDEG_70 "｜　｜温　度｜　　　｜　〇　〇　\x1b[31m●\x1b[39m　｜　　　｜解　除｜　　｜\n"
#define DISP_STATUS_HEATINGDEG "｜　　　　　　　　　｜　\x1b[31m●\x1b[39m　　　　〇｜　　　　　　　　　　｜\n"
#define DISP_STATUS_KEEPINGDEG "｜　　　　　　　　　｜　〇　　　　\x1b[31m●\x1b[39m｜　　　　　　　　　　｜\n"
#define COUNTRESET 0

extern int nowDeg;
extern int targetDeg;
extern int keepDegFlag;
extern int dropDegCount;
int raiseDegCount;
int tempDeg;
char deg[20];
char temp[20];
char displayDeg1[80] = "｜　｜　　　｜　　　｜　　 \x1b[31m";
char displayDeg2[80] = "\x1b[39m　　｜　　　｜　　　｜　　｜\n";

/// <summary>
/// 保温温度まで水を加熱させる
/// </summary>
void raiseDeg() {
	
	messageReset();
	printf("\r加熱を開始します。");
	Sleep(2000);

	strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_HEATINGDEG);

	// 0.5秒毎に10度ずつ加熱する
	while (nowDeg < targetDeg) {

		// h入力：保温温度変更
		// q入力：アプリ終了
		if (GetKeyState('T') & 0x8000) {
			changeTargetDeg();
		}
		else if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

		Sleep(100);
		raiseDegCount++;

		// 0.5秒毎に温度を5度上昇させる
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
		printf("\r加熱中（保温温度変更：Ｔ）");
		
	}

	strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_KEEPINGDEG);
	changeDisplay();
	printf("\rお湯が沸きました。");
	Sleep(2000);
}

/// <summary>
/// 時間経過により温度を減少させる（保温設定温度以下にはならない）
/// </summary>
void downDeg() {

	if (nowDeg > targetDeg) {
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
		strcpy(display[ROW_TARGETDEG_NUMBER], DISP_TARGETDEG_98);
		break;
	case 1:
		targetDeg = TARGETDEG_90;
		strcpy(display[ROW_TARGETDEG_NUMBER], DISP_TARGETDEG_90);
		break;
	case 2:
		targetDeg = TARGETDEG_70;
		strcpy(display[ROW_TARGETDEG_NUMBER], DISP_TARGETDEG_70);
		break;
	}
	changeDisplay();
	Sleep(500);
}

keepDeg() {

	do {
		printf("\r保温中。給湯する場合はロックを解除してください(入力Ｒ)。");

		// r入力：ロックが解除されたときの処理
		// h入力：保温温度変更
		// q入力：アプリ終了
		if (GetKeyState('R') & 0x8000) {
			lockOff();
			break;
		}
		else if (GetKeyState('T') & 0x8000) {
			changeTargetDeg();
		}
		else if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

		// 2秒毎に温度を１℃下げる
		Sleep(50);
		dropDegCount++;
		if (dropDegCount == 40) {
			downDeg();
		}


	} while (nowDeg >= targetDeg);
}