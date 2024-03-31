// 2024-03-31 자료구조 공부
// 전화번호부 v1.0
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define CAPACITY 100
#define BUFFER_SIZE 100

char* names[CAPACITY];		// 이름을 저장하는 배열
char* numbers[CAPACITY];	// 전화번호를 저장하는 배열(010-xxxx-xxxx과 같은 경우로 저장할 수 있으니 char* 형태 + 맨처음 0을 인식)
int n = 0;					// 저장된 데이터 수

// 전화번호부 명령어
// add [name] [call-number] : 새로운 사람을 전화번호부에 추가한다
// find [name] : 이름으로 전화번호를 검색한다.
// status : 전화번호부에 저장된 모든 사람들을 검색한다.
// delete [name[ : 전화번호부에서 해당 사람의 정보를 삭제한다.
// exit : 프로그램을 종료한다.
void add();
void find();
void status();
void delete();

int main(void) {
	char command[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "add") == 0) {
			add();
		}
		else if (strcmp(command, "find") == 0) {
			find();
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "delete") == 0) {
			delete();
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		else {
			printf("Unknown Command.\n");
		}
	}
	return 0;
}

void add(void) {
	char tmp1[BUFFER_SIZE], tmp2[BUFFER_SIZE];
	scanf("%s%s", tmp1, tmp2);
	names[n] = strdup(tmp1);
	numbers[n] = strdup(tmp2);
	n++;
	printf("%s was added successfully.\n", tmp1);
}

void find(void) {
	char tmp[BUFFER_SIZE];
	scanf("%s", tmp);
	for (int i = 0; i < n; i++) {
		if (strcmp(tmp, names[i]) == 0) {
			printf("%s\n", numbers[i]);
			return;
		}
	}
	printf("No person named '%s' exists.\n", tmp);
}

void status(void) {
	for (int i = 0; i < n; i++) {
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);
}

void delete(void) {
	char tmp[BUFFER_SIZE];
	scanf("%s", tmp);
	for (int i = 0; i < n; i++) {
		if (strcmp(tmp, names[i]) == 0) {
			// 맨 마지막 사람을 삭제된 사람 자리로 옮긴다.(덮어씌운다.)
			// 그렇다면 맨 마지막에 중복되는 건? n이 여기서 1 줄어들므로 status에서는 보이지 않음
			// 거기에 더불어서 나중에 add를 또 한다면 그 부분이 덮어씌워지므로 상관 없음
			names[i] = names[n - 1];
			numbers[i] = numbers[n - 1];
			n--;
			printf("'%s' was deleted successfully.\n", tmp);
			return;
		}
	}
	printf("No person named '%s' exists.\n", tmp);
}