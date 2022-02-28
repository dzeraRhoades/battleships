#ifndef FUNCS_H
#define FUNCS_H

#endif // FUNCS_H
enum botDir{UP, DOWN, RIGHT, LEFT, NONE};

class stackNode
{
public:
    int x;
    int y;
    stackNode* next;

};

class MyStack
{
public:
    MyStack();


   stackNode* top;
   int row;
   botDir direction;

   int push(int x, int y);


   int pop();


   int is_empty();

   int clean();

};


