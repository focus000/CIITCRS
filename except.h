#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
#include <setjmp.h>

#define T Except_T

typedef struct T
{
    char const *reason;
} T;

typedef struct Except_Frame Except_Frame; 
struct Except_Frame
{
    Except_Frame *prev;
    jmp_buf env;
    char const *file;
    int line;
    T const *exception;
};

extern Except_Frame *Except_stack;

void Except_raise(T const *e, char const *file, int line);

#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__)
#define RERAISE Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line)

#undef T
#endif