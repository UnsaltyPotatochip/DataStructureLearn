// 2024-06-01 자료구조 공부
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// 직접적으로 문자열 리터럴을 data필드에 할당하기 보다는 strdup()를 사용하여 값을 복사해야 free할 때, 문제를 일으키지 않는다.
// malloc 함수는 메모리 할당이 실패하면 자동으로 할당을 하지 않게 되므로(NULL이 되므로), 실패시 free를 하지 않아도 된다.

struct node {
	char* data;
	struct node* next;
};

typedef struct node NODE;
// 헤드 노드를 미리 초기화해놓는다.
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
		printf("head 메모리 할당 실패.\n");
		return;
	}
	head->data = strdup("Tom");
	head->next = NULL;

	NODE* nd = (NODE*)malloc(sizeof(NODE));
	if (nd == NULL) {
		printf("nd1 메모리 할당 실패.\n");
		return;
	}
	nd->data = strdup("Mary");
	nd->next = NULL;
	head->next = nd;

	NODE* nd2 = (NODE*)malloc(sizeof(NODE));
	if (nd2 == NULL) {
		printf("nd2 메모리 할당 실패.\n");
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
		printf("\n원하는 작업을 말씀해주십시오.\n\n");
		printf("1. 첫번째 노드 지우기\n");
		printf("2. 노드를 중간에 추가하기\n");
		printf("3. 중간의 노드를 지우기\n");
		printf("4. 특정 노드를 찾기\n");
		printf("5. 끝내기\n\n>>> ");
		int answer = 0;
		scanf("%d", &answer);
		printf("\n");
		switch (answer) {
		case 1:
			// 삭제된 첫번째 노드를 할당 해제한다.
			free(remove_first());
			print_data(head);
			break;
		case 2:
			exception = add_after(nd, "Jim");
			if (exception == 0) printf("이전 노드가 NULL입니다.\n");
			print_data(head);
			break;
		case 3:
			// 삭제된 노드를 할당 해제한다.
			free(remove_after(nd));
			print_data(head);
			break;
		case 4:
			printf("Q. ");
			scanf("%s", search);
			if (find(search) != -1) {
				printf("\n%d번째 노드의 %s가 존재합니다.\n", find(search), search);
			}
			else {
				printf("그런 건 없습니다.\n");
			}
			break;
		case 5:
			print_data(head);
			flag = 1;
			break;
		default:
			printf("잘못된 입력입니다.\n\n\n");
			break;
		}
	}
	anti_garbage();
	return 0;
}

// 모든 노드를 순회하면서 메모리 할당을 해제한다.
void anti_garbage(void) {
	NODE* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		if (tmp->data) {
			free(tmp->data);  // 동적 할당된 데이터만 메모리 해제
		}
		free(tmp);
	}
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

int add_after(NODE* prev, char* item) {
	if (prev == NULL) return 0;
	NODE* tmp = (NODE*)malloc(sizeof(NODE));
	if (tmp == NULL) {
		printf("tmp 메모리 할당 실패.\n");		
		return 0;
	}
	tmp->data = strdup(item);	// 문자열을 복사하여 동적 할당한다.
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
		// 삭제된 노드를 반환한다.
		return tmp;
	}
}

// 중간에 있는 노드를 삭제한다.
NODE* remove_after(NODE* prev) {
	if (prev->next == NULL) return NULL;
	else {
		NODE* tmp = prev->next;
		prev->next = prev->next->next;
		// 삭제된 노드를 반환한다.
		return tmp;
	}
}

// 노드를 순회한다.
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