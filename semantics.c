#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utils/ast.h"
#include "Utils/symbol_table.h"
#include "y.tab.h"

extern FILE *yyin;
extern AST *astroot;
extern SymbolTable *symbol_table;

void traverse(AST *astroot);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("\nUsage: <exefile> <inputfile>\n");
        exit(0);
    }
    yyin = fopen(argv[1], "r");
    symbol_table = (SymbolTable *)malloc(sizeof(SymbolTable));
    symbol_table->prev = NULL;
    symbol_table->next = NULL;
    symbol_table->symbol_head = NULL;
    stack = NULL;
    yyparse();
    traverse(astroot);
}

void traverse(AST *astroot)
{
    if (astroot == NULL)
        return;

    switch (astroot->type)
    {
        case ast_stmts:
        {
            for (int i = 0; i < 4; i++)
                if (astroot->child[i] != NULL) {
                    if (astroot->child[i]->type == ast_push_scope) {
                        push_symbol_table();
                    } else if (astroot->child[i]->type == ast_pop_scope) {
                        pop_symbol_table();
                    } else {
                        // Code gen here
                    }
                }
        }
        case ast_stmt_list:
        {
            break;
        }
        case ast_assgn_stmt:
        {
            break;
        }
        case ast_cond_stmt:
        {
            break;
        }
        case ast_loop_stmt:
        {
            break;
        }
        case ast_decl_stmt:
        {
            break;
        }
        case ast_array_decl_stmt:
        {
            break;
        }
        case ast_expressions_stmt:
        {
            break;
        }
        case ast_arry_assgn_stmt:
        {
            break;
        }
        case ast_variable_stmt:
        {
            astroot->symbol->type = astroot->type;
            push_symbol(astroot->symbol);
            break;
        }
        case ast_var_list:
        {
            for (int i = 0; i < 4; i++)
                if (astroot->child[i] != NULL)
                    astroot->child[i]->datatype = astroot->datatype;
            break;
        }
        case ast_var_expr:
        {
            Symbol *symbol= search_symbol(astroot->symbol->name);
            if (symbol == NULL) {
                printf("Error: Undeclared variable %s\n", astroot->symbol->name);
                exit(0);
            }
            break;
        }
        case ast_aeq_stmt:
        {
            break;
        }
        case ast_seq_stmt:
        {
            break;
        }
        case ast_meq_stmt:
        {
            break;
        }
        case ast_deq_stmt:
        {
            break;
        }
        case ast_incr_stmt:
        {
            break;
        }
        case ast_decr_stmt:
        {
            break;
        }
        case ast_or_stmt:
        {
            break;
        }
        case ast_and_stmt:
        {
            break;
        }
        case ast_eq_stmt:
        {
            break;
        }
        case ast_neq_stmt:
        {
            break;
        }
        case ast_lt_stmt:
        {
            break;
        }
        case ast_gt_stmt:
        {
            break;
        }
        case ast_geq_stmt:
        {
            break;
        }
        case ast_leq_stmt:
        {
            break;
        }
        case ast_add_stmt:
        {
            break;
        }
        case ast_sub_stmt:
        {
            break;
        }
        case ast_mul_stmt:
        {
            break;
        }
        case ast_div_stmt:
        {
            break;
        }
        case ast_unary_not:
        {
            break;
        }
        case ast_unary_add:
        {
            break;
        }
        case ast_unary_sub:
        {
            break;
        }
    }
    for (int i = 0; i < 4; i++)
        traverse(astroot->child[i]);
}
