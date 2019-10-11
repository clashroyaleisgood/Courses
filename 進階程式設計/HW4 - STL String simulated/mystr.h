#ifndef MYSTR_H_INCLUDED
#define MYSTR_H_INCLUDED
using std::ostream;
using std::istream;

class String
{
friend ostream & operator << (ostream &os, const String &str);
friend istream & operator >> (istream &is, String &str);

public:
    String();
    String(const char name[]);
    String(const String &rhs);
    String & operator = (const String &rhs);
    String & operator = (char c);
    String & operator += (const String &rhs);
    String & operator += (char c);
    ~String();

    const char & operator [] (size_t index) const;
    char & operator [] (size_t index);

    size_t size() const { return size_; };
    size_t capacity() const { return capacity_; };
    const char* c_str() const { return str_; };
    void clear() { str_[0] = '\0'; size_ = 0; };
    void swap(String &rhs);
    size_t label() const { return label_; };    //for debugging

private:
    size_t size_= 0, capacity_= 0;  /// 不含 '\0'
    char *str_= nullptr;
    size_t label_=0;                // for dubugging
    static size_t counter;          // for debugging

    bool resize(size_t size, bool copy);
    void copy_to(char rhs[], size_t limit) const;   /// strcpy(rhs, str_)
    void copy_from(char rhs[], size_t limit);       /// strcpy(str_, rhs)
};
ostream & operator << (ostream &os, const String &str);
istream & operator >> (istream &is, String &str);
int cmp(const String &lhs, const String &rhs);

String operator + (const String &lhs, const String &rhs);
String operator + (const String &lhs, char c);
String operator + (char c, const String &rhs);

bool operator == (const String &lhs, const String &rhs);    /// 只用他就可以覆蓋 str-str, str-char[], char[]-str
bool operator != (const String &lhs, const String &rhs);
bool operator <  (const String &lhs, const String &rhs);
bool operator >= (const String &lhs, const String &rhs);
bool operator >  (const String &lhs, const String &rhs);
bool operator <= (const String &lhs, const String &rhs);

#endif // MYSTR_H_INCLUDED
