#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// 연산자 enum 모음
typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

// 템플릿 스택
Stack<int> st;
Stack<precedence> cst;

// 연산자 새로넣을 때 우선순위
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
// 스택 안에 있을 때 우선순위
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};
// new_expr index
int idx = 0;


// token을 print하기 위해 char 값을 가져오는 함수
char printToken(precedence token) {
    switch (token) {
        case lparen:
            return '(';
        case rparen:
            return ')';
        case plus:
            return '+';
        case minus:
            return '-';
        case divide:
            return '/';
        case times:
            return '*';
        case mod:
            // % 의 경우 %% 로해야해서 아스키 코드값 반환
            return 37;
        case eos:
            return '\0';
    }

}

// 토큰 가여오기
precedence getToken(char *expr, char *symbol, int *n) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
        case '(' :
            return lparen;
        case ')' :
            return rparen;
        case '+' :
            return plus;
        case '-' :
            return minus;
        case '/' :
            return divide;
        case '*' :
            return times;
        // 위에 printToken과 같은 이유로 아스키 코드 37로 인식
        case 37 :
            return mod;
        case '\0' :
            return eos;
        default:
            return operand;
    }
}

// infix -> postfix 에서 output 출력
void showNewExpr(char *expr) {
    for (int i = 0; i < idx; i++) {
        printf("%c", expr[i]);
    }
    printf("\n");
}

// infix -> postfix 에서 스택에 있는 값 출력
void showCst() {
    int i;
    for (i = 0; i <= cst.get_top(); i++) {
        printf("%3c",printToken(cst.get(i)));
    }
    // printf 포매팅 기법
    printf("%*d", 30-3*i, cst.get_top()-1);
    printf("     ");
}


void postfix(char *expr, char *new_expr) {
    char symbol;
    precedence token;
    int n = 0;
    cst.push(eos);  // 스택 처음에 끝나는 종료 token 삽입
    for (token = getToken(expr, &symbol, &n); token != eos; token = getToken(expr, &symbol, &n)) {
        if (token == operand) { // token이 연산자가 아니고 숫자면 그냥 바로 new_expr에 삽입
            new_expr[idx++] = symbol;
            printf("%2d    ", symbol - '0');    // token 출력
            showCst();  // stack 출력
            showNewExpr(new_expr);  // new_expr cnffur
        } else if (token == rparen) {   // 오른쪽 괄호
            while (cst.get(cst.get_top()) != lparen) {  // 왼쪽 괄호 나올 때까지 pop 해서 expr에 삽입
                new_expr[idx++] = printToken(cst.pop());
            }
            cst.pop();
        } else {    // 이외 연산자
            while (isp[cst.get(cst.get_top())] >= icp[token]) {
                new_expr[idx++] = printToken(cst.pop());
            }
            cst.push(token);
            printf("%2c    ",printToken(token));
            showCst();
            showNewExpr(new_expr);
        }
    }
    // 마지막에 숫자인경우 하나 남아서 pop해줌
    new_expr[idx++] = printToken(cst.pop());
    showCst();
    showNewExpr(new_expr);
}

// 정수형 stack 출력
void showStack() {
    int i;
    for(i = 0; i <= st.get_top(); i++) {
        printf("%3d", st.get(i));
    }
    printf("%*d\n",35-3*i, st.get_top()-1);
}

// postfix 연산
int eval(char *expr) {
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    token = getToken(expr, &symbol, &n);
    while (token != eos) {  // eos 만날 때 까지 token 가져오기
        if (token == operand) { // token 이 숫자면 stack에 push, 출력해준다.
            st.push(symbol - '0');
            printf("%3c      ", symbol);
        } else {
            op2 = st.pop();
            op1 = st.pop();
            switch (token) {
                case plus:
                    st.push(op1 + op2);
                    break;
                case minus:
                    st.push(op1 - op2);
                    break;
                case times:
                    st.push(op1 * op2);
                    break;
                case divide:
                    st.push(op1 / op2);
                    break;
                case mod:
                    st.push(op1 % op2);
                    break;
            }
            printf("%3c",printToken(token));
            printf("      ");
        }
        showStack();
        token = getToken(expr, &symbol, &n);
    }

    return st.pop();
}


int main() {
    char *expr = (char *) malloc(sizeof(char) * 100);
    char *new_expr = (char *) calloc('\0', sizeof(char) * 100);

    scanf("%s", expr);
    printf(" Token | Stack                 |  Top | Output\n");
    postfix(expr, new_expr);
    printf("Postfix :");
    showNewExpr(new_expr);
    printf("\n");
    printf("Eval of Postfix :\n");
    printf("  Token | Stack                         |  Top\n");
    int ans = eval(new_expr);
    printf("Eval : %d", ans);

    free(new_expr);
    free(expr);
    return 0;
}

