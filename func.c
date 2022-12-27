#include <stdlib.h>
#include <stdio.h>
#include "func.h"

void Push(TSym* list, int sym) {
    //printf("%d \n", sym);
    if (list->Head) {
        list->Tail->Next = (struct TSymNode*)malloc(sizeof(struct TSymNode));
        TSymNode* cur = list->Tail->Next;
        cur->Last = list->Tail;
        cur->Next = NULL;
        cur->Sym = sym;
        list->Tail = cur;
    }
    else {
        list->Tail = list->Head = (struct TSymNode*)malloc(sizeof(struct TSymNode));
        list->Head->Next = NULL;
        list->Head->Last = NULL;
        list->Head->Sym = sym;
    }
    //printf("END\n");

}

int Delete(TSym* list) {
    int symbol = list->Tail->Sym;
    if (list->Tail->Last) {
        TSymNode* cur = list->Tail->Last;
        cur->Next = NULL;
        list->Tail = cur;
    }
    else {
        list->Head = list->Tail = NULL;
    }
    return symbol;
}

int Math(TSym* parametrs, TSym* func) {
    int operand = Delete(func);
    if (operand == '(') {
        parametrs->CountBracket -= 1;
        return 2;
    }
    int num1 = Delete(parametrs);
    int num2 = Delete(parametrs);

    while (num1 == '(') {
        num1 = Delete(parametrs);
    }
    while (num2 == '(') {
        num2 = Delete(parametrs);
    }
    //printf("%d %d %c\n", num1, num2, operand);
    if (operand == '*') {
        Push(parametrs, num1 * num2);
    }
    else if (operand == '+') {
        Push(parametrs, num1 + num2);
    }
    else if (operand == '-') {
        Push(parametrs, num2 - num1);
    }
    else if (operand == '/') {
        if (num1 == 0) {
            printf("division by zero");
            return 1;
        }
        Push(parametrs, num2/num1);
    }
    parametrs->Size -= 1;
    return 0;
}

int CheckPriority(int lastSym, int newSym) {
    if ((lastSym == '/' || lastSym == '*') && newSym != '(') {
        return 1;
    }
    else if ((lastSym == '-' || lastSym == '+') && (newSym == '+' || newSym == '-')) {
        return 1;
    }
    return 0;
}

