#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXDEG 100

extern int nowDeg;

char degs[11][80] = {
	"｜　｜　　　｜　　　｜ - - -｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   1 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   2 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   3 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   4 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   5 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   6 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   7 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   8 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   9 0｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜ 1 0 0｜　　　｜給　湯｜　　｜\n",
};

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

		strcpy(str[5], degs[nowDeg / 10]);

		changeDisplay();
		printf("\r加熱中");

	}
	
	printf("\rお湯が沸きました。");
	Sleep(2000);
}