#include "Player.h"
void WorldPlayer::moving(const int &index, const int &dice)
{
    current_dice_ = dice;
    int position = players_[index].position();
    int new_position = (position+dice) % maps_.num_of_unit();

    players_[index].set_position(new_position);
    maps_[position]->Leave(index);
    maps_[new_position]->Enter(index);
}

bool WorldPlayer::buy_land(const int &index)
{
    int position = players_[index].position();
    if ( maps_[position]->WhoOwn() == -1 ) // no one buy
    {
        if ( players_[index].money() >= maps_[position]->Price() ) // have enough money
        {
            std::cout<<players_[index].name()<<", do you want to buy "<<maps_[position]->LandName()<<"? (1:Yes[default] / 2:No) ...>";
            if(do_decision())
            {
                if ( maps_[position]->type() == C )
                {
                    players_[index].add_c_unit();
                }
                players_[index].add_unit();
                maps_[position]->SetOwn(index);
                players_[index] -= maps_[position]->Price();
                std::cout<<"You pay $"<<maps_[position]->Price()<<" to buy "<<maps_[position]->LandName()<<std::endl;
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}
void WorldPlayer::fine(const int &index, int cost)
{
    players_[index] -= cost;
}

void WorldPlayer::get_price(const int &index, int price)
{
    players_[index] += price;
}

