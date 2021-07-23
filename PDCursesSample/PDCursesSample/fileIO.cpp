#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "temp.h"

//�f�B���N�g���擾
void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

void fwriteResult(int questionLen, int questionNo, int missCtr, int sTime) {
	FILE* fp;
	char s[BUFFSIZE];
	errno_t error;
	error = fopen_s(&fp, "result.txt", "w");

	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		if (questionNo == questionLen) {
			fputs("GAME CLEAR\n", fp);
		}
		else {
			fprintf(fp, "YOUR SCORE : %d\n", questionNo);
		}
		fprintf(fp, "YOUR TIME : %d\n", sTime);
		fprintf(fp, "TYPING MISS : %d\n", missCtr);
		fclose(fp);
	}
}

WORDLIST load_csv(char file_path[], char delim[]) {
	FILE* fp;					//csv�t�@�C���i�[�p�̃t�@�C���^�\����
	char s[BUFFSIZE];			//csv�t�@�C������ǂݎ������������i�[����z��
	char word[BUFFSIZE];					//������̕�����̈ꎞ�I�Ȋi�[�ꏊ
	char answer[BUFFSIZE];
	char* ctx;
	int questionLen = 0;
	WORDLIST wordList;
	QUESTION* tmpQuestion = NULL;
	QUESTION* previousQuestion = NULL;

	wordList.firstQuestion = tmpQuestion;

	errno_t error;
	error = fopen_s(&fp, file_path, "r");

	if (error != 0) {	//���s�����ꍇ�G���[���b�Z�[�W��\��
		fprintf_s(stderr, "failed to open %s", file_path);
	}

	for (int i = 0; fgets(s, BUFFSIZE, fp) != NULL; i++) {
		if (i == 0) continue;
		tmpQuestion = new QUESTION();

		sprintf_s(tmpQuestion->word, strtok_s(s, delim, &ctx));
		sprintf_s(tmpQuestion->answer, strtok_s(NULL, delim, &ctx));

		fprintf_s(stdout, "word: %s\t", tmpQuestion->word);
		fprintf_s(stdout, "answer: %s\n", tmpQuestion->answer);

		tmpQuestion->nextQuestion = NULL;

		if (previousQuestion == NULL) {
			wordList.firstQuestion = tmpQuestion;
		}
		else {
			previousQuestion->nextQuestion = tmpQuestion;
		}
		previousQuestion = tmpQuestion;
		questionLen++;
	}

	/*while (fscanf_s(fp, "%s ,%s", word, answer) != EOF) {
		fprintf_s(stdout, "word: %s\t", word);
		fprintf_s(stdout, "answer: %s\n", answer);
		questionLen++;
		tmpQuestion = new QUESTION();
		sprintf_s(tmpQuestion->word, word);
		sprintf_s(tmpQuestion->answer, answer);
		tmpQuestion->nextQuestion = NULL;
		if (previousQuestion != NULL) {
			previousQuestion->nextQuestion = tmpQuestion;
		}
		previousQuestion = tmpQuestion;
	}*/
	wordList.questionLen = questionLen;

	return wordList;
}

//ini�t�@�C���ǂݍ���
int readIni(int sectionNum) {

	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);

	char settingFile[CHARBUFF];
	char section[CHARBUFF];
	char questionNumLabel[CHARBUFF];
	int questionNum;

	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);

	sprintf_s(section, "section%d", sectionNum);
	sprintf_s(questionNumLabel, "questionNum");
	questionNum = GetPrivateProfileInt(section, questionNumLabel, -1, settingFile);

	return questionNum;
}