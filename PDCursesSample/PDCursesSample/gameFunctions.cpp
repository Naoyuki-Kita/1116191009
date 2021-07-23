#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "temp.h"

void initScreen(void) {

	move(15, 50);
	addstr("PLEASE PUSH 'S' KEY!!");

	int key = 0;
	while (1) {
		key = getch();
		if (key == 's') {
			refresh();
			erase();
			break;
		}
	}
}

void showMissCtr(int life) {
	move(10, 85);
	addstr("タイポ");
	refresh();
	mvprintw(12, 87, "%d", life);
	refresh();
}

//ゲームスタート
void startGame(int questionLen, int* missCtr, int* questionNo, WORDLIST wordList) {
	srand((unsigned int)clock());
	int number = 0;
	QUESTION* question = wordList.firstQuestion;

	for (int i = 1; i <= questionLen; i++) {
		move(5, 47);
		addstr("SPELL THIS WORD");
		number = rand() % wordList.questionLen;
		question = wordList.firstQuestion;
		for (int j = 0; j < number; j++) {
			question = question->nextQuestion;
		}
		test(question, missCtr);
		*questionNo = i;
		if (*missCtr > 10) break;
	}

}

//問題の表示・入力キーとの判定
void test(QUESTION* question, int* missCtr) {
	errno_t error;
	mvprintw(10, 53, "%s", question->word);  //問題の表示
	refresh();

	int word_len = strlen(question->answer);  //問題のスペル数を格納
	int j = 0;
	int key = 0;
	showMissCtr(*missCtr);  //スペルミス数の表示

	while (1) {
		key = getch();  //入力されたキー
		if (key == question->answer[j]) { //入力キーと問題のスペルがあっている
			mvprintw(15, 53 + j, "%c", key); //入力キーを表示
			refresh();
			j++;
			if (j == word_len) { //問題クリア
				erase();
				break;
			}
		}
		else { //入力キーと正解アルファベットが間違っている
			showMissCtr(++(*missCtr)); //タイピングミスカウントアップ
			if (*missCtr > 10) { //タイピングミス11回した
				erase();
				move(15, 50);
				addstr("GAME OVER");
				refresh();
				break;
			}
		}
	}
}