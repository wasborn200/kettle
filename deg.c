#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXDEG 100

extern int nowDeg;

char degs[11][80] = {
	"�b�@�b�@�@�@�b�@�@�@�b - - -�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m1 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m2 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m3 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m4 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m5 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m6 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m7 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m8 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   \x1b[31m9 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b \x1b[31m1 0 0\x1b[39m�b�@�@�@�b���@���b�@�@�b\n",
};

/// <summary>
/// �������M������
/// </summary>
void raiseDeg() {
	
	messageReset();
	printf("\r���M���J�n���܂��B");
	Sleep(2000);

	// 0.5�b����10�x�����M����
	while (nowDeg < MAXDEG) {
		Sleep(500);
		nowDeg += 10;

		strcpy(str[5], degs[nowDeg / 10]);

		changeDisplay();
		printf("\r���M��");

	}
	
	printf("\r�����������܂����B");
	Sleep(2000);
}

//void downDeg() {
//
//	// 2�b����1�x�����x��������
//	while (nowDeg < MAXDEG) {
//		Sleep(500);
//		nowDeg += 10;
//
//		strcpy(str[5], degs[nowDeg / 10]);
//
//		changeDisplay();
//		printf("\r���M��");
//
//	}
//
//	printf("\r�����������܂����B");
//	Sleep(2000);
//}