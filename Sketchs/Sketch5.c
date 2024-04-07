// 2024-04-07 �ڷᱸ�� ����
// ��ȭ��ȣ�� v2.0
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define CAPACITY 100
#define BUFFER_SIZE 100

char* names[CAPACITY];		// �̸��� �����ϴ� �迭
char* numbers[CAPACITY];	// ��ȭ��ȣ�� �����ϴ� �迭(010-xxxx-xxxx�� ���� ���� ������ �� ������ char* ���� + ��ó�� 0�� �ν�)
int n = 0;					// ����� ������ ��

// ��ȭ��ȣ�� ��ɾ�
// add [name] [call-number] : ���ο� ����� ��ȭ��ȣ�ο� �߰��Ѵ�
// find [name] : �̸����� ��ȭ��ȣ�� �˻��Ѵ�.
// status : ��ȭ��ȣ�ο� ����� ��� ������� �˻��Ѵ�.
// delete [name] : ��ȭ��ȣ�ο��� �ش� ����� ������ �����Ѵ�.
// exit : ���α׷��� �����Ѵ�.
// load [fileName] : ������ ������ִ� ���� �ϳ��� �ҷ��´�.
// save [fileName] : ���� ��ϵ� ������ ���Ϸ� �����Ѵ�.
// help : ��� ������ ��ɾ �����ش�.
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

	// ��ȭ��ȣ�ο� ���ĺ� ������ ����ǰ� �����Ѵ�.
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
	// ���Ͽ� �����ϱ� ���ؼ� ���� �ش� ������ fopen()�Լ��� �б���(r)�� ����.
	FILE* fp = fopen(fileName, "r");
	// ���� ���� ���� �������� ���� ����ó��
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	// ������ ���� ������ ������ �ݺ��ؼ� �̸��� ��ȭ��ȣ�� �о �迭�� �����Ѵ�.
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = strdup(buf1);
		numbers[n] = strdup(buf2);
		n++;
	}
	// ������ ���� ������ �ݵ�� �ݾ��־�� �Ѵ�.
	fclose(fp);
}

void save(void) {
	char fileName[BUFFER_SIZE];
	scanf("%s", fileName);

	// ���� ���� ������ �ۼ��Ϸ��� �ϹǷ�, ����(w)���� ����.
	FILE* fp = fopen(fileName, "w");
	// ������ ������ ������ ���� �������� ���
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
	printf("add [name] [call-number] : ���ο� ����� ��ȭ��ȣ�ο� �߰��Ѵ�.\n");
	printf("find [name] : �̸����� ��ȭ��ȣ�� �˻��Ѵ�.\n");
	printf("status : ��ȭ��ȣ�ο� ����� ��� ������� �˻��Ѵ�.\n");
	printf("delete [name] : ��ȭ��ȣ�ο��� �ش� ����� ������ �����Ѵ�.\n");
	printf("load [fileName] : ������ ������ִ� ���� �ϳ��� �ҷ��´�.\n");
	printf("save [fileName] : ���� ��ϵ� ������ ���Ϸ� �����Ѵ�.\n");
	printf("help : ��� ������ ��ɾ �����ش�.\n");
	printf("exit : ���α׷��� �����Ѵ�.\n");
}

// Ž���ϴ� �Լ�
int search(char* tmp) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], tmp) == 0) {
			return i;
		}
	}
	// Ž���� ������ ���
	return -1;
}