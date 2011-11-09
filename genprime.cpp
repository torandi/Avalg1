#include <gmp.h>
#include <cstdlib>
#include <iostream>
#include <limits.h>

using namespace std;

int main() {
   int num_primes = 5000;
   cout<<"#ifndef PRIMES_H"<<endl<<"#define PRIMES_H"<<endl;
   cout<<"int num_primes = "<<num_primes<<";"<<endl;
   cout<<"unsigned int primes["<<(num_primes+1)<<"] = {2";
   mpz_t num;
   mpz_init(num);
   mpz_set_ui(num, 2);
   for(int i=0;i<num_primes;++i) {
      mpz_nextprime(num,num);
      cout<<","<<num;
   }
   
   cout<<"};"<<endl<<"#endif"<<endl;
}

