#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsetable.h"

ParseTable* loadParseTable(const char* csvFilePath) {
    FILE* file = fopen(csvFilePath, "r");
    if (!file) return NULL;

    ParseTable* table = (ParseTable*)malloc(sizeof(ParseTable));
    table->entries = NULL;
    table->count = 0;

    char line[256];
    char headers[16][16];
    int headerCount = 0;

    // Ler os headers
    if (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ",\n");
        while (token != NULL) {
            strcpy(headers[headerCount++], token);
            token = strtok(NULL, ",\n");
        }
    }

    // Ler as linhas da tabela
    while (fgets(line, sizeof(line), file) != NULL) {
        char nonTerminal[16];
        char* token = strtok(line, ",\n");
        strcpy(nonTerminal, token);

        for (int i = 1; i < headerCount; i++) {
            token = strtok(NULL, ",\n");
            if (token && strlen(token) > 0) {
                table->entries = (ParseTableEntry*)realloc(table->entries, (table->count + 1) * sizeof(ParseTableEntry));
                strcpy(table->entries[table->count].nonTerminal, nonTerminal);
                strcpy(table->entries[table->count].terminal, headers[i]);
                strcpy(table->entries[table->count].production, token);
                table->count++;
            }
        }
    }

    fclose(file);
    return table;
}

void freeParseTable(ParseTable* table) {
    if (table) {
        free(table->entries);
        free(table);
    }
}
