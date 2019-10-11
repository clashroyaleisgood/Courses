#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;
int main()
{
    int n;
    stringstream oss;
    while(cin >> n)
    {
        if(n == 0) {
            break;
        }
        string str;
        cin >> str;

        int group_num = str.size()/n;
        for(int i=0; i<str.size(); i+=group_num) {
            reverse(&str[i], &str[i+group_num]);
        }
        cout << str << endl;
        // oss << str << endl;
    }/*
    string s;
    while(oss >> s) {
        cout << s << endl;
    }*/
}
