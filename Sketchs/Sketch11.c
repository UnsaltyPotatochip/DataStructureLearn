// 2024-05-08 자료구조 공부
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

struct node {
	char* data;
	struct node* next;
};

typedef struct node NODE;
// 헤드 노드를 미리 초기화해놓는다.
NODE* head = NULL;

int main(void) {
	// 헤드 노드를 선언한다.
	// 데이터 필드 : "Tuesday"라는 문자열
	// 링크 필드 : NULL
	head = (NODE*)malloc(sizeof(NODE));
	head->data = "Tuesday";
	head->next = NULL;

	// q 노드는 일종의 임시적인 변수
	// 어느 한 시점에 가장 최근에 만들어진 노드의 주소만 가리킨다.
	// 따라서 q의 값이 바뀌어도, 두번째 노드의 주소는 이미 head의 next(링크필드)에 저장되있다.
	
	// 두번째 노드 생성
	// 데이터 필드 : "Thursday"라는 문자열
	// 링크 필드 : NULL
	NODE* q = (NODE*)malloc(sizeof(NODE));
	q->data = "Thursday";
	q->next = NULL;
	// 해당 노드의 주소를 head 노드의 링크 필드에 저장한다.
	head->next = q;

	// 세번째 노드 생성
	// 데이터 필드 : "Monday"라는 문자열
	// 링크 필드 : 헤드 노드
	q = (NODE*)malloc(sizeof(NODE));
	q->data = "Monday";
	q->next = head;
	// 헤드가 세번째 노드를 가리키게 되므로, 결과적으로 세번째 노드가 가장 앞에 오게 된다.
	head = q;

	NODE* p = head;
	while (p != NULL) {
		printf("%s\n", p->data);
		// 다음 노드를 가리키게 된다.
		p = p->next;
	}

	// 모든 노드를 순회하면서 메모리 할당을 해제한다.
	NODE* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}

	return 0;
}