#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    int N, Q, round = 1;
    cin >> N >> Q;
    while(!(N==0 && Q==0))
    {
        int marbles[N] = {}, queries[Q] = {};
        for(int i=0; i<N; ++i) {
            cin >> marbles[i];
        }
        for(int i=0; i<Q; ++i) {
            cin >> queries[i];
        }
        cout << "CASE# " << round << ':' << endl;

        sort(marbles, marbles+N);
        for(int q: queries) {
            int *pos = lower_bound(marbles, marbles+N, q);
            if(*pos == q) {
                cout << q << " found at " << pos - marbles +1<< endl;
                // cout << "pos: " << pos << "  query: " << marbles << "   query end " << marbles+N << endl;
            } else {
                cout << q << " not found" << endl;
            }
        }

        cin >> N >> Q;
        round += 1;
    }
}
