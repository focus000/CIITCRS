#include "assert.h"

Except_T const Assert_Failed = { "Assertion failed" };

// why define assert(int e) ?
void (assert)(int e) {
    assert(e);
}