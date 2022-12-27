#include <stdlib.h>
#include <stdio.h>
#include "func.h"

int main(void) {
    TSym parametrs;
    parametrs.Head = parametrs.Tail = NULL;
    parametrs.CountBracket = 0;
    parametrs.Size = 0;
    TSym func;
    func.Head = func.Tail = NULL;
    int c;
    int lastsymIsOper = 0;
    int num = 0;
    int isNum = 1;
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            isNum = 0;
            num *= 10;
            num += c - '0';
            lastsymIsOper = 0;
        }
        else {
            if (isNum == 0) {
                Push(&parametrs, num);
                parametrs.Size += 1;
                num = 0;
                isNum = 1;
            }
            if (c == '(') {
            ++parametrs.CountBracket;
            Push(&parametrs, '(');
            Push(&func, '(');
            }
            else if (c == '*' || c == '-' || c == '+' || c == '/') {
            if (lastsymIsOper == 1) {
                printf("syntax error");
                return 0;
            }
            lastsymIsOper = 1;
            int chekPr = 0;
            while (chekPr == 0) {
                if (func.Tail == NULL) {
                    break;
                }
                if (CheckPriority(func.Tail->Sym, c) == 1) {
                    if (Math(&parametrs, &func)) {
                        return 0;
                    }
                }
                else {
                    chekPr = 1;
                }

            }
            Push(&func, c);
            }

            else if (c == ')') {
            if (parametrs.CountBracket == 0) {
                printf("syntax error");
                return 0;
            }
            if (parametrs.Tail->Sym == '(') {
                printf("syntax error");
                return 0;
            }
            int deleteBr = 0;
            while (deleteBr != 2) {
                deleteBr = Math(&parametrs, &func);
                if (deleteBr == 1) {
                    return 0;
                }
            }
            }
            else {
                printf("syntax error");
                return 0;
            }
        }
    }
    
    if (isNum == 0) {
        Push(&parametrs, num);
        parametrs.Size += 1;
        num = 0;
    }
    if (parametrs.CountBracket != 0 || lastsymIsOper == 1 || parametrs.Size == 0) {
        printf("syntax error");
        return 0;
    }
    while (parametrs.Size != 1) {
        if (Math(&parametrs, &func)) {
            return 0;
        }
    }
    int lastSym = Delete(&parametrs);
    printf("%d", lastSym);
    return 0;
}

