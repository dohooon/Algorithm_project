// 구현 해야될 부분은 -- 구현 으로 표시해둠

#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define NUMBER 20

typedef struct m_i_s
{
    int member;
    int item;
    int satisfaction_score;
}m_i_s;

m_i_s table[100];                    //원래 테이블
m_i_s random_matched_table[100];     //랜덤함수로 매칭된 테이블
m_i_s result_table[100];             //결과로 저장할 테이블

int member_mark[NUMBER] = {0};
int item_mark[NUMBER] = {0};          //마크되면 1, 아니면 0

/*     정렬 함수 구현 참고용
void swap(Node *a, Node * b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void sort() {
    for(int j = 1; j < SIZE - 1; j++) {
        for(int k = 1; k < SIZE - j; k++) {
            if(node[k].post < node[k + 1].post) {
                swap(&node[k], &node[k + 1]);
            }
        }
    }
}
*/

/*     구조체 복사 함수 구현 참고용
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME 20

struct person {
    char *name;
    int age;
};

int main()
{
    struct person a;
    struct person b;

    // 구조체 a 초기화
    a.name = (char *)malloc(sizeof(NAME) + 1);
    strcpy(a.name, "john");
    a.age = 20;

    // 구조체 a의 구조체 b로 깊은 복사
    b.name = (char *)malloc(sizeof(NAME) + 1);
    strcpy(b.name, a.name);
    b.age = a.age;

    // 복사된 내용 출력
    printf("%s, %d\n", a.name, a.age); // john, 20
    printf("%s, %d\n", b.name, b.age); // john, 20

    // 구조체 a 값 변경
    strcpy(a.name, "marry");
    a.age = 30;

    // 구조체 a 값 변경 후 구조체 b 의 값에는 영향을 미치지 않음을 알 수 있음
    printf("%s, %d\n", a.name, a.age); // marry, 30
    printf("%s, %d\n", b.name, b.age); // john, 20
}
*/

int Random_Selection();

int main() {
    
    /* 파일 읽어와서 구조체 table에 담기 */
    int i = 0;
    int idx = 0;

    FILE *fp;   
    fp = fopen("C:\\c-coding\\satisfaction.txt", "r");

    char buffer[1001], *token;

    while(!feof(fp)) {
        i = 0;
        fgets(buffer, 1001, fp);
        token = strtok(buffer, " ");
        while(token != NULL) {
            if (i == 0) {
                table[idx].member = atoi(token);
            }
            else if (i == 1) {
                table[idx].item = atoi(token);
            }
            else if (i == 2) {
                table[idx].satisfaction_score = atoi(token);
            }
            i++;
            token = strtok(NULL, " ");
        }
        idx++;
    }
    
    /*          잘 입력됐는지 확인용
    for (i = 0; i < idx; i++) {
        printf("%d %d %d\n", table[i].member, table[i].item, table[i].satisfaction_score);
    }
    */

    fclose(fp);

//메인 알고리즘//

    int max_score = 0, epoch = 0;
    int n = 1000, s = 2000;
    int temp = 0, result = 0;

    while(epoch < n && max_score < s) {   //n번 돌렸거나 정답(s)이 구해졌으면 끝
        
        temp = Random_Selection();
        epoch += 1;

        if (result > max_score) {
            result = temp;                   //기존 max_score보다 새로운 값이 크면 새로운 값으로 업데이트
            //random_matched_table을 result_table에 복사 -- 구현
        }
        temp = 0;
    }

    printf("max_score = %d\n\n", result);     //구한 max_score 출력

    for (i = 0; i < idx; i++) {               //max_score일때의 매칭결과 출력
        printf("%d %d %d\n", result_table[i].member, result_table[i].item, result_table[i].satisfaction_score);
    }

    return 0;

}

int Random_Selection() {
    int m = 0, k = 0, random_number = 0, max_score = 0;
    int b = 0;
    srand(time(NULL));

    for (int i = 0; i < NUMBER; i++) {            //마크 다 됐으면 반복 끝내는 부분
        
        for (int j = 0; j < NUMBER; j++) {
            if (member_mark[j] == 0) {
                break;
            }
            else if (j == NUMBER - 1) {
                b == 1;
                break;
            }
        }

        if (b == 1) {
            break;
        }
        
        random_number = rand() % NUMBER;
        
        if (member_mark[random_number] == 0) {
            m = random_number;
            //k = m이 가장 선호하는 아이템 넘버 (sort 사용) -- 구현
            member_mark[m] = 1;
            item_mark[k] = 1;
            //matched_table[random_number]에 m, k, s 저장 -- 구현
        }
    }

    //max_score = matched_table[0~19].s 합
    //mark 초기화
    
    return max_score;
}