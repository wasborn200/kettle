#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

extern char str[18][80];

/// <summary>
/// ��ʕ\���̃��Z�b�g�y�эĕ\��
/// </summary>
void changeDisplay() {
	system("cls");
	for (int i = 0; i < 18; i++)
	{
		printf(str[i]);
	}
}

/// <summary>
/// ���b�Z�[�W�̃��Z�b�g
/// </summary>
void messageReset() {
	printf("\r�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
}