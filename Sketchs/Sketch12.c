// 2024-05-11 �ڷᱸ�� ����
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

struct node {
	char* data;
	struct node* next;
};

typedef struct node NODE;
// ��� ��带 �̸� �ʱ�ȭ�س��´�.
NODE* head = NULL;

void print_data(NODE*);
void anti_garbage();
void push_node();

int main(void) {
	head = (NODE*)malloc(sizeof(NODE));
	if (head == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return;
	}
	head->data = "Tuesday";
	head->next = NULL;

	NODE* q = (NODE*)malloc(sizeof(NODE));
	if (q == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return;
	}
	q->data = "Thursday";
	q->next = NULL;
	head->next = q;

	NODE* p = (NODE*)malloc(sizeof(NODE));
	if (p == NULL) {
		printf("�޸� �Ҵ� ����\n");
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

// ��� ��带 ��ȸ�ϸ鼭 �� ����� data �ʵ� ���� �����͸� ����Ѵ�.
void print_data(NODE* head) {
	NODE* buff = head;
	while (buff != NULL) {
		printf("%s\n", buff->data);
		// ���� ��带 ����Ű�� �ȴ�.
		buff = buff->next;
	}
}

// ��� ��带 ��ȸ�ϸ鼭 �޸� �Ҵ��� �����Ѵ�.
void anti_garbage(void) {
	int flag = 0;
	NODE* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		// ���� push_node�� ���� �����Ҵ����� �������ʵ带 ���� ��� ����
		if (flag == 0) free(tmp->data);
		free(tmp);
		flag++;
	}
}

// �Ǿտ� ���ο� ��带 �߰��Ѵ�.
// head�� ���������� �ƴ� ��� : void push_node(NODE** head) -> ȣ�� ��, push_node(&head);
// Ȥ�� �̷��� ����� �ִ� : NODE *push_node(NODE *head) -> ȣ�� ��, head = push_node(head);
void push_node(void) {
	NODE* push = (NODE*)malloc(sizeof(NODE));
	if (push == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return;
	}
	char* data = (char*)malloc(256 * sizeof(char));
	if (data == NULL) {
		printf("�޸� �Ҵ� ����\n");
		free(push); // push�� �Ҵ�� �޸� ����
		return;
	}
	scanf("%s", data);
	push->data = data;
	// head�� ���������� �ƴ϶�� push->next = *head; *head = push;
	// �ٸ� ����� ��� : �Ʒ��� �״�� �� ��, return push;
	push->next = head;
	head = push;
}