#include <iostream>
#include "charactors.h"
#include "Match.h"
#include <fstream>
#include <random>
using namespace std;

int main()
{
    ifstream player_list("players.txt");
    string line;
    //getline(player_list,line);
    //getline(player_list,line);
    //the_match.kick_start(line);
    //the_match.debug_invitation(line);
    //male1 and female1 file are small testbech for debug.
    ifstream men_list("male.txt");
    ifstream women_list("female.txt");
    Match the_match(men_list,women_list);
    while(getline(player_list,line)){
        //the_match.debug_start();
        the_match.kick_start(line);
   }

    cout << "Hello world!" << endl;
    return 0;
}
