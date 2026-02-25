// 1. 공백 없는 문자열 s가 있습니다. 
// 스택을 사용하여 문자열을 뒤집어 출력하는 소스를 작성하세요. 힌트) 한 글자씩 스택에...

// 예) hello->olleh

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "test.h"


int main(void) {

    char s[100];
    IntStack st;
    int ch; 

    printf("문자 입력 : ");
    scanf("%s", s);

    int len = strlen(s);

    // 스택 초기화
    if (Initialize(&st, 100) == -1) {
        printf("스택 초기화 실패\n");
        return 1;
    }

    // 푸시
    for (int i = 0; i < len; i++) {
        Push(&st, s[i]);
    }

    printf("결과 : ");

    // 팝
    for (int i = 0; i < len; i++) {
        if (Pop(&st, &ch) == 0)
            printf("%c", ch);
    }

    Terminate(&st);

    return 0;

    }