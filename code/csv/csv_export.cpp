#include <iostream>
#include <fstream>
#include "Surfer.hpp"

int main()
{
    //Εισαγωγή δεδομένων
    std::string filename;
    int visitors;
    int lpage=10;
    int upage=100;
    int pstep=10;
    double ldampingfactor=0.50;
    double udampingfactor=0.99;
    double lstep=0.05;
    std::cout<<"Give number of visitors:";
    std::cin>>visitors;
    std::cout<<std::endl<<"Give filename:";
    std::cin>>filename;
    filename+=".csv";
    std::string path="Result_Set/"+filename;
    //======================================
    std::ofstream ofs;
    ofs.open(path,std::ios::out);
    for(double dp=ldampingfactor;dp<=udampingfactor;dp+=lstep)
    {
        ofs<<";DMP_"<<dp;
    }
    ofs<<std::endl;
    double top_rank_element;
    std::string top;
    double dp;
    for(int i=lpage;i<=upage;i+=pstep)
    {
        ofs<<i;
        dp=ldampingfactor;
        while(dp<=udampingfactor)
        {
            Surfer s(i);
            s.Surfing(visitors,dp);
            top_rank_element=s.getTop();
            top=std::to_string(top_rank_element);
            std::replace_if(top.begin(),top.end(),[](char &a) {return a=='.';},',');
            ofs<<";"<<top;
            dp=dp+lstep;
        }
        ofs<<std::endl;
    }
    ofs.close();
    std::cout<<std::endl<<"At current folder at:"<<__TIME__<<" file:"<<path<<" created!!!!!"<<std::endl;
    return 0; 
}