#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 1000
#define MAXDEG 100.0

extern int nowWater;

char waters[10][30] = {
	"■□□□□□□□□□",
	"■■□□□□□□□□",
	"■■■□□□□□□□",
	"■■■■□□□□□□",
	"■■■■■□□□□□",
	"■■■■■■□□□□",
	"■■■■■■■□□□",
	"■■■■■■■■□□",
	"■■■■■■■■■□",
	"■■■■■■■■■■"
};

void addWater() {
	printf("水がありません。水を入れるにはAltキーを押し続けてください。\n");
	do
	{
		while (GetKeyState(VK_MENU) & 0x8000) {
			if (nowWater < MAXWATER) {
				nowWater += 100;
			}
			else {
				break;
			}
			printf("水位：%s", waters[nowWater / 100 - 1]);
			if (nowWater < MAXWATER) {
				printf("\r");
			}
			Sleep(500);
		}

	} while (nowWater != MAXWATER);
	printf("\n水が満タンになりました。\n");
}

//void addWater() {
//	printf("水がありません。水を入れるにはAltキーを押し続けてください。\n");
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
//			printf(" ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー-\n");
//			printf("|　　　　　　　　　　　　　　　　　       　　　　　　　       　 |\n");
//			printf("|　　　　　　　　　　　　　　　　　　　       　　　　　　　　　　|\n");
//			printf("|　　　　　　　　　　　　　　　　　　       　　　　　　　　　　　|\n");
//			printf("|　　　　　　　　　　　　　　　　　　　       　　　　　　　　　　|\n");
//			printf("|　　　　　　　　　　　　　　　　　　       　　　　　　　　　　　|\n");
//			printf("|　　　　　　　　　　　　　　　　　       　　　　　　　       　 |\n");
//			printf("|　　　　　　　　　　　　　　　　　　　       　　　　　　　　　　|\n");
//			printf("|　　　　　　　　　　　　　　　　　　       　　　　　　　　　　　|\n");
//			printf("|　　　　　　　　　　　　　　　　　　　       　　　　　　　　　　|\n");
//			printf("|　　　　　　　　　　　　　　　　　　       　　　　　　　　　　　|\n");
//			printf("|　　　　　　　    　");
//			printf("水位：%s", waters[nowWater / 100 - 1]);
//			printf("                   |\n");
//			printf(" ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー-\n");
//			//if (nowWater < MAXWATER) {
//			//	system("cls");
//			//}
//			Sleep(500);
//		}
//
//	} while (nowWater != MAXWATER);
//	printf("\n水が満タンになりました。\n");
//}

void drainWater() {
	int lockCount = 0;

	printf("\nお湯を出すにはSHIFTキーを押し続けてください。\n");

	do
	{
		while (GetKeyState(VK_SHIFT) & 0x8000) {
			if (nowWater >= 100) {
				nowWater -= 100;
			}
			else {
				break;
			}
			printf("お湯を排出中、水位：%d\n", nowWater);
			Sleep(500);
		}

		if (nowWater < 100) {
			break;
		}
		Sleep(1000);
		lockCount++;

	} while (lockCount < 5);

	if (lockCount >= 5) {
		printf("ロックされました。\n");
	}

	lockCount = 0;
}