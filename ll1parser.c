#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll1parser.h"

typedef struct {
    char items[256][16];
    int top;
} Stack;

void push(Stack* stack, const char* item) {
    strcpy(stack->items[++stack->top], item);
}

void pop(Stack* stack) {
    if (stack->top >= 0) stack->top--;
}

char* top(Stack* stack) {
    return stack->items[stack->top];
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

const char* lookupProduction(ParseTable* table, const char* nonTerminal, const char* terminal) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->entries[i].nonTerminal, nonTerminal) == 0 && strcmp(table->entries[i].terminal, terminal) == 0) {
            return table->entries[i].production;
        }
    }
    return NULL;
}

int parse(ParseTable* table, const char* input) {
    Stack stack;
    stack.top = -1;

    push(&stack, "$");
    push(&stack, "E");

    char inputCopy[256];
    strcpy(inputCopy, input);
    strcat(inputCopy, "$");
    int inputIndex = 0;

    while (!isEmpty(&stack)) {
        char* stackTop = top(&stack);
        char currentInput[2] = { inputCopy[inputIndex], '\0' };

        if (strcmp(stackTop, currentInput) == 0) {
            pop(&stack);
            inputIndex++;
        } else if (lookupProduction(table, stackTop, currentInput)) {
            pop(&stack);
            const char* production = lookupProduction(table, stackTop, currentInput);

            if (strcmp(production, "@") != 0) {
                for (int i = strlen(production) - 1; i >= 0; i--) {
                    char symbol[2] = { production[i], '\0' };
                    push(&stack, symbol);
                }
            }
        } else {
            printf("Erro de sintaxe: esperado '%s', mas encontrado '%s'\n", stackTop, currentInput);
            return 0;
        }
    }

    return 1;
}
