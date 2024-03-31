// 2024-03-31 �ڷᱸ�� ����
// ��ȭ��ȣ�� v1.0
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
// delete [name[ : ��ȭ��ȣ�ο��� �ش� ����� ������ �����Ѵ�.
// exit : ���α׷��� �����Ѵ�.
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
			// �� ������ ����� ������ ��� �ڸ��� �ű��.(������.)
			// �׷��ٸ� �� �������� �ߺ��Ǵ� ��? n�� ���⼭ 1 �پ��Ƿ� status������ ������ ����
			// �ű⿡ ���Ҿ ���߿� add�� �� �Ѵٸ� �� �κ��� ��������Ƿ� ��� ����
			names[i] = names[n - 1];
			numbers[i] = numbers[n - 1];
			n--;
			printf("'%s' was deleted successfully.\n", tmp);
			return;
		}
	}
	printf("No person named '%s' exists.\n", tmp);
}