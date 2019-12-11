#ifndef STACK_H
#define STACK_H

#include "list_sl.h"

typedef Lista_SL Stack;

void creastack(Stack* S);
void push(Stack* S, int value);
int pop(Stack* S);
void LiberaStack(Stack* S);
int StackVuoto(Stack* S);
void stampastack(Stack* S);

#endif
