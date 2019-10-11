#include "Map.h"
#include "Player.h"

using namespace std;
//----decision----
bool do_decision()
{
    string action;
    getline(std::cin, action);
    if(action.size()==0 || action[0] != '2')
        return true;
    else
        return false;
}

//----MapUnit----
void MapUnit::Leave(const int index)
{
    who_is_here_[index] = false;
    how_many_people_ -= 1;
}
void MapUnit::Enter(const int index)
{
    who_is_here_[index] = true;
    how_many_people_ += 1;
}

void MapUnit::Reset()
{
    who_own_ = -1;
}

//----Upgradable----
void Upgradable::Event(WorldPlayer &p, int ind)
{
    if(p.buy_land(ind)){}
    else if(WhoOwn() == ind) // upgrade or not
    {
        if(p[ind].money() >= upgrade_cost_ && LV_ != MaxUpgradLV)
        {
            cout<<p[ind].name()<<", do you want to upgrade "<<LandName()<<"? (1:Yes[default] / 2:No) ...>";
            if(do_decision())
            {
                LV_ += 1;
                p.fine(ind,upgrade_cost_);
                cout<<"You pay $"<<upgrade_cost_<<" to upgrade "<<LandName()<<" to Lv."<<LV_<<std::endl;
            }
            else
                return ;
        }
        else
            return ;
    }
    else if(WhoOwn() != -1) // fine
    {
        cout<<p[ind].name()<<", you must pay $"<<Fine()<<" to Player "<<WhoOwn()<<" ( "<<p[WhoOwn()].name()<<" )"<<endl;
        if(p[ind].money() >= Fine())
        {
            p.fine(ind, Fine());
            p.get_price(WhoOwn(), Fine());
        }
        else
        {
            cout<<p[ind].name()<<" is bankrupt!";
            p.get_price(WhoOwn(),p[ind].money());
            p.dead(ind);
        }
    }
}

void Upgradable::Reset()
{
    who_own_ = -1;
    LV_ = 1;
}

int Upgradable::Fine()const
{
    return fine_[LV_-1];
}
void Upgradable::Print(int collectable_sum)const
{
    if(WhoOwn() == -1)   ///buyable
        printf("B$ %4d   ", Price());
    else if(LV_ != 5)   ///upgradable
        printf("U$ %4d L%d", upgrade_cost_, LV_);
    else
        printf("L5        ");
    cout << "    ";
}
//----Collectable-----
void Collectable::Event(WorldPlayer &p, int ind)
{
    if(!p.buy_land(ind))
    {
        if(WhoOwn() != -1)
        {
            cout<<p[ind].name()<<", you must pay $"<<Fine()<<" to Player "<<WhoOwn()<<" ( "<<p[WhoOwn()].name()<<" )"<<endl;
            if(p[ind].money() >= Fine())
            {
                p.fine(ind,p[WhoOwn()].c_unit() * Fine());
                p.get_price(WhoOwn(),p[WhoOwn()].c_unit() * Fine());
            }
            else
            {
                cout<<p[ind].name()<<" is bankrupt!";
                p.get_price(WhoOwn(),p[ind].money());
                p.dead(ind);
            }
        }
    }
}
void Collectable::Print(int collectable_sum)const
{
    if(WhoOwn() == -1)   ///buyable
        printf("B$ %4d   ", Price());
    else
        printf("x%d        ", collectable_sum);
    cout << "    ";
}
//----Randomcast----
void RandomCost::Event(WorldPlayer &p, int ind)
{
    if(!p.buy_land(ind))
    {
        if(WhoOwn() != -1)
        {
            cout<<p[ind].name()<<", you must pay $"<<Fine()<<" to Player "<<WhoOwn()<<" ( "<<p[WhoOwn()].name()<<" )"<<endl;
            if(p[ind].money() >= Fine())
            {
                p.fine(ind,p.get_current_dice() * Fine());
                p.get_price(WhoOwn(),p.get_current_dice() * Fine());
            }
            else
            {
                cout<<p[ind].name()<<" is bankrupt!";
                p.get_price(WhoOwn(),p[ind].money());
                p.dead(ind);
            }
        }
    }
}
void RandomCost::Print(int collectable_sum)const
{
    if(WhoOwn() == -1)   ///buyable
        printf("B$ %4d   ", Price());
    else
        printf("?         ");
    cout << "    ";
}
//----Jail----
void Jail::Event(WorldPlayer &p, int ind)
{
    p[ind].swap_jail();
    if(p[ind].jail_state())
        cout<<p[ind].name()<<", you are in Jail ( "<<LandName()<<" ) now ! you can not do anything!"<<endl;
    else
        cout<<p[ind].name()<<", you are released from Jail ( "<<LandName()<<" ) "<<endl;
}
void Jail::Print(int collectable_sum)const
{
    cout << "J$            ";
}
//----wordmap----
WorldMap::~WorldMap()
{
    for(int i=0; i<now_; ++i)
        delete units_[i];
}

void WorldMap::Add(Upgradable &U)
{
    MapUnit *p=nullptr;
    try
    {
        p = new Upgradable(U);
        units_[now_] = p;
        now_+=1;
    }
    catch (bad_alloc &exp)
    {
        cout << "fail new" << endl;
    }
}

void WorldMap::Add(Collectable &C)
{
    MapUnit *p=nullptr;
    try
    {
        p = new Collectable(C);
        units_[now_] = p;
        now_+=1;
    }
    catch (bad_alloc &exp)
    {
        cout << "fail new" << endl;
    }
}

void WorldMap::Add(RandomCost &R)
{
    MapUnit *p=nullptr;
    try
    {
        p = new RandomCost(R);
        units_[now_] = p;
        now_+=1;
    }
    catch (bad_alloc &exp)
    {
        cout << "fail new" << endl;
    }
}

void WorldMap::Add(Jail &J)
{
    MapUnit *p=nullptr;
    try
    {
        p = new Jail(J);
        units_[now_] = p;
        now_+=1;
    }
    catch (bad_alloc &exp)
    {
        cout << "fail new" << endl;
    }
}
