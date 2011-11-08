#include <cstdlib>
#include <iostream>
#include <gmp.h>

using namespace std;

void init();

int main() {
   mpz_t num;
   mpz_init(num);
   init();
   
    while(!cin.eof()) {
      cin>>num;
      if(!cin.eof()) {
         cout<<"Num: "<<num<<endl;
      }
   }
}

void init() {

}
