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
	addstr("�^�C�|");
	refresh();
	mvprintw(12, 87, "%d", life);
	refresh();
}

//�Q�[���X�^�[�g
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

//���̕\���E���̓L�[�Ƃ̔���
void test(QUESTION* question, int* missCtr) {
	errno_t error;
	mvprintw(10, 53, "%s", question->word);  //���̕\��
	refresh();

	int word_len = strlen(question->answer);  //���̃X�y�������i�[
	int j = 0;
	int key = 0;
	showMissCtr(*missCtr);  //�X�y���~�X���̕\��

	while (1) {
		key = getch();  //���͂��ꂽ�L�[
		if (key == question->answer[j]) { //���̓L�[�Ɩ��̃X�y���������Ă���
			mvprintw(15, 53 + j, "%c", key); //���̓L�[��\��
			refresh();
			j++;
			if (j == word_len) { //���N���A
				erase();
				break;
			}
		}
		else { //���̓L�[�Ɛ����A���t�@�x�b�g���Ԉ���Ă���
			showMissCtr(++(*missCtr)); //�^�C�s���O�~�X�J�E���g�A�b�v
			if (*missCtr > 10) { //�^�C�s���O�~�X11�񂵂�
				erase();
				move(15, 50);
				addstr("GAME OVER");
				refresh();
				break;
			}
		}
	}
}