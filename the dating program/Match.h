#ifndef MATCH_H
#define MATCH_H
#include<unordered_map>
#include <queue>
#include <memory>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<stack>
#include"charactors.h"
using namespace std;

class Match
{
    public:
        Match(ifstream& men_list, ifstream& women_list) {
            initializing(men_list,women_list);
        }
        virtual ~Match() {}
        //a debugging begin for no main charactor
        void debug_start(){
            int debug_count=1;
            while(men_pool.size()|| women_pool.size()){
                cout<<"Round "<<debug_count++<<" begins:"<<endl;
                make_invitations();
                matching_n_reset();
                cout<<'\n'<<endl;
            }
        }
        // this is the real begin.
        void kick_start(string player){

            istringstream in(player);
            add_player(in);
            do{
                make_invitations();

            }while(matching_n_reset());
            restore();
        }
        // a unit debugging to test the make_invitation and matching_n_reset function
        void debug_invitation(string player){
            istringstream in(player);
            add_player(in);
            make_invitations();
            matching_n_reset();
        }



    private:
        //this is the recycle bin for men that are removed once find his match
        stack<shared_ptr<Man>> missing_male_bin;

        //this is the data base of all the players.
        unordered_map<int,shared_ptr<Man>> men_pool;
        unordered_map<int,shared_ptr<woman>> women_pool;

        shared_ptr<woman> queen=make_shared<woman>(woman());
        //the function that find the most popular lady
        void find_queen(const shared_ptr<woman>& a);
        //add players into the pool
        void initializing(ifstream& men_list,ifstream& women_list);
        //Traverse men_pool to MAKE INVITATIONS
        void make_invitations();
        //reset all women's popularity and their selection of men when one round of matching ends
        void reset_women_pool();
        //the matching process and reset for the next round
        bool matching_n_reset();
        //the method that add the players into the pool
        void add_player(istream& is);
        //restore the pools after the main charactor find the other part, constructed to improve the performance
        //when handling a list of main charactor because otherwise you need to initialize a new pair of
        //women and men pool for intorducing every main charactor.
        void restore();

};

#endif // MATCH_H
