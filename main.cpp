#include "window.cpp"
#include <iostream>

int main()
{
  Window window;
  
  while (window.running() && !window.checkmate())
  {
    window.update();
    window.render();
  }
  if (window.getWinner() == 'W') std::cout << "White won\n";
  else std::cout << "Black won\n";
}
