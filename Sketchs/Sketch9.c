// 2024-04-27 �ڷᱸ�� ����
// ��ȭ��ȣ�� v5.2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define INIT_CAPACITY 100
#define BUFFER_LENGTH 100

// �� ����� ������ ����ü�� ����д�.
typedef struct {
	char* name;
	char* number;
	char* email;
	char* group;
}PERSON;

// PERSON Ÿ���� �迭 directory�� �����Ѵ�.
PERSON** directory;

int capacity;
int n = 0;	// ��ȭ��ȣ�ο� ����� ������ ��

char** names;		// �̸��� �����ϴ� �迭
char** numbers;		// ��ȭ��ȣ�� �����ϴ� �迭(010-xxxx-xxxx�� ���� ���� ������ �� ������ char* ���� + ��ó�� 0�� �ν�)

// ��ȭ��ȣ�� ��ɾ�
// add : ���ο� ����� ��ȭ��ȣ�ο� �߰��Ѵ�
// find : �̸����� ��ȭ��ȣ�� �˻��Ѵ�.
// status : ��ȭ��ȣ�ο� ����� ��� ������� �˻��Ѵ�.
// delete [name] : ��ȭ��ȣ�ο��� �ش� ����� ������ �����Ѵ�.
// exit : ���α׷��� �����Ѵ�.
// load [fileName] : ������ ������ִ� ���� �ϳ��� �ҷ��´�.
// save [fileName] : ���� ��ϵ� ������ ���Ϸ� �����Ѵ�.
// clear : ������Ʈ â ����� �����.
void add(char*, char*, char*, char*);
void handle_add(char*);
void find(char*);
void status();
void delete(char*);
void load(char*);
void save(char*);

void init();

int read_line(FILE*, char[], int);
int search(char*);			// Ž���ϴ� �Լ�
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
	// ���� ����Ǿ��ִ� ������ ���� �����÷ε� ��츦 ����
	// ���� ���� ������ ���� �ʹ� ���Ƽ� ��á�ٸ�, �ٽ� ���Ҵ��� ���ش�.
	if (n >= capacity) reallocate();

	int i = n - 1;
	while (i >= 0 && strcmp(directory[i]->name, name) > 0) {
		directory[i + 1] = directory[i];
		i--;
	}

	// �������� ������ ��ĭ�� �ű� �� ����ִ� ĭ�� ���ο� ������ �����ؾ��ϹǷ�
	// �ش� ĭ�� ����� ����ü ��ü�� �����Ҵ��Ѵ�.
	directory[i + 1] = (PERSON*)malloc(sizeof(PERSON));
	// load���� �Ѿ���� ��� �̹� load���� strdup�� �ؼ� �����Ǿ��� ������
	// �ѹ� �� strdup�� �� �ʿ䰡 ����.
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
		// ����ü �������� ġȯ ������ ����ǹǷ� ��� �׸���� ���ε��� ġȯ�� �ʿ䰡 ����.
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

	// ���Ͽ� �����ϱ� ���ؼ� ���� �ش� ������ fopen()�Լ��� �б���(r)�� ����.
	FILE* fp = fopen(fileName, "r");
	// ���� ���� ���� �������� ���� ����ó��
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while (1) {
		// �� �̻� ���� �� �ִ� ������ ����
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0) break;
		// #�� �������� ������ ���� ó�� ������ ��ū�� name���� �о���̰�, �̸����� ������ ���ٰ� ����
		name = strtok(buffer, "#");
		// #�� �������� ��ū�� ������ �ι�° ��ū�� number�� �о���δ�.
		token = strtok(NULL, "#");
		// ��ū�� ���鹮���̸� number�� NULL�� ����Ѵ�.
		if (strcmp(token, " ") == 0) number = NULL;
		else number = strdup(token);
		// #�� �������� ��ū�� ������ ����° ��ū�� email�� �о���δ�.
		token = strtok(NULL, "#");
		// ��ū�� ���鹮���̸� email�� NULL�� ����Ѵ�.
		if (strcmp(token, " ") == 0) email = NULL;
		else email = strdup(token);
		// #�� �������� ��ū�� ������ �׹�° ��ū�� group�� �о���δ�.
		token = strtok(NULL, "#");
		// ��ū�� ���鹮���̸� group�� NULL�� ����Ѵ�.
		if (strcmp(token, " ") == 0) group = NULL;
		else group = strdup(token);
		// �о���� name�� number�� email�� group�� ���� directory�� �߰��Ѵ�.
		// name���� group���� ���� strdup���� �Ѱ� �־��� ������ add���� ���� strdup�� �� �ʿ� ����.
		add(strdup(name), number, email, group);
	}
	// ������ ���� ������ �ݵ�� �ݾ��־�� �Ѵ�.
	fclose(fp);
}

void save(char* fileName) {
	// ���� ���� ������ �ۼ��Ϸ��� �ϹǷ�, ����(w)���� ����.
	FILE* fp = fopen(fileName, "w");
	// ������ ������ ������ ���� �������� ���
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

// ����ü ������ directory�� �̸� �ʱ�ȭ ���ִ� �Լ�
void init(void) {
	directory = (PERSON**)malloc(INIT_CAPACITY * sizeof(PERSON*));
	capacity = INIT_CAPACITY;
	n = 0;
}

// �����÷� ������ ���� ������ ������ ������ ���Ҵ����ִ� �Լ�
void reallocate() {
	capacity *= 2;
	// �ӽ������� ������ �� ����ü ������ �迭�� �����Ҵ��Ѵ�.
	PERSON** tmp = (PERSON**)malloc(capacity * sizeof(PERSON*));
	// �ӽ������� �����ص� ����ü ������ �迭�� �������� �ű��.
	for (int i = 0; i < n; i++) {
		tmp[i] = directory[i];
	}
	// ������ directory��� ����ü ������ �迭�� �޸� �Ҵ������Ѵ�.
	free(directory);
	// �ӽ������� �����ص� ����ü ������ �迭�� �ּڰ��� �ٽ� directory��� �̸����� ����Ų��.
	directory = tmp;
}

// delete �Լ����� �ش� ������ �����ص� �޸𸮸� �Ҵ� �����ϴ� �Լ�
void release_person(PERSON* p) {
	free(p->name);
	// NULL�� �����͸� free��ų �ʿ�� �����Ƿ�, NULL�� �ƴ� ��츸 free��Ų��.
	if (p->number != NULL) free(p->number);
	if (p->email != NULL) free(p->email);
	if (p->group != NULL) free(p->group);
	// ����ü �������� ������� ���� free�� �ڿ� ����ü ������ ��ü�� free��Ų��.
	free(p);
}

// Ű����Ӹ��� �ƴ϶� ���Ϸκ��͵� ���� �� �ִ�.
// FILE* �Ű����� �ڸ��� stdin�� ������, Ű����κ��� �Է��� ���� �� �ְ� �ȴ�.
int read_line(FILE* fp, char str[], int n) {
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		// ���ڿ��� ������ �ִٸ� ���ڿ��� �Է¹��� ���ڸ� �Է��Ѵ�.
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
	// Ž���� ������ ���
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

	// �������� �ʴ� �׸���� �ϳ��� ���鹮�ڷθ� ���ܵд�.
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