#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXDEG 100

extern int nowDeg;
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

	// 0.5秒毎に10度ずつ加熱する
	while (nowDeg < MAXDEG) {
		Sleep(500);
		nowDeg += 10;
		changeDisplayDeg();
		//strcpy(str[5], degs[nowDeg / 10]);

		changeDisplay();
		printf("\r加熱中");

	}
	
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