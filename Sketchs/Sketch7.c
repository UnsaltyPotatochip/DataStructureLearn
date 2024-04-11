// 2024-04-11 자료구조 공부
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main(void) {
	char str[] = "My name is Chanbyeol Han, also known as UnsaltyPotatochip.";
	char delim[] = " ";		// delimeter, 구분문자
	char* token;

	token = strtok(str, delim);		// 첫번째 호출
	while (token != NULL) {
		// 토큰까지의 문자 개수와 문자열을 표시함
		// 토큰이 여러번 연속으로 나올 경우는 그냥 하나의 토큰으로 인식함
		printf("next token is : %s:%d\n", token, strlen(token));
		token = strtok(NULL, delim);	// 이어지는 호출들
		// 이어지는 호출에서는 그냥 NULL로 냅둬야 이어서 토큰을 인식한다.
	}
	return 0;
}