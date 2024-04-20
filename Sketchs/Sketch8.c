// 2024-04-11 �ڷᱸ�� ����
// ��ȭ��ȣ�� v4.0
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define CAPACITY 100
#define BUFFER_LENGTH 100

// �� ����� ������ ����ü�� ����д�.
typedef struct {
	char* name;
	char* number;
	char* email;
	char* group;
}PERSON;

// PERSON Ÿ���� �迭 directory�� �����Ѵ�.
PERSON directory[CAPACITY];

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
// save as [fileName] : ���� ��ϵ� ������ ���Ϸ� �����Ѵ�.
// clear : ������Ʈ â ����� �����.
void add(char*, char*, char*, char*);
void handle_add(char*);
void find(char*);
void status();
void delete(char*);
void load(char*);
void save(char*);

int read_line(FILE*, char[], int);
int search(char*);			// Ž���ϴ� �Լ�
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

	// ��� �׸���� strdup�� �����Ͽ� �����Ѵ�.
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
		// ����ü �������� ġȯ ������ ����ǹǷ� ��� �׸���� ���ε��� ġȯ�� �ʿ䰡 ����.
		directory[i] = directory[i + 1];
	}
	n--;
	printf("'%s' was deleted succesfully.\n", name);
}

void load(char* fileName) {
	char buffer[BUFFER_LENGTH];
	char* name, * number, * email, * group;

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
		name = strtok(buffer, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
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
		fprintf(fp, "%s#", directory[i].name);
		fprintf(fp, "%s#", directory[i].number);
		fprintf(fp, "%s#", directory[i].email);
		fprintf(fp, "%s#\n", directory[i].group);
	}
	fclose(fp);
}

// Ű����Ӹ��� �ƴ϶� ���Ϸκ��͵� ���� �� �ִ�.
// FILE* �Ű����� �ڸ��� stdin�� ������, Ű����κ��� �Է��� ���� �� �ְ� �ȴ�.
int read_line(FILE *fp, char str[], int n) {
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		// ���ڿ��� ������ �ִٸ� ���ڿ��� �Է¹��� ���ڸ� �Է��Ѵ�.
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
	char empty[] = " ";

	printf("   Phone : ");
	read_line(stdin, number, BUFFER_LENGTH);
	printf("   Email : ");
	read_line(stdin, email, BUFFER_LENGTH);
	printf("   Group : ");
	read_line(stdin, group, BUFFER_LENGTH);

	// �������� �ʴ� �׸���� �ϳ��� ���鹮�ڷθ� ���ܵд�.
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