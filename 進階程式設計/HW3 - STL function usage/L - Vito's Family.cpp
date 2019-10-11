#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
int main()
{
    int test_cases=0;
    cin >> test_cases;
    while(test_cases --)
    {
        int n;
        cin >> n;
        int relatives[n] = {};
        for(int i=0; i<n; ++i) {
            cin >> relatives[i];
        }

        nth_element(relatives, relatives + n/2, relatives+n);
        int center= relatives[n/2];

        int dist[n] = {};
        for(int i=0; i<n; ++i) {
            dist[i] = abs(relatives[i] - center);
        }
        cout << accumulate(dist, dist+n, 0) << endl;

    }
}
