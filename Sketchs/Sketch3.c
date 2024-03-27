// 2024-03-27 자료구조 공부
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int read_line(char*, int);

int main(void) {
	int cnt = 0;
	char str[50];
	while (1) {		
		printf("$ ");
		// gets_s(str, sizeof(str));		// 공백문자를 포함하여 입력받는다
		cnt = read_line(str, sizeof(str));
		if (!strcmp(str, "close")) {
			printf("shutting down, have a nice day!\n");
			break;
		}
		printf("%s:%d\n", str, cnt);
	}
	return 0;
}

int read_line(char *str, int limit) {
	int ch, i = 0;
	int flag = 1;
	while ((ch = getchar()) != '\n') {
		if (flag == 0) {
			if (ch == ' ') flag = 1;
		}
		else {
			if (ch == ' ') continue;
			else flag = 0;
		}
		if (i < limit) str[i++] = ch;
	}
	if (str[i - 1] == ' ') i--;
	str[i] = '\0';
	return i;
}