#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
#include <setjmp.h>

#define T Except_T

// 异常是 Except_T 的全局或静态变量，Except_T 则只有一个用来描述异常信息的字段。
typedef struct T {
  char const *reason;
} T;

typedef struct Except_Frame Except_Frame;
struct Except_Frame {
  Except_Frame *prev;
  jmp_buf env;
  char const *file;
  int line;
  const T *exception;
};

enum { Except_entered = 0, Except_raised, Except_handled, Except_finalized };

extern Except_Frame *Except_stack;
extern const Except_T Assert_Failed;

void Except_raise(T const *e, char const *file, int line);

#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__)
#define RERAISE \
  Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line)

#define TRY                                 \
  do {                                      \
    volatile int Except_flag;               \
    Except_Frame Except_Frame;              \
    Except_Frame.prev = Except_stack;       \
    Except_stack = &Except_Frame;           \
    Except_flag = setjmp(Except_Frame.env); \
    if (Except_flag == Except_entered) {
#define EXCEPT(e)                                                       \
  if (Except_flag == Except_entered) Except_stack = Except_stack->prev; \
  }                                                                     \
  else if (Except_Frame.exception == &(e)) {                            \
    Except_flag = Except_handled;
#define ELSE                                                            \
  if (Except_flag == Except_entered) Except_stack = Except_stack->prev; \
  }                                                                     \
  else {                                                                \
    Except_flag = Except_handled;
#define FINALLY                                                         \
  if (Except_flag == Except_entered) Except_stack = Except_stack->prev; \
  }                                                                     \
  {                                                                     \
    if (Except_flag == Except_entered) Except_flag = Except_finalized;
#define END_TRY                                                         \
  if (Except_flag == Except_entered) Except_stack = Except_stack->prev; \
  }                                                                     \
  if (Except_flag == Except_raised) RERAISE;                            \
  }                                                                     \
  while (0)

#undef T
#endif