#ifndef DDSTRING_H
#define DDSTRING_H

#include "Object.h"

namespace DemoData
{

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);

public:
    String();
    String(const char c);
    String(const char* s);
    String(const String& s);

    int length() const;
    const char* str() const;

    /* 数组访问操作符重载函数 */
    char& operator [](int index);
    char operator [](int index) const;  // 返回的是非引用对象, 不是原对象, 因此, 不能通过赋值对原对象赋值(const对象要求不能改变对象)

    /* 判断是否以指定字符串开始或结束 */
    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;
    // 比较函数
    bool equal(const char* l, const char* r, int len) const;

    /* 在指定位置插入字符串 */
    String& insert(int index, const char* s);
    String& insert(int index, const String& s);

    /* 去掉字符串两端的空白字符 */
    String& trim();

    /* 比较操作符重载函数 */
    bool operator >(const char* s) const;
    bool operator >(const String& s) const;
    bool operator <(const char* s) const;
    bool operator <(const String& s) const;
    bool operator ==(const char* s) const;
    bool operator ==(const String& s) const;
    bool operator !=(const char* s) const;
    bool operator !=(const String& s) const;
    bool operator >=(const char* s) const;
    bool operator >=(const String& s) const;
    bool operator <=(const char* s) const;
    bool operator <=(const String& s) const;

    /* 加法操作符重载函数 */
    String operator +(const char* s) const;
    String operator +(const String& s) const;
    String& operator +=(const char* s);
    String& operator +=(const String& s);

    /* 赋值操作符重载函数 */
    String& operator =(const char c);
    String& operator =(const char* s);
    String& operator =(const String& s);

    ~String();
};

}

#endif // DDSTRING_H
