#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#include "header.h"
#include "control.c"
#include "water.c"
#include "deg.c"

#define MINDEG 10
#define TARGETDEG_98 98
#define LACKWATER 0
#define COUNTRESET 0
#define ROW_MAX_NUMBER 21
#define COLUMN_NUMBER 80
#define LOCK_ON 0
#define LOCK_OFF 1
#define DISP_LOCKON "｜　　ーーー　　　　　ーーーーーーー　　　　｜　〇　｜　　｜\n"
#define DISP_LOCKOFF "｜　　ーーー　　　　　ーーーーーーー　　　　｜　\x1b[31m●\x1b[39m　｜　　｜\n"


int nowDeg = MINDEG;
int targetDeg = TARGETDEG_98;
int nowWater = LACKWATER;
int keepDegFlag = COUNTRESET;
int lock = LOCK_ON;

// 初期画面表示

char display[ROW_MAX_NUMBER][COLUMN_NUMBER] = {
	" ーーーーーーーーーーーーーーーーーーーーーーーーーーーーー\n",   // 0
	"｜　　　　　　　　　　　　　　　　　　　　　　　　　　　　｜\n",  // 1
	"｜　　ーーー　　　　　ーーーーーーー　　　　　ーーー　　　｜\n",  // 2
	"｜　｜　　　｜　　　｜　　温　度　　｜　　　｜　　　｜　　｜\n",  // 3
	"｜　｜加　熱｜　　　｜　　　　　　　｜　　　｜給　湯｜　　｜\n",  // 4
	"｜　｜　　　｜　　　｜　　 \x1b[31m- - -\x1b[39m　　｜　　　｜　　　｜　　｜\n",  // 5
	"｜　　ーーー　　    ｜　　　　　　　｜　　　　ーーー　　　｜\n",  // 6
	"｜　　入力Ｈ　　　　｜加熱　　　保温｜　　　　入力Ａ　　　｜\n",  // 7
	"｜　　　　　　　　　｜　〇　　　　〇｜　　　　　　　　　　｜\n",  // 8
	"｜　　ーーー　　　　｜　　　　　　　｜　　　　ーーー　　　｜\n",  // 9
	"｜　｜保　温｜　　　｜　98　90　70　｜　　　｜ロック｜　　｜\n",  // 10
	"｜　｜温　度｜　　　｜　\x1b[31m●\x1b[39m　〇　〇　｜　　　｜解　除｜　　｜\n",  // 11
	"｜　｜変　更｜　　　｜　　　　　　　｜　　　｜　　　｜　　｜\n",  // 12
	"｜　　ーーー　　　　　ーーーーーーー　　　　｜　〇　｜　　｜\n",  // 13
	"｜　　入力Ｔ　　　　　　　　　　　　　　　　｜　　　｜　　｜\n",  // 14
	"｜　　　　　　　　　　▼　　　　　　　　　　　ーーー　　　｜\n",  // 15
	"｜　　ーーー　　水位：□□□□□□□□□□　　入力Ｌ　　　｜\n",  // 16
	"｜　｜給　水｜　　　　　　　　　　　　　　　　　　　　　　｜\n",  // 17
	"｜　　ーーー　　　　　　　　　　　　　　　　　　　　　　　｜\n",  // 18
	"｜　　入力Ｗ　　　　　　　　　　　【アプリ終了　入力：Ｑ】｜\n",  // 19
	" ーーーーーーーーーーーーーーーーーーーーーーーーーーーーー\n"    // 20
};

int main(void)
{
	changeDisplay();
	printf("給湯ポットアプリ開始");
	Sleep(2000);

	while(1) {
		
		// 給水モード(水が無い状態)
		if (nowWater == LACKWATER && nowDeg == MINDEG) {
			addWater();
		}

		// 加熱モード(水があり、保温温度以下の状態)
		if (nowWater > LACKWATER && nowDeg < targetDeg) {
			raiseDeg();
		}

		// 水があり、お湯が沸いている状態
		if (nowWater > LACKWATER && nowDeg >= targetDeg) {
			if(lock == LOCK_ON){
				// 保温モード(ロック未解除)
				keepDeg();
			}
			else {
				// 給湯モード(ロック解除済み)
				drainWater();
			}
		}

	}

	return 0;
}