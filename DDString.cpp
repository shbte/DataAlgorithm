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

/* 数组访问操作符重载函数 */
char& String::operator [](int index)
{
    // 判断参数下标是否合法
    if((0 <= index) && (index < m_length))
    {
        // return *(m_str + index); // 指针法
        return m_str[index];    // 数组下标法
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }
}
char String::operator [](int index) const
{
    // 调用现有函数, 提高代码复用性
    return (const_cast<String&>(*this))[index];
}

/* 判断是否以指定字符串开始或结束 */
bool String::startWith(const char* s) const
{
    // 判断匹配字符串是否合法(不能为空)
    bool ret = (s != NULL);

    if(ret)
    {
        // 获取匹配字符串长度
        int slen = strlen(s);

        // m_str从头开始匹配s, 匹配长度为slen
        ret = equal(m_str, s, slen);
    }

    return ret;
}
bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}
bool String::endOf(const char* s) const
{
    // 判断字符串是否合法(不能为空)
    bool ret = (s != NULL);

    if(ret)
    {
        int slen = strlen(s);
        // 获取尾部长度为slen的字符串
        char* str = m_str + (m_length - slen);

        // str从头开始匹配s, 匹配长度为slen
        ret = equal(str, s, slen);
    }

    return ret;
}
bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}
bool String::equal(const char* l, const char* r, int len) const
{
    bool ret = true;

    // 任意字符匹配不成功时, 循环结束(ret=false)
    for(int i = 0; (i < len) && ret; i++)
    {
        ret = (ret && (l[i] == r[i]));
    }

    return ret;
}

/* 在指定位置插入字符串 */
String& String::insert(int index, const char* s)
{
    // 判断插入位置是否合法
    if((0 <= index) && (index <= m_length))
    {
        // 判断插入字符串是否合法
        if((s != NULL) && (s[0] != '\0'))
        {
            int slen = strlen(s);
            char* str = reinterpret_cast<char*>(malloc(m_length + slen + 1));

            if(str)
            {
                strncpy(str, m_str, index);
                strncpy(str + index, s, slen);

                // 最后的+1为结尾符, 可以在cpy时添加, 也可后续手动追加
                //strncpy(str + index + slen, m_str + index, m_length - index + 1);

                // 没有追加结尾符, 可在后续手动追加
                strncpy(str + index + slen, m_str + index, m_length - index);
                // 结尾符, cpy结束时手动追加
                str[m_length + slen] = '\0';

                // 释放原内存空间
                free(m_str);

                // 更新成员变量
                m_str = str;
                m_length = strlen(str); // =m_length + slen     : 结尾符不计算长度

                return *this;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough to insert String value...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "parameter s is Invalid...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "parameter index is Invalid...");
    }
}
String& String::insert(int index, const String& s)
{
    return insert(index, s.m_str);
}

/* 去掉字符串两端的空白字符 */
String& String::trim()
{
    int begin = 0;
    int end = m_length - 1;

    // 从头寻找第一个非空字符的下标
    while(m_str[begin] == ' ')
    {
        begin++;

        if(begin == m_length)
        {
            THROW_EXCEPTION(InvalidParameterException, "parameter s is Invalid...");
        }
    }
    // 从尾寻找第一个非空字符的下标
    while(m_str[end] == ' ')
    {
        end--;
    }

    // 将非空字符串移动到开头
    for(int i = 0, j = begin; j <= end; i++, j++)
    {
        m_str[i] = m_str[j];
    }
    // 结尾符
    m_str[end - begin + 1] = '\0';
    // 更新长度
    m_length = end - begin + 1;

    return *this;
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
        // s有结尾符, 因此, str不用特意追加结尾符
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
