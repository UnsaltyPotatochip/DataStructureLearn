// 2024-03-18 자료구조 공부
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 100
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main(void) {
	// words라는 배열의 각 칸마다 문자열을 넣을 것이므로, 각 칸은 해당 문자열들을 가리키는 포인터 변수가 되어야한다.
	char* words[100];
	int n = 0;	// number of strings
	// 입력받을 문자열을 저장해 둘 임시버퍼
	char buffer[BUFFER_SIZE];
	// scanf로 문자열을 입력받을 때에는 해당 변수이름이 주소를 가리키는 포인터 변수이므로 주소값을 추출하는 &기호를 쓰지 않는다.
	while (scanf("%s", buffer) != EOF) {
		// EOF는 파일의 끝을 이야기한다, 파일의 끝에 도달하기 전까지 계속 입력받는다는 조건문
		// strdup는 문자열을 받아서 해당 문자열의 복제본을 만들고, 그 복제본의 주소를 반환하는 함수이다.
		// strcpy는 문자열을 다른 문자열로 복사만을 하는 함수여서, 현재 words의 각 칸은 문자열이 아닌 문자열을 가리키는 포인터이므로, 쓸 수 없다.
		words[n] = strdup(buffer);
		n++;
	}

	// 입력받은 단어들을 출력한다.
	for (int i = 0; i < n; i++) {
		printf("%s\n", words[i]);
	}

	/*
	* 따로 공부한 부분 *
	// char str[] = "hello";
	char* str = "hello";
	printf("%s\n\n\n", str);

	char str2[6];
	str2[0] = 'h';
	str2[1] = 'e';
	str2[2] = 'l';
	str2[3] = 'l';
	str2[4] = 'o';
	str2[5] = '\0';	// Null character, 문자열의 끝을 표시하는 역할
	// Null character의 존재로, 배열의 크기는 항상 문자열의 길이보다 적어도 1만큼은 커야함을 알 수 있다.
	printf("%s", str2);
	*/
	return 0;
}