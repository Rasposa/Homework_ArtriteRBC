#include <iostream>

#include <vector>
#include <string>
#include <fstream>



class Case {
public:
  int    index;
  float  dl;
  float  rc;
  float  dc;
  float  mob;
  float  dts;
  float  il;
  float  er;
  float  tcse;
  float  art;
  float  rm;
  float  bur;
  float  tof;
  float  sin;
  float  atg;
  float  nr;
  float  hla_b27;
  float  dj;
  std::string diagnos;

  Case(std::string);
};


class RBC {
private:
  std::vector<Case> cases;
  std::fstream file;

public:
  RBC(std::string);
  
  virtual bool        show_table();
  virtual std::string do_diagnosis(std::string);
  virtual Case        insert_case(std::string);

  virtual std::vector<Case> get_cases() { return this->cases; }
};