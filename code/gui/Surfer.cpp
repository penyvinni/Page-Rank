#include "Surfer.hpp"
#define ITER 100

using namespace std;

Surfer::Surfer(int pages) : matrix(pages, pages) {}

Surfer::~Surfer() {}

string Surfer::Surfing(int visitors,double DAMPING_FACTOR)
{
    string res="";
    this->reset_visits();
    mt19937 mt(std::chrono::high_resolution_clock().now().time_since_epoch().count());
    uniform_int_distribution<int> go(0, this->rows - 1); //0-4
    uniform_real_distribution<double> ran(0.0, 1.0);
    //Damping_Factor--><=0.85-->Γειτονική ιστοσελίδα.
    //Damping_Factor-->>0.85-->Τυχαία ιστοσελίδα.
    int *startingpoints = new int[visitors];  //πινακας για την τοποθετηση των επισκεπτων στην αρχη
    for (int i = 0; i < visitors; i++)  
    {
        startingpoints[i] = go(mt);
        cout << "Visitor " << i + 1 << " is placed in Web Page " << startingpoints[i] << endl;
        res+="Visitor "+to_string(i+1)+" is placed in Web Page "+to_string(startingpoints[i])+"\n";
        this->visits[startingpoints[i]]++;  // επειδη θελω τη σελιδα βαζω το stra που ειναι το περιεχομενο του πιν/οι αρχικες σελιδες των επισκεπτων
    }
    cout << std::endl;
    vector<int> nbs;
    int nextpage;
    const int iterations=ITER*this->rows;
    for (int i = 0; i <iterations; i++)  //
    {
        for (int j = 0; j < visitors; j++)
        {
            if (ran(mt) <= DAMPING_FACTOR)
            {
                nbs = this->neiborghs(startingpoints[j]);  //βρισκω τους γειτονες μεσω την συναρτησης neiborghs απο την matrix, το this για το καλεσμα απο την κληρονομ, starting που ηταν ο επισκ στην αρχη
                if (nbs.empty())  // μπορει μια σελιδα να μην εχει λινκς αρα παω σε τυχαια ιστοσελιδα
                {
                    cout << "DeadEnd!!-- ";
                    res+="DeadEnd!!-- ";
                    nextpage = go(mt);  // paragei tyxaia timh
                    while (nextpage == startingpoints[j])
                    {
                        nextpage = go(mt);
                    }
                }
                else
                    nextpage = nbs[go(mt) % nbs.size()]; //2%2=0---- 3%2=1  4%2=0  διαιρει το μεγεθος του πιν με την τιμη που θα παραξει το go
            }
            else
            {
                nextpage = go(mt);
                while (nextpage == startingpoints[j])   // αν η προηγουμενη ειναι ιση με την επομενη
                {
                    nextpage = go(mt);
                }
            }
            this->visits[nextpage]++;
            cout << "Visitor " << j + 1 << " goes from Web Page " << startingpoints[j] << " to Web Page " << nextpage << endl;
            res+="Visitor"+to_string(j+1)+ " goes from Web Page "+to_string(startingpoints[j])+" to Web Page "+to_string(nextpage)+"\n";
            startingpoints[j] = nextpage;
        }
        res+="\n";
    }
    this->find_ranking(); //βαθμος
    return res;
}

double Surfer::getTop()const
{
    if(this->rank.empty()) {return -1.0;}
    return this->rank.at(0).grade;
}