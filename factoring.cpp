#include <cstdlib>
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <list>

using namespace std;

#define PRIME_TEST_REPS 10

void init();
bool factorize(const mpz_class &num, list<mpz_class> &factors);
void output_factors(list<mpz_class> &factors);

int main() {
   mpz_class num;
   init();

   list<mpz_class> factors;
   
    while(!cin.eof()) {
      cin>>num;
      if(!cin.eof()) {
         cerr<<"Num: "<<num<<endl;
         if(factorize(num,factors)) {
            output_factors(factors);
         } else {
            cout<<"fail"<<endl;
         }
         factors.clear();
         cout<<endl;
      }
   }
}

void init() {

}

void output_factors(list<mpz_class> &factors) {
   for(list<mpz_class>::const_iterator it=factors.begin();it!=factors.end();++it) {
      cout<<*it<<endl;
   }
}

bool factorize(const mpz_class &num, list<mpz_class> &factors) {
   int prob_prime = mpz_probab_prime_p(num.get_mpz_t(), PRIME_TEST_REPS);
   if(prob_prime == 0) {
      //Do polarts
      return false;
   } else {
      if(prob_prime == 1)
         cerr<<num<<" is probably prime"<<endl;
      factors.push_back(num);
      return true;
   }
}
