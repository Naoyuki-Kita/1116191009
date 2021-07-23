// PDCursesSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "temp.h"

int main()
{
	int msTime = 0;
	int sectionNum = 1;
	char filePath[BUFFSIZE] = "WordList.csv";
	char delim[BUFFSIZE] = ", ";
	int a = 0;
	int b = 0;

	int* missCtr = &a;
	int* questionNo = &b;

	WORDLIST wordList = load_csv(filePath, delim);
	
	initscr(); //画面初期化
	noecho();
	cbreak();
	keypad(stdscr, TRUE); //特殊キー有効化

	//iniファイル(問題と答え)読み込む
	int questionLen = readIni(sectionNum);

	//初期画面表示
	initScreen();

	//スタート時間取得
	msTime = clock();

	//ゲーム開始
	startGame(questionLen, missCtr, questionNo, wordList);
	endwin();

	//時間計測
	msTime = clock() - msTime;
	double sTime = (double)msTime / 1000;

	//ファイル出力
	fwriteResult(questionLen, *questionNo, *missCtr, sTime);

	return 0;

}








