// 2024-04-11 �ڷᱸ�� ����
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main(void) {
	char str[] = "My name is Chanbyeol Han, also known as UnsaltyPotatochip.";
	char delim[] = " ";		// delimeter, ���й���
	char* token;

	token = strtok(str, delim);		// ù��° ȣ��
	while (token != NULL) {
		// ��ū������ ���� ������ ���ڿ��� ǥ����
		// ��ū�� ������ �������� ���� ���� �׳� �ϳ��� ��ū���� �ν���
		printf("next token is : %s:%d\n", token, strlen(token));
		token = strtok(NULL, delim);	// �̾����� ȣ���
		// �̾����� ȣ�⿡���� �׳� NULL�� ���־� �̾ ��ū�� �ν��Ѵ�.
	}
	return 0;
}