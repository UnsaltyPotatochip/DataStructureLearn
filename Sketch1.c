// 2024-03-16 �ڷᱸ�� ����
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int* array = (int*)malloc(4 * sizeof(int));
	for (int i = 0; i < 4; i++) {
		*(array + i) = i;
		printf("%d\n", *(array + i));
	}
	printf("\n");
	int* tmp = (int*)malloc(8 * sizeof(int));
	for (int i = 0; i < 8; i++) {
		if (*(array + i) == i) {
			*(tmp + i) = 30;
		}
		else {
			*(tmp + i) = i;
		}
		printf("%d\n", *(tmp + i));
	}
	array = tmp;
	/*
		�̷��� �Ǹ� array�� ������ ����Ű�� ���� 4��¥�� �迭�� �Ҵ����
		�޸� �ּҸ� �ƹ��� ������ �ʰ� �Ǳ� ������ ������ array�� ����Ű��
		���� 4��¥�� �迭��ŭ�� �޸� �ּҴ� 'Garbage'�� �ȴ�.
	*/
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("%d\n", *(array + i));
	}
	return 0;
}