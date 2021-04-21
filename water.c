#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 2000			// �ō�����
#define LIMITWATER 200			// �������s�����߂̍Œᐅ��
#define MINDEG 10
#define LACKWATER 0
#define WATER_200 200			// �����⋋�����s���ۂ̐��ʕω��̒l
#define COUNTRESET 0
#define ROW_STATUS_NUMBER 8		// ���M�A�ۉ���ԕ\�������̍s�ԍ�
#define ROW_LOCK_NUMBER 13		// �ۉ����x�\�������̍s�ԍ�
#define ROW_WATER_NUMBER 16		// ���ʕ\�������̍s�ԍ�
#define ROW_WATERS_NUMBER 11
#define COLUMN_NUMBER 80
#define MSG_RESET_ON 1
#define MSG_RESET_OFF 0
#define DISP_STATUS_DEFAULT "�b�@�@�@�@�@�@�@�@�@�b�@�Z�@�@�@�@�Z�b�@�@�@�@�@�@�@�@�@�@�b\n"

extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];
extern int nowDeg;

// ��ʕ\�������̐��ʕ\���ύX�Ɏg�p����z��
char waters[ROW_WATERS_NUMBER][COLUMN_NUMBER] = {
	"�b�@�@�[�[�[�@�@���ʁF���������������������@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m��\x1b[39m�������������������@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m����\x1b[39m�����������������@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m������\x1b[39m���������������@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m��������\x1b[39m�������������@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m����������\x1b[39m�����������@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m������������\x1b[39m���������@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m��������������\x1b[39m�������@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m����������������\x1b[39m�����@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m������������������\x1b[39m���@�@���͂k�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m��������������������\x1b[39m�@�@���͂k�@�@�@�b\n"
};

/// <summary>
/// ���ʂ�MAX�ɂȂ�܂Ő��������
/// </summary>
int addWater(int nowWater) {
	int msgResetFlag = MSG_RESET_OFF;

	messageReset();
	printf("\r����(���͂v)��A���M�{�^��(���͂g)�������Ă��������B");

	// ����MAX�ɂȂ�܂ŁA�������邽�߂̃A�i�E���X�𑱂���
	do
	{
		// T���́F�ۉ����x�ύX
		// H���́F���M���[�h�ֈڍs�i���ʂ��������ʈȏ�̎��j
		// Q���́F�A�v���I��
		// W���́F����
		if (GetKeyState('T') & 0x8000) {
			changeTargetDeg();
			msgResetFlag = MSG_RESET_ON;
		}
		else if (GetKeyState('H') & 0x8000) {
			if (nowWater >= LIMITWATER) {
				break;
			}
		}
		else if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

		// Alt�L�[������������ԁA0.5�b���ɐ��ʂ�200�㏸������
		while (GetKeyState('W') & 0x8000) {
			if (nowWater < MAXWATER) {
				nowWater += WATER_200;
				nowDeg = MINDEG;

				strcpy(display[ROW_WATER_NUMBER], waters[nowWater / WATER_200]);
				changeDisplay();
				printf("\r������");
				msgResetFlag = MSG_RESET_ON;
				Sleep(500);
			}
			else {
				break;
			}
		}

		// �������ł͂Ȃ����A���b�Z�[�W�̕\�������ɖ߂�
		if (msgResetFlag == MSG_RESET_ON) {
			messageReset();
			printf("\r����(���͂v)��A���M�{�^��(���͂g)�������Ă��������B");
			msgResetFlag = MSG_RESET_OFF;
		}

	} while (nowWater < MAXWATER);

	if (nowWater == MAXWATER) {
		messageReset();
		printf("\r�������t�ɂȂ�܂����B");
		Sleep(2000);
	}

	return nowWater;
}

/// <summary>
/// �������s���B
/// ��莞�ԉ����s��Ȃ��ꍇ�A���������b�N����
/// </summary>
int drainWater(int nowWater, int* loc) {
	int msgResetFlag = MSG_RESET_OFF;
	int lockCount = COUNTRESET;

	messageReset();
	printf("\r����(���͂`)���s���Ă��������B�ă��b�N(���͂k)");

	do {
		if (GetKeyState('L') & 0x8000 || lockCount >= 100) {
			lockOn(loc);
			break;
		}

		// A�L�[������������ԁA200�����ʂ�����������
		while (GetKeyState('A') & 0x8000) {
			lockCount = COUNTRESET;
			nowWater -= WATER_200;

			strcpy(display[ROW_WATER_NUMBER], waters[nowWater / WATER_200]);
			changeDisplay();
			printf("\r������");
			msgResetFlag = MSG_RESET_ON;
			Sleep(500);

			if (nowWater == LACKWATER) {
				break;
			}

		}

		// �������ł͂Ȃ����A���b�Z�[�W�̕\�������ɖ߂�
		if (msgResetFlag == MSG_RESET_ON && nowWater != LACKWATER) {
			messageReset();
			printf("\r����(���͂`)���s���Ă��������B�ă��b�N(���͂k)");
			msgResetFlag = MSG_RESET_OFF;
		}

		Sleep(100);
		lockCount++;

	} while (nowWater != LACKWATER);

	// ���ʂ�0�ɂȂ������A��ʕ\���������ɖ߂��i�ۉ����x�������j
	if (nowWater == LACKWATER) {
		strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_DEFAULT);
		strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
		lockOn(loc);
		nowDeg = MINDEG;
		reflectDeg();
		changeDisplay();
		printf("\r�����������Ȃ�܂����B");
		Sleep(2000);
	}

	return nowWater;
}