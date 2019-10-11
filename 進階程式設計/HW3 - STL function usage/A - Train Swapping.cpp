#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    int round = 0;
    cin >> round;
    while(round--)
    {
        int n= 0;
        cin >> n;
        int train[n]= {}, count= 0;
        for(int i=0; i<n; ++i) {
            cin >> train[i];
        }
        for(int i=0; i<n-1; ++i) {
            for(int j=i+1; j<n; ++j) {
                if(train[i] > train[j]) {
                    swap(train[i], train[j]);
                    count +=1;
                }
            }
        }
        cout << "Optimal train swapping takes " << count << " swaps." << endl;
    }
}
