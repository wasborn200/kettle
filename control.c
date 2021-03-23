#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define ROW_LOCK_NUMBER 6
#define ROW_MAX_NUMBER 18
#define COLUMN_NUMBER 80
#define DISP_LOCKON "�b�@�b�@�Z�@�b�@    �b�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n"
#define DISP_LOCKOFF "�b�@�b�@\x1b[31m��\x1b[39m�@�b�@    �b�@�@�@�b�@�@�@�b�@�@�@�b�@�@�b\n"

extern char display[ROW_MAX_NUMBER][COLUMN_NUMBER];

/// <summary>
/// ��ʕ\���̃��Z�b�g�y�эĕ\��
/// </summary>
void changeDisplay() {
	system("cls");
	for (int i = 0; i < ROW_MAX_NUMBER; i++)
	{
		printf(display[i]);
	}
}

/// <summary>
/// ���b�Z�[�W�̃��Z�b�g
/// </summary>
void messageReset() {
	printf("\r�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
}

/// <summary>
/// ���������b�N����
/// </summary>
void lockOn() {
	strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKON);
	changeDisplay();
	printf("\r���������b�N����܂����B");
	Sleep(1000);
}

/// <summary>
/// �������b�N����������
/// </summary>
void lockOff() {
	strcpy(display[ROW_LOCK_NUMBER], DISP_LOCKOFF);
	changeDisplay();
	printf("\r�������b�N����������܂����B");
	Sleep(1000);
}