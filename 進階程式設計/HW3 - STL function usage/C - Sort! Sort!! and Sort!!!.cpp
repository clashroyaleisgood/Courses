#include <iostream>
#include <algorithm>
using namespace std;

class Compare
{
public:
    void SetDivisor(int d) { divisor_ = d; }
    // TODO: operator ()
    bool operator()(int lhs, int rhs) const;

private:
    int divisor_ = 1;
};
// ------------------------------------------------------------------
bool Compare::operator()(int lhs, int rhs) const
{
    // TODO
    int lhs_mod = lhs% divisor_,
        rhs_mod = rhs% divisor_;
    if(lhs_mod < rhs_mod)
        return true;
    else if(lhs_mod > rhs_mod)
        return false;

    if(lhs%2 == 0)          // 偶
    {
        if(rhs%2 == 0)
            return lhs < rhs;
        else
            return false;
    }
    else
    {
        if(rhs%2 == 0)
            return true;
        else
            return lhs > rhs;
    }
}
// ------------------------------------------------------------------
int main()
{
    constexpr size_t MaxDataSize = 10000;
    int M=0, N=0, data[MaxDataSize]={};
    while (cin >> N >> M)
    {
        cout << N << ' ' << M << endl;
        if (N==0 && M==0) break;

        Compare comp;
        comp.SetDivisor(M);

        for (int i=0; i<N; i+=1)
        {
            cin >> data[i];
        }
        sort(data, data+N, comp);
        for (int i=0; i<N; i+=1)
        {
            cout << data[i] << endl;
        }
    }
}

/*
15 3
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
0 0
*/
