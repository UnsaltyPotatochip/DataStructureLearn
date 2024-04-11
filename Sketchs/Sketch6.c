// 2024-04-11 자료구조 공부
// 전화번호부 v3.2
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define INIT_CAPACITY 3
#define BUFFER_SIZE 100

char** names;		// 이름을 저장하는 배열
char** numbers;		// 전화번호를 저장하는 배열(010-xxxx-xxxx과 같은 경우로 저장할 수 있으니 char* 형태 + 맨처음 0을 인식)

int capacity = INIT_CAPACITY;	// 배열의 크기
int n = 0;						// 저장된 데이터 수

// 전화번호부 명령어
// add [name] [call-number] : 새로운 사람을 전화번호부에 추가한다
// find [name] : 이름으로 전화번호를 검색한다.
// status : 전화번호부에 저장된 모든 사람들을 검색한다.
// delete [name] : 전화번호부에서 해당 사람의 정보를 삭제한다.
// exit : 프로그램을 종료한다.
// load [fileName] : 정보가 저장되있는 파일 하나를 불러온다.
// save [fileName] : 현재 등록된 정보를 파일로 저장한다.
// help [command] : 해당 명령어의 가이드를 보여준다.
// clear : 프롬포트 창 기록을 지운다.
void add(char*, char*);
void find(char*);
void status();
void delete(char*);
void load(char*);
void save(char*);
void help(char*);

int read_line(char[], int);
int search(char*);			// 탐색하는 함수
void init_directory();		// 배열 names와 numbers 생성
void process_command();		// 사용자의 명령을 받아 처리하는 함수
void reallocate();			// 배열 용량 초과시 재할당 해주는 함수

int main(void) {
	init_directory();
	process_command();
	return 0;
}

void add(char* arg1, char* arg2) {
	// 배열이 꽉 찰 경우 재할당한다.
	if (n >= capacity) reallocate();

	// 전화번호부에 알파벳 순으로 저장되게 정렬한다.
	int i = n - 1;
	while (i >= 0 && strcmp(names[i], arg1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = strdup(arg1);
	numbers[i + 1] = strdup(arg2);
	n++;
	printf("%s was added successfully.\n", arg1);
}

void find(char* arg1) {
	int index = search(arg1);
	if (index == -1) printf("No person named '%s' exists.\n", arg1);
	else printf("%s\n", numbers[index]);
}

void status(void) {
	for (int i = 0; i < n; i++) {
		printf("%-15s %-15s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);
}

void delete(char* arg1) {
	int index = search(arg1);
	if (index == -1) {
		printf("No person named '%s' exists.\n", arg1);
		return;
	}
	for (int i = index; i < n - 1; i++) {
		names[i] = names[i + 1];
		numbers[i] = numbers[i + 1];
	}
	n--;
	printf("'%s' was deleted succesfully.\n", arg1);
}

void load(char* arg1) {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	// 파일에 접근하기 위해서 먼저 해당 파일을 fopen()함수로 읽기모드(r)로 연다.
	FILE* fp = fopen(arg1, "r");
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

void save(char* arg1) {
	// 파일 내부 내용을 작성하려고 하므로, 쓰기(w)모드로 연다.
	FILE* fp = fopen(arg1, "w");
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

void help(char* command) {
	if (strcmp(command, "add") == 0) {
		printf("add [name] [call-number] : 새로운 사람을 전화번호부에 추가한다.\n");
	}
	else if (strcmp(command, "find") == 0) {
		printf("find [name] : 이름으로 전화번호를 검색한다.\n");
	}
	else if (strcmp(command, "status") == 0) {
		printf("status : 전화번호부에 저장된 모든 사람들을 검색한다.\n");
	}
	else if (strcmp(command, "delete") == 0) {
		printf("delete [name] : 전화번호부에서 해당 사람의 정보를 삭제한다.\n");
	}
	else if (strcmp(command, "exit") == 0) {
		printf("exit : 프로그램을 종료한다.\n");
	}
	else if (strcmp(command, "save") == 0) {
		printf("save [fileName] : 현재 등록된 정보를 파일로 저장한다.\n");
	}
	else if (strcmp(command, "load") == 0) {
		printf("load [fileName] : 정보가 저장되있는 파일 하나를 불러온다.\n");
	}
	else if (strcmp(command, "help") == 0) {
		printf("help : 사용 가능한 명령어를 보여준다.\n");
	}
	else if (strcmp(command, "clear") == 0) {
		printf("clear : 현재 프롬포트 창의 기록을 지운다.\n");
	}
	else if (strcmp(command, "all") == 0) {
		printf("add [name] [call-number] : 새로운 사람을 전화번호부에 추가한다.\n");
		printf("find [name] : 이름으로 전화번호를 검색한다.\n");
		printf("status : 전화번호부에 저장된 모든 사람들을 검색한다.\n");
		printf("delete [name] : 전화번호부에서 해당 사람의 정보를 삭제한다.\n");
		printf("exit : 프로그램을 종료한다.\n");
		printf("save [fileName] : 현재 등록된 정보를 파일로 저장한다.\n");
		printf("load [fileName] : 정보가 저장되있는 파일 하나를 불러온다.\n");
		printf("help : 사용 가능한 명령어를 보여준다.\n");
		printf("clear : 현재 프롬포트 창의 기록을 지운다.\n");
	}
	else {
		printf("Type 'help all'.\n");
	}
}

void init_directory(void) {
	// 할당될 메모리의 byte수를 지정한다.
	// 직접 숫자로 지정하는 것보다 이렇게 sizeof 연산자를 사용하는 것이 바람직하다.
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

// line 단위의 입력은 fgets, getline 등의 함수들을 이용하여 할 수도 있다.
// 사용자가 줄바꿈을 하기 전까지 입력받는다.
// limit은 배열 str의 크기이다. 즉 limit보다 더 긴 line의 경우에는 뒷 부분이 짤린다.
int read_line(char str[], int limit) {
	// getchar의 반환값은 int이다. 그래서 getchar를 입력받을 ch를 int로 지정한다.
	int ch, i = 0;
	
	// 줄바꿈 문자가 나올때까지 읽는다.
	while ((ch = getchar()) != '\n')
		// 배열의 용량을 초과하지 않을 때만 저장한다.
		if (i < limit - 1) str[i++] = ch;
	
	// 마지막에 Null character('\0')를 추가해준다.
	str[i] = '\0';

	// 실제로 읽은 문자수를 반환한다.
	return i;
}

void process_command(void) {
	char command_line[BUFFER_SIZE];
	char* command, * arg1, * arg2;

	while (1) {
		printf("$ ");
		// 명령줄을 통째로 받는다.
		if (read_line(command_line, BUFFER_SIZE) <= 0) continue;
		
		// 첫번째 토큰, 명령어
		command = strtok(command_line, " ");
		if (command == NULL) continue;

		if (strcmp(command, "add") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Number owner's name required.\n");
				printf("Type 'help add'.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL) {
				printf("Number required.\n");
				printf("Type 'help add'.\n");
				continue;
			}
			add(arg1, arg2);
		}
		else if (strcmp(command, "find") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Number owner's name required.\n");
				printf("Type 'help find'.\n");
				continue;
			}
			find(arg1);
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "delete") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Number owner's name required.\n");
				printf("Type 'help delete'.\n");
				continue;
			}
			delete(arg1);
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		else if (strcmp(command, "save") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("File name required.\n");
				printf("Type 'help save'.\n");
				continue;
			}
			save(arg1);
		}
		else if (strcmp(command, "load") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("File name required.\n");
				printf("Type 'help load'.\n");
				continue;
			}
			load(arg1);
		}
		else if (strcmp(command, "help") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				arg1 = "all";
				help(arg1);
				continue;
			}
			help(arg1);
		}
		else if (strcmp(command, "clear") == 0) {
			system("cls");
		}
		else {
			printf("Unknown Command, Type 'help all'.\n");
		}
	}
}

int search(char* tmp) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], tmp) == 0) {
			return i;
		}
	}
	// 탐색에 실패한 경우
	return -1;
}

void reallocate(void) {
	capacity *= 2;
	// 크기가 2배인 배열을 할당한다.
	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	// 원본 배열 names와 numbers의 값을 새로운 배열에 모두 복사한다.
	for (int i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	// 원본배열 names와 numbers는 필요 없으므로 할당을 해제해 garbage를 없애준다.
	free(names);
	free(numbers);

	// names와 numbers가 새로운 배열을 가리키도록 한다.
	names = tmp1;
	numbers = tmp2;
}
