#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsetable.h"
#include "ll1parser.h"

int main() {
    
    const char* parseTableFilePath = "./parse_table.csv";
    ParseTable* parseTable = loadParseTable(parseTableFilePath);

    if (!parseTable) {
        fprintf(stderr, "Erro ao carregar a tabela de análise.\n");
        return 1;
    }

    const char* inputFilePath = "./input.txt";
    FILE* inputFile = fopen(inputFilePath, "r");
    if (!inputFile) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        freeParseTable(parseTable);
        return 1;
    }

    char input[256];
    if (fgets(input, sizeof(input), inputFile) != NULL) {
        if (parse(parseTable, input)) {
            printf("Entrada aceita com sucesso!\n");
        } else {
            printf("Erro ao processar a entrada.\n");
        }
    }

    fclose(inputFile);
    freeParseTable(parseTable);

    return 0;
}
