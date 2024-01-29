#include "multiply.h"
#include "custom_class/include/my_class.h"
#include <iostream>

int main(){
  int i = 5;
  int j = 6;
  int result = multiply(i, j);
  std::cout << result << std::endl;

  float a = 8.0;
  float b = 2.0;
  float c = divide(a, b);
  std::cout << c << std::endl;
  return 0;
}
