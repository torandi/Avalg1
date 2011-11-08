#include <cstdlib>
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <list>
#include <string>

using namespace std;

#define PRIME_TEST_REPS 10

void init();
bool factorize(mpz_t num);
bool pollard(mpz_t ret, mpz_t N, mpz_t x0);
void square_plus_one(mpz_t &z);

int main() {
   mpz_t num;
   mpz_init(num);
   init();

   while(!cin.eof()) {
      cin>>num;
      if(!cin.eof()) {
         if(!factorize(num)) {
            cerr<<"fail"<<endl;
         }
         cout<<endl;
      }
   }
}

void init() {

}

bool factorize(mpz_t num) {
   if(mpz_cmp_ui(num,1)==0) {
      return true;
   }
   int prob_prime = mpz_probab_prime_p(num, PRIME_TEST_REPS);
   cout<<"factorize("<<num<<")"<<endl;
   sleep(1);
   if(prob_prime == 0) {
      mpz_t d, tmp, x0;
      mpz_init(d);
      mpz_init(tmp);
      mpz_init(x0);
      mpz_set_ui(x0, 2);
      if(pollard(d, num, x0)) {
         mpz_fdiv_q(tmp, num, d);
         cerr<<"Pollard: "<<d<<", "<<tmp<<endl;
         if(factorize(d) && factorize(tmp))
            return true;
         else
            return false;
      } else {
         cerr<<"Pollard failed!"<<endl;
         return false;
      }
   } else {
      if(prob_prime == 1)
         cerr<<num<<" is probably prime"<<endl;
      /*else
         cerr<<num<<" is definitly prime"<<endl;*/
      cout<<num<<endl;
      return true;
   }
}

bool pollard(mpz_t d, mpz_t N, mpz_t x0) {
   mpz_t x1, x2, tmp;
   mpz_init(x1);
   mpz_init(x2);
   mpz_init(tmp);

   mpz_set(x1, x0);
   mpz_set(x2, x0);
   mpz_set_ui(d, 1);

   while(mpz_cmp_ui(d,1)==0) {
      square_plus_one(x1);
      mpz_mod(x1, x1, N);

      square_plus_one(x2);
      square_plus_one(x2);
      mpz_mod(x2, x2, N);

      cout<<"x1: "<<x1<<", x2: "<<x2<<endl;

      mpz_sub(tmp, x2, x1);
      mpz_abs(tmp, tmp);

      mpz_gcd(d, tmp, N);
   }
   return !(mpz_cmp(d,N)==0);
}

void square_plus_one(mpz_t &z) {
   mpz_pow_ui(z, z , 2);
   mpz_add_ui(z ,z ,1);
}
