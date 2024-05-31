// 2024-06-01 �ڷᱸ�� ����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// ���������� ���ڿ� ���ͷ��� data�ʵ忡 �Ҵ��ϱ� ���ٴ� strdup()�� ����Ͽ� ���� �����ؾ� free�� ��, ������ ����Ű�� �ʴ´�.
// malloc �Լ��� �޸� �Ҵ��� �����ϸ� �ڵ����� �Ҵ��� ���� �ʰ� �ǹǷ�(NULL�� �ǹǷ�), ���н� free�� ���� �ʾƵ� �ȴ�.

struct node {
	char* data;
	struct node* next;
};

typedef struct node NODE;
// ��� ��带 �̸� �ʱ�ȭ�س��´�.
NODE* head = NULL;

NODE* remove_first(void);
NODE* remove_after(NODE*);
int find(char*);
int add_after(NODE*, char*);
void anti_garbage(void);
void print_data(NODE*);

int main(void) {
	head = (NODE*)malloc(sizeof(NODE));
	if (head == NULL) {
		printf("head �޸� �Ҵ� ����.\n");
		return;
	}
	head->data = strdup("Tom");
	head->next = NULL;

	NODE* nd = (NODE*)malloc(sizeof(NODE));
	if (nd == NULL) {
		printf("nd1 �޸� �Ҵ� ����.\n");
		return;
	}
	nd->data = strdup("Mary");
	nd->next = NULL;
	head->next = nd;

	NODE* nd2 = (NODE*)malloc(sizeof(NODE));
	if (nd2 == NULL) {
		printf("nd2 �޸� �Ҵ� ����.\n");
		return;
	}
	nd2->data = strdup("Harry");
	nd2->next = NULL;
	nd->next = nd2;

	int exception = 0;
	int flag = 0;

	while (1) {
		char search[50] = { 0 };
		if (flag == 1) {
			break;
		}
		printf("\n���ϴ� �۾��� �������ֽʽÿ�.\n\n");
		printf("1. ù��° ��� �����\n");
		printf("2. ��带 �߰��� �߰��ϱ�\n");
		printf("3. �߰��� ��带 �����\n");
		printf("4. Ư�� ��带 ã��\n");
		printf("5. ������\n\n>>> ");
		int answer = 0;
		scanf("%d", &answer);
		printf("\n");
		switch (answer) {
		case 1:
			// ������ ù��° ��带 �Ҵ� �����Ѵ�.
			free(remove_first());
			print_data(head);
			break;
		case 2:
			exception = add_after(nd, "Jim");
			if (exception == 0) printf("���� ��尡 NULL�Դϴ�.\n");
			print_data(head);
			break;
		case 3:
			// ������ ��带 �Ҵ� �����Ѵ�.
			free(remove_after(nd));
			print_data(head);
			break;
		case 4:
			printf("Q. ");
			scanf("%s", search);
			if (find(search) != -1) {
				printf("\n%d��° ����� %s�� �����մϴ�.\n", find(search), search);
			}
			else {
				printf("�׷� �� �����ϴ�.\n");
			}
			break;
		case 5:
			print_data(head);
			flag = 1;
			break;
		default:
			printf("�߸��� �Է��Դϴ�.\n\n\n");
			break;
		}
	}
	anti_garbage();
	return 0;
}

// ��� ��带 ��ȸ�ϸ鼭 �޸� �Ҵ��� �����Ѵ�.
void anti_garbage(void) {
	NODE* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		if (tmp->data) {
			free(tmp->data);  // ���� �Ҵ�� �����͸� �޸� ����
		}
		free(tmp);
	}
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

int add_after(NODE* prev, char* item) {
	if (prev == NULL) return 0;
	NODE* tmp = (NODE*)malloc(sizeof(NODE));
	if (tmp == NULL) {
		printf("tmp �޸� �Ҵ� ����.\n");		
		return 0;
	}
	tmp->data = strdup(item);	// ���ڿ��� �����Ͽ� ���� �Ҵ��Ѵ�.
	tmp->next = prev->next;
	prev->next = tmp;
	return 1;
}

NODE* remove_first(void) {
	if (head == NULL) {
		return NULL;
	}
	else {
		NODE* tmp = head;
		head = head->next;
		// ������ ��带 ��ȯ�Ѵ�.
		return tmp;
	}
}

// �߰��� �ִ� ��带 �����Ѵ�.
NODE* remove_after(NODE* prev) {
	if (prev->next == NULL) return NULL;
	else {
		NODE* tmp = prev->next;
		prev->next = prev->next->next;
		// ������ ��带 ��ȯ�Ѵ�.
		return tmp;
	}
}

// ��带 ��ȸ�Ѵ�.
int find(char* word) {
	NODE* p = head;
	int flag = 0;
	while (p != NULL) {
		if (strcmp(p->data, word) == 0) return flag;
		p = p->next;
		flag += 1;
	}
	return -1;
}