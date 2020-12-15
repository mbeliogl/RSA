#include <iostream>
#include <cmath>
using namespace std;

template <class X>
X modPower(const X& base, const X& exponent, const X& modulus){

    X zero(0);
    X one(1);
    X two(2);

    X n;
    
    if(base == zero){
        return zero;
    }

    if(exponent == zero) {
        return one;  
    }

    else if(exponent % two == zero){
        n = modPower(base, exponent/two, modulus);
        return n % modulus * n % modulus;
    }

    else{
        n = modPower(base, exponent/two , modulus);
        return base % modulus * n % modulus * n % modulus;
    }
}



template <class X>
bool isPrime(const X& num){
    
    X zero(0);
    X one(1);
    X two(2);
    X three(3);

    if(num == zero || num == one){
        return false;
    }
    else if(num <= 3){
        return true; 
    }

    for(int i = 2; i*i <= num; ++i){
        //cout << "i: " << i << endl;
        if(num % i == zero){
            return false;
        }
    }

    return true;
}



template <class X>
X extendedEuclid(const X& a, const X& b, X* x, X* y){
    X zero(0);
    X one(1);
    X two(2);

    if(a == zero){
        *x = zero;
        *y = one;
        return b;
    }

    X x1, y1;
    X d = extendedEuclid(b % a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;

    return d;
}