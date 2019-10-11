#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;
int main()
{
    int rounds= 0;
    cin >> rounds;
    getchar();
    for(int i=0; i<rounds; ++i)
    {
        string line;
        int nums[10001] = {};
        getline(cin, line);
        istringstream iss(line);

        int ind = 0;
        while(iss >> nums[ind]) {
            ind += 1;
        }/*
        for(int j=0; j<ind; ++j) {
            cout << nums[j];
        }*/
        cout << "Case " << i+1 << ": " << *max_element(nums, nums+ ind) << endl;

    }
}
