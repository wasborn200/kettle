#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define KEEPDEG1 "�b�@���͂��@�b�I�@���b�@�@\x1b[31m��\x1b[39m�@�Z�@�Z�@�@�@�@�@�@�@�b\n"
#define KEEPDEG2 "�b�@���͂��@�b�I�@���b�@�@�Z�@\x1b[31m��\x1b[39m�@�Z�@�@�@�@�@�@�@�b\n"
#define KEEPDEG3 "�b�@���͂��@�b�I�@���b�@�@�Z�@�Z�@\x1b[31m��\x1b[39m�@�@�@�@�@�@�@�b\n"

extern int nowDeg;
extern int maxDeg;
extern int keepDegFlag;
extern int dropDegCount;
int raiseDegCount;
int tempDeg;
char deg[20];
char temp[20];
char displayDig1[100] = "�b�@�b�@�@�@�b�@�@�@�b \x1b[31m";
char displayDig2[100] = "\x1b[39m�b�@�@�@�b���@���b�@�@�b\n";

/// <summary>
/// �������M������
/// </summary>
void raiseDeg() {
	
	messageReset();
	printf("\r���M���J�n���܂��B");
	Sleep(2000);
	strcpy(str[13], KEEPDEG1);

	// 0.5�b����10�x�����M����
	while (nowDeg < maxDeg) {
		Sleep(100);
		raiseDegCount++;
		if (raiseDegCount == 5) {
			if ((tempDeg = maxDeg - nowDeg) <= 5) {
				nowDeg += tempDeg;
			}
			else {
				nowDeg += 5;
			}
			changeDisplayDeg();
			changeDisplay();
			raiseDegCount = 0;
		}
		printf("\r���M���i�ۉ����x�ύX�Fh�j");
		
		// h�L�[����͂��邱�Ƃōō����x��ύX����
        if (GetKeyState('H') & 0x8000) {
			changeMaxDeg();
		}
	}

	changeDisplay();
	printf("\r�����������܂����B");
	Sleep(2000);
}

/// <summary>
/// ���x�\��������ύX����
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

void changeMaxDeg() {
	
	if (keepDegFlag != 2) {
		keepDegFlag++;
	}
	else {
		keepDegFlag = 0;
	}

	switch (keepDegFlag) {
	case 0:
		maxDeg = 98;
		strcpy(str[13], KEEPDEG1);
		break;
	case 1:
		maxDeg = 90;
		strcpy(str[13], KEEPDEG2);
		break;
	case 2:
		maxDeg = 70;
		strcpy(str[13], KEEPDEG3);
		break;
	}
	changeDisplay();
}

void downDeg() {

	if (nowDeg != maxDeg) {
		nowDeg -= 1;
		changeDisplayDeg();
		changeDisplay();
	}
	dropDegCount = 0;
}