#include "matrix.hpp"
#include <numeric>
#include <string>
#define DIFF 0.0001

using namespace std;

matrix::matrix(int r,int c):rows(r),columns(c)
{
    //Δεσμευση μνήμης και αρχικοποιήση με τυχαιές τιμές.
    mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution <int> dist(0,1);
    p=new int*[r];  //δεσμευση μνημης
    this->visits=new int[r];
    for(int i=0;i<r;i++)
    {
        this->visits[i]=0;
        p[i]=new int[r];
    }
    for(int i=0;i<r;i++)  //γεμισμα πιν με τυχαιες τιμες 0 ή 1 
    {
        for(int j=0;j<c;j++)
        {
            if(i==j)
            {
                p[i][j]=0;
                continue;
            }
            p[i][j]=dist(mt);
        }
    }
}

matrix::~matrix()
{
   for(int i=0;i<this->rows;i++)  //αποδεσμευση
   {
       delete[] p[i];
   }
   delete[] p;
   p=0;   
}

void matrix::reset_visits()
{
    for(int i=0;i<this->rows;i++)
    {
        this->visits[i]=0;
    }
}

int matrix::nrows()const {return this->rows;}
int matrix::ncols()const {return this->columns;}

vector <int> matrix::neiborghs(int r)
{
    std::vector <int> n;
    for(int j=0;j<this->columns;j++)
    {
        if(this->p[r][j]!=0)
        {
            n.push_back(j);
        }
    }
    return n;
}

string matrix::find_ranking()
{
  
  string result="";
  this->rank.clear();
  int sum=0;
  for(int i=0;i<this->rows;i++)
  {
      sum+=this->visits[i];
  }
  for(int i=0;i<this->rows;i++)
  {
      this->rank.push_back(pagerank{i,(double)this->visits[i]/sum});   // 1ο ειναι ο αριθμος της σελ δλδ το i και 2ο ο βαθμος της σελ που υπολογιζεται ετσι
  }
  sort(this->rank.begin(),this->rank.end(),[](const pagerank &p1,const pagerank &p2) {return p1.grade>p2.grade;});  // εδω βαοηθαει η δομη γιατι εχω  και αριθμο και βαθμο για την ταξιμονηση (αν ειχα double θα ειχα μονο τον αριθμο)
  //χρησιμ labda στην ταξινομηση για να πω τον τροπο
  int counter=1;  // εμφανιση τη θεση
  for(auto &x:this->rank)
  {
      cout<<counter<<"."<<x.page<<"-->"<<x.grade<<endl;
      result+=to_string(counter)+".Web Page "+to_string(x.page)+"-->"+to_string(x.grade)+"\n";
      counter++;
  }
  return result; 

}


