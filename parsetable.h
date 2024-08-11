#ifndef PARSETABLE_H
#define PARSETABLE_H

typedef struct {
    char nonTerminal[16];
    char terminal[16];
    char production[64];
} ParseTableEntry;

typedef struct {
    ParseTableEntry* entries;
    int count;
} ParseTable;

ParseTable* loadParseTable(const char* csvFilePath);
void freeParseTable(ParseTable* table);

#endif // PARSETABLE_H
