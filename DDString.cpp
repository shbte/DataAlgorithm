#include <cstring>

#include "DDString.h"
#include "Exception.h"

namespace DemoData
{

void String::init(const char* s)
{
    // 将空指针转换成空字符串
    s = (s ? s : "");
    // 先malloc开辟空间, 然后赋值内容
    m_str = strdup(s);

    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create String Object...");
    }
}

/* 构造函数 */
String::String()
{
    init("");
}
String::String(const char c)
{
    char s[] = {c, '\0'};

    init(s);
}
String::String(const char* s)
{
    init(s);
}
String::String(const String& s)
{
    init(s.m_str);
}

/* 比较操作符重载函数 */
bool String::operator >(const char* s) const
{
    s = (s ? s : "");

    int ret = strcmp(this->m_str, s);
    return (ret > 0);
}
bool String::operator >(const String& s) const
{
    int ret = strcmp(this->m_str, s.m_str);
    return (ret > 0);
}
bool String::operator <(const char* s) const
{
    s = (s ? s : "");

    int ret = strcmp(this->m_str, s);
    return (ret < 0);
}
bool String::operator <(const String& s) const
{
    int ret = strcmp(this->m_str, s.m_str);
    return (ret < 0);
}
bool String::operator ==(const char* s) const
{
    s = (s ? s : "");

    int ret = strcmp(this->m_str, s);
    return (ret == 0);
}
bool String::operator ==(const String& s) const
{
    int ret = strcmp(this->m_str, s.m_str);
    return (ret == 0);
}
bool String::operator !=(const char* s) const
{
    s = (s ? s : "");

    int ret = strcmp(this->m_str, s);
    return (ret != 0);
}
bool String::operator !=(const String& s) const
{
    int ret = strcmp(this->m_str, s.m_str);
    return (ret != 0);
}
bool String::operator >=(const char* s) const
{
    s = (s ? s : "");

    int ret = strcmp(this->m_str, s);
    return (ret >= 0);
}
bool String::operator >=(const String& s) const
{
    int ret = strcmp(this->m_str, s.m_str);
    return (ret >= 0);
}
bool String::operator <=(const char* s) const
{
    s = (s ? s : "");

    int ret = strcmp(this->m_str, s);
    return (ret <= 0);
}
bool String::operator <=(const String& s) const
{
    int ret = strcmp(this->m_str, s.m_str);
    return (ret <= 0);
}

/* 加法操作符重载函数 */
String String::operator +(const char* s) const
{
    String ret;
    // 将空指针转换为空字符
    s = (s ? s : "");
    int len = m_length + strlen(s);
    // 结尾符长度+1
    char* str = reinterpret_cast<char*>(malloc(len + 1));

    if(str)
    {
        strcpy(str, m_str);
        strcat(str, s);

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = strlen(str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add String values...");
    }

    return ret;
}
String String::operator +(const String& s) const
{
    return (*this + s.m_str);
}
String& String::operator +=(const char* s)
{
    return (*this = *this + s);
}
String& String::operator +=(const String& s)
{
    return (*this = *this + s.m_str);
}

/* 赋值操作符重载函数 */
String& String::operator =(const char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}
String& String::operator =(const char* s)
{
    s = (s ? s : "");
    char* str = strdup(s);

    if(str)
    {
        free(m_str);

        m_str = str;
        m_length = strlen(str);
    }

    return *this;
}
String& String::operator =(const String& s)
{
    return (*this = s.m_str);
}

int String::length() const
{
    return m_length;
}
const char* String::str() const
{
    return m_str;
}

String::~String()
{
    free(m_str);
}

}
