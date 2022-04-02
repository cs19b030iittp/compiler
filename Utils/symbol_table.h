#ifndef SYMBOL_H_NAME
#define SYMBOL_H_NAME

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Stores the information of one variable
typedef struct Symbol {
    char* name;
    int type;
    int size;
    struct Symbol* prev;
    struct Symbol* next;
} Symbol;

extern Symbol* stack;

// Stores symbols for a particular scope
typedef struct SymbolTable {
    Symbol* symbol_head;
    struct SymbolTable* next;
    struct SymbolTable* prev;
} SymbolTable;

extern SymbolTable* symbol_table;  // Symbol table for current scope

Symbol* symbol_init(char* name, int type, Symbol* prev, Symbol* next);

void push_symbol(Symbol* symbol);

Symbol* search_symbol(char* id);

void push_symbol_table();

void pop_symbol_table();

// Stack functions
void push(Symbol* symbol);

Symbol* pop();
#endif