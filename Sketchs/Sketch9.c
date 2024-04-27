// 2024-04-27 자료구조 공부
// 전화번호부 v5.2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define INIT_CAPACITY 100
#define BUFFER_LENGTH 100

// 한 사람의 정보를 구조체로 묶어둔다.
typedef struct {
	char* name;
	char* number;
	char* email;
	char* group;
}PERSON;

// PERSON 타입의 배열 directory를 선언한다.
PERSON** directory;

int capacity;
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
// save [fileName] : 현재 등록된 정보를 파일로 저장한다.
// clear : 프롬포트 창 기록을 지운다.
void add(char*, char*, char*, char*);
void handle_add(char*);
void find(char*);
void status();
void delete(char*);
void load(char*);
void save(char*);

void init();

int read_line(FILE*, char[], int);
int search(char*);			// 탐색하는 함수
int compose_name(char[], int);
void print_person(PERSON*);
void reallocate();
void release_person(PERSON*);

int main(void) {
	init();
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
	free(directory);
	return 0;
}

void add(char* name, char* number, char* email, char* group) {
	// 현재 저장되어있는 정보의 수가 오버플로될 경우를 방지
	// 만일 현재 정보의 수가 너무 많아서 꽉찼다면, 다시 재할당을 해준다.
	if (n >= capacity) reallocate();

	int i = n - 1;
	while (i >= 0 && strcmp(directory[i]->name, name) > 0) {
		directory[i + 1] = directory[i];
		i--;
	}

	// 정보들을 앞으로 한칸씩 옮긴 후 비어있는 칸에 새로운 정보를 저장해야하므로
	// 해당 칸에 사용할 구조체 객체를 동적할당한다.
	directory[i + 1] = (PERSON*)malloc(sizeof(PERSON));
	// load에서 넘어오는 경우 이미 load에서 strdup을 해서 복제되었기 때문에
	// 한번 더 strdup을 할 필요가 없다.
	directory[i + 1]->name = name;
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;
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

	PERSON* p = directory[index];
	for (int i = index; i < n - 1; i++) {
		// 구조체 변수간의 치환 연산이 적용되므로 멤버 항목들을 따로따로 치환할 필요가 없다.
		directory[i] = directory[i + 1];
	}
	n--;
	release_person(p);
	printf("'%s' was deleted succesfully.\n", name);
}

void load(char* fileName) {
	char buffer[BUFFER_LENGTH];
	char* name, * number, * email, * group;
	char* token;

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
		// #을 기준으로 나눠서 가장 처음 나오는 토큰을 name으로 읽어들이고, 이름없는 정보는 없다고 가정
		name = strtok(buffer, "#");
		// #을 기준으로 토큰을 나눠서 두번째 토큰인 number를 읽어들인다.
		token = strtok(NULL, "#");
		// 토큰이 공백문자이면 number는 NULL로 취급한다.
		if (strcmp(token, " ") == 0) number = NULL;
		else number = strdup(token);
		// #을 기준으로 토큰을 나눠서 세번째 토큰인 email을 읽어들인다.
		token = strtok(NULL, "#");
		// 토큰이 공백문자이면 email은 NULL로 취급한다.
		if (strcmp(token, " ") == 0) email = NULL;
		else email = strdup(token);
		// #을 기준으로 토큰을 나눠서 네번째 토큰인 group을 읽어들인다.
		token = strtok(NULL, "#");
		// 토큰이 공백문자이면 group은 NULL로 취급한다.
		if (strcmp(token, " ") == 0) group = NULL;
		else group = strdup(token);
		// 읽어들인 name과 number와 email과 group을 전부 directory에 추가한다.
		// name부터 group까지 전부 strdup으로 넘겨 주었기 때문에 add에서 따로 strdup을 할 필요 없다.
		add(strdup(name), number, email, group);
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
		fprintf(fp, "%s#", directory[i]->name);
		if (directory[i]->number != NULL) fprintf(fp, "%s#", directory[i]->number);
		else fprintf(fp, " #");
		if (directory[i]->email) fprintf(fp, "%s#", directory[i]->email);
		else fprintf(fp, " #");
		if (directory[i]->group) fprintf(fp, "%s#\n", directory[i]->group);
		else fprintf(fp, " #");
	}
	fclose(fp);
}

// 구조체 포인터 directory를 미리 초기화 해주는 함수
void init(void) {
	directory = (PERSON**)malloc(INIT_CAPACITY * sizeof(PERSON*));
	capacity = INIT_CAPACITY;
	n = 0;
}

// 오버플로 방지를 위해 정보를 저장할 공간을 재할당해주는 함수
void reallocate() {
	capacity *= 2;
	// 임시적으로 저장해 둘 구조체 포인터 배열을 동적할당한다.
	PERSON** tmp = (PERSON**)malloc(capacity * sizeof(PERSON*));
	// 임시적으로 저장해둔 구조체 포인터 배열로 정보들을 옮긴다.
	for (int i = 0; i < n; i++) {
		tmp[i] = directory[i];
	}
	// 기존의 directory라는 구조체 포인터 배열을 메모리 할당해제한다.
	free(directory);
	// 임시적으로 저장해둔 구조체 포인터 배열의 주솟값을 다시 directory라는 이름으로 가리킨다.
	directory = tmp;
}

// delete 함수에서 해당 정보를 저장해둔 메모리를 할당 해제하는 함수
void release_person(PERSON* p) {
	free(p->name);
	// NULL인 데이터를 free시킬 필요는 없으므로, NULL이 아닌 경우만 free시킨다.
	if (p->number != NULL) free(p->number);
	if (p->email != NULL) free(p->email);
	if (p->group != NULL) free(p->group);
	// 구조체 포인터의 멤버들을 전부 free한 뒤에 구조체 포인터 자체를 free시킨다.
	free(p);
}

// 키보드뿐만이 아니라 파일로부터도 읽을 수 있다.
// FILE* 매개변수 자리에 stdin을 넣으면, 키보드로부터 입력을 받을 수 있게 된다.
int read_line(FILE* fp, char str[], int n) {
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		// 문자열에 공간이 있다면 문자열에 입력받은 문자를 입력한다.
		if (i < n - 1) str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int search(char* tmp) {
	for (int i = 0; i < n; i++) {
		if (strcmp(tmp, directory[i]->name) == 0) {
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

	printf("   Phone : ");
	read_line(stdin, number, BUFFER_LENGTH);
	printf("   Email : ");
	read_line(stdin, email, BUFFER_LENGTH);
	printf("   Group : ");
	read_line(stdin, group, BUFFER_LENGTH);

	// 존재하지 않는 항목들은 하나의 공백문자로만 남겨둔다.
	add(strdup(name), (char*)(strlen(number) > 0 ? strdup(number) : NULL),
		(char*)(strlen(email) > 0 ? strdup(email) : NULL),
		(char*)(strlen(group) > 0 ? strdup(group) : NULL));
}

void print_person(PERSON *p) {
	printf("%s:\n", p->name);
	if (p->number != NULL) printf("   Phone : %s\n", p->number);
	else printf("   Phone : NULL\n");
	if (p->email != NULL) printf("   Email : %s\n", p->email);
	else printf("   Email : NULL\n");
	if (p->group != NULL) printf("   Group : %s\n", p->group);
	else printf("   Group : NULL\n");
}