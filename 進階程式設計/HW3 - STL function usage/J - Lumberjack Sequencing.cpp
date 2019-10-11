#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    int n;
    cin >> n;
    cout << "Lumberjacks:" << endl;
    while(n--)
    {
        int lumberjack[10]= {};
        for(int i=0; i<10; ++i) {
            cin >> lumberjack[i];
        }
        if(is_sorted(lumberjack, lumberjack+10)) {
            cout << "Ordered" << endl;
        } else {
            reverse(lumberjack, lumberjack+10);
            if(is_sorted(lumberjack, lumberjack+10)) {
                cout << "Ordered" << endl;
            } else {
                cout << "Unordered" << endl;
            }
        }
    }
}
