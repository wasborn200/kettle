#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

/// <summary>
/// 時間経過を設定する
/// </summary>
/// <param name="i">経過時間(秒)</param>
void interval(double i)
{
	clock_t g;
	g = i * CLOCKS_PER_SEC + clock();
	while (g > clock());
}