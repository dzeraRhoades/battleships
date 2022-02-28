#include"funcs.h"

MyStack::MyStack()
{
    top = nullptr;
    row = 0;
    direction = NONE;
}

int MyStack::push(int x, int y)
{
    stackNode* new_node = new stackNode;
    new_node->next = top;
    top = new_node;
    new_node->x = x;
    new_node->y = y;
    row++;
    return 0;
}

int MyStack::pop()
{
    if (is_empty())
        return -1;
    stackNode* tmp;
    tmp = top;
    top = top->next;
    delete tmp;
    row--;
    return 0;
}

int MyStack::is_empty()
{
    if (top == nullptr)
        return 1;
    else
        return 0;
}

int MyStack::clean()
{
    while(!is_empty())
    {
        pop();
    }
    return 0;
}
