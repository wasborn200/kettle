#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXDEG 100.0

extern double nowDeg;

void raiseDeg() {

	printf("���M���J�n���܂��B\n");
	while (nowDeg < MAXDEG) {
		Sleep(500);
		nowDeg += 10.0;
		printf("���x:%.0f��\n", nowDeg);
	}
	printf("�����������܂����B\n");
}