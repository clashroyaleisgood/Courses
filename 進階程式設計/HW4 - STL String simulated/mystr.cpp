#include <iostream>
#include "mystr.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

constexpr bool DEBUGGER = false;
size_t String::counter = 0;

void String::copy_to(char rhs[], size_t limit) const
{
    size_t bound = min(size_, limit);
    for(size_t i=0; i<bound; ++i)
    {
        rhs[i] = str_[i];
    }
    rhs[bound] = '\0';
}
void String::copy_from(char rhs[], size_t size)
{
    for(size_t i=0; i<size; ++i)
    {
        str_[i] = rhs[i];
    }
    str_[size] = '\0';
}
bool String::resize(size_t size, bool copy)    /// 改好 capacity_
{
    if(size > capacity_)    /// capacity not enough
    {
        size_t new_cap = size+10;   /// 不含 \0
        if(DEBUGGER)
            cout << "resize " << label_ << " from " << capacity_ << " to " << new_cap << endl;
        try
        {
            char *newstr = new char[new_cap +1];
            /// strcpy(newstr, str_);   /// 這樣會跳過 \0
            if(copy)
                copy_to(newstr, new_cap);
            else
                newstr[new_cap] = '\0';

            delete str_;
            str_ = newstr;
            capacity_ = new_cap;
            return true;
        }
        catch (bad_alloc &exp)
        {
            cout << "ERROR: can\'t new a new string" << endl;
            return false;
        }
    }
    else
    {
        if(DEBUGGER)
            cout << "resize " << label_ << " from " << capacity_ << " to " << size << endl;
        return true;
    }
}

String::String()
{
    if(DEBUGGER) {
        label_ = ++counter;
        cout << "in String()" << " label: " << counter << endl;
    }
    char *newstr= new char[1];
    *newstr= '\0';
    str_= newstr;
}
String::String(const char name[])
{
    if(DEBUGGER) {
        label_ = ++counter;
        cout << "in String(const char*)" << " label: " << counter << " str: \"" << name << "\"" << endl;
    }
    char * newstr = new char[1];    ///初始化都必須作
    str_ = newstr;
    str_[0] = '\0';

    size_t size= strlen(name);
    resize(size, false);        /// 不複製 str_ 的內容到新的 str_
    strcpy(str_, name);         /// 要複製 name 的內容到新的 str_

    size_ = size;
}
String::String(const String &rhs)
{
    if(DEBUGGER) {
        label_ = ++counter;
        cout << "in String(const String)   ";
        cout << label_ << " (" << rhs.label_ << ")" << endl;
    }
    char * newstr = new char[1];    ///初始化都必須作
    str_ = newstr;
    str_[0] = '\0';

    resize(rhs.size_, false);           /// 用 size 來 new
    copy_from(rhs.str_, rhs.size_);     /// 複製到 rhs.size_ 為止

    size_ = rhs.size_;
}
String & String::operator = (const String &rhs)
{
    if(DEBUGGER) {
        cout << "in operator ";
        cout << label_ << " = " << rhs.label_ << endl;
    }
    resize(rhs.size_, true);    ///保留
    copy_from(rhs.str_, rhs.size_);

    size_ = rhs.size_;

    return *this;
}
String & String::operator = (char c)
{
    if(DEBUGGER) {
        cout << "in operator ";
        cout << label_ << " = \'" << c << "\'" << endl;
    }
    resize(1, false);       /// 不用保留 右邊只是個字元
    str_[0] = c;
    str_[1] = '\0';
    size_ = 1;

    return *this;
}
String & String::operator += (const String & rhs)
{
    if(DEBUGGER)
        cout << "in operator \"" << *this << "\" += \"" << rhs << "\"" << endl;

    resize(size_ + rhs.size_, true);

    for(size_t i=0; i<rhs.size_; ++i)
    {
        str_[size_ + i] = rhs.str_[i];
    }
    size_ += rhs.size_;     /// 這邊才能更新 str_ 位置
    str_[size_] = '\0';
    return *this;
}
String & String::operator += (char c)
{
    if(DEBUGGER)
        cout << "in operator \"" << *this << "\" += \"" << c << "\"" << endl;

    resize(size_ + 1, true);
    str_[size_] = c;
    size_ += 1;
    str_[size_] = '\0';

    return *this;
}
String operator + (const String &lhs, const String &rhs)
{
    if(DEBUGGER)
        cout << "in opearator " << lhs.label() << " + " << rhs.label() << endl;
    String temp(lhs);
    temp += rhs;
    return temp;
}
String operator + (const String &lhs, char c)
{
    if(DEBUGGER)
        cout << "in opearator " << lhs.label() << " + \'" << c << "\'" << endl;
    String temp(lhs);
    temp += c;
    return temp;
}
String operator + (char c, const String &rhs)   //還是不要把它弄成 friend 好了
{
    if(DEBUGGER)
        cout << "in opearator \'" << c << "\' + " << rhs.label() << endl;
    char str[2] = "";
    str[0] = c;
    String temp(str);
    temp += rhs;
    return temp;
}
String::~String()
{
    if(DEBUGGER) {
        cout << "in ~String()" << " label: " << label_ << "  (" << size_ << "/" << capacity_ << ")";
        cout << "  str: \"" << *this << "\" pos: " << &str_ << endl;
    }
    delete [] str_;
}
ostream & operator << (ostream &os, const String &str)
{
    for(size_t i=0; i<str.size_; ++i)
        os << str.str_[i];
    return os;
}
istream & operator >> (istream &is, String &str)
{
    char c;
    str.clear();
    while(str.size() == 0)
    {
        while(is.get(c))
        {
            if(c == ' ' or c == '\0' or c == '\n' or c == '\t')
                break;
            str += c;
        }
    }
    return is;
}

const char & String::operator [] (size_t index) const
{
    if(DEBUGGER)
        cout << "in opeartor " << label_ << "[" << index << "] safe" << endl;
    if(index < size_)
    {
        return str_[index];
    }
    else
    {
        cout << "ERROR: index out of range" << endl;
        cout << *this << "[" << index << "]";
        system("pause");
        return str_[size_ -1];
    }
}
char & String::operator [] (size_t index)
{
    if(DEBUGGER)
        cout << "in opeartor " << label_ << "[" << index << "] dangerous" << endl;
    return const_cast<char &>( static_cast<const String &>(*this)[index] );
}
void String::swap(String &rhs)
{
    String temp(*this);
    *this = rhs;
    rhs = temp;
}
int cmp(const String &lhs, const String &rhs)       /// -1: <, 0: =, 1: >
{
    for(size_t i=0; i<lhs.size() && i<rhs.size(); ++i)  /// 有沒有字元不同
    {
        if(lhs[i] < rhs[i])
            return -1;
        else if(lhs[i] > rhs[i])
            return 1;
    }
    if(lhs.size() < rhs.size())                         /// 都一樣就比長短
        return -1;
    else if(lhs.size() > rhs.size())
        return 1;
    else
        return 0;
}
bool operator == (const String &lhs, const String &rhs) { return cmp(lhs, rhs) == 0; }
bool operator != (const String &lhs, const String &rhs) { return cmp(lhs, rhs) != 0; }
bool operator <  (const String &lhs, const String &rhs) { return cmp(lhs, rhs) <  0; }
bool operator >  (const String &lhs, const String &rhs) { return cmp(lhs, rhs) >  0; }
bool operator <= (const String &lhs, const String &rhs) { return cmp(lhs, rhs) <= 0; }
bool operator >= (const String &lhs, const String &rhs) { return cmp(lhs, rhs) >= 0; }

