#include <cmath>
#include <iostream>
#include <fstream>
#include "numberTheory.hpp"
#include "ReallyLongInt.hpp"

using namespace std;

int main(int argc, char** argv){
    
    ReallyLongInt zero(0);
    ReallyLongInt one(1);
    ReallyLongInt huge(999999999999);

    ReallyLongInt x;
    ReallyLongInt y;

    ReallyLongInt p(argv[1]);
    ReallyLongInt q(argv[2]);
  
    
    ofstream publicFout(argv[3]); //publicKey.txt
    ofstream privateFout(argv[4]); //privateKey.txt

    if(p >= huge || q >= huge){
        
        cout << "Primality is not being tested!" << endl;
    }

    if(isPrime(p) == false || isPrime(q) == false){
        cout << "One of the numbers is not prime!" << endl;
        return 1;
    }

    //PRINTING FOR TESTING 
    cout << "p: " << p << endl;
    cout << "q: " << q << endl;


    ReallyLongInt n = p*q;
    ReallyLongInt t = (p-one) * (q-one); //phi of n 

    cout << "n: " << n << endl;
    cout << "t: " << t << endl;


    /**
     * Choosing e 
     * The following conditions apply: 
     * e must be: 1 < e < t
     * e must be: coprime with n, t 
     * */
    ReallyLongInt e(2);
    
    while(e < t){
        if(extendedEuclid(e, t, &x, &y) == one){
            x = (x % t + t) % t; //modular inverse of e and t
            break;
        }
        else{ 
            e++;
        }
    }


    cout << "e: " << e << endl;
    cout << "d: " << x << endl;

    publicFout << e << " " << n << endl;
    privateFout << x << " " << n << endl;
      
}


