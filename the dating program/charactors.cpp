#include"charactors.h"
#include<string>

void woman::eval(const shared_ptr<Man>& a ){
        int score_a=a->show_appearence()*expect_appearence+a->show_wealth()*expect_wealth+a->show_personality()*expect_personality;
        int score_b=loved_one->show_appearence()*expect_appearence+loved_one->show_wealth()*expect_wealth+loved_one->show_personality()*expect_personality;
        int alt_score_a=a->show_appearence()+a->show_wealth()+a->show_personality();
        int alt_score_b=loved_one->show_appearence()+loved_one->show_wealth()+loved_one->show_personality();
        if(score_a>score_b)
            loved_one=a;
        else if(score_a==score_b){
            if(alt_score_a>alt_score_b)
                loved_one=a;
            else if(alt_score_a==alt_score_b)
                loved_one=(a->show_id()<loved_one->show_id())?a:loved_one;
        }
}
istream& operator >>(istream& is, woman& w){
    string id;
    string wealth;
    string appearence;
    string personality;
    string expect_wealth;
    string expect_appearence;
    string expect_personality;

    getline(is,id,',');
    getline(is,appearence,',');
    getline(is,personality,',');
    getline(is,wealth,',');
    getline(is,expect_appearence,',');
    getline(is,expect_personality,',');
    getline(is,expect_wealth);


    if(is){
        w=woman(stoi(id),stoi(appearence),stoi(personality),stoi(wealth),stoi(expect_appearence),stoi(expect_personality),stoi(expect_wealth));

        if(w.expect_appearence+w.expect_personality+w.expect_wealth!=100)
            cout<<"Female No. "<<w.id<<" is corrupted."<<endl;
    }
    else
        w=woman();
    return is;
}
//Man::comparetype::comparetype(int e_appearence,int e_personality,int e_wealth):expect_appearence(e_appearence),expect_personality(e_personality),
  //                                                                              expect_wealth(e_wealth) {}
istream& operator >>(istream& is, Man& m){

    string id;
    string wealth;
    string appearence;
    string personality;
    string expect_wealth;
    string expect_appearence;
    string expect_personality;
    getline(is,id,',');
    getline(is,appearence,',');
    getline(is,personality,',');
    getline(is,wealth,',');
    getline(is,expect_appearence,',');
    getline(is,expect_personality,',');
    getline(is,expect_wealth);


    if(is){
        m=Man(stoi(id),stoi(appearence),stoi(personality),stoi(wealth),stoi(expect_appearence),stoi(expect_personality),stoi(expect_wealth));

        if(m.expect_appearence+m.expect_personality+m.expect_wealth!=100)
            cout<<"Male No. "<<m.id<<" is corrupted"<<endl;

    }
    else
        m=Man();
    return is;
}

	shared_ptr<woman> Man::dream_girl()  {
        if(dream_girls.empty()){
            cerr<<"I need to know all the girls first"<<endl;
        }

         shared_ptr<woman> a=dream_girls.top();
        while(!(a->is_avail())){
            if(dream_girls.empty()){
                cerr<<"No one fucking wants you!!"<<endl;
            }
            if(a->show_id()!=-1)
                girl_bin.push_back(a);
            dream_girls.pop();
            a=dream_girls.top();
        }
        return a;

    }
    void Man::restore_dream_girls(){
        if(!girl_bin.empty()){
            for(auto iter=girl_bin.begin();iter!=girl_bin.end();++iter){

                dream_girls.push(*iter);

            }
        }
        girl_bin.clear();

    }


    Man::Man():base(){}


    //carefult it's a max_heap or min_heap
    bool Man::comparetype::operator()(const shared_ptr<woman>& a,  const shared_ptr<woman>& b){
            int score_a=(a->show_personality()*expect_personality)+(a->show_appearence()*expect_appearence)+(a->show_wealth()*expect_wealth);
            int score_b=(b->show_personality()*expect_personality)+(b->show_appearence()*expect_appearence)+(b->show_wealth()*expect_wealth);
            int alt_score_a=a->show_appearence()+a->show_wealth()+a->show_personality();
            int alt_score_b=b->show_appearence()+b->show_wealth()+b->show_personality();
           // cout<<score_a<<"!"<<endl;
           // cout<<score_b<<endl;
           // cout<<a->show_personality()<<"!!!"<<endl;
            //cout<<expect_personality<<"@@@"<<expect_appearence<<"@@@"<<expect_wealth<<endl;
            if(score_a<score_b){

                return true;
            }
            else if(score_a==score_b){
                if(alt_score_a<alt_score_b){

                    return true;
                }
                else if(alt_score_a==alt_score_b){

                    return (a->show_id()>b->show_id())? true:false;
                }
                else{

                    return false;
                }
            }
            else{

                return false;
            }

        }

    void Man::build_heap(const unordered_map<int,shared_ptr<woman>>& women_pool){
        for(auto w:women_pool)
                dream_girls.push(w.second);
       // cout<<"No. "<<id<<" has met all girls."<<endl;

    }
