#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

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
#define DISP_DEG_BEFORE "｜　｜　　　｜　　　｜　　 \x1b[31m\0"
#define DISP_DEG_AFTER "\x1b[39m　　｜　　　｜　　　｜　　｜\n\0"
#define COUNTRESET 0

extern int nowDeg;
extern int targetDeg;

/// <summary>
/// 保温温度まで水を加熱させる
/// </summary>
void raiseDeg() {
	int diffDeg;
	int raiseDegCount = COUNTRESET;

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
			if ((diffDeg = targetDeg - nowDeg) <= DEG_5) {
				nowDeg += diffDeg;
			}
			else {
				nowDeg += DEG_5;
			}
			reflectDeg();
			changeDisplay();
			raiseDegCount = COUNTRESET;
			printf("\r加熱中");
		}
		
	}

	strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_KEEPINGDEG);
	changeDisplay();
	printf("\rお湯が沸きました。");
	Sleep(2000);
}

keepDeg(int* loc) {
	int dropDegCount = COUNTRESET;

	do {
		printf("\r保温中。給湯する場合はロックを解除してください(入力Ｌ)。");

		// r入力：ロックが解除されたときの処理
		// h入力：保温温度変更
		// q入力：アプリ終了
		if (GetKeyState('L') & 0x8000) {
			lockOff(loc);
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
			dropDegCount = COUNTRESET;
		}


	} while (nowDeg >= targetDeg);
}

/// <summary>
/// 時間経過により温度を減少させる（保温設定温度以下にはならない）
/// </summary>
void downDeg() {

	if (nowDeg > targetDeg) {
		nowDeg--;
		reflectDeg();
		changeDisplay();
	}
}


/// <summary>
/// 温度表示部分を変更する
/// </summary>
void reflectDeg() {
	char deg[20];
	char temp[20];

	strcpy(display[ROW_DISPLAYDEG_NUMBER], "");

	// 現在の温度を文字にして、間にスペースを入れる
	// 最低温度の時は'-'で表示する
	sprintf(temp, "%3d", nowDeg);
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		if (i % 2 == 0) {
			if (nowDeg == MINDEG)
			{
				deg[i] = '-';
			}
			else {
				deg[i] = temp[j];
			}
			j++;
		}
		else {
			deg[i] = ' ';
		}
	}
	deg[5] = '\0';

	strcat(display[ROW_DISPLAYDEG_NUMBER], DISP_DEG_BEFORE);
	strcat(display[ROW_DISPLAYDEG_NUMBER], deg);
	strcat(display[ROW_DISPLAYDEG_NUMBER], DISP_DEG_AFTER);
}

/// <summary>
/// 保温温度を変更する
/// </summary>
void changeTargetDeg() {
	
	static int keepDegFlag = COUNTRESET;

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