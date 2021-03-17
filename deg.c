#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXDEG 100

extern int nowDeg;
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

	// 0.5�b����10�x�����M����
	while (nowDeg < MAXDEG) {
		Sleep(500);
		nowDeg += 10;
		changeDisplayDeg();
		//strcpy(str[5], degs[nowDeg / 10]);

		changeDisplay();
		printf("\r���M��");

	}
	
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