#include <iostream>
#include <algorithm>
using namespace std;

class Card
{
    friend ostream & operator << (ostream &os, const Card &rhs);
    friend bool operator < (const Card &lhs, const Card &rhs);
public:
    void Set(char s, char d);
private:
    char suit_ = ' ', digit_ = ' ';
    int num_ = 0;
};
// ------------------------------------------------------------------
void Card::Set(char s, char d)
{
    // TODO
    suit_ = s;
    digit_ = d;
    num_ += 1;
}
// ------------------------------------------------------------------
bool operator < (const Card &lhs, const Card &rhs)
{
    // TODO
    //enum suit= {'C', 'D', 'S', 'H'};
    if(lhs.suit_ != rhs.suit_)
    {
        if(rhs.suit_ == 'H')
            return true;
        else if(lhs.suit_ == 'H')
            return false;
        else
            return lhs.suit_ < rhs.suit_;
    }
    else
    {
        char cmp[]= "23456789TJQKA";
        int ind1, ind2;
        for(int i=0; i<13; ++i)
        {
            if(lhs.digit_ == cmp[i])
                ind1 = i;
            if(rhs.digit_ == cmp[i])
                ind2 = i;
        }
        return ind1 < ind2;
    }
}
// ------------------------------------------------------------------
ostream & operator << (ostream &os, const Card &card)
{
    os << card.suit_ << card.digit_;
    return os;
}
// ------------------------------------------------------------------
int main()
{
    char start = ' ';
    while (cin >> start && start!='#')
    {
        constexpr char position[] = "NESW";
        constexpr size_t NumPeople = sizeof(position)-1;

        // determine the first player to get cards
        int j = 0;
        for (size_t i=0; i<NumPeople; i+=1)
        {
            if (position[i]==start)
            {
                j = (i+1)%NumPeople;
                break;
            }
        }

        // read in and distribute cards
        constexpr size_t NumCards = 13;
        Card cards[NumPeople][NumCards];
        for (size_t i=0; i<NumPeople*NumCards; i+=1)
        {
            char s, n;
            cin >> s >> n;
            cards[j][i/NumPeople].Set(s, n);
            j = (j+1)%NumPeople;
        }

        // sort cards of every player
        for (size_t j=0; j<NumPeople; j+=1)
        {
            sort(cards[j], cards[j]+NumCards);
        }

        // find the first player to display
        for (size_t i=0; i<NumPeople; i+=1)
        {
            if (position[i]=='S')
            {
                j = i;
                break;
            }
        }

        // display cards of every player
        for (size_t t=0; t<NumPeople; t+=1, j=(j+1)%NumPeople)
        {
            cout << position[j] << ':';
            for (size_t i=0; i<NumCards; i+=1)
            {
                cout << ' ' << cards[j][i];
            }
            cout << endl;
        }
    }
}
/*
N
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
S
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
#
*/
