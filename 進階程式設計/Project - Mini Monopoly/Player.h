#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "Map.h"
#include <string>
#include <stdlib.h>
using std::string;

class Player
{
public:
    const string& name() const { return name_; }
    const int& money() const { return money_; }
    const int& unit() const { return unit_; }
    const int& c_unit() const { return c_unit_; }
    const int& position() const { return position_; }
    bool is_alive() const { return alive_; }

    void set_name(const string &s) { name_ = s; alive_ = true; }
    void set_position(const int& i) { position_ = i; }
    void add_unit() { unit_ += 1; }
    void add_c_unit() { c_unit_ += 1; }

    Player& operator+=(const int& i) { money_+=i; return *this; }
    Player& operator-=(const int& i) { money_-=i; return *this; }

    void dead() { alive_ = false; }

    bool jail_state() const { return jail_; }
    void swap_jail() { jail_ = !jail_; }
    bool can_dice() const { return jail_state(); }

private:
    string name_ = "";
    int money_ = 30000;
    int unit_ = 0;
    int c_unit_ = 0;
    int position_ = 0;
    bool alive_ = false;
    bool jail_ = false;
};

class WorldPlayer
{
public:
    WorldPlayer(const int& num_of_player, WorldMap& maps):total_player_(num_of_player), maps_(maps) {};

    void moving(const int &index, const int &dice);
    bool buy_land(const int &index);
    bool add_player(const string &s)
    {
        if (siz_ >= total_player_)
            return false;
        players_[siz_].set_name(s);
        siz_ += 1;
        return true;
    }


    const Player& operator[](int index) const
    {
        if (index < total_player_)
            return players_[index];
        else
            exit(-1);
    }
    Player& operator[](int index)
    {
        if (index < total_player_)
            return players_[index];
        else
            exit(-1);
    }
    const int& num_of_player() const { return siz_; }
    int total_player() const { return total_player_; }
    void dead(const int& index)
    {
        --siz_;
        players_[index].dead();
        for (int i = 0; i < maps_.num_of_unit(); ++i)
        {
            if (maps_[i]->WhoOwn() == index)
            {
                maps_[i]->Reset();
            }
        }
    }
    void fine(const int &index, int cost);
    void get_price(const int &index, int price);
    int get_current_dice() const { return current_dice_; }
private:
    int total_player_ = 0;
    int siz_ = 0;
    int current_dice_ = 0;
    Player players_[MaxPeopleNum];
    WorldMap& maps_;
};

#endif // PLAYER_H_INCLUDED
