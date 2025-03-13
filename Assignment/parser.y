%{
    #define YYSTYPE char*
    #include "sym_tab.c"
    #include "parser.tab.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    int temp;
    int scope=0;
    int func=0; // function 0 represents main
    int type=-1;
    char* vval="~";
    int vtype = -1;  
    int condition_result = 0;  
    double expr1_val = 0.0;    
    double expr2_val = 0.0;
    int skip_execution = 0;
    int indent_level = 0;
    int error_count = 0;
    void yyerror(char* s);
    int yylex();
    int yydebug=1;
    extern int yylineno;
    symbol *global_p = NULL; 
    FILE *fp;
    
    // Print node in AST with proper indentation
    void print_ast(const char* node_type, const char* value) {
        for (int i = 0; i < indent_level; i++) {
            fprintf(fp, "  ");
        }
        fprintf(fp, "└─ %s", node_type);
        if (value != NULL) {
            fprintf(fp, ": %s", value);
        }
        fprintf(fp, "\n");
    }

    // Increase tree depth
    void increase_indent() {
        indent_level++;
    }

    // Decrease tree depth
    void decrease_indent() {
        if (indent_level > 0) {
            indent_level--;
        }
    }
%}


%token T_INT T_CHAR T_DOUBLE T_WHILE T_INC T_DEC T_OROR T_ANDAND T_EQCOMP T_NOTEQUAL T_GREATEREQ T_LESSEREQ T_LEFTSHIFT T_RIGHTSHIFT T_PRINTLN T_STRING T_FLOAT T_BOOLEAN T_IF T_ELSE T_STRLITERAL T_DO T_INCLUDE T_HEADER T_MAIN T_ID T_NUM T_FOR

%start START

%%
START : PROG { 
          print_ast("PROGRAM", NULL); 
          printf("Valid syntax\n"); 
          YYACCEPT; 
      }    
      ; 
      

FUNC_DEF: MAIN {
           print_ast("FUNCTION_DEFINITION", "main");
           fprintf(fp,"\n");
           increase_indent();
           decrease_indent();
         }
        | FUNC {
           print_ast("FUNCTION_DEFINITION", "user_defined");
           fprintf(fp,"\n");
           increase_indent();
           decrease_indent();
         }
        ;

PROG : FUNC_DEF PROG {
         print_ast("PROGRAM_ELEMENT", "function");
         increase_indent();
         decrease_indent();
       }
     | DECLR ';' PROG {
         print_ast("PROGRAM_ELEMENT", "declaration");
         increase_indent();
         decrease_indent();
       }                 
     | ASSGN ';' PROG {
         print_ast("PROGRAM_ELEMENT", "assignment");
         increase_indent();
         decrease_indent();
       }     
     | error ';' PROG {
         print_ast("ERROR", "invalid_statement");
         error_count++;
       }
     |                     
     ;

DECLR : TYPE LISTVAR {
          print_ast("DECLARATION", NULL);
          increase_indent();
          decrease_indent();
        }
      ;    

LISTVAR : LISTVAR ',' VAR {
            print_ast("VARIABLE_LIST", "multiple_vars");
            increase_indent();
            decrease_indent();
          }
        | VAR {
            print_ast("VARIABLE_LIST", "single_var");
            increase_indent();
            decrease_indent();
          }
        ;

VAR : T_ID '=' EXPR {
        print_ast("VARIABLE_INIT", $1);
        increase_indent();
        decrease_indent();
        if(!skip_execution) {
            if(check_symbol_table($1,scope,func))  
                yyerror($1);
            else {
                insert_into_table($1,type,yylineno,scope,func);
                insert_value_to_name($1,vval,scope,func);
                type=-1;
                vval="~";
            }
        }
    }
    | T_ID {
        print_ast("VARIABLE_DECL", $1);
        increase_indent();
        decrease_indent();
        if(!skip_execution) {
            if(check_symbol_table($1,scope,func))
                yyerror($1);
            insert_into_table($1,type,yylineno,scope,func);
        }
    }
    | T_ID ARRAY_DECL {
        print_ast("ARRAY_DECL", $1);
        increase_indent();
        decrease_indent();
        if(!skip_execution) {
            if(check_symbol_table($1,scope,func))  
                yyerror($1);
            else {
                insert_into_table($1, type, yylineno, scope,func);
                symbol *s = get_symbol($1, scope,func);
                if (strcmp(vval, "~") != 0) {
                    insert_value_to_name($1, vval, scope,func);
                }
                type = -1;
                vval = "~";
            }
        }
    }
    ;

ARRAY_DECL : ARRAY_DIM ARRAY_INIT {
               print_ast("ARRAY_DECLARATION", "with_init");
               increase_indent();
               decrease_indent();
             }
           | ARRAY_DIM {
               print_ast("ARRAY_DECLARATION", "dimensions_only");
               increase_indent();
               decrease_indent();
             }
           | ARRAY_INIT {
               print_ast("ARRAY_DECLARATION", "init_only");
               increase_indent();
               decrease_indent();
             }
           ;

ARRAY_DIM : '[' T_NUM ']' ARRAY_DIM {
              print_ast("ARRAY_DIMENSION", $2);
              increase_indent();
              decrease_indent();
            }
          | '[' T_NUM ']' { 
              print_ast("ARRAY_DIMENSION", $2);
              increase_indent();
              decrease_indent();
              char str[32];
              sprintf(str, "%d", atoi($2));
              $$ = strdup(str);
            }
          ;

ARRAY_INIT : '=' '{' ARRAY_LIST '}' {
               print_ast("ARRAY_INITIALIZER", NULL);
               increase_indent();
               decrease_indent();
             }
           ;

ARRAY_LIST : ARRAY_LIST ',' EXPR {
               print_ast("ARRAY_ELEMENT", NULL);
               increase_indent();
               decrease_indent();
             }
           | EXPR {
               print_ast("ARRAY_ELEMENT", NULL);
               increase_indent();
               decrease_indent();
             }
           ;

TYPE : T_INT {
         type=INT;
         print_ast("TYPE", "int");
         increase_indent();
         decrease_indent();
       }
     | T_FLOAT {
         type=FLOAT;
         print_ast("TYPE", "float");
         increase_indent();
         decrease_indent();
       }
     | T_DOUBLE {
         type=DOUBLE;
         print_ast("TYPE", "double");
         increase_indent();
         decrease_indent();
       }
     | T_CHAR {
         type=CHAR;
         print_ast("TYPE", "char");
         increase_indent();
         decrease_indent();
       }
     ;

ASSGN : T_ID { 
            print_ast("ASSIGNMENT", $1);
            increase_indent();
            if(!skip_execution) {  
                global_p = get_symbol($1, scope,func);
                type = global_p == NULL ? -1 : global_p->type;
            }
        } '=' EXPR {
            if(!skip_execution) {  
                if(global_p == NULL) 
                    yyerror($1);
                else if(vtype != type && !(vtype == DOUBLE && type == FLOAT) && !(vtype == FLOAT && type == DOUBLE)) {
                    fprintf(stderr, "Type mismatch: Cannot assign type %d to type %d\n", vtype, type);
                    yyerror($1);
                }
                else {
                    insert_value_to_symbol(global_p, vval);
                }
                vval = "~";
                type = -1;
                global_p = NULL;
            }
            decrease_indent();
        }
    | T_ID '[' EXPR ']' '=' EXPR {
            print_ast("ARRAY_ASSIGNMENT", $1);
            increase_indent();
            if(!skip_execution) {
                symbol *s = get_symbol($1, scope,func);
                if(s == NULL) {
                    fprintf(stderr, "%s is not declared\n", $1);
                    yyerror($1);
                }
                else {
                    // Handle array assignment
                    char index_str[32];
                    sprintf(index_str, "[%s]", $3);
                    char *new_val = malloc(strlen(s->val) + strlen(index_str) + strlen($6) + 1);
                    sprintf(new_val, "%s%s=%s", s->val, index_str, $6);
                    insert_value_to_symbol(s, new_val);
                    free(new_val);
                }
            }
            decrease_indent();
        }
    ;

EXPR : EXPR REL_OP E {
        print_ast("RELATIONAL_EXPRESSION", $2);
        increase_indent();
        expr2_val = atof($3);
        switch($2[0]) {
            case '<':
                if (strlen($2) == 2)
                    condition_result = (expr1_val <= expr2_val);
                else
                    condition_result = (expr1_val < expr2_val);
                break;
            case '>':
                if (strlen($2) == 2)
                    condition_result = (expr1_val >= expr2_val);
                else
                    condition_result = (expr1_val > expr2_val);
                break;
            case '=':
                condition_result = (expr1_val == expr2_val);
                break;
            case '!':
                condition_result = (expr1_val != expr2_val);
                break;
        }
        decrease_indent();
    }
    | E {
        print_ast("EXPRESSION", $1);
        increase_indent();
        decrease_indent();
        vval = $1;
        expr1_val = atof($1);
    }
    ;
       
E : E '+' T { 
         print_ast("ADD_EXPRESSION", "+");
         increase_indent();
         if ( vtype == INT ) {
                sprintf( $$, "%d", ( atoi( $1 ) + atoi( $3 ) ) );
            } else if ( vtype == FLOAT || vtype == DOUBLE ) {
                sprintf( $$, "%lf", ( atof( $1 ) + atof( $3 ) ) );
            } else {
                fprintf( stderr, "Operation %s not supported for type %d",
                         $2, vtype );
                yyerror( $$ );
                $$ = "~";
            }
         decrease_indent();
        }  
  | E '-' T {  
            print_ast("SUB_EXPRESSION", "-");
            increase_indent();
            if ( vtype == INT ) {
                sprintf( $$, "%d", ( atoi( $1 ) - atoi( $3 ) ) );
            } else if ( vtype == FLOAT || vtype == DOUBLE ) {
                sprintf( $$, "%lf", ( atof( $1 ) - atof( $3 ) ) );
            } else {
                fprintf( stderr, "Operation %s not supported for type %d",
                         $2, vtype );
                yyerror( $$ );
                $$ = "~";
            }
            decrease_indent();
        }
  | T {$$=$1;}  
  ;
    
T : T '*' F { 
                 print_ast("MUL_EXPRESSION", "*");
                 increase_indent();
                 if ( vtype == INT ) {
                    sprintf( $$, "%d", ( atoi( $1 ) * atoi( $3 ) ) );
                } else if ( vtype == FLOAT || vtype == DOUBLE ) {
                    sprintf( $$, "%lf", ( atof( $1 ) * atof( $3 ) ) );
                } else {
                    fprintf( stderr, "Operation %s not supported for type %d",
                             $2, vtype );
                    yyerror( $$ );
                    $$ = "~";
                }
                 decrease_indent();
            }  
  | T '/' F {  
                print_ast("DIV_EXPRESSION", "/");
                increase_indent();
                if ( vtype == INT ) {
                    sprintf( $$, "%d", ( atoi( $1 ) / atoi( $3 ) ) );
                } else if ( vtype == FLOAT || vtype == DOUBLE ) {
                    sprintf( $$, "%lf", ( atof( $1 ) / atof( $3 ) ) );
                } else {
                    fprintf( stderr, "Operation %s not supported for type %d",
                             $2, vtype );
                    yyerror( $$ );
                    $$ = "~";
                }
                decrease_indent();
            }  
  | F {$$=$1;}  
  ;

F : '(' EXPR ')' {
      print_ast("PARENTHESIZED_EXPR", NULL);
      increase_indent();
      $$ = $2;
      decrease_indent();
    }
  | T_ID {
            print_ast("IDENTIFIER", $1);
            increase_indent();
            symbol *s=get_symbol($1,scope,func);
            if(s==NULL) {
                fprintf(stderr,"%s is not declared\n",$1);
                yyerror($1);
            }
            if(!strcmp(s->val,"~")) {
                fprintf(stderr,"%s is not initialized\n",$1);
                yyerror($1);
            }
            $$=strdup(s->val);
            vtype=s->type;
            if(vtype!=type&&type!=-1) {
                fprintf(stderr,"Cannot assign type %d to type %d\n",vtype,type);
                yyerror($1);
            }
            decrease_indent();
         }
  | T_NUM {
        print_ast("LITERAL", $1);
        increase_indent();
        if(!skip_execution) {
            $$=strdup($1);
            vtype=get_type($1);
            if(vtype!=type && type!=-1 && !(vtype==DOUBLE && type==FLOAT) && !(vtype==FLOAT && type==DOUBLE)) {
                fprintf(stderr,"Cannot assign type %d to type %d\n", vtype, type );
                yyerror( $1 );
            }
	   if(type == -1) {
                condition_result = (atof($1) != 0);
            }
        }
        decrease_indent();
    }
  | T_STRLITERAL {
                    print_ast("STRING_LITERAL", $1);
                    increase_indent();
                    $$=strdup($1);
                    vtype=1;
                    if(vtype!=type) {
                        fprintf(stderr,"Cannot assign char * to type %d\n",type);
                        yyerror( $1 );
                    }
                    decrease_indent();
                 }
  | INCREMENT {
      print_ast("INCREMENT_EXPR", NULL);
      increase_indent();
      decrease_indent();
    }
  ;

INCREMENT : T_INC T_ID {
                print_ast("PRE_INCREMENT", $2);
                increase_indent();
                symbol *s=get_symbol($2,scope,func);
                if(s==NULL) {
                    fprintf(stderr,"%s is not declared\n",$2);
                    yyerror($2);
                }
                if(!strcmp(s->val,"~")) {
                    fprintf(stderr,"%s is not initialized\n",$2);
                    yyerror($2);
                }
                char new_value[32];
                if(s->type==INT) {
                    int val = atoi(s->val) + 1;
                    sprintf(new_value,"%d",val);
                } else if(s->type==FLOAT || s->type==DOUBLE) {
                    double val = atof(s->val) + 1.0;
                    sprintf(new_value,"%lf",val);
                }
                insert_value_to_symbol(s,new_value);
                $$=strdup(new_value);
                vtype=s->type;
                decrease_indent();
            }
  | T_DEC T_ID {
                print_ast("PRE_DECREMENT", $2);
                increase_indent();
                symbol *s=get_symbol($2,scope,func);
                if(s==NULL) {
                    fprintf(stderr,"%s is not declared\n",$2);
                    yyerror($2);
                }
                if(!strcmp(s->val,"~")) {
                    fprintf(stderr,"%s is not initialized\n",$2);
                    yyerror($2);
                }
                char new_value[32];
                if(s->type==INT) {
                    int val = atoi(s->val) - 1;
                    sprintf(new_value,"%d",val);
                } else if(s->type==FLOAT || s->type==DOUBLE) {
                    double val = atof(s->val) - 1.0;
                    sprintf(new_value,"%lf",val);
                }
                insert_value_to_symbol(s,new_value);
                $$=strdup(new_value);
                vtype=s->type;
                decrease_indent();
            }
  | T_ID T_INC {
                print_ast("POST_INCREMENT", $1);
                increase_indent();
                symbol *s=get_symbol($1,scope,func);
                if(s==NULL) {
                    fprintf(stderr,"%s is not declared\n",$1);
                    yyerror($1);
                }
                if(!strcmp(s->val,"~")) {
                    fprintf(stderr,"%s is not initialized\n",$1);
                    yyerror($1);
                }
                $$=strdup(s->val);
                char new_value[32];
                if(s->type==INT) {
                    int val = atoi(s->val) + 1;
                    sprintf(new_value,"%d",val);
                } else if(s->type==FLOAT || s->type==DOUBLE) {
                    double val = atof(s->val) + 1.0;
                    sprintf(new_value,"%lf",val);
                }
                insert_value_to_symbol(s,new_value);
                vtype=s->type;
                decrease_indent();
            }
  | T_ID T_DEC {
                print_ast("POST_DECREMENT", $1);
                increase_indent();
                symbol *s=get_symbol($1,scope,func);
                if(s==NULL) {
                    fprintf(stderr,"%s is not declared\n",$1);
                    yyerror($1);
                }
                if(!strcmp(s->val,"~")) {
                    fprintf(stderr,"%s is not initialized\n",$1);
                    yyerror($1);
                }
                $$=strdup(s->val);
                char new_value[32];
                if(s->type==INT) {
                    int val = atoi(s->val) - 1;
                    sprintf(new_value,"%d",val);
                } else if(s->type==FLOAT || s->type==DOUBLE) {
                    double val = atof(s->val) - 1.0;
                    sprintf(new_value,"%lf",val);
                }
                insert_value_to_symbol(s,new_value);
                vtype=s->type;
                decrease_indent();
            }
  ;

REL_OP : T_LESSEREQ {
           print_ast("RELATIONAL_OPERATOR", "<=");
           $$ = "<=";
         }
       | T_GREATEREQ {
           print_ast("RELATIONAL_OPERATOR", ">=");
           $$ = ">=";
         }
       | '<' {
           print_ast("RELATIONAL_OPERATOR", "<");
           $$ = "<";
         }
       | '>' {
           print_ast("RELATIONAL_OPERATOR", ">");
           $$ = ">";
         }
       | T_EQCOMP {
           print_ast("RELATIONAL_OPERATOR", "==");
           $$ = "==";
         }
       | T_NOTEQUAL {
           print_ast("RELATIONAL_OPERATOR", "!=");
           $$ = "!=";
         }
       ;

MAIN : TYPE T_MAIN '(' {
          print_ast("MAIN_FUNCTION", "main");
          increase_indent();
          temp=func;func=0;
       } EMPTY_LISTVAR ')' '{' {scope++;} STMT '}' {
          scope--; 
          func=temp;
          decrease_indent();
       }
     ;

FUNC : TYPE T_ID '('{
          print_ast("FUNCTION", $2);
          increase_indent();
          ++func;
       } EMPTY_LISTVAR ')' '{' {scope++;} STMT '}' {
          scope--;
          decrease_indent();
       }
     ;

EMPTY_LISTVAR : LISTVAR {
                  print_ast("PARAMETER_LIST", "with_params");
                  increase_indent();
                  decrease_indent();
                }
              | {
                  print_ast("PARAMETER_LIST", "empty");
                }     
              ;

STMT : STMT_NO_BLOCK STMT 
     | BLOCK STMT 
     | LOOP_STMT STMT 
     | 
     ;

STMT_NO_BLOCK : DECLR ';' {
                  print_ast("DECLARATION_STATEMENT", NULL);
                  increase_indent();
                  decrease_indent();
                }
              | ASSGN ';' {
                  print_ast("ASSIGNMENT_STATEMENT", NULL);
                  increase_indent();
                  decrease_indent();
                }
              | IF_STMT {
                  print_ast("IF_STATEMENT", NULL);
                  increase_indent();
                  decrease_indent();
                }
              | error ';' {
                  print_ast("ERROR", "statement_error");
                  error_count++;
                }
              ;

IF_STMT : T_IF '(' COND ')' {
            print_ast("IF", NULL);
            increase_indent();
            if(!condition_result) {
                skip_execution = 1;
            }
            print_ast("CONDITION", condition_result ? "true" : "false");
            decrease_indent();
        } '{' STMT '}' {
            skip_execution = 0;
        } ELSE_PART
        ;

ELSE_PART : T_ELSE {
            print_ast("ELSE", NULL);
            increase_indent();
            if(condition_result) {
                skip_execution = 1;
            }
        } '{' STMT '}' {
            skip_execution = 0;
            decrease_indent();
        }
        | {
            print_ast("NO_ELSE", NULL);
          }
        ;

LOOP_STMT : WHILE_LOOP {
              print_ast("LOOP", "while");
              increase_indent();
              decrease_indent();
            }
          | DO_WHILE_LOOP {
              print_ast("LOOP", "do_while");
              increase_indent();
              decrease_indent();
            }
          | FOR_LOOP {
              print_ast("LOOP", "for");
              increase_indent();
              decrease_indent();
            }
          ;

WHILE_LOOP : T_WHILE '(' COND ')' {
               print_ast("WHILE_LOOP", NULL);
               increase_indent();
               if(!condition_result) {
                   skip_execution = 1;
               }
               print_ast("CONDITION", condition_result ? "true" : "false");
               decrease_indent();
           } BLOCK {
               skip_execution = 0;
           }
           ;

DO_WHILE_LOOP : T_DO {
                  print_ast("DO_WHILE_LOOP", NULL);
                  increase_indent();
                } BLOCK T_WHILE '(' COND ')' ';' {
                  print_ast("CONDITION", condition_result ? "true" : "false");
                  decrease_indent();
                }
                ;

FOR_LOOP : T_FOR '(' FOR_INIT ';' COND ';' FOR_UPDATE ')' {
             print_ast("FOR_LOOP", NULL);
             increase_indent();
             if(!condition_result) {
                 skip_execution = 1;
             }
             print_ast("CONDITION", condition_result ? "true" : "false");
             decrease_indent();
         } BLOCK {
             skip_execution = 0;
         }
         ;

FOR_INIT : DECLR {
             print_ast("FOR_INIT", "declaration");
             increase_indent();
             decrease_indent();
           }
         | ASSGN {
             print_ast("FOR_INIT", "assignment");
             increase_indent();
             decrease_indent();
           }
         | {
             print_ast("FOR_INIT", "empty");
           }
         ;

FOR_UPDATE : INCREMENT {
               print_ast("FOR_UPDATE", "increment");
               increase_indent();
               decrease_indent();
             }
           | ASSGN {
               print_ast("FOR_UPDATE", "assignment");
               increase_indent();
               decrease_indent();
             }
           | {
               print_ast("FOR_UPDATE", "empty");
             }
           ;

BLOCK : '{' {
          print_ast("BLOCK", NULL);
          increase_indent();
          scope++;
        } STMT '}' {
          scope--;
          decrease_indent();
        }
      ;

COND : EXPR {
         print_ast("CONDITION_EXPR", NULL);
         increase_indent();
         decrease_indent();
       }
     | ASSGN {
         print_ast("CONDITION_ASSGN", NULL);
         increase_indent();
         decrease_indent();
       }
     ;

%%

void yyerror(char* s)
{
    printf("Error :%s at %d \n", s, yylineno);
    error_count++;
    yyclearin;
}

int main(int argc, char* argv[])
{
    t = allocate_space_for_table();
    fp = fopen("AST.txt", "w");
    fprintf(fp, "ABSTRACT SYNTAX TREE\n");
    
    yyparse();
    
    if (error_count == 0) {
    } else {
        printf("Invalid syntax - %d error(s) found\n", error_count);
    }
    
    fclose(fp);
    display_symbol_table();
    return 0;
}
