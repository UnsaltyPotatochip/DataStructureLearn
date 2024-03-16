// 2024-03-16 자료구조 공부
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
		이렇게 되면 array가 기존에 가리키던 정수 4개짜리 배열을 할당받은
		메모리 주소를 아무도 가지지 않게 되기 때문에 기존의 array가 가리키던
		정수 4개짜리 배열만큼의 메모리 주소는 'Garbage'가 된다.
	*/
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("%d\n", *(array + i));
	}
	return 0;
}