#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;
int main()
{
    // stringstream oss;

    string s, t;
    while(cin >> s >> t)
    {
        if(s == "0")
            break;
        bool found = true;
        auto pos = t.begin();
        for(int i=0; i<s.size(); ++i)
        {
            char c = s[i];
            pos = find(pos, t.end(), c);
            // cout << "process " << c << endl;

            if(pos == t.end()) {
                found = false;
                break;
            }
            pos += 1;
        }
        if(found) {
            cout << "Yes" << endl;
            // oss << "Yes" << endl;
        } else {
            cout << "No" << endl;
            // oss << "No" << endl;
        }
    }
    /*
    while(oss >> s) {
        cout << s << endl;
    }*/

}
