#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;
int main()
{
    int round = 0;
    cin >> round;
    for(int i=0; i<round; ++i)
    {
        int n=0;
        cin >> n;
        int nums[n] = {};
        for(int j=0; j<n; ++j) {
            cin >> nums[j];
        }
        int sum = accumulate(nums, nums+n, 0);
        double avg = static_cast<double>( sum )/ n;
        double count = count_if(nums, nums+n, [avg](int n){ return n>avg; });
        // cout << count/ n << endl;
        cout << setiosflags(ios::fixed) << setprecision(3) << count*100/ n << "%" << endl;
    }
}
