#include "Match.h"

void Match::find_queen(const shared_ptr<woman>& a){
    int pa=a->check_popularity();
    int pb=queen->check_popularity();
    int alt_a=a->show_appearence()+a->show_personality()+a->show_wealth();
    int alt_q=queen->show_appearence()+queen->show_personality()+queen->show_wealth();
    if(pa>pb)
        queen=a;
    else if(pa==pb){
        if(alt_a>alt_q)
            queen=a;
        else if(alt_a==alt_q)
            queen= a->show_id()<queen->show_id()?a:queen;
    }
}

void Match::initializing(ifstream& men_list,ifstream& women_list){
    shared_ptr<Man> mdummy=make_shared<Man>(Man());

    while(women_list){
        woman w;
        women_list>>w;
        //cout<<w.appearence<<" "<<w.personality<<" "<<w.wealth<<endl;
        //cout<<w.loved_one->show_id()<<endl;
        if(w.show_id()!=101){
            w.loved_one=mdummy;
            women_pool[w.show_id()]=make_shared<woman>(w);
        }
    }

    while(men_list){
        Man m;
        men_list>>m;
        //cout<<m.appearence<<" "<<m.personality<<" "<<m.wealth<<endl;
        //cout<<"Male No. "<<m.show_id()<<" has met all the girls."<<endl;
        if(m.show_id()!=101){
            m.meet_women(women_pool);
            //cout<<m.dream_girls.size()<<endl;
            men_pool[m.show_id()]=make_shared<Man>(m);
        }
    }
    //cout<<"Initialization complete. "<<men_pool.size()<<" "<<women_pool.size()<<endl;
}

void Match::make_invitations() {

    for(auto a:men_pool ){
        shared_ptr<woman> w=(a.second)->dream_girl();
        w->meet(a.second);
        ++(w->popularity);
        find_queen(w);

    }
    //cout<<queen->show_id()<<endl;
}

void Match::reset_women_pool(){
    shared_ptr<Man> dummy=make_shared<Man>(Man());
    //int w_size =women_pool.size();
    for(auto a:women_pool){
       // cout<<(a.second)->show_id()<<endl;
        (a.second)->reset(dummy);
    }
    queen=make_shared<woman>(woman());
}

bool Match::matching_n_reset(){
    shared_ptr<Man> the_one=queen->loved_one;
    if(queen->show_id()==-1){
        cout<<"Congratulation: you just found your man. Male:"<<the_one->show_id()<<endl;
        queen->availability=false;
        women_pool.erase(-1);
        return false;
    }
    if(the_one->show_id()==-1){
        cout<<"Congratulation: you just found your woman. Female:"<<queen->show_id()<<endl;
        men_pool.erase(-1);
        return false;
    }
    // this is to remove the couple from futher matching
    queen->availability=false;
    //the_one->availability=false;
    //cout<<the_one->show_id()<<" "<<queen->show_id()<<" : "<<queen->check_popularity()<<endl;

    missing_male_bin.push(the_one);
    men_pool.erase(the_one->show_id());

    if(men_pool.find(the_one->show_id())!=men_pool.end())
        cout<<"erase failed."<<endl;

    reset_women_pool();
    return true;
}

 void Match::add_player(istream& is){
    string wealth;
    string appearence;
    string personality;
    string expect_wealth;
    string expect_appearence;
    string expect_personality;
    string sex;
    getline(is,sex,',');
    getline(is,appearence,',');
    getline(is,personality,',');
    getline(is,wealth,',');
    getline(is,expect_appearence,',');
    getline(is,expect_personality,',');
    getline(is,expect_wealth);
    bool the_sex=stoi(sex);
    if(is){
    // the basic idea is to remove a random player in the pool, store it in the missing ptr and add the player in the -1 position
        if(the_sex){
            int id=rand()%100;
            //For debug, id=15 or don't erase the random player.
            //int id=15;
            missing_male_bin.push(men_pool[id]);
            men_pool.erase(id);
            shared_ptr<Man> b=make_shared<Man>(Man(-1,stoi(appearence),stoi(personality),stoi(wealth),
                                                   stoi(expect_appearence),stoi(expect_personality),stoi(expect_wealth)));
            men_pool[-1]=b;

            b->meet_women(women_pool);
            if(b->dream_girls.size()==100)
                cout<< "Player "<<" met all the girls."<<endl;
            if(b->expect_appearence+b->expect_personality+b->expect_wealth==100)
                cout<<"Player "<<" created. "<<endl;
            else
                cout<<"Player's data is corrupted"<<endl;

        }
        else{
            int id=rand()%100;
            //for debug id=99
            //int id=99;
            women_pool[id]->availability=false;
            shared_ptr<woman> b=make_shared<woman>(woman(-1,stoi(appearence),stoi(personality),stoi(wealth),
                                                   stoi(expect_appearence),stoi(expect_personality),stoi(expect_wealth)));
            women_pool[-1]=b;

            b->loved_one=make_shared<Man>(Man());
            //cout<<women_pool[id]->show_id()<<endl;

            //updata men's dream girl list
            for(auto &a: men_pool)
                (a.second)->new_girl(b);
            //if(men_pool[0]->dream_girls.size()==101)
            cout<<"Player is introduced. "<<endl;

            if(b->expect_appearence+b->expect_personality+b->expect_wealth==100)
                cout<<"Player created. "<<endl;
            else
                cout<<"Player's data is corrupted"<<endl;
        }
    }
    else{
        cout<<"Failed to add player into the pool";
    }
}

void Match::restore(){
    for(auto &a:women_pool){
        if((a.second)->show_id()!=-1)
            (a.second)->availability=true;
        //women_pool[i]->reset(make_shared<Man>(Man()));
    }
    while(!missing_male_bin.empty()){
        auto a=missing_male_bin.top();
        men_pool[a->show_id()]=a;
        missing_male_bin.pop();
    }
    if(men_pool.size()!=100)
            cout<<"Restore failed."<<men_pool.size()<<endl;
    else{
        for(auto &a:men_pool){
            (a.second)->restore_dream_girls();

        }
    }
    reset_women_pool();
    cout<<"*****************************"<<endl;

}
