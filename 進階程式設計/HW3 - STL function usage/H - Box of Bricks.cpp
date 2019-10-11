#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
int main()
{
    int n, sets = 1;
    cin >> n;
    while(n) {
        int stacks[n] = {}, avg=0;
        for(int i=0; i<n; ++i){
            cin >> stacks[i];
        }
        /*
        for(int e: stacks) {
            cout << e;
        }*/
        avg = accumulate(stacks, stacks+n, 0) / n;
        int difference = 0;
        for(int e: stacks) {
            difference += abs(avg - e);
        }
        // cout << difference;
        cout << "Set #" << sets << endl;
        cout << "The minimum number of moves is " << difference/2 << "." << endl << endl;

        cin >> n;
        sets += 1;
    }
}
