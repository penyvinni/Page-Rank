#include "matrix.hpp"
#include <string>

class Surfer:public matrix{
     public:
       Surfer(int pages);
       ~Surfer();
       std::string Surfing(int visitors,double DAMPING_FACTOR);
       double getTop()const;
};