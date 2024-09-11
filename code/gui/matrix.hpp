#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>

struct pagerank
{
   int page;
   double grade;
};  // επιεδη θελω να αποθηκευσω 2 δεδομενα σε vector φτιαχνω μια δομη για τον αριθμο της σελ και τον βαθμο της



class matrix
{
   protected:
      int rows;
      int columns;
      int **p;
      int *visits;
      std::vector <pagerank> rank;  // αντικειμενο/μεταβλητη  τυπου pagerank
   public:
      matrix(int r,int c);
      ~matrix();
      void reset_visits(); // για την surfer
      int nrows()const;
      int ncols()const;
      std::vector <int> neiborghs(int r);
      //Βαθμός των ιστοσελίδων
      std::string find_ranking();
};