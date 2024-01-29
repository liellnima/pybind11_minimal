#ifndef _MY_CLASS_H
#define _MY_CLASS_H

#include <string>
using std::string;

class Repetitor{
private:
  string text_s;
public:
  int repeat_i;
  Repetitor(int i, string s);
  string repeat();
};


float divide(float i, float j);

#endif
