#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXDEG 100

extern int nowDeg;

char degs[11][80] = {
	"｜　｜　　　｜　　　｜ - - -｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m1 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m2 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m3 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m4 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m5 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m6 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m7 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m8 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜   \x1b[31m9 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
	"｜　｜　　　｜　　　｜ \x1b[31m1 0 0\x1b[39m｜　　　｜給　湯｜　　｜\n",
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

//void downDeg() {
//
//	// 2秒毎に1度ずつ温度が下がる
//	while (nowDeg < MAXDEG) {
//		Sleep(500);
//		nowDeg += 10;
//
//		strcpy(str[5], degs[nowDeg / 10]);
//
//		changeDisplay();
//		printf("\r加熱中");
//
//	}
//
//	printf("\rお湯が沸きました。");
//	Sleep(2000);
//}