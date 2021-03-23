#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 1000
#define MINDEG 10
#define LACKWATER 0
#define WATER_100 100
#define COUNTRESET 0
#define ROW_LOCK_NUMBER 6
#define ROW_WATER_NUMBER 16
#define ROW_WATERS_NUMBER 11
#define COLUMN_NUMBER 80
#define DISP_LOCKON "�b�@�b�@�Z�@�b�@    �b�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n"
#define DISP_LOCKOFF "�b�@�b�@\x1b[31m��\x1b[39m�@�b�@    �b�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n"

extern int nowWater;
extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];
extern int nowDeg;

char waters[ROW_WATERS_NUMBER][COLUMN_NUMBER] = {
	"�b�@�@�@�@�@���ʁF���������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m��\x1b[39m�������������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m����\x1b[39m�����������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m������\x1b[39m���������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m��������\x1b[39m�������������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m����������\x1b[39m�����������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m������������\x1b[39m���������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m��������������\x1b[39m�������@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m����������������\x1b[39m�����@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m������������������\x1b[39m���@�@�@�@�@�@�b\n",
	"�b�@�@�@�@�@���ʁF\x1b[34m��������������������\x1b[39m�@�@�@�@�@�@�b\n"
};

/// <summary>
/// ���ʂ�1000�ɂȂ�܂Ő��������
/// </summary>
void addWater() {
	messageReset();
	printf("\rAlt�L�[�������Ő������Ă��������B(�A�v���I��:q)");

	// ���ʂ�1000�ɂȂ�܂ŁA�������邽�߂̃A�i�E���X�𑱂���
	do
	{
		// Alt�L�[������������ԁA0.5�b���ɐ��ʂ�100�㏸������
		while (GetKeyState(VK_MENU) & 0x8000) {
			if (nowWater < MAXWATER) {
				nowWater += WATER_100;
			}
			else {
				break;
			}

			strcpy(display[ROW_WATER_NUMBER], waters[nowWater / WATER_100]);
			changeDisplay();
			printf("\r������");

			Sleep(500);
		}

		printf("\rAlt�L�[�������Ő������Ă��������B(�A�v���I��:q)");

		if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

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
	
	int lockCount = COUNTRESET;
	lockOff();
	changeDisplay();
	printf("\r�������o���ɂ�SHIFT�L�[�����������Ă��������B�������b�N�Fr");

	do
	{
		// Shift�L�[������������ԁA100�����ʂ�����������
		while (GetKeyState(VK_SHIFT) & 0x8000) {
			int lockCount = 0;
			if (nowWater >= WATER_100) {
				nowWater -= WATER_100;
			}
			else {
				break;
			}

			strcpy(display[16], waters[nowWater / WATER_100]);
			changeDisplay();
			printf("\r������");

			Sleep(500);
		}

		// ���ʂ�0�ɂȂ�Ƃ����������Ȃ������Ƃ̃A�i�E���X���s���B
		// ���ʂ��O�ł͂Ȃ��AShift�L�[�������Ă��Ȃ����́A�������߂̃A�i�E���X���s���B
		if (nowWater == LACKWATER) {
			strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
			nowDeg = MINDEG;
			reflectDeg();
			changeDisplay();
			printf("\r�����������Ȃ�܂����B");
			Sleep(2000);
			break;
		}
		
		messageReset();
		printf("\r�������o���ɂ�SHIFT�L�[�����������Ă��������B�������b�N�Fr");
		Sleep(100);
		lockCount++;

		// ���L�[�������Ƌ��������b�N����
		if (GetKeyState('R') & 0x8000) {
			lockOn();
			break;
		}

	} while (lockCount < 100);

	// �����������10�b�o�߂���Ƌ��������b�N�����
	if (lockCount >= 100) {
		lockOn();
	}

	lockCount = COUNTRESET;
}