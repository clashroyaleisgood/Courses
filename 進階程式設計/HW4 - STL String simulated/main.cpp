#include <iostream>
#include "mystr.h"
#include <stdio.h>

using namespace std;
/// 以 opeartor (const char*) 去實作 opeartor (const String &) --> String ope String.str_
/// 或是只做 operator(const String &) 的版本                   --> char* 會自動轉成 String & (透過 String(char*) )

int main()
{
    String simple_a, simple_b("123|"), simple_c("456| "), simple_d = "789";
    simple_c[4] = '\0';
    cout << simple_a << simple_b << simple_c << simple_d << endl;
    cout << "---------------------------------------------------" << endl;
    cout << simple_a +simple_b +simple_c +simple_d << endl;
    cout << "---------------------------------------------------" << endl;

    simple_a += simple_a+simple_b+ "somethingelse|" +simple_c+simple_d;
    cout << simple_a << endl;
    for(int i=0; i<simple_a.size(); i+=1)
        simple_a[i] = 'a' +i;
    cout << simple_a << endl;

    cout << "input sth...>";
    cin >> simple_a;
    cout << "input: " << simple_a.c_str() << endl;

    cout <<"swapping (a, b) ...>";
    cin >> simple_a >> simple_b;
    simple_a.swap(simple_b);
    cout << simple_a << simple_b << endl;

    simple_a="123";
    simple_b="123";
    if(simple_a==simple_b && simple_a=="123" && "123"==simple_a)
        cout << "a==b && a==\"123\" && \"123\"==a ---> True" << endl;
}
///* --------------------- 後面這段請搭配 DEBUGGER 服用 --------------------- *///
/*
int main()
{
    String a("0123 456");
    a[4] = '\0';
    cout << a << " >" << a.size() << " >" << a.capacity() << endl;
    cout << "--------------------------------------------------- 1" << endl;

    String b(a);
    b += b;
    cout << b << " >" << b.size() << " >" << b.capacity() << endl;

    cout << "--------------------------------------------------- 2" << endl;
    cout << (b + "123")[10] << endl;
    cout << "--------------------------------------------------- 3" << endl;
    String c("1");
    cout << "--------------------------------------------------- 4" << endl;
    '1' == c;
    cout << "--------------------------------------------------- 5" << endl;
    c != "1";
    cout << "--------------------------------------------------- end of main" << endl;

}
*/
/// 討厭! a(b+"123") 時他會把 b+"123" 產生的 temp string 直接拿給 a 用
