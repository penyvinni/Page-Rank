#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>

struct pagerank
{
   int page;
   double grade;
};



class matrix
{
   protected:
      int rows;
      int columns;
      int **p;
      int *visits;
      std::vector <pagerank> rank;
   public:
      matrix(int r,int c);
      ~matrix();
      void reset_visits();
      int nrows()const;
      int ncols()const;
      std::vector <int> neiborghs(int r);
      //Βαθμός των ιστοσελίδων
      std::string find_ranking();
};