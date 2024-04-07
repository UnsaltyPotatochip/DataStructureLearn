// PracticeProject05 활용
// 파일입출력 연습
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define CAPACITY 100
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int user;
int com;
int score;

void mainScreen();
void init();
int check(int);
void inGame();

int main(void) {
	while (1) {
		int main_command;
		mainScreen();
		scanf("%d", &main_command);
		if (main_command == 1) {
			system("cls");
			init();
			inGame();
		}
		else if (main_command == 2) {
			system("cls");
			printf("It's simple!\n");
			printf("You just choose and type number of 0~100\n");
			printf("Then, you will know it is over or lower\n");
			printf("If your number is correct, you win!\n");
			printf("Any trial will counted!\n");
			printf("You better to get lower score!\n");
			printf("Good Luck!\n");
			getch();
			system("cls");
		}
		else if (main_command == 3) {
			// 점수 읽어들이기
			system("cls");
			char buf[CAPACITY];
			FILE* fp = fopen("record.txt", "r");
			if (fp == NULL) {
				printf("Loading failed.\n");
			}
			else {
				while ((fscanf(fp, "%s", buf) != EOF)) {
					printf("%s\n", buf);
				}
				fclose(fp);
			}
			getch();
			system("cls");
		}
		else if (main_command == 4) {
			break;
		}
		else {
			system("cls");
			printf("Unknown Command, Try again!\n");
			getch();
			system("cls");
		}
	}
	return 0;
}

void mainScreen(void) {
	printf("1. Start\n");
	printf("2. How to Play\n");
	printf("3. Record\n");
	printf("4. Exit Game\n");
	printf(">>> ");
}

void init(void) {
	srand((unsigned)time(NULL));
	score = 0;
	com = rand() % 101;
}

void inGame(void) {
	while (1) {
		printf(">>> ");
		scanf("%d", &user);
		if (check(user) == 0) {
			score++;
		}
		else {
			system("cls");
			printf("Answer is %d.\n", com);
			printf("You won!\n");
			printf("Your trial is %d.\n", score);
			getch();
			system("cls");
			break;
		}
	}
	// 점수 기록하기
	FILE* fp = fopen("record.txt", "a");
	if (fp == NULL) {
		printf("Recording score failed.\n");
		return;
	}
	fprintf(fp, "%d_trial\n", score);
	fclose(fp);
}

int check(int trial) {
	if (com > trial) {
		system("cls");
		printf("It's more bigger!\n");
		getch();
		system("cls");
		return 0;
	}
	else if (com < trial) {
		system("cls");
		printf("It's more smaller!\n");
		getch();
		system("cls");
		return 0;
	}
	else {
		system("cls");
		printf("Correct!\n");
		getch();
		system("cls");
		return 1;
	}
}
