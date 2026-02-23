#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 구조체 정의 ---
typedef struct {
    char title[100];
    char director[50];
    int year;
    double rating;
} Movie;

typedef struct {
    Movie* data;
    int count;
    int capacity;
} MovieManager;

// --- 유틸리티 및 입력 방어 함수 ---
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getSafeInt(const char* prompt) {
    char buffer[100];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (sscanf(buffer, "%d", &value) == 1) return value;
        printf("[오류] 숫자만 입력 가능합니다.\n");
    }
}

double getSafeDouble(const char* prompt) {
    char buffer[100];
    double value;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (sscanf(buffer, "%lf", &value) == 1) {
            if (value >= 0.0 && value <= 10.0) return value;
            else printf("[오류] 평점은 0.0 ~ 10.0 사이로 입력하세요.\n");
        }
        else printf("[오류] 숫자(실수)만 입력 가능합니다.\n");
    }
}

// --- 정렬 비교 함수들 ---
int compareTitle(const void* a, const void* b) { return strcmp(((Movie*)a)->title, ((Movie*)b)->title); }
int compareYear(const void* a, const void* b) { return ((Movie*)a)->year - ((Movie*)b)->year; }
int compareRating(const void* a, const void* b) {
    double r1 = ((Movie*)a)->rating;
    double r2 = ((Movie*)b)->rating;
    return (r1 < r2) - (r1 > r2); // 내림차순
}

// --- 파일 입출력 ---
void saveToFile(const MovieManager* mm) {
    FILE* fp = fopen("movies.txt", "w");
    if (!fp) return;
    for (int i = 0; i < mm->count; i++) {
        fprintf(fp, "%s|%s|%d|%.1f\n", mm->data[i].title, mm->data[i].director, mm->data[i].year, mm->data[i].rating);
    }
    fclose(fp);
    printf(">> 'movies.txt'에 데이터가 저장되었습니다.\n");
}

void loadFromFile(MovieManager* mm) {
    FILE* fp = fopen("movies.txt", "r");
    if (!fp) return;
    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        if (mm->count == mm->capacity) {
            mm->capacity *= 2;
            mm->data = (Movie*)realloc(mm->data, sizeof(Movie) * mm->capacity);
        }
        char* ptr = strtok(line, "|");
        if (ptr) strcpy(mm->data[mm->count].title, ptr);
        if ((ptr = strtok(NULL, "|"))) strcpy(mm->data[mm->count].director, ptr);
        if ((ptr = strtok(NULL, "|"))) mm->data[mm->count].year = atoi(ptr);
        if ((ptr = strtok(NULL, "|"))) mm->data[mm->count].rating = atof(ptr);
        mm->count++;
    }
    fclose(fp);
    printf(">> 데이터를 불러왔습니다.\n");
}

// --- 기능 함수들 ---
void addMovie(MovieManager* mm) {
    if (mm->count == mm->capacity) {
        mm->capacity *= 2;
        mm->data = (Movie*)realloc(mm->data, sizeof(Movie) * mm->capacity);
    }
    printf("제목: "); fgets(mm->data[mm->count].title, 100, stdin);
    mm->data[mm->count].title[strcspn(mm->data[mm->count].title, "\n")] = 0;
    printf("감독: "); fgets(mm->data[mm->count].director, 50, stdin);
    mm->data[mm->count].director[strcspn(mm->data[mm->count].director, "\n")] = 0;
    mm->data[mm->count].year = getSafeInt("연도: ");
    mm->data[mm->count].rating = getSafeDouble("평점: ");
    mm->count++;
}

// 줄 맞춤을 최적화한 목록 출력 함수
void printMovies(const MovieManager* mm) {
    if (mm->count == 0) { printf(">> 등록된 데이터가 없습니다.\n"); return; }

    // 헤더 출력: 너비를 넉넉하게 지정 (| 기호로 구분)
    printf("\n%-4s | %-25s | %-15s | %-6s | %-4s\n", "ID", "제목", "감독", "연도", "평점");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < mm->count; i++) {
        // %-25.25s: 25칸 왼쪽 정렬하되, 넘치면 자름
        printf("[%02d] | %-25.25s | %-15.15s | %-6d | %-4.1f\n",
            i + 1,
            mm->data[i].title,
            mm->data[i].director,
            mm->data[i].year,
            mm->data[i].rating);
    }
    printf("--------------------------------------------------------------------------\n");
}

void updateMovie(MovieManager* mm) {
    if (mm->count == 0) return;
    printMovies(mm);
    int id = getSafeInt("수정할 ID 번호: ");
    if (id < 1 || id > mm->count) return;
    int idx = id - 1;
    char input[100];
    printf("새 제목 (엔터 시 유지): "); fgets(input, 100, stdin);
    if (input[0] != '\n') { input[strcspn(input, "\n")] = 0; strcpy(mm->data[idx].title, input); }
    printf("새 평점 (엔터 시 유지): "); fgets(input, 100, stdin);
    if (input[0] != '\n') mm->data[idx].rating = atof(input);
    printf(">> 수정 완료!\n");
}

void deleteMovie(MovieManager* mm) {
    if (mm->count == 0) return;
    printMovies(mm);
    int id = getSafeInt("삭제할 ID 번호: ");
    if (id < 1 || id > mm->count) return;
    for (int i = id - 1; i < mm->count - 1; i++) mm->data[i] = mm->data[i + 1];
    mm->count--;
    printf(">> 삭제 완료.\n");
}

int main() {
    MovieManager mm = { (Movie*)malloc(sizeof(Movie) * 2), 0, 2 };
    loadFromFile(&mm);

    while (1) {
        printf("\n================ 🎬 영화 관리 시스템 ===============\n");
        printf(" 1.추가 | 2.목록 | 3.수정 | 4.삭제 | 5.정렬 | 6.종료\n");
        printf("====================================================\n");

        int choice = getSafeInt("선택 > ");

        if (choice == 1) addMovie(&mm);
        else if (choice == 2) printMovies(&mm);
        else if (choice == 3) updateMovie(&mm);
        else if (choice == 4) deleteMovie(&mm);
        else if (choice == 5) {
            if (mm.count < 1) { printf(">> 정렬할 데이터가 없습니다.\n"); continue; }
            printf("[1.제목순 2.연도순 3.평점순] 선택: ");
            int s = getSafeInt("");
            if (s == 1) qsort(mm.data, mm.count, sizeof(Movie), compareTitle);
            else if (s == 2) qsort(mm.data, mm.count, sizeof(Movie), compareYear);
            else if (s == 3) qsort(mm.data, mm.count, sizeof(Movie), compareRating);
            printf(">> 정렬 완료!\n");
        }
        else if (choice == 6) { saveToFile(&mm); break; }
        else printf(">> 잘못된 메뉴입니다.\n");
    }
    free(mm.data);
    return 0;
}