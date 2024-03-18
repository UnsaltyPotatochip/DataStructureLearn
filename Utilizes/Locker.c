// PracticeProject01 활용
// 그냥 배열이랑 포인터 공부하려고 한거지 사실 존나 비효율적인 코드

// 2024-03-18
// 힙 영역에 메모리를 동적할당 후 메모리 할당을 해제하지 않았던 문제를 해결함
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

void setting_pwd(void);
void checking(int*);

int main(void) {
	int* pwd = (int*)malloc(4 * sizeof(int));
	setting_pwd(pwd);
	checking(pwd);

	free(pwd);
	return 0;
}

void setting_pwd(int *pwd) {
	int tmp = 0;
	printf("한자리 수 정수 4개로 이루어진 비밀번호를 설정하세요.\n");
	for (int i = 0; i < 4; i++) {
		printf(">>> ");

		scanf_s("%d", &tmp);
		if (0 <= tmp && tmp < 10) {
			*(pwd + i) = tmp;
		}
		else {
			printf("한자리 정수를 다시 입력하십시오.\n");
			i--;
		}
	}
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
