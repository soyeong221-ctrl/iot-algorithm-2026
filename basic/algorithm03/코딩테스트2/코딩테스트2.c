// 2. 1부터 N까지 적힌 카드가 있습니다. 
// 다음 과정을 카드가 1장 남을 때까지 반복합니다. 
// // 마지막 카드번호를 출력하는 소스를 작성하세요. 
// - 맨 위 카드 1장을 버린다
// - 그 다음 맨 위 카드 1장을 맨 아래로 옮긴다

// 예) 입력 6->결과 4

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "test.h"

int main(void) {
    IntQueue qu;
    int n, i, x;

    printf("카드 개수: ");
    scanf("%d", &n);

    Initialize(&qu, n);


    for (i = 1; i <= n; i++) {
        Enque(&qu, i);
    }

    for (i = 0; i < n - 1; i++) {
        Deque(&qu, &x); // - 맨 위 카드 버리기

        Deque(&qu, &x); // - 맨 아래로 보내기
        Enque(&qu, x);
    }


    Deque(&qu, &x);
    printf("마지막 카드 번호: %d\n", x);

    Terminate(&qu);
    return 0;

}