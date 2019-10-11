#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <math.h>
#include <numeric>

using namespace std;
struct node
{
    int x=0, y=0;
    void set() { cin >> x >> y; };
};
double dist(node &lhs, node &rhs)
{
    return pow(pow(lhs.x - rhs.x, 2) + pow(lhs.y - rhs.y, 2), 0.5);
}
ostream & operator << (ostream &os, const node &n)
{
    os << " (" << n.x << "," << n.y << ") ";
    return os;
}

void put_line(int n)
{
    cout << "**********************************************************" << endl;
    cout << "Network #" << n << endl;
}
int main()
{
    int N=0, round = 1;
    cin >> N;
    while(N)
    {
        node nodes[N];
        for(int i=0; i<N; ++i) {
            nodes[i].set();
        }

        int order[N];
        iota(order, order+N, 0);
        int perfect_order[N] = {};
        double min_dist= 999999999999999999;
        do
        {
            double temp_dist = 0;
            for(int i=0; i<N-1; ++i)
            {
                temp_dist += dist(nodes[order[i]], nodes[order[i+1]] );
            }
            if(temp_dist < min_dist)
            {
                min_dist = temp_dist;
                copy(order, order+N, perfect_order);
            }

/*
            for(int e: order) {
                cout << nodes[e];
            }
            cout << temp_dist << endl;
*/
        } while(next_permutation(order, order+N));
/*
        cout << "perfect order: ";
        for(int e: perfect_order)
        {
            cout << nodes[e];
        }
*/
        put_line(round);

        for(int i=0; i<N-1; ++i)
        {
            int ind_1= perfect_order[i], ind_2= perfect_order[i+1];
            cout << "Cable requirement to connect" << nodes[ind_1] << "to" << nodes[ind_2] << "is ";
            cout << setiosflags(ios::fixed) << setprecision(2) << dist(nodes[ind_1], nodes[ind_2]) + 16 << " feet." << endl;
        }
        cout << "Number of feet of cable required is ";
        cout << setiosflags(ios::fixed) << setprecision(2) << min_dist + 16*(N-1) << "." << endl;


        cin >> N;
        round += 1;
    }
}
/// (111,84)  (43,116)  (38,101)  (28,62)  (55,28)  (5,19) 225.446
/*

    node N[3];
    int order[3] = {0, 1, 2};
    for(int i=0; i<3; ++i)
    {
        N[i].set(i, i+1);
    }

    do
    {
        for(int e: order) {
            cout << N[e].to_str();
        }
        cout << endl;
    } while(next_permutation(order, order+3));
*/
