#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAXWATER 2000
#define LIMITWATER 200
#define MINDEG 10
#define LACKWATER 0
#define WATER_200 200
#define COUNTRESET 0
#define ROW_STATUS_NUMBER 8
#define ROW_WATERS_NUMBER 11
#define ROW_LOCK_NUMBER 13
#define ROW_WATER_NUMBER 16
#define COLUMN_NUMBER 80
#define MSG_RESET_ON 1
#define MSG_RESET_OFF 0
#define DISP_STATUS_DEFAULT "�b�@�@�@�@�@�@�@�@�@�b�@�Z�@�@�@�@�Z�b�@�@�@�@�@�@�@�@�@�@�b\n"

extern int nowWater;
extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];
extern int nowDeg;
extern int msgResetFlag;

char waters[ROW_WATERS_NUMBER][COLUMN_NUMBER] = {
	"�b�@�@�[�[�[�@�@���ʁF���������������������@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m��\x1b[39m�������������������@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m����\x1b[39m�����������������@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m������\x1b[39m���������������@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m��������\x1b[39m�������������@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m����������\x1b[39m�����������@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m������������\x1b[39m���������@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m��������������\x1b[39m�������@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m����������������\x1b[39m�����@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m������������������\x1b[39m���@�@���͂q�@�@�@�b\n",
	"�b�@�@�[�[�[�@�@���ʁF\x1b[34m��������������������\x1b[39m�@�@���͂q�@�@�@�b\n"
};

/// <summary>
/// ���ʂ�MAX�ɂȂ�܂Ő��������
/// </summary>
void addWater() {
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
			}
			else {
				break;
			}

			strcpy(display[ROW_WATER_NUMBER], waters[nowWater / WATER_200]);
			changeDisplay();
			printf("\r������");
			msgResetFlag = MSG_RESET_ON;

			Sleep(500);
		}

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
}

/// <summary>
/// �������s���B
/// ��莞�ԉ����s��Ȃ��ꍇ�A���������b�N����
/// </summary>
void drainWater() {
	
	int lockCount = COUNTRESET;
	changeDisplay();
	printf("\r����(���͂`)���s���Ă��������B�ă��b�N(���͂q)");

	do
	{
		// R���́F���b�N
		// Q���́F�A�v���I��
		if (GetKeyState('R') & 0x8000) {
			lockOn();
			break;
		}
		else if (GetKeyState('Q') & 0x8000) {
			exit(0);
		}

		// A�L�[������������ԁA200�����ʂ�����������
		while (GetKeyState('A') & 0x8000) {
			int lockCount = 0;
			if (nowWater >= WATER_200) {
				nowWater -= WATER_200;
			}
			else {
				break;
			}

			strcpy(display[16], waters[nowWater / WATER_200]);
			changeDisplay();
			printf("\r������");
			msgResetFlag = MSG_RESET_ON;

			Sleep(500);
		}

		// ���ʂ�0�ɂȂ�Ƃ����������Ȃ������Ƃ̃A�i�E���X���s���B
		if (nowWater == LACKWATER) {
			strcpy(display[ROW_STATUS_NUMBER], DISP_STATUS_DEFAULT);
			strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
			nowDeg = MINDEG;
			reflectDeg();
			changeDisplay();
			printf("\r�����������Ȃ�܂����B");
			Sleep(2000);
			break;
		}
		
		if (msgResetFlag == MSG_RESET_ON) {
			messageReset();
			printf("\r����(���͂`)���s���Ă��������B�ă��b�N(���͂q)");
			msgResetFlag = MSG_RESET_OFF;
		}


		Sleep(100);
		lockCount++;

	} while (lockCount < 100);

	// �����������10�b�o�߂���Ƌ��������b�N�����
	if (lockCount >= 100) {
		lockOn();
	}

	lockCount = COUNTRESET;
}