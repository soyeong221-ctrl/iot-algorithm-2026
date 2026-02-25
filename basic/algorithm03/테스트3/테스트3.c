// 3. 정수 N이 주어집니다. 
// 재귀함수로 1+2+....+N 값을 출력하는 소스를 작성하세요.
// 예) 입력 5->출력 15


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


int sum(int n) {

    if (n == 1) {
        return 1;
    }
    else {
        return n + sum(n - 1);
    }
}
int main(void) {
    int n;

    printf("정수 입력 : ");

    scanf("%d", &n);

    printf("%d\n", sum(n));

    return 0;
}