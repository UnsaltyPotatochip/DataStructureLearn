// 2024-04-20 자료구조 공부
// 전화번호부 v4.0
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define CAPACITY 100
#define BUFFER_LENGTH 100

// 한 사람의 정보를 구조체로 묶어둔다.
typedef struct {
	char* name;
	char* number;
	char* email;
	char* group;
}PERSON;

// PERSON 타입의 배열 directory를 선언한다.
PERSON directory[CAPACITY];

int n = 0;	// 전화번호부에 저장된 데이터 수

char** names;		// 이름을 저장하는 배열
char** numbers;		// 전화번호를 저장하는 배열(010-xxxx-xxxx과 같은 경우로 저장할 수 있으니 char* 형태 + 맨처음 0을 인식)

// 전화번호부 명령어
// add : 새로운 사람을 전화번호부에 추가한다
// find : 이름으로 전화번호를 검색한다.
// status : 전화번호부에 저장된 모든 사람들을 검색한다.
// delete [name] : 전화번호부에서 해당 사람의 정보를 삭제한다.
// exit : 프로그램을 종료한다.
// load [fileName] : 정보가 저장되있는 파일 하나를 불러온다.
// save as [fileName] : 현재 등록된 정보를 파일로 저장한다.
// clear : 프롬포트 창 기록을 지운다.
void add(char*, char*, char*, char*);
void handle_add(char*);
void find(char*);
void status();
void delete(char*);
void load(char*);
void save(char*);

int read_line(FILE*, char[], int);
int search(char*);			// 탐색하는 함수
int compose_name(char[], int);
void print_person(PERSON);

int main(void) {
	char command_line[BUFFER_LENGTH];
	char* command, * argument;
	char name_str[BUFFER_LENGTH];

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) continue;
		command = strtok(command_line, " ");

		if (strcmp(command, "load") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument);
		}
		else if (strcmp(command, "add") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			handle_add(name_str);
		}
		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "delete") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			delete(name_str);
		}
		else if (strcmp(command, "save") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguemnts.\n");
				continue;
			}
			save(argument);
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		else if (strcmp(command, "clear") == 0) {
			system("cls");
		}
		else {
			printf("Unknown Command, Type 'help all'.\n");
		}
	}
	return 0;
}

void add(char* name, char* number, char* email, char* group) {
	int i = n - 1;
	while (i >= 0 && strcmp(directory[i].name, name) > 0) {
		directory[i + 1] = directory[i];
		i--;
	}

	// 모든 항목들을 strdup로 복제하여 저장한다.
	directory[i + 1].name = strdup(name);
	directory[i + 1].number = strdup(number);
	directory[i + 1].email = strdup(email);
	directory[i + 1].group = strdup(group);
	n++;
}

void find(char* name) {
	int index = search(name);
	if (index == -1) printf("No person named '%s' exists.\n", name);
	else print_person(directory[index]);
}

void status(void) {
	for (int i = 0; i < n; i++) {
		print_person(directory[i]);
	}
	printf("Total %d persons.\n", n);
}

void delete(char* name) {
	int index = search(name);
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}
	for (int i = index; i < n - 1; i++) {
		// 구조체 변수간의 치환 연산이 적용되므로 멤버 항목들을 따로따로 치환할 필요가 없다.
		directory[i] = directory[i + 1];
	}
	n--;
	printf("'%s' was deleted succesfully.\n", name);
}

void load(char* fileName) {
	char buffer[BUFFER_LENGTH];
	char* name, * number, * email, * group;

	// 파일에 접근하기 위해서 먼저 해당 파일을 fopen()함수로 읽기모드(r)로 연다.
	FILE* fp = fopen(fileName, "r");
	// 파일 여는 것이 실패했을 때의 예외처리
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while (1) {
		// 더 이상 읽을 수 있는 라인이 없음
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0) break;
		name = strtok(buffer, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
	}
	// 볼일이 끝난 파일은 반드시 닫아주어야 한다.
	fclose(fp);
}

void save(char* fileName) {
	// 파일 내부 내용을 작성하려고 하므로, 쓰기(w)모드로 연다.
	FILE* fp = fopen(fileName, "w");
	// 모종의 이유로 파일을 열기 실패했을 경우
	if (fp == NULL) {
		printf("Open failed\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s#", directory[i].name);
		fprintf(fp, "%s#", directory[i].number);
		fprintf(fp, "%s#", directory[i].email);
		fprintf(fp, "%s#\n", directory[i].group);
	}
	fclose(fp);
}

// 키보드뿐만이 아니라 파일로부터도 읽을 수 있다.
// FILE* 매개변수 자리에 stdin을 넣으면, 키보드로부터 입력을 받을 수 있게 된다.
int read_line(FILE *fp, char str[], int n) {
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		// 문자열에 공간이 있다면 문자열에 입력받은 문자를 입력한다.
		if (i < n-1) str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int search(char* tmp) {
	for (int i = 0; i < n; i++) {
		if (strcmp(tmp, directory[i].name) == 0) {
			return i;
		}
	}
	// 탐색에 실패한 경우
	return -1;
}

int compose_name(char str[], int limit) {
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " ");
	if (ptr == NULL) return 0;

	strcpy(str, ptr);
	length += strlen(ptr);

	while ((ptr = strtok(NULL, " ")) != NULL) {
		if (length + strlen(ptr) + 1 < limit) {
			str[length++] = ' ';
			str[length] = '\0';
			strcat(str, ptr);
			length += strlen(ptr);
		}
	}
	return length;
}

void handle_add(char* name) {
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
	char empty[] = " ";

	printf("   Phone : ");
	read_line(stdin, number, BUFFER_LENGTH);
	printf("   Email : ");
	read_line(stdin, email, BUFFER_LENGTH);
	printf("   Group : ");
	read_line(stdin, group, BUFFER_LENGTH);

	// 존재하지 않는 항목들은 하나의 공백문자로만 남겨둔다.
	add(name, (char*)(strlen(number) > 0 ? number : empty),
		(char*)(strlen(email) > 0 ? email : empty),
		(char*)(strlen(group) > 0 ? group : empty));
}

void print_person(PERSON p) {
	printf("%s:\n", p.name);
	printf("   Phone : %s\n", p.number);
	printf("   Email : %s\n", p.email);
	printf("   Group : %s\n", p.group);
}
