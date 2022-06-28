#ifndef SYMBOLMATH_H
#define SYMBOLMATH_H

#include "LinkStack.h"

using namespace DemoData;

bool is_left(char c)
{
    return ((c == '(') || (c == '{') || (c == '<') || (c == '['));
}
bool is_right(char c)
{
    return ((c == ')') || (c == '}') || (c == '>') || (c == ']'));
}
bool is_quot(char c)
{
    return ((c == '\'') || (c == '\"'));
}

bool is_math(char l, char r)
{
    return ((l == '(') && (r == ')')) ||
           ((l == '{') && (r == '}')) ||
           ((l == '<') && (r == '>')) ||
           ((l == '[') && (r == ']')) ||
           ((l == '\'') && (r == '\'')) ||
           ((l == '\"') && (r == '\"'));
}

bool Symbol_Math(const char* code)
{
    bool ret = false;

    int index = 0;
    LinkStack<char> stack;
    ret = (code == NULL) ? false : true;

    while(ret && (code[index] != '\0'))
    {
        if(is_left(code[index]))
        {
            // 左符号, 进栈
            stack.push(code[index]);
        }
        else if((stack.size() > 0) && is_right(code[index]))
        {
            // 右符号, 匹配成功则出栈
            if(is_math(stack.top(), code[index]))
            {
                stack.pop();
            }
            else
            {
                // 右符号匹配不成功, 则结束
                ret = false;
            }
        }
        else if(is_quot(code[index]))
        {
            if((stack.size() > 0) && is_math(stack.top(), code[index]))
            {
                // 单双引号匹配成功, 出栈
                stack.pop();
            }
            else
            {
                // 单双引号匹配成功, 入栈
                stack.push(code[index]);
            }
        }
        else
        {

        }
        index++;
    }

    return (ret && (!stack.size()));
}

#endif // SYMBOLMATH_H
