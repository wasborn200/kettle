#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 1000

extern int nowWater;
extern char str[13][80];
extern int nowDeg;
extern char degs[11][80];

char waters[11][80] = {
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n"
};

/// <summary>
/// ���ʂ�1000�ɂȂ�܂Ő��������
/// </summary>
void addWater() {
	messageReset();
	printf("\r��������܂���B��������ɂ�Alt�L�[�����������Ă��������B");

	// ���ʂ�1000�ɂȂ�܂ŁA�������邽�߂̃A�i�E���X�𑱂���
	do
	{
		// Alt�L�[������������ԁA0.5�b���ɐ��ʂ�100�㏸������
		while (GetKeyState(VK_MENU) & 0x8000) {
			if (nowWater < MAXWATER) {
				nowWater += 100;
			}
			else {
				break;
			}

			strcpy(str[11], waters[nowWater / 100]);
			changeDisplay();
			printf("\r������");

			Sleep(500);
		}

		printf("\r��������܂���B��������ɂ�Alt�L�[�����������Ă��������B");

	} while (nowWater != MAXWATER);

	messageReset();
	printf("\r�������^���ɂȂ�܂����B");
	Sleep(2000);
}

/// <summary>
/// �������s���B
/// ��莞�ԉ����s��Ȃ��ꍇ�A���������b�N����
/// </summary>
void drainWater() {
	
	int lockCount = 0;
	strcpy(str[6], "�b�@�b�@���@�b�@    �b�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n");
	changeDisplay();
	printf("\r�������o���ɂ�SHIFT�L�[�����������Ă��������B");

	do
	{
		// Shift�L�[������������ԁA100�����ʂ�����������
		while (GetKeyState(VK_SHIFT) & 0x8000) {
			int lockCount = 0;
			if (nowWater >= 100) {
				nowWater -= 100;
			}
			else {
				break;
			}

			strcpy(str[11], waters[nowWater / 100]);
			changeDisplay();
			printf("\r������");

			Sleep(500);
		}

		// ���ʂ�0�ɂȂ�Ƃ����������Ȃ������Ƃ̃A�i�E���X���s���B
		// Shift�L�[�������Ă��Ȃ������Ȃ�A�������߂̃A�i�E���X���s���B
		if (nowWater < 100) {
			nowDeg = 10;
			strcpy(str[5], degs[0]);
			changeDisplay();
			printf("\r�����������Ȃ�܂����B");
			Sleep(2000);
			break;
		}
		else {
			printf("\r�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
			printf("\r�������o���ɂ�SHIFT�L�[�����������Ă��������B");
		}
		Sleep(1000);
		lockCount++;

	} while (lockCount < 10);

	// lockCount��10�ɂȂ�Ƌ��������b�N�����
	if (lockCount >= 10) {
		strcpy(str[6], "�b�@�b�@�Z�@�b�@    �b�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n");
		changeDisplay();
		printf("\r���������b�N����܂����B");
		Sleep(2000);
	}

	lockCount = 0;
}