// 2024-03-18 �ڷᱸ�� ����
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 100
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main(void) {
	// words��� �迭�� �� ĭ���� ���ڿ��� ���� ���̹Ƿ�, �� ĭ�� �ش� ���ڿ����� ����Ű�� ������ ������ �Ǿ���Ѵ�.
	char* words[100];
	int n = 0;	// number of strings
	// �Է¹��� ���ڿ��� ������ �� �ӽù���
	char buffer[BUFFER_SIZE];
	// scanf�� ���ڿ��� �Է¹��� ������ �ش� �����̸��� �ּҸ� ����Ű�� ������ �����̹Ƿ� �ּҰ��� �����ϴ� &��ȣ�� ���� �ʴ´�.
	while (scanf("%s", buffer) != EOF) {
		// EOF�� ������ ���� �̾߱��Ѵ�, ������ ���� �����ϱ� ������ ��� �Է¹޴´ٴ� ���ǹ�
		// strdup�� ���ڿ��� �޾Ƽ� �ش� ���ڿ��� �������� �����, �� �������� �ּҸ� ��ȯ�ϴ� �Լ��̴�.
		// strcpy�� ���ڿ��� �ٸ� ���ڿ��� ���縸�� �ϴ� �Լ�����, ���� words�� �� ĭ�� ���ڿ��� �ƴ� ���ڿ��� ����Ű�� �������̹Ƿ�, �� �� ����.
		words[n] = strdup(buffer);
		n++;
	}

	// �Է¹��� �ܾ���� ����Ѵ�.
	for (int i = 0; i < n; i++) {
		printf("%s\n", words[i]);
	}

	/*
	* ���� ������ �κ� *
	// char str[] = "hello";
	char* str = "hello";
	printf("%s\n\n\n", str);

	char str2[6];
	str2[0] = 'h';
	str2[1] = 'e';
	str2[2] = 'l';
	str2[3] = 'l';
	str2[4] = 'o';
	str2[5] = '\0';	// Null character, ���ڿ��� ���� ǥ���ϴ� ����
	// Null character�� �����, �迭�� ũ��� �׻� ���ڿ��� ���̺��� ��� 1��ŭ�� Ŀ������ �� �� �ִ�.
	printf("%s", str2);
	*/
	return 0;
}