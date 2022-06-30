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
