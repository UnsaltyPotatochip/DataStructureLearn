// PracticeProject01 활용
// 그냥 배열이랑 포인터 공부하려고 한거지 사실 존나 비효율적인 코드
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
	printf("한자리 수 정수 4개로 이루어진 비밀번호를 설정하세요.\n");
	for (int i = 0; i < 4; i++) {
		printf(">>> ");
		//scanf("%d", &tmp[i]);
		scanf("%d", &(*(tmp + i)));
		if (tmp[i] < 0 || tmp[i] >= 10) {
			printf("한자리 수 정수로 다시 입력하십시오.\n");
			i--;
		}

	}
	return tmp;
}

void checking(int* pwd) {
	int* tmp = (int*)malloc(4 * sizeof(int));
	tmp = pwd;
	system("cls");
	printf("현재 설정된 비밀번호는 ");
	for (int i = 0; i < 4; i++) {
		//printf("%d", tmp[i]);
		printf("%d", *(tmp + i));
	}
	printf(" 입니다.\n");
	Sleep(2000);
	system("cls");
}