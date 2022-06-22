#include <cstdlib>
#include <cstring>

#include "Exception.h"

/*
 *
 * ArithmeticException          计算异常
 * NullPointerException         空指针异常
 * IndexOutOfBoundsException    越界异常
 * NoEnoughMemoryException      内存不足异常
 * InvalidParameterException     参数错误异常
 *
 */
namespace DemoData
{

void Exception::init(const char* message, const char* file, int line)
{
    m_message = strdup(message);

    if(file != NULL)
    {
        char cline[16];
        itoa(line, cline, 10);

        m_location = static_cast<char*>(malloc(strlen(file) + strlen(cline) + 2));

        if(m_location != NULL)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, cline);
        }
    }
}

Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file, line);
}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator=(const Exception& e)
{
    if(this != &e)
    {
        free(m_message);
        free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }
    return *this;
}

const char* Exception::message() const
{
    return m_message;
}

const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{

}

};
