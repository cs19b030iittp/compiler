#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utils/ast.h"
#include "Utils/symbol_table.h"
#include "y.tab.h"

extern FILE *yyin;
extern AST *astroot;
extern SymbolTable* current_symbol_table;
extern SymbolTable* persistent_symbol_table;
extern int current_scope;
extern int unused_scope;
FILE *fp;

void assign_type (AST *astroot);
void traverse(AST *astroot);
void typecheck(AST *astroot);
void binary_op_type_checking(AST *astroot);
void add_params(AST* astroot);
void check_params(AST* astroot);
bool compatible_types(int type1,int type2);
void generate_code(AST* astroot);
int get_size(int type);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("\nUsage: <exefile> <inputfile>\n");
        exit(0);
    }
    yyin = fopen(argv[1], "r");
    yyparse();
    current_symbol_table = NULL;
    persistent_symbol_table = NULL;
    // current_symbol_table = (SymbolTable *)malloc(sizeof(SymbolTable));
    // current_symbol_table->prev = NULL;
    // current_symbol_table->next = NULL;
    // current_symbol_table->symbol_head = NULL;
    // current_symbol_table->scope = current_scope;
    current_scope = -1;
    unused_scope = 0;
    traverse(astroot);
    fp = fopen("assembly.asm","w+");
    fprintf(fp,"    .data\n");
    fprintf(fp,"    .text\n");
    fprintf(fp,"    .globl main\n");
    fprintf(fp,"begin:\n");
    // generate_code(astroot);
}

void generate_code(AST* astroot){
    
    if (astroot == NULL)
        return;

    for (int i = 0; i < 4; i++)
        traverse(astroot->child[i]);

    switch (astroot->type)
    {
        case ast_var_list:
        {
            break;
        }
        case ast_stmts:
        {
            break;
        }
        case ast_push_scope:
        {
            break;
        }
        case ast_pop_scope:
        {
            break;
        }
        case ast_start_stmt:
        {
            break;
        }
        case ast_func_stmt:
        {
            break;
        }
        case ast_func_list_stmt:
        {
            break;
        }
        case ast_param_list_stmt:
        {
            break;
        }
        case ast_param_stmt:
        {
            break;
        }
        case ast_arg_list_stmt:
        {
            break;
        }
        case ast_func_call_stmt:
        {
            break;
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
        case ast_array_stmt:
        {
            break;
        }
        case ast_variable_stmt:
        {
            break;
        }
        case ast_var_expr:
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
        case ast_const_val:
        {
            
            break;
        }
        case ast_print_stmt:
        {
            break;
        }
        case ast_input_stmt:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

void traverse(AST *astroot)
{
    if (astroot == NULL)
        return;

    switch (astroot->type)
    {
        case ast_var_list:
        {
            astroot->scope_no = current_scope;
            for (int i = 0; i < 4; i++) {
                if (astroot->child[i] != NULL) {
                    astroot->child[i]->datatype = astroot->datatype;
                    if (astroot->child[i]->type == ast_variable_stmt) {
                        astroot->child[i]->symbol->type = astroot->datatype;
                    }
                }
            }
            break;
        }
    }

    for (int i = 0; i < 4; i++){
        traverse(astroot->child[i]);
    }

    switch (astroot->type)
    {
        case ast_stmts:
        {
            break;
        }
        case ast_push_scope:
        {
            current_scope = unused_scope;
            ++unused_scope;
            push_symbol_table();
            push_persistent_symbol_table();
            break;
        }
        case ast_pop_scope:
        {
            printf("Size of scope: %d bytes\n",persistent_symbol_table->size);
            pop_symbol_table();
            if(current_symbol_table != NULL){
                current_scope = current_symbol_table->scope;
            }
            adjust_persistent_symbol_table();
            break;
        }
        case ast_start_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_func_stmt:
        {
            astroot->scope_no = current_scope;
            add_params(astroot);
            break;
        }
        case ast_func_list_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_param_list_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_param_stmt:
        {
            astroot->scope_no = current_scope;
            astroot->symbol->size = get_size(astroot->symbol->type);
            push_symbol(astroot->symbol);
            break;
        }
        case ast_arg_list_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_func_call_stmt:
        {
            astroot->scope_no = current_scope;
            check_params(astroot);
            break;
        }
        case ast_stmt_list:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_assgn_stmt:
        {
            astroot->scope_no = current_scope;
            astroot->val = astroot->child[1]->val;
            astroot->datatype = astroot->child[0]->datatype;
            typecheck(astroot);
            break;
        }
        case ast_cond_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_loop_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_decl_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_array_decl_stmt:
        {
            astroot->scope_no = current_scope;
            astroot->symbol->size = get_size(astroot->symbol->type) * astroot->symbol->size;
            push_symbol(astroot->symbol);
            printf("Array size: %d\n",astroot->symbol->size);
            break;
        }
        case ast_expressions_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_arry_assgn_stmt:
        {
            astroot->scope_no = current_scope;
            Symbol *symbol = search_symbol(astroot->symbol->name);
            if(symbol == NULL){
                printf("Identifier undeclared\n");
            }
            if(symbol->is_array != 1){
                printf("Identifier not an array type.\n");
                exit(0);
            }
            if(astroot->child[1]->datatype != INT_TYPE){
                printf("array subscript not an integer\n");
                exit(0);
            }
            astroot->datatype = symbol->type;
            break;
        }
        case ast_array_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_variable_stmt:
        {
            astroot->scope_no = current_scope;
            astroot->symbol->type = astroot->datatype;
            Symbol* symbol = search_symbol(astroot->symbol->name);
            if(symbol != NULL){
                printf("Identified %s already declared in current scope\n",symbol->name);
                exit(0);
            }
            astroot->symbol->size = get_size(astroot->symbol->type);
            push_symbol(astroot->symbol);
            break;
        }
        case ast_var_list:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_var_expr:
        {
            astroot->scope_no = current_scope;
            Symbol *symbol = search_symbol(astroot->symbol->name);
            if (symbol == NULL)
            {
                printf("\nError: Variable %s not declared\n", astroot->symbol->name);
                exit(0);
            }
            astroot->symbol = symbol;
            astroot->datatype = symbol->type;
            break;
        }
        case ast_or_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_and_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_eq_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_neq_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_lt_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_gt_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_geq_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_leq_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_add_stmt:
        {
            astroot->scope_no = current_scope;
            binary_op_type_checking(astroot);
            break;
        }
        case ast_sub_stmt:
        {
            astroot->scope_no = current_scope;
            binary_op_type_checking(astroot);
            break;
        }
        case ast_mul_stmt:
        {
            astroot->scope_no = current_scope;
            binary_op_type_checking(astroot);
            break;
        }
        case ast_div_stmt:
        {
            astroot->scope_no = current_scope;
            binary_op_type_checking(astroot);
            break;
        }
        case ast_unary_not:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_unary_add:
        {
            astroot->scope_no = current_scope;
            astroot->datatype = astroot->child[0]->datatype;
            break;
        }
        case ast_unary_sub:
        {
            astroot->scope_no = current_scope;
            astroot->datatype = astroot->child[0]->datatype;
            break;
        }
        case ast_const_val:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_print_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        case ast_input_stmt:
        {
            astroot->scope_no = current_scope;
            Symbol *symbol = search_symbol(astroot->symbol->name);
            if(symbol == NULL){
                printf("Identifier undeclared\n");
                exit(0);
            }
            break;
        }
        case ast_return_stmt:
        {
            astroot->scope_no = current_scope;
            break;
        }
        default:
        {
            astroot->scope_no = current_scope;
            break;
        }
    }
}

void typecheck(AST *astroot) {
    if (astroot->child[0]->datatype == INT_TYPE && astroot->child[1]->datatype == DOUBLE_TYPE) {
        astroot->child[1]->val.int_val= (int)astroot->child[1]->val.double_val;
        astroot->datatype = INT_TYPE;
    } else if (astroot->child[0]->datatype == DOUBLE_TYPE && astroot->child[1]->datatype == INT_TYPE) {
        astroot->child[0]->val.double_val= (double)astroot->child[1]->val.int_val;
        astroot->datatype = DOUBLE_TYPE;
    } else if(astroot->child[0]->datatype != astroot->child[1]->datatype) {
        printf("Types: %d    %d\n",astroot->child[0]->datatype,astroot->child[1]->datatype);
        printf("\nError: Type mismatch in assignment statement\n");
        exit(0);
    }
}

void binary_op_type_checking(AST *astroot){
    if(astroot->child[0]->datatype == DOUBLE_TYPE && astroot->child[1]->datatype == DOUBLE_TYPE){
        astroot->datatype = DOUBLE_TYPE;
        astroot->val.double_val = astroot->child[0]->val.double_val + astroot->child[1]->val.double_val;
    } else if(astroot->child[0]->datatype == INT_TYPE && astroot->child[1]->datatype == DOUBLE_TYPE){
        astroot->datatype = DOUBLE_TYPE;
        astroot->val.double_val = astroot->child[0]->val.int_val + astroot->child[1]->val.double_val;
    } else if(astroot->child[0]->datatype == DOUBLE_TYPE && astroot->child[1]->datatype == INT_TYPE){
        astroot->datatype = DOUBLE_TYPE;
        astroot->val.double_val = astroot->child[0]->val.double_val + astroot->child[1]->val.int_val;
    } else if(astroot->child[0]->datatype == INT_TYPE && astroot->child[1]->datatype == INT_TYPE) {
        astroot->datatype = DOUBLE_TYPE;
        astroot->val.int_val = astroot->child[0]->val.int_val + astroot->child[1]->val.int_val;
    } else{
        printf("Invalid operands for +");
        exit(0);
    }
}

void add_params(AST* astroot){
    AST* params = astroot->child[1];
    Symbol* func = astroot->symbol;
    if(search_symbol(func->name) != NULL){
        printf("Function with name %s already exists\n",func->name);
        exit(0);
    }
    Symbol* cur_param = NULL;
    while(params != NULL){
        char* name = params->child[1]->symbol->name;
        int type = params->child[1]->symbol->type;
        if(cur_param == NULL){
            func->param_list = symbol_init(name,type,NULL,NULL);
            cur_param = func->param_list;
        } else{
            cur_param->next = symbol_init(name,type,NULL,NULL);
            cur_param->next->prev = cur_param;
            cur_param = cur_param->next;
        }
        // printf("Parameters: %s\n",params->child[1]->symbol->name);
        params = params->child[0];
    }
    push_symbol(func);// push the function symbol
}

// check if implicit type conversion can take place between 2 given types
bool convertible_types(int type1,int type2){
    if(type1 == type2){
        return true;
    }
    if(type1 == STR_TYPE || type2 == STR_TYPE){
        return false;
    }
    return true;
}

void check_params(AST* astroot){
    AST* args = astroot->child[0];
    Symbol* func = search_symbol(astroot->symbol->name);
    if(func == NULL){
        printf("No function with name %s exists.\n",astroot->symbol->name);
        exit(0);
    }
    Symbol* params = func->param_list;
    while(args != NULL && params != NULL){
        if(!convertible_types(params->type,args->child[1]->datatype)){
            printf("Type mismatch in function %s for parameter %s\n",astroot->symbol->name,params->name);
            exit(0);
        }
        // printf("Checking: %d\n",args->child[1]->datatype);
        // printf("Checking : %s\n",params->name);
        params = params->next;
        args = args->child[0];
    }
    if(params != NULL){
        printf("Type: %s\n",params->name);
        printf("Too few arguments for the function %s\n",astroot->symbol->name);
        exit(0);
    } else if(args != NULL){
        printf("Too many arguments for the function %s\n",astroot->symbol->name);
        exit(0);
    }
    // printf("Return type : %d\n",func->type);
    astroot->datatype = func->type;
}

int get_size(int type){
    if(type == INT_TYPE){
        return 4;
    }
    if(type == DOUBLE_TYPE){
        return 8;
    }
    if(type == STR_TYPE){
        return 300;
    }
    if(type == BOOL_TYPE){
        return 1;
    }
    return 0;
}