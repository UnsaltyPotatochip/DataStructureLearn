// PracticeProject01 Ȱ��
// �׳� �迭�̶� ������ �����Ϸ��� �Ѱ��� ��� ���� ��ȿ������ �ڵ�
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int* setting_pwd(void);
void checking(int*);

int main(void) {
	int* pwd = (int*)malloc(4 * sizeof(int));
	pwd = setting_pwd();
	checking(pwd);
	return 0;
}

int* setting_pwd(void) {
	int *tmp = (int*)malloc(4 * sizeof(int));
	printf("���ڸ� �� ���� 4���� �̷���� ��й�ȣ�� �����ϼ���.\n");
	for (int i = 0; i < 4; i++) {
		printf(">>> ");
		//scanf("%d", &tmp[i]);
		scanf("%d", &(*(tmp + i)));
		if (tmp[i] < 0 || tmp[i] >= 10) {
			printf("���ڸ� �� ������ �ٽ� �Է��Ͻʽÿ�.\n");
			i--;
		}

	}
	return tmp;
}

void checking(int* pwd) {
	int* tmp = (int*)malloc(4 * sizeof(int));
	tmp = pwd;
	system("cls");
	printf("���� ������ ��й�ȣ�� ");
	for (int i = 0; i < 4; i++) {
		//printf("%d", tmp[i]);
		printf("%d", *(tmp + i));
	}
	printf(" �Դϴ�.\n");
	Sleep(2000);
	system("cls");
}