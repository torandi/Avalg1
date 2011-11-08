#include <cstdlib>
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <list>

using namespace std;

#define PRIME_TEST_REPS 10

void init();
bool factorize(mpz_t num, list<mpz_class> &factors);
void output_factors(list<mpz_class> &factors);
void pollard(mpz_t ret, mpz_t N, mpz_t x0);
void square_plus_one(mpz_t &z);

int main() {
   mpz_t num;
   mpz_init(num);
   init();

   list<mpz_class> factors;
   
    while(!cin.eof()) {
      cin>>num;
      if(!cin.eof()) {
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

bool factorize(mpz_t num, list<mpz_class> &factors) {
   int prob_prime = mpz_probab_prime_p(num, PRIME_TEST_REPS);
   if(prob_prime == 0) {
      mpz_t d, tmp, x0;
      mpz_init(d);
      mpz_init(tmp);
      mpz_init(x0);
      mpz_set_ui(x0, 2);
      pollard(d, num, x0);
      mpz_div(tmp, num, d);
      if(factorize(d, factors) && factorize(tmp, factors))
         return true;
      else
         return false;
   } else {
      if(prob_prime == 1)
         cerr<<num<<" is probably prime"<<endl;
      factors.push_back(mpz_class(num));
      return true;
   }
}

void pollard(mpz_t d, mpz_t N, mpz_t x0) {
   mpz_t x1, x2, tmp;
   mpz_init(x1);
   mpz_init(x2);
   mpz_init(d);

   mpz_set(x1, x0);
   mpz_set(x2, x0);
   mpz_set_ui(d, 1);

   while(mpz_cmp_ui(d,1)) {
      square_plus_one(x1);
      mpz_mod(x1, x1, N);

      square_plus_one(x2);
      square_plus_one(x2);
      mpz_mod(x2, x2, N);

      mpz_sub(tmp, x2, x1);
      mpz_abs(tmp, tmp);

      mpz_gcd(d, tmp, N);
   }
}

void square_plus_one(mpz_t &z) {
   mpz_pow_ui(z, z , 2);
   mpz_add_ui(z ,z ,1);
}
