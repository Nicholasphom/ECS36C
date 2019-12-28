#include "teamdata.h"
#include <fstream>
#include "json.hpp"

int TeamData::numPlayers() const
{
    return numPlayers_;
}

TeamData::TeamData(std::string filename)
{
    std::ifstream fileread;
    fileread.open(filename.c_str());
	if (fileread.fail()) {
		std::cerr << "Error";
	}
	nlohmann::json jsonobj;
	if (fileread.is_open()) {
		fileread >> jsonobj;
	}

    numPlayers_ = jsonobj["metadata"]["numPlayers"];
    int queuesize = (numPlayers_ - 1) * (numPlayers_) * 0.5;
    for(int i = 0; i < queuesize; i++)
        {
        int p1 = itr.value()["playerOne"];
        int p2 = itr.value()["playerTwo"];
        double wp = itr.value()["winPercentage"];
        winPercentages_[p1][p2] = wp;
        }
}
