#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXDEG 100

extern int nowDeg;

char degs[11][80] = {
	"�b�@�b�@�@�@�b�@�@�@�b - - -�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   1 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   2 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   3 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   4 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   5 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   6 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   7 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   8 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b   9 0�b�@�@�@�b���@���b�@�@�b\n",
	"�b�@�b�@�@�@�b�@�@�@�b 1 0 0�b�@�@�@�b���@���b�@�@�b\n",
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