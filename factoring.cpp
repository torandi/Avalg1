#include <cstdlib>
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <list>
#include <string>

using namespace std;

#define PRIME_TEST_REPS 10
#define MAX_ITERATIONS 500 
#define BIGGEST_PRIME 100000

void init();
bool factorize(mpz_t num);
bool pollard(mpz_t ret, mpz_t N, mpz_t x0);
void square_plus_one(mpz_t &z);

list<string> output_buffer;

int main() {
   mpz_t num;
   mpz_init(num);
   init();

   while(!cin.eof()) {
      cin>>num;
      if(!cin.eof()) {
         output_buffer.clear();
         if(factorize(num)) {
            for(list<string>::iterator it=output_buffer.begin();it!=output_buffer.end(); ++it) {
               cout<<*it<<endl;
            }
         } else {
            cout<<"fail"<<endl;
         }
         cout<<endl;
      }
   }
}

void init() {

}

void output_num(mpz_t num) {
   char buffer[512];
   gmp_snprintf(buffer,512,"%Zd",num);
   output_buffer.push_back(string(buffer));
}

bool factorize(mpz_t num) {
   if(mpz_cmp_ui(num,1)==0) {
      return true;
   }
   int prob_prime = mpz_probab_prime_p(num, PRIME_TEST_REPS);
   //sleep(1);
   if(prob_prime == 0) {
      cerr<<"factorize("<<num<<")"<<endl;
      mpz_t d, tmp, x0;
      mpz_init(d);mpz_init(tmp); mpz_init(x0);
      mpz_set_ui(x0, 2);
      while(mpz_cmp_ui(x0, 5)<0) {
         if(pollard(d, num, x0)) {
            mpz_fdiv_q(tmp, num, d);
            //cerr<<"Pollard: "<<d<<", "<<tmp<<endl;
            if(factorize(d) && factorize(tmp))
               return true;
            else
               return false;
         } else {
            if(mpz_root(d, num, 2)!=0) {
               if(factorize(d) && factorize(d))
                  return true;
               else
                  return false;
            } else {
               mpz_add_ui(x0,x0,1);
            }
         }
      }
      cerr<<"Pollard failed!"<<endl;
      mpz_t prime, r, q;
      mpz_init(r); mpz_init(q); mpz_init( prime);
      while( mpz_cmp_ui(prime, BIGGEST_PRIME) < 0 && mpz_cmp(prime, num)<0)  {
         mpz_nextprime(prime, prime);
         mpz_fdiv_qr(q, r , num, prime); 
         if(mpz_cmp_ui(r, 0) == 0) {
            output_num(prime);
            if(factorize(q))
               return true;
            else
               return false;
         }
      }  
      return false;
   } else {
      if(prob_prime == 1)
         cerr<<num<<" is probably prime"<<endl;
      /*else
         cerr<<num<<" is definitly prime"<<endl;*/
      output_num(num);
      return true;
   }
}

bool pollard(mpz_t d, mpz_t N, mpz_t x0) {
   int iterations=0;
   mpz_t x1, x2, tmp;
   mpz_init(x1); mpz_init(x2);mpz_init(tmp);

   mpz_set(x1, x0);
   mpz_set(x2, x0);
   mpz_set_ui(d, 1);

   while(mpz_cmp_ui(d,1)==0 ) {
      if(++iterations > MAX_ITERATIONS) {
         return false;
      }
      square_plus_one(x1);
      mpz_mod(x1, x1, N);

      square_plus_one(x2);
      square_plus_one(x2);
      mpz_mod(x2, x2, N);

      //cout<<"x1: "<<x1<<", x2: "<<x2<<endl;

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
