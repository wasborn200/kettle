#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXDEG 100.0

extern double nowDeg;

void raiseDeg() {

	printf("加熱を開始します。\n");
	while (nowDeg < MAXDEG) {
		Sleep(500);
		nowDeg += 10.0;
		printf("温度:%.0f℃\n", nowDeg);
	}
	printf("お湯が沸きました。\n");
}