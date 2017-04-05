#ifndef CHARACTORS_H
#define CHARACTORS_H
#include<queue>
#include<memory>
#include<vector>
#include<iostream>
#include<unordered_map>
#include<functional>
#include<list>
using namespace std;
//consider it as a general "human" without regarding of sex
class base
{
friend class Match;
public:
    base(int id,int appearence,int personality,int wealth,int e_face,int e_character,int e_wealth)
    :id(id),appearence(appearence),personality(personality),wealth(wealth),expect_appearence(e_face),
    expect_personality(e_character),expect_wealth(e_wealth) { availability=true;}
    base()=default;
    virtual ~base() {}
    int show_id() {return id;}
    int show_appearence() const {return appearence;}
    int show_wealth() const {return wealth;}
    int show_personality() const {return personality;}
    bool is_avail() const {return availability;}
protected:
    int id=101;
    int appearence=0;
    int personality=0;
    int wealth=0;


    int expect_appearence=0;
    int expect_personality=0;
    int expect_wealth=0;
    bool availability=true;



};


class woman;

class Man: public base
{
friend class Match;
friend istream& operator >>(istream& is, Man& w);
public:
    Man(int id,int appearence,int personality,int wealth,int e_appear,int e_personality,int e_wealth)
        :base(id,appearence,personality,wealth,e_appear,e_personality,e_wealth),dream_girls(comparetype{this->expect_appearence,this->expect_personality,this->expect_wealth})
    {}

    Man(int id,int appearence,int personality,int wealth,int e_appear,int e_personality,int e_wealth,
         const unordered_map<int,shared_ptr<woman>>& women_pool)
        :base(id,appearence,personality,wealth,e_appear,e_personality,e_wealth),dream_girls(comparetype{this->expect_appearence,this->expect_personality,this->expect_wealth})
    {
        build_heap(women_pool);
    }

    Man();
    //for batch initializing the max heap
    void meet_women(const unordered_map<int,shared_ptr<woman>>& girl) { build_heap(girl);}
    //for just add one new girl into the heap
    void new_girl(const shared_ptr<woman>& girl)    {dream_girls.push(girl);}

    ~Man() {}
    //return the max
     shared_ptr<woman> dream_girl();
private:
    // the custom compare method
    struct comparetype{

    //comparetype(int e_appearence,int e_personnality,int e_wealth);
    bool operator () (const shared_ptr<woman>& a,  const shared_ptr<woman>& b);
        //return m->Mycompare(a,b);

    int expect_appearence;
    int expect_personality;
    int expect_wealth;
    };
   // bool Mycompare(const shared_ptr<woman>& a,  const shared_ptr<woman>& b);
    // main max heap data structrue that return the most interested girl according the
    //the rating method of the spec.
    //PAY ATTENTION TO HOW YOU CONSTRUCT THE COMPARETYPE CLASS
    priority_queue<shared_ptr<woman>,vector<shared_ptr<woman>>,comparetype>
    dream_girls;
    //the recycle bin for the restore process in match class to collect the dream girl
    //once it is removed from the heap.
    //POTENTIAL OPTIMIZATION:it might be optimized by being used in the matching making process
    //because it is collected in sorted order and it would be a waste to just add them back to the heap
    //every time. So I defind it as linked list rather than stack for further update.
    //the main problem is when add a new female main characror, it main need some handling as to wether
    //add it into the heap or the already sorted list and remove it after the match.
    list<shared_ptr<woman>> girl_bin;
    // add the girls back
    void restore_dream_girls();
    //fucntion to build the dream girl heap
    void build_heap(const unordered_map<int,shared_ptr<woman>>& girl);
};



class woman : public base
{
friend class Match;
friend istream& operator >>(istream& is, woman& w);

public:
	woman(int id,int appearence,int personality,int wealth,int e_appear,int e_personality,int e_wealth)
        :base(id,appearence,personality,wealth,e_appear,e_personality,e_wealth),popularity(0)
    {}
    woman()=default;
	~woman(){}
	int check_popularity() const {return popularity;}
	//evaluation of the male player who invite this girl according to the spec.
	void meet(const shared_ptr<Man>& a) {eval(a);}
	//reset after each round
	void reset( const shared_ptr<Man>& dummy)  {popularity=0;loved_one=dummy;}
private:
    //number of male who invite this girl
    int popularity=0;
    //the one that match this girl's requirement best
	shared_ptr<Man> loved_one;
    //the process to select "the one"
	void eval(const shared_ptr<Man>& a );

};
#endif // CHARACTORS_H
