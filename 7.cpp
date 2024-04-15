#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_EXPR_LEN 100
#define MAX_STACK_SIZE 50
#define MAX_CODE_SIZE 50

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
} Triple;

typedef struct {
    char op;
    int tripleIndex;
} IndirectTriple;

void generateCode(char expr[]);
void printQuadruples(Quadruple quadruples[], int count);
void printTriples(Triple triples[], int count);
void printIndirectTriples(IndirectTriple indirectTriples[], int count);

int main() {
    char expression[MAX_EXPR_LEN];
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    generateCode(expression);
    return 0;
}

void generateCode(char expr[]) {
    Quadruple quadruples[MAX_CODE_SIZE];
    Triple triples[MAX_CODE_SIZE];
    IndirectTriple indirectTriples[MAX_CODE_SIZE];

    char opStack[MAX_STACK_SIZE];
    char argStack[MAX_STACK_SIZE][10];

    int opTop = -1;
    int argTop = -1;

    int tripleCount = 0;
    int indirectTripleCount = 0;
    int quadrupleCount = 0;

    char *token = strtok(expr, " \t\n");
    while(token != NULL) {
        if(strcmp(token, "(") == 0) {
            opStack[++opTop] = *token;
        } else if(strcmp(token, ")") == 0) {
            while(opTop != -1 && opStack[opTop] != '(') {
                triples[tripleCount].op = opStack[opTop--];
                strcpy(triples[tripleCount].arg1, argStack[argTop--]);
                strcpy(triples[tripleCount].arg2, argStack[argTop--]);
                indirectTriples[indirectTripleCount].op = triples[tripleCount].op;
                indirectTriples[indirectTripleCount++].tripleIndex = tripleCount;
                tripleCount++;
            }
            if(opTop != -1)
                opTop--;
        } else if(strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            opStack[++opTop] = *token;
        } else {
            strcpy(argStack[++argTop], token);
        }
        token = strtok(NULL, " \t\n");
    }

    while(opTop != -1) {
        triples[tripleCount].op = opStack[opTop--];
        strcpy(triples[tripleCount].arg1, argStack[argTop--]);
        strcpy(triples[tripleCount].arg2, argStack[argTop--]);
        indirectTriples[indirectTripleCount].op = triples[tripleCount].op;
        indirectTriples[indirectTripleCount++].tripleIndex = tripleCount;
        tripleCount++;
    }

    for(int i = 0; i < tripleCount; i++) {
        strcpy(quadruples[quadrupleCount].result, triples[i].arg1);
        strcpy(quadruples[quadrupleCount].arg1, triples[i].arg2);
        strcpy(quadruples[quadrupleCount].arg2, "_");
        quadruples[quadrupleCount++].op = triples[i].op;
    }

    printf("Three Address Code:\n");
    printQuadruples(quadruples, quadrupleCount);
    printf("\nTriples:\n");
    printTriples(triples, tripleCount);
    printf("\nIndirect Triples:\n");
    printIndirectTriples(indirectTriples, indirectTripleCount);
}

void printQuadruples(Quadruple quadruples[], int count) {
    for(int i = 0; i < count; i++) {
        printf("%s = %s %c %s\n", quadruples[i].result, quadruples[i].arg1, quadruples[i].op, quadruples[i].arg2);
    }
}

void printTriples(Triple triples[], int count) {
    for(int i = 0; i < count; i++) {
        printf("(%s, %s, %c)\n", triples[i].arg1, triples[i].arg2, triples[i].op);
    }
}

void printIndirectTriples(IndirectTriple indirectTriples[], int count) {
    for(int i = 0; i < count; i++) {
        printf("(%d, %c)\n", indirectTriples[i].tripleIndex, indirectTriples[i].op);
    }
}

// INPUT : (a + b) * (c - d)
