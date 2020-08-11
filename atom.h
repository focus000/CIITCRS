#ifndef ATOM_INCLUDE
#define ATOM_INCLUDE

extern int Atom_length(char const *str);
extern char const *Atom_new(char const *str, int len);
extern char const *Atom_string(char const *str);
extern char const *Atom_int(long n);

#endif