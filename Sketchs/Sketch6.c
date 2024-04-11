// 2024-04-11 �ڷᱸ�� ����
// ��ȭ��ȣ�� v3.1
// �̿Ϲ���
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define INIT_CAPACITY 3
#define BUFFER_SIZE 100

char** names;		// �̸��� �����ϴ� �迭
char** numbers;		// ��ȭ��ȣ�� �����ϴ� �迭(010-xxxx-xxxx�� ���� ���� ������ �� ������ char* ���� + ��ó�� 0�� �ν�)

int capacity = INIT_CAPACITY;	// �迭�� ũ��
int n = 0;						// ����� ������ ��

// ��ȭ��ȣ�� ��ɾ�
// add [name] [call-number] : ���ο� ����� ��ȭ��ȣ�ο� �߰��Ѵ�
// find [name] : �̸����� ��ȭ��ȣ�� �˻��Ѵ�.
// status : ��ȭ��ȣ�ο� ����� ��� ������� �˻��Ѵ�.
// delete [name] : ��ȭ��ȣ�ο��� �ش� ����� ������ �����Ѵ�.
// exit : ���α׷��� �����Ѵ�.
// load [fileName] : ������ ������ִ� ���� �ϳ��� �ҷ��´�.
// save [fileName] : ���� ��ϵ� ������ ���Ϸ� �����Ѵ�.
// help [command] : �ش� ��ɾ��� ���̵带 �����ش�.
// clear : ������Ʈ â ����� �����.
void add();
void find();
void status();
void delete();
void load();
void save();
void help();

int read_line(char[], int);
int search(char*);			// Ž���ϴ� �Լ�
void init_directory();		// �迭 names�� numbers ����
void process_command();		// ������� ����� �޾� ó���ϴ� �Լ�

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
		else if (strcmp(command, "clear") == 0) {
			system("cls");
		}
		else {
			printf("Unknown Command, Type 'help all'.\n");
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
	char command[BUFFER_SIZE];
	scanf("%s", command);
	if (strcmp(command, "add") == 0) {
		printf("add [name] [call-number] : ���ο� ����� ��ȭ��ȣ�ο� �߰��Ѵ�.\n");
	}
	else if (strcmp(command, "find") == 0) {
		printf("find [name] : �̸����� ��ȭ��ȣ�� �˻��Ѵ�.\n");
	}
	else if (strcmp(command, "status") == 0) {
		printf("status : ��ȭ��ȣ�ο� ����� ��� ������� �˻��Ѵ�.\n");
	}
	else if (strcmp(command, "delete") == 0) {
		printf("delete [name] : ��ȭ��ȣ�ο��� �ش� ����� ������ �����Ѵ�.\n");
	}
	else if (strcmp(command, "exit") == 0) {
		printf("exit : ���α׷��� �����Ѵ�.\n");
	}
	else if (strcmp(command, "save") == 0) {
		printf("save [fileName] : ���� ��ϵ� ������ ���Ϸ� �����Ѵ�.\n");
	}
	else if (strcmp(command, "load") == 0) {
		printf("load [fileName] : ������ ������ִ� ���� �ϳ��� �ҷ��´�.\n");
	}
	else if (strcmp(command, "help") == 0) {
		printf("help : ��� ������ ��ɾ �����ش�.\n");
	}
	else if (strcmp(command, "clear") == 0) {
		printf("clear : ���� ������Ʈ â�� ����� �����.\n");
	}
	else if (strcmp(command, "all") == 0) {
		printf("add [name] [call-number] : ���ο� ����� ��ȭ��ȣ�ο� �߰��Ѵ�.\n");
		printf("find [name] : �̸����� ��ȭ��ȣ�� �˻��Ѵ�.\n");
		printf("status : ��ȭ��ȣ�ο� ����� ��� ������� �˻��Ѵ�.\n");
		printf("delete [name] : ��ȭ��ȣ�ο��� �ش� ����� ������ �����Ѵ�.\n");
		printf("exit : ���α׷��� �����Ѵ�.\n");
		printf("save [fileName] : ���� ��ϵ� ������ ���Ϸ� �����Ѵ�.\n");
		printf("load [fileName] : ������ ������ִ� ���� �ϳ��� �ҷ��´�.\n");
		printf("help [command] : ��� ������ ��ɾ �����ش�.\n");
		printf("clear : ���� ������Ʈ â�� ����� �����.\n");
	}
	else {
		printf("Invalid syntax, type 'help all'.\n");
	}
}

void init_process(void) {
	// �Ҵ�� �޸��� byte���� �����Ѵ�.
	// ���� ���ڷ� �����ϴ� �ͺ��� �̷��� sizeof �����ڸ� ����ϴ� ���� �ٶ����ϴ�.
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

// line ������ �Է��� fgets, getline ���� �Լ����� �̿��Ͽ� �� ���� �ִ�.
// ����ڰ� �ٹٲ��� �ϱ� ������ �Է¹޴´�.
// limit�� �迭 str�� ũ���̴�. �� limit���� �� �� line�� ��쿡�� �� �κ��� ©����.
int read_line(char str[], int limit) {
	// getchar�� ��ȯ���� int�̴�. �׷��� getchar�� �Է¹��� ch�� int�� �����Ѵ�.
	int ch, i = 0;
	
	// �ٹٲ� ���ڰ� ���ö����� �д´�.
	while ((ch = getchar()) != '\n')
		// �迭�� �뷮�� �ʰ����� ���� ���� �����Ѵ�.
		if (i < limit - 1) str[i++] = ch;
	
	// �������� Null character('\0')�� �߰����ش�.
	str[i] = '\0';

	// ������ ���� ���ڼ��� ��ȯ�Ѵ�.
	return i;
}

void process_command(void) {

}

int search(char* tmp) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], tmp) == 0) {
			return i;
		}
	}
	// Ž���� ������ ���
	return -1;
}