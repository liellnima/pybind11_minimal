#include "../include/my_class.h"
#include <iostream>

Repetitor::Repetitor(int i, string s){
  repeat_i = i;
  text_s = s;
}

string Repetitor::repeat(){
  string result;
  string space = " ";
  for (int c=0; c<repeat_i; c++){
    result += text_s;
    result += space;
  }
  return result;
}


float divide(float i, float j){
  return i / j;
}
