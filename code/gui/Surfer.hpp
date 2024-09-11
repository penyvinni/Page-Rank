#include "matrix.hpp"
#include <string>

class Surfer:public matrix{  // πλοηγηση των επισκεπτων
     public:
       Surfer(int pages);
       ~Surfer();
       std::string Surfing(int visitors,double DAMPING_FACTOR);
       double getTop()const;
};