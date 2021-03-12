#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

extern char str[13][80];

/// <summary>
/// 画面表示のリセット及び再表示
/// </summary>
void changeDisplay() {
	system("cls");
	for (int i = 0; i < 13; i++)
	{
		printf(str[i]);
	}
}

/// <summary>
/// メッセージのリセット
/// </summary>
void messageReset() {
	printf("\r　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
}



/// <summary>
/// 時間経過を設定する
/// </summary>
/// <param name="i">経過時間(秒)</param>
//void interval(double i)
//{
//	clock_t g;
//	g = i * CLOCKS_PER_SEC + clock();
//	while (g > clock());
//}
