// 2024-04-07 자료구조 공부
// 전화번호부 v2.0
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
// delete [name] : 전화번호부에서 해당 사람의 정보를 삭제한다.
// exit : 프로그램을 종료한다.
// load [fileName] : 정보가 저장되있는 파일 하나를 불러온다.
// save [fileName] : 현재 등록된 정보를 파일로 저장한다.
// help : 사용 가능한 명령어를 보여준다.
void add();
void find();
void status();
void delete();
void load();
void save();
void help();

int search(char*);

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
		else if (strcmp(command, "save") == 0) {
			save();
		}
		else if (strcmp(command, "load") == 0) {
			load();
		}
		else if (strcmp(command, "help") == 0) {
			help();
		}
		else {
			printf("Unknown Command, Type 'help'.\n");
		}
	}
	return 0;
}

void add(void) {
	char tmp1[BUFFER_SIZE], tmp2[BUFFER_SIZE];
	scanf("%s%s", tmp1, tmp2);

	// 전화번호부에 알파벳 순으로 저장되게 정렬한다.
	int i = n - 1;
	while (i >= 0 && strcmp(names[i], tmp1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = strdup(tmp1);
	numbers[i + 1] = strdup(tmp2);
	n++;
	printf("%s was added successfully.\n", tmp1);
}

void find(void) {
	char tmp[BUFFER_SIZE];
	scanf("%s", tmp);
	int index = search(tmp);
	if (index == -1) printf("No person named '%s' exists.\n", tmp);
	else printf("%s\n", numbers[index]);
	printf("No person named '%s' exists.\n", tmp);
}

void status(void) {
	for (int i = 0; i < n; i++) {
		printf("%-15s %-15s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);
}

void delete(void) {
	char tmp[BUFFER_SIZE];
	scanf("%s", tmp);
	int index = search(tmp);
	if (index == -1) {
		printf("No person named '%s' exists.\n", tmp);
		return;
	}
	for (int i = index; i < n - 1; i++) {
		names[i] = names[i + 1];
		numbers[i] = numbers[i + 1];
	}
	n--;
	printf("'%s' was deleted succesfully.\n", tmp);
}

void load(void) {
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf("%s", fileName);
	// 파일에 접근하기 위해서 먼저 해당 파일을 fopen()함수로 읽기모드(r)로 연다.
	FILE* fp = fopen(fileName, "r");
	// 파일 여는 것이 실패했을 때의 예외처리
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	// 파일의 끝에 도달할 때까지 반복해서 이름과 전화번호를 읽어서 배열에 저장한다.
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = strdup(buf1);
		numbers[n] = strdup(buf2);
		n++;
	}
	// 볼일이 끝난 파일은 반드시 닫아주어야 한다.
	fclose(fp);
}

void save(void) {
	char fileName[BUFFER_SIZE];
	scanf("%s", fileName);

	// 파일 내부 내용을 작성하려고 하므로, 쓰기(w)모드로 연다.
	FILE* fp = fopen(fileName, "w");
	// 모종의 이유로 파일을 열기 실패했을 경우
	if (fp == NULL) {
		printf("Open failed\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}

	fclose(fp);
}

void help(void) {
	printf("add [name] [call-number] : 새로운 사람을 전화번호부에 추가한다.\n");
	printf("find [name] : 이름으로 전화번호를 검색한다.\n");
	printf("status : 전화번호부에 저장된 모든 사람들을 검색한다.\n");
	printf("delete [name] : 전화번호부에서 해당 사람의 정보를 삭제한다.\n");
	printf("load [fileName] : 정보가 저장되있는 파일 하나를 불러온다.\n");
	printf("save [fileName] : 현재 등록된 정보를 파일로 저장한다.\n");
	printf("help : 사용 가능한 명령어를 보여준다.\n");
	printf("exit : 프로그램을 종료한다.\n");
}

// 탐색하는 함수
int search(char* tmp) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], tmp) == 0) {
			return i;
		}
	}
	// 탐색에 실패한 경우
	return -1;
}