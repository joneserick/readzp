#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;

int main() {

  auto t1 = Clock::now();
  char letter;

  ifstream reader("text.xml");

  if(!reader){

     std::cout << "Error opening file"  << std::endl;
     return -1;

  }else{

    for(int i = 0; !reader.eof(); i++){
      reader.get(letter);

    }

    reader.close();

  }

  auto t2 = Clock::now();

  std::cout << "Delta t2-t1: "
            << std::chrono::duration_cast<std::chrono::minutes>(t2 - t1).count()
            << " minute(s) " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()
            << " second(s) " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
            << " milliseconds " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
            << " nanoseconds" << std::endl;

  return 0;
}
