typedef struct TSymNode {
    int Sym;
    struct TSymNode* Next;
    struct TSymNode* Last;
} TSymNode;

typedef struct TSym {
    struct TSymNode* Head;
    struct TSymNode* Tail;
    int CountBracket;
    int Size;
} TSym;


void Push(TSym* list, int sym);
int Delete(TSym* list);
int Math(TSym* parametrs, TSym* func);
int CheckPriority(int lastSym, int newSym);
