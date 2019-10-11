#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <cstdio>
#include <stdexcept>

bool do_decision();

enum LandType {U,C,R,J,Ndef};
constexpr int MaxPeopleNum = 4;
constexpr int MaxFineNum = 5;
constexpr int MaxLandNum = 20;
constexpr int MaxUpgradLV = 5;
class WorldPlayer;

class MapUnit
{
public:
    MapUnit() {}
    MapUnit(LandType type,int id,const std::string &name,int price,int fine):
        type_(type),id_(id),name_(name),price_(price),fine_(fine) {}
    virtual ~MapUnit(){}
//-----return private var-----
    LandType type()const{ return type_; }
    int LandId()const { return id_; }
    const std::string LandName()const { return name_; }
    int Price()const { return price_; }
    int WhoOwn()const { return who_own_; }
    const bool* WhoIsHere()const { return who_is_here_; }
    int HowManyPeople()const { return how_many_people_; }
//----set----
    void SetOwn(const int owner) { who_own_ = owner; }
    void Leave(const int index);
    void Enter(const int index);
    virtual void Reset();
//----what will do in this land----
    virtual void Event(WorldPlayer &p, int ind) = 0;
//virtual void Event(WorldPlayer &p, int ind);
    virtual int Fine()const { return fine_; }
    virtual void Print(int collectable_sum) const =0;
private:
    LandType type_ = Ndef;
    int id_ = -1;
    std::string name_ = "ndef";
    int price_ = -1;
    bool who_is_here_[MaxPeopleNum] = {};
    int how_many_people_ = 0;
protected:
    int who_own_ = -1;
    int fine_ = -1;
};

class Upgradable : public MapUnit
{
public:
    Upgradable() = default;
    virtual ~Upgradable(){}
    Upgradable(int id,const std::string &name,int price,int upgrade_cost,const int fine[]):
    MapUnit(U,id,name,price,-1),upgrade_cost_(upgrade_cost)
    {
        for(int i=0 ; i<MaxFineNum ; i+=1)
            fine_[i] = fine[i];
    }

    virtual void Event(WorldPlayer &p, int ind);
    virtual void Reset();
    virtual int Fine()const;
    virtual void Print(int collectable_sum)const;
private:
    int LV_ = 1;
    int upgrade_cost_ = -1;
    int fine_[MaxFineNum] = {} ;
};

class Collectable : public MapUnit
{
public:
    Collectable() = default;
    virtual ~Collectable(){}
    Collectable(int id,const std::string &name,int price,int fine):
        MapUnit(C,id,name,price,fine) {}

    virtual void Event(WorldPlayer &p, int ind);
    virtual void Print(int collectable_sum)const;
};

class RandomCost : public MapUnit
{
public:
    RandomCost() = default;
    virtual ~RandomCost(){}
    RandomCost(int id,const std::string &name,int price,int fine):
        MapUnit(R,id,name,price,fine) {}

    virtual void Event(WorldPlayer &p, int ind);
    virtual void Print(int collectable_sum)const;
};

class Jail : public MapUnit
{
public:
    Jail() = default;
    virtual ~Jail(){}
    Jail(int id,const std::string &name):
        MapUnit(R,id,name,-1,-1) {}

    virtual void Event(WorldPlayer &p, int ind);
    virtual void Print(int collectable_sum)const;
};

class WorldMap
{
public:
    void Add(Upgradable &U);
    void Add(Collectable &C);
    void Add(RandomCost &R);
    void Add(Jail &J);

    WorldMap() {}
    WorldMap(const WorldMap &) = delete;
    WorldMap & operator = (const WorldMap &) = delete;

    MapUnit* Land(int ind)const { return units_[ind]; }
    MapUnit* operator[](int index) { return (units_[index]); }
    const MapUnit* operator[](int index) const { return (units_[index]); }
    int num_of_unit()const {return now_;}
    virtual ~WorldMap();
private:
    MapUnit* units_[MaxLandNum]= {};
    int now_ = 0;
};

#endif // MAP_H
