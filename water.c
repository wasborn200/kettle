#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 1000
#define MAXDEG 100.0

extern int nowWater;

char waters[10][30] = {
	"��������������������",
	"��������������������",
	"��������������������",
	"��������������������",
	"��������������������",
	"��������������������",
	"��������������������",
	"��������������������",
	"��������������������",
	"��������������������"
};

void addWater() {
	printf("��������܂���B��������ɂ�Alt�L�[�����������Ă��������B\n");
	do
	{
		while (GetKeyState(VK_MENU) & 0x8000) {
			if (nowWater < MAXWATER) {
				nowWater += 100;
			}
			else {
				break;
			}
			printf("���ʁF%s", waters[nowWater / 100 - 1]);
			if (nowWater < MAXWATER) {
				printf("\r");
			}
			Sleep(500);
		}

	} while (nowWater != MAXWATER);
	printf("\n�������^���ɂȂ�܂����B\n");
}

//void addWater() {
//	printf("��������܂���B��������ɂ�Alt�L�[�����������Ă��������B\n");
//	do
//	{
//		while (GetKeyState(VK_MENU) & 0x8000) {
//			if (nowWater < MAXWATER) {
//				nowWater += 100;
//			}
//			else {
//				break;
//			}
//			system("cls");
//			printf(" �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[-\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@       �@ |\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@�@�@�@|\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@�@�@�@�@|\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@�@�@�@|\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@�@�@�@�@|\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@       �@ |\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@�@�@�@|\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@�@�@�@�@|\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@�@�@�@|\n");
//			printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@       �@�@�@�@�@�@�@�@�@�@�@|\n");
//			printf("|�@�@�@�@�@�@�@    �@");
//			printf("���ʁF%s", waters[nowWater / 100 - 1]);
//			printf("                   |\n");
//			printf(" �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[-\n");
//			//if (nowWater < MAXWATER) {
//			//	system("cls");
//			//}
//			Sleep(500);
//		}
//
//	} while (nowWater != MAXWATER);
//	printf("\n�������^���ɂȂ�܂����B\n");
//}

void drainWater() {
	int lockCount = 0;

	printf("\n�������o���ɂ�SHIFT�L�[�����������Ă��������B\n");

	do
	{
		while (GetKeyState(VK_SHIFT) & 0x8000) {
			if (nowWater >= 100) {
				nowWater -= 100;
			}
			else {
				break;
			}
			printf("������r�o���A���ʁF%d\n", nowWater);
			Sleep(500);
		}

		if (nowWater < 100) {
			break;
		}
		Sleep(1000);
		lockCount++;

	} while (lockCount < 5);

	if (lockCount >= 5) {
		printf("���b�N����܂����B\n");
	}

	lockCount = 0;
}