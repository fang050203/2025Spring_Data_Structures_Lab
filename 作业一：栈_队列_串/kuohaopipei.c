#include <stdio.h>
#include <stdlib.h>
#define N 100010

int stk[N];
int tt = 0;

int main() {
    char c;
    while (1) {
        scanf("%c", &c);
        if (c == '\n') break;

        if (c == '[' || c == '{' || c == '(') {
            // 栈满检查
            if (tt >= N - 1) {
                printf("False");
                return 0;
            }
            stk[++tt] = c;
        } else {
            // 栈空时遇到右括号，直接失败
            //stk[++tt]=c;
            if (tt == 0) {
                printf("False");
                return 0;
            }
            // 检查括号是否匹配
            if ((stk[tt] == '[' && c == ']') || 
                (stk[tt] == '{' && c == '}') || 
                (stk[tt] == '(' && c == ')')) {
                tt--;
            } else {
                // 不匹配的右括号，立即失败
                printf("False");
                return 0;
            }
        }
    }
    printf(tt == 0 ? "True" : "False");
    return 0;
}
