// p.13 알고리즘이란?
// 세 정수를 입력, 최대값 출력

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int a, b, c;
	int max = 0;

	printf("세 정수 중 최댓값 리턴.\n");

	printf("a값: "); scanf("%d", &a);
	printf("b값: "); scanf("%d", &b);
	printf("c값: "); scanf("%d", &c);

	max = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}

	printf("최댓값은 %d\n", max);

	return 0;
}

