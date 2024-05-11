// 2024-05-11 자료구조 공부
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

void print_data(NODE*);
void anti_garbage();
void push_node();

int main(void) {
	head = (NODE*)malloc(sizeof(NODE));
	if (head == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}
	head->data = "Tuesday";
	head->next = NULL;

	NODE* q = (NODE*)malloc(sizeof(NODE));
	if (q == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}
	q->data = "Thursday";
	q->next = NULL;
	head->next = q;

	NODE* p = (NODE*)malloc(sizeof(NODE));
	if (p == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}
	p->data = "Friday";
	p->next = NULL;
	q->next = p;

	push_node();
	print_data(head);
	anti_garbage();
	return 0;
}

// 모든 노드를 순회하면서 각 노드의 data 필드 내부 데이터를 출력한다.
void print_data(NODE* head) {
	NODE* buff = head;
	while (buff != NULL) {
		printf("%s\n", buff->data);
		// 다음 노드를 가리키게 된다.
		buff = buff->next;
	}
}

// 모든 노드를 순회하면서 메모리 할당을 해제한다.
void anti_garbage(void) {
	int flag = 0;
	NODE* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		// 현재 push_node에 의해 동적할당으로 데이터필드를 받은 노드 전용
		if (flag == 0) free(tmp->data);
		free(tmp);
		flag++;
	}
}

// 맨앞에 새로운 노드를 추가한다.
// head가 전역변수가 아닐 경우 : void push_node(NODE** head) -> 호출 시, push_node(&head);
// 혹은 이러한 방법도 있다 : NODE *push_node(NODE *head) -> 호출 시, head = push_node(head);
void push_node(void) {
	NODE* push = (NODE*)malloc(sizeof(NODE));
	if (push == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}
	char* data = (char*)malloc(256 * sizeof(char));
	if (data == NULL) {
		printf("메모리 할당 실패\n");
		free(push); // push에 할당된 메모리 해제
		return;
	}
	scanf("%s", data);
	push->data = data;
	// head가 전역변수가 아니라면 push->next = *head; *head = push;
	// 다른 방법의 경우 : 아래를 그대로 한 뒤, return push;
	push->next = head;
	head = push;
}