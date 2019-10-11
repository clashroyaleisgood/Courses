#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "Player.h"
#include "Map.h"

using namespace std;
constexpr bool DEBUGGER = false;

void refresh_page(int round, const WorldMap &worldmap, const WorldPlayer &worldplayer, int map_size);
int dicing();

int main()
{
    srand(time(NULL));
    const string DEFAULT_NAMES[4]{"A-Tu", "Little-Mei", "King-Baby", "Mrs.Money"};

/********************************** read files *******************************************/
    WorldMap worldmap;

    int place_counter = 0;
    ifstream file("map.dat");

    if(!file) {
        cout << "can\'t find map.dat" << endl;
        return 0;
    }

    while(file.peek() != EOF) {
        string temp;
        getline(file, temp);
        //cout << "Get: \t\t" << temp << endl;
        if(temp.size() == 0)    /// 濾掉空行
            continue;

        stringstream place(temp);

        char type;
        string name;
        place >> type >> name;
        if(name.size() > 10)
            name.resize(10);        ///名字最多 10 個字

        switch(type)    /************ constuct here ********************/
        {
        case 'U':
        {
            int price = 0, upgrade_cost = 0 , fine[5] = {};
            place >> price >> upgrade_cost;
            for(int i=0; i<5; ++i)
                place >> fine[i];

            if(DEBUGGER) {
                cout << "type U > ";
                printf("%10s", name.c_str());
                cout << " > " << price << " > " << upgrade_cost << " > ";
                for(int e: fine)
                    cout << e << " ";
                cout << endl;
            }
            /// construct here
            Upgradable u(place_counter, name, price, upgrade_cost, fine);
            worldmap.Add(u);
        }
        break;
        case 'C':
        {
            int price, fine;
            place >> price >> fine;
            if(DEBUGGER) {
                cout << "type C > ";
                printf("%10s", name.c_str());
                cout << " > " << price << " > " << fine << endl;
            }
            /// construct here
            Collectable c(place_counter, name, price, fine);
            worldmap.Add(c);
        }
        break;
        case 'R':
        {
            int price, fine;
            place >> price >> fine;
            if(DEBUGGER) {
                cout << "type R > ";
                printf("%10s", name.c_str());
                cout << " > " << price << " > " << fine << endl;
            }
            /// construct here
            RandomCost r(place_counter, name, price, fine);
            worldmap.Add(r);
        }
        break;
        case 'J':
        {
            if(DEBUGGER) {
                cout << "type J > ";
                printf("%10s", name.c_str());
                cout << endl;
            }
            /// construct here
            Jail j(place_counter, name);
            worldmap.Add(j);
        }
        break;
        }

        string check;
        place >> check;
        if(check.size() != 0) {
            cout << endl << "Invalid map format : " << temp << endl;
            return 0;
        }
        place_counter += 1;
    }

    file.close();
    /****************** 如果建築物是奇數個就要退出 ***********************/
    if(place_counter %2 !=0 || place_counter > MaxLandNum) {
        cout << endl << "Invalid map count: " << place_counter << endl;
        return 0;
    }

    if(DEBUGGER) {
        system("pause");
        system("cls");
    }
/********************************** player count *****************************************/
    size_t player_sum=0;
    cout << "How many players?(Maximum:4)...>";
    cin >> player_sum;
    cin.get();
    if(player_sum == 0)
        player_sum = 1;
    else if(player_sum > 4)
        player_sum = 4;
    WorldPlayer worldplayer(player_sum, worldmap);
/********************************** player names/construct *******************************/
    for(size_t i=0; i<player_sum; ++i)
    {
        string name;
        cout << "Please input player " << i+1 << "\'s name (Default: " << DEFAULT_NAMES[i] << ")...>";
        getline(cin, name);
        if(name.size() == 0)
            name = DEFAULT_NAMES[i];
        else if(name.size() > 15)
            name.resize(15);    /// 上限 15 個字
        // else pass
        if(DEBUGGER)
            cout << "get: " << name << endl;
        worldplayer.add_player(name);
        /****************************** construct here ****************************/
    }

/****************************************** game routine ************************************/
    for(int i=0; i<worldplayer.total_player(); ++i)
        worldmap[0]->Enter(i);

    while(worldplayer.num_of_player() != 1)
    {
        for(int round=0; round<worldplayer.total_player(); ++round) // round 就是當下進行操作的遊戲者
        {
            const Player &round_player = worldplayer[round];
            if(!round_player.is_alive())
                continue;
            if(worldplayer.total_player() == 1)
                break;

            /************************** refresh page ********************************/
            refresh_page(round, worldmap, worldplayer, place_counter);

///---- In Jail or not ---- can not dice and move------------------------
            if(!round_player.can_dice())
            {
                /************************** player before dice ********************************/
                cout << round_player.name() << ", your action? (1:Dice [default] / 2:Exit)...>";
                if(do_decision())    /// 規則應該是這樣沒錯
                    ;//cout << "you choose " << action << endl;
                else
                    return 0;

                /****************************** move player ******************************/
                int dice_result = dicing();
                worldplayer.moving(round, dice_result);

                /************************** refresh page ********************************/
                refresh_page(round, worldmap, worldplayer, place_counter);
            }
///-----------------------------------------------------------------------
            ///----Event----
            worldmap[round_player.position()]->Event(worldplayer, round);
            /************************************** end ***********************************/
            system("pause");
        }
    }
    cout << "the winner is determined!" << endl;
    system("pause");
}

/************************************ end/ function implementation *****************************************/
void formatting_person(bool arrow, int index, const string &name, int money, int building_count);
void formatting_mapunit_before(const bool whos[], int player_sum, int index, const string &name, int own_by); // == + [] + name
void formatting_person(bool arrow, int index, const Player &p);
void formatting_mapunit(int index, int player_sum, const MapUnit *m, int collectable_sum);

void refresh_page(int round, const WorldMap &worldmap, const WorldPlayer &worldplayer, int map_size)
{
    system("cls");
    /********************************** show map **********************************/
    for(int i=0; i<map_size/2; ++i) {
        int back = map_size -i-1;

        formatting_mapunit(i, worldplayer.total_player(), worldmap[i], worldplayer[worldmap[i]->WhoOwn()].c_unit());
        formatting_mapunit(back, worldplayer.total_player(), worldmap[back], worldplayer[worldmap[back]->WhoOwn()].c_unit());
        cout << endl;
    }
    cout << endl;
    /******************************* show players *********************************/
    for(int i=0; i<worldplayer.total_player(); ++i) {
        if(worldplayer[i].is_alive())
            formatting_person( i==round, i, worldplayer[i]);
    }
    cout << endl;
}
void formatting_person(bool arrow, int index, const Player &p)
{
    formatting_person(arrow, index, p.name(), p.money(), p.unit());
}
void formatting_mapunit(int index, int player_sum, const MapUnit *m, int collectable_sum)
{
    formatting_mapunit_before(m->WhoIsHere(), player_sum, index, m->LandName(), m->WhoOwn());
    m->Print(collectable_sum);  /// formatting_mapunit_after
}
void formatting_person(bool arrow, int index, const string &name, int money, int building_count)
{
    if(arrow)
        cout << "=>";
    else
        cout << "  ";
    //-------------------
    printf("[%d]  %15s  $%d with %d units\n", index, name.c_str(), money, building_count);
}
void formatting_mapunit_before(const bool whos[], int player_sum, int index, const string &name, int own_by = -1)
{
    cout << "=";
    for(int i=0; i<player_sum; ++i)
        if(whos[i])
            cout << i;
        else
            cout << " ";
    cout << "=  ";
    //--------------------------------------
    printf("[%02d]", index);
    //cout << "[" << index << "]";

    printf("%10s ", name.c_str());
    if(own_by == -1)
        cout << "    ";
    else
        cout << "{" << own_by << "} ";
}

int dicing()
{
    return rand() % 6 + 1;
}

