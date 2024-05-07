// 2024-05-07 자료구조 공부
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

typedef struct {
	char* data;
	NODE* next;		// 다음 노드의 주소를 저장할 필드
}NODE;
// 위와 같이 자신과 동일한 구조체에 대한 포인터를 멤버로 가진다는 의미에서 "자기참조형 구조체"라고 부르기도 한다.

int main(void) {
	// 연결리스트의 첫 번째 노드의 주소를 저장할 포인터이다.
	NODE* head = NULL;
	return 0;
}