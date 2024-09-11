#include <wx/wx.h>
#include "Surfer.hpp"

class Frame : public wxFrame
{
private:
   wxTextCtrl *pages, *visitors, *dampingfactor, *results; 
   wxBoxSizer *sizer;
   Surfer *s;

public:
   Frame() : wxFrame(nullptr, wxID_ANY, "Random Surfer", wxDefaultPosition, wxSize(300, 500)),s(nullptr)   // Frame το παραθυρο
   {
      //wxBoxSizer,wxGridSizer
      this->sizer = new wxBoxSizer(wxVERTICAL);

      //Εισαγωγη σελίδων
      wxPanel *panel = new wxPanel(this, wxID_ANY);
      wxGridSizer *gs1 = new wxGridSizer(0, 2, 5, 5);
      wxStaticText *st1 = new wxStaticText(panel, wxID_ANY, "PAGES", wxDefaultPosition, wxSize(100, 20));
      this->pages = new wxTextCtrl(panel, wxID_ANY, "10", wxDefaultPosition, wxSize(80, 20));
      gs1->Add(st1);  // εισαγωγη στο panel
      gs1->Add(this->pages);
      panel->SetSizer(gs1);
      this->sizer->Add(panel);  // αυτος ο δεικτης θα χειριζεται το panel

      //Εισαγωγή επισκεπτών
      wxPanel *panel1 = new wxPanel(this, wxID_ANY);
      wxGridSizer *gs2 = new wxGridSizer(0, 2, 5, 5);
      wxStaticText *st2 = new wxStaticText(panel1, wxID_ANY, "Visitors", wxDefaultPosition, wxSize(100, 20));
      this->visitors = new wxTextCtrl(panel1, wxID_ANY, "3", wxDefaultPosition, wxSize(80, 20));
      gs2->Add(st2);
      gs2->Add(this->visitors);
      panel1->SetSizer(gs2);
      this->sizer->Add(panel1);

      //Εισαγωγή Damping-Factor
      wxPanel *panel2 = new wxPanel(this, wxID_ANY);
      wxGridSizer *gs3 = new wxGridSizer(0, 2, 5, 5);
      wxStaticText *st3 = new wxStaticText(panel2, wxID_ANY, "Damping Factor", wxDefaultPosition, wxSize(100, 20));
      this->dampingfactor = new wxTextCtrl(panel2, wxID_ANY, "0.85", wxDefaultPosition, wxSize(80, 20));
      gs3->Add(st3);
      gs3->Add(this->dampingfactor);
      panel2->SetSizer(gs3);
      this->sizer->Add(panel2);

      //συναρτησεις
      wxPanel *panel4 = new wxPanel(this, wxID_ANY);
      wxGridSizer *gs4 = new wxGridSizer(0, 2, 3, 3);
      wxButton *b2 = new wxButton(panel4, wxID_ANY, "Rank", wxDefaultPosition, wxSize(50, 20));
      wxButton *b1 = new wxButton(panel4, wxID_ANY, "Surf", wxDefaultPosition, wxSize(50, 20));
      b1->Bind(wxEVT_BUTTON, &Frame::execute_Surfing, this);
      b2->Bind(wxEVT_BUTTON, &Frame::execute_Ranking, this);
      gs4->Add(b1);
      gs4->Add(b2);
      panel4->SetSizer(gs4);
      this->sizer->Add(panel4);
      this->results = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(290, 300), wxTE_MULTILINE);
      this->results->SetEditable(false);
      this->sizer->Add(this->results);
      this->SetSizer(this->sizer);
   }

   ~Frame()
   {
      delete s;
      exit(EXIT_SUCCESS);
   }

   void execute_Surfing(wxCommandEvent &ev)
   {
      std::string pgs = std::string(this->pages->GetValue());
      std::string vs = std::string(this->visitors->GetValue());
      std::string dp = std::string(this->dampingfactor->GetValue());
      int number_of_pages = std::stoi(pgs);  //stoi μετατρεπει τη συμβολοσειρα σε ακεραιο
      int number_of_visitors = std::stoi(vs);
      double number_of_damping_factor = std::stod(dp);  //stod μετατρεπει τη συμβολοσειρα σε double
      s = new Surfer(number_of_pages);
      this->results->SetValue(s->Surfing(number_of_visitors, number_of_damping_factor));
   }
   void execute_Ranking(wxCommandEvent &ev)
   {
      if (s == nullptr)
      {
         wxMessageBox("No Surfing made please make a surf first");
         return;
      }
      std::string rank = "\tRanking Pages\n";
      rank+=s->find_ranking();
      wxMessageBox(rank, "Ranking", wxCENTRE);
   }
};

class app : public wxApp
{
public:
   bool OnInit() wxOVERRIDE
   {
      Frame *f = new Frame();
      f->Show();
      return true;
   }
};

wxIMPLEMENT_APP(app);
