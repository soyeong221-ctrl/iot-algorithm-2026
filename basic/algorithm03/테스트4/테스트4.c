// 4. 학생의 이름과 점수가 N명 주어집니다.
// 최고 점수 학생의 이름과 점수를 출력하는 소스를 작성하세요.
// 최고 점수가 동점일 경우 먼저 나온 점수가 결정됩니다.
// 예) 입력 : 4 / 김 70 이 88 박 88 최 60 / 출력 : 이 88


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> //

int main() {
    int n;
    char name[100], best_name[100];
    int score, best_score = -1;

    printf("학생 수 입력 : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {

        printf("이름과 점수 동시에 입력 (ex 박소영 100) : ");
        scanf("%s %d", name, &score);

        if (score > best_score) {
            best_score = score;
            strcpy(best_name, name);
        }
    }


    printf("%s %d\n", best_name, best_score);

    return 0;
}
