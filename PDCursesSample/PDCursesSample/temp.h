#pragma once

#define CHARBUFF 124
#define BUFFSIZE 1024
#define NUMDATA 120


struct QUESTION {
	char word[CHARBUFF];
	char answer[CHARBUFF];
	QUESTION* nextQuestion;
};

struct WORDLIST {
	int questionLen;
	QUESTION* firstQuestion;
};

void showMissCtr(int life);
void initScreen(void);
void fwriteResult(int questionLen, int questionNo, int missCtr, int sTime);
void startGame(int questionLen, int* missCtr, int* questionNo, WORDLIST wordList);
void test(QUESTION* question, int* missCtr);
int readIni(int sectionNum);
WORDLIST load_csv(char file_path[], char delim[]);

