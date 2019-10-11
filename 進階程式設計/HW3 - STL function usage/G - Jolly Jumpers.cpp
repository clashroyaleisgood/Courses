#include <iostream>
#include <algorithm>
#include <numeric>
#include <sstream>

using namespace std;
int main()
{
    int n;
    stringstream oss;
    while(cin >> n)
    {
/*
        if(n == 0) {
            break;
        }*/
        int jolly[n] = {}, result[n] = {};
        for(int i=0; i<n; ++i){
            cin >> jolly[i];
        }
        adjacent_difference(jolly, jolly+n, result);
        /*
        for(int e: result) {
            cout << e;
        }*/
        bool check_same[n] = {}, same= false;
        for(int i=0; i<n; ++i) {
            result[i] = abs(result[i]);
        }

/*
        for(int i=1; i<n; ++i) {
            // cout << "    processing " << result[i] << endl;
            if(check_same[result[i]-1 ] == true) {
                same = true;
                break;
            }
            check_same[result[i]-1 ] = true;
        }
*/
        sort(result+1, result+n);
        if( unique(result+1, result+n) != result+n) {
            cout << "Not jolly" << endl;
            // oss << "Not jolly cause not unique" << endl;
        } else if(all_of(result+1, result+n, [n](int r){ return r<n; })) {
            cout << "Jolly" << endl;
            // oss << "Jolly" << endl;
        } else {
            cout << "Not jolly" << endl;
            // oss << "Not jolly cause out of range" << endl;
        }
    }
/*
    string temps;
    while(getline(oss, temps)) {
        cout << temps << endl;
    }*/
}
