#include <iostream>
#include <vector>
#include <cmath>
#include "json.hpp"
#include "priorityqueue.h"
#include "teamdata.h"

/*std::pair<int, int> pickTeams(Teamdata teamlist)
{
    double goal = 50.0;
    std::pair<int, int> team;

    for(auto &wp : teamlist.winPercentages_) //rewrite to normal for loop later
        {
        if(std::abs)

        }

}*/

int main(int argc, char** argv) {
    Teamdata team(argv[1]);
    PriorityQueue teamq(team.getSize());

    nlohmann::json teamlist;
    teamlist["teams"];
    while(!teamq.isEmpty())
    {
        auto min = teamq.min();
        int player1 = min.second.first;
        int player2 = min.second.second;
        teamlist.at("teams").push_back(min.second);
    }

    for(int i = 0; i < team.numPlayers(); i++)
    {
        for(int j = 0; j < team.numPlayers(); j++)
        {
            double wp = team.winPercentages(i, j);
            if(wp > 50.00)
            {
                wp = 50.00 - wp;
            }
            if(wp < 50.00)
            {
                wp = wp - 50.00;
            }
            KeyValuePair node = std::make_pair(wp, std::make_pair(i,j));
            teamq.insert(node);
        }
    }

    for (auto i = teamq.size(); i > 0; --i)
    {
        auto player = teamq.getValue(i);
        auto p1 = player.first;
        auto p2 = player.second;
        if( p1 == player1 || p1 == p2 || p2 == player2 || p2 == p2)
        {
            teamq.removeNode(i);
        }
    }


}
