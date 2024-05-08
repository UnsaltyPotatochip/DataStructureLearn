// 2024-05-08 �ڷᱸ�� ����
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

int main(void) {
	// ��� ��带 �����Ѵ�.
	// ������ �ʵ� : "Tuesday"��� ���ڿ�
	// ��ũ �ʵ� : NULL
	head = (NODE*)malloc(sizeof(NODE));
	head->data = "Tuesday";
	head->next = NULL;

	// q ���� ������ �ӽ����� ����
	// ��� �� ������ ���� �ֱٿ� ������� ����� �ּҸ� ����Ų��.
	// ���� q�� ���� �ٲ�, �ι�° ����� �ּҴ� �̹� head�� next(��ũ�ʵ�)�� ������ִ�.
	
	// �ι�° ��� ����
	// ������ �ʵ� : "Thursday"��� ���ڿ�
	// ��ũ �ʵ� : NULL
	NODE* q = (NODE*)malloc(sizeof(NODE));
	q->data = "Thursday";
	q->next = NULL;
	// �ش� ����� �ּҸ� head ����� ��ũ �ʵ忡 �����Ѵ�.
	head->next = q;

	// ����° ��� ����
	// ������ �ʵ� : "Monday"��� ���ڿ�
	// ��ũ �ʵ� : ��� ���
	q = (NODE*)malloc(sizeof(NODE));
	q->data = "Monday";
	q->next = head;
	// ��尡 ����° ��带 ����Ű�� �ǹǷ�, ��������� ����° ��尡 ���� �տ� ���� �ȴ�.
	head = q;

	NODE* p = head;
	while (p != NULL) {
		printf("%s\n", p->data);
		// ���� ��带 ����Ű�� �ȴ�.
		p = p->next;
	}

	// ��� ��带 ��ȸ�ϸ鼭 �޸� �Ҵ��� �����Ѵ�.
	NODE* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}

	return 0;
}