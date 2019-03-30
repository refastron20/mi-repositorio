#include "Polinomio.hpp"
#include "Monomio.hpp"
#include "operadoresExternosPolinomios.hpp"
#include <iostream>

using namespace ed;
int main(){
  Polinomio p1;

  std::cout << "Escriba p1" << '\n';
  cin>>p1;
  std::cout << "p1=" <<p1<< '\n';

  /*double x;

  std::cout << "introduzca x" << '\n';
  std::cin >> x;
  std::cout << "x=" <<x<< '\n';

  Polinomio p2;

  std::cout << "Escriba p2" << '\n';
  cin>>p2;
  std::cout << "p2=" <<p2<< '\n';

  if (p1==p2) {
    std::cout << "son iguales" << '\n';
  }else{
    std::cout << "no son iguales" << '\n';
  }*/

  Monomio m;

  std::cout << "Escriba m" << '\n';
  std::cin >> m;

  if (p1==m) {
    std::cout << "son iguales" << '\n';
  }else{
    std::cout << "no son iguales" << '\n';
  }

  return 0;
}
