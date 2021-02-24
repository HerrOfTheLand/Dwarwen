#ifndef DWARVEN_TOKEN_T
#define DWARVEN_TOKEN_T

enum Token_TokenType {
    Token_TokenType_INSTRUCTION,
    Token_TokenType_NUMBER
};

enum Token_TokenInstruction {
    Token_TokenInstruction_ERR,
    Token_TokenInstruction_NOP,
    Token_TokenInstruction_PUSH,
    Token_TokenInstruction_ADD,
    Token_TokenInstruction_HLT
};

struct Token_Token {
    int type;
    int data;
    int line;
};

extern struct Token_Token*
Token_Token_create ( enum Token_TokenType type, int data, int line );

extern void
Token_Token_destroy ( struct Token_Token* token );


struct Token_TokenList {
    struct Token_Token** data;
    int len;
    int size;
};

extern struct Token_TokenList*
Token_TokenList_create( int size );

extern struct Token_Token*
Token_TokenList_push_back ( struct Token_TokenList* list, struct Token_Token* token );

extern struct Token_Token*
Token_TokenList_get ( struct Token_TokenList* list, int index );

extern void
Token_Token_present( struct Token_Token* token );

extern void
Token_TokenList_destroy( struct Token_TokenList* list );

#endif