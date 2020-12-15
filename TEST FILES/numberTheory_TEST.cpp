#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "numberTheory.hpp"
#include "ReallyLongInt.hpp"

TEST_CASE("Testing the numberTheory functions")
{
    SECTION("TESTING modPower()"){

        ReallyLongInt r1(2);
        ReallyLongInt r2(2);
        ReallyLongInt r3(3);
        REQUIRE(modPower(r1,r2,r3).toLongLong() == 1);

        ReallyLongInt r4(2);
        ReallyLongInt r5(3);
        ReallyLongInt r6(3);
        REQUIRE(modPower(r4,r5,r6).toLongLong() == 2);

        ReallyLongInt r7(12);
        ReallyLongInt r8(12);
        ReallyLongInt r9(123);
        REQUIRE(modPower(r7,r8,r9).toLongLong() == 66);

        //base is '0'
        ReallyLongInt zero;
        REQUIRE(modPower(zero, r1, r2).toLongLong() == 0);

        //exp is '0'
        REQUIRE(modPower(r9, zero, r7).toLongLong() == 1);

        //big numbers 
        //ReallyLongInt base(769480);
        //ReallyLongInt exp(421385);
        //ReallyLongInt mod(91245);
        //REQUIRE(modPower(base, exp, mod).toLongLong() == 46045);
        //cout << modPower(base, exp, mod) << endl;

        //super long from string (realistic)
        string base = "158369723";
        string exp = "421385";
        string mod = "7623";
        ReallyLongInt rbase(base);
        ReallyLongInt rexp(exp);
        ReallyLongInt rmod(mod);

        //REQUIRE(modPower(rbase,rexp,rmod) == 189);
        //cout << modPower(rbase,rexp,rmod) << endl;
    }

    
    SECTION("TESTING isPrime()"){

        //Numbers
        REQUIRE(isPrime(1) == false);
        REQUIRE(isPrime(0) == false);
        REQUIRE(isPrime(2) == true);
        REQUIRE(isPrime(3) == true);

        REQUIRE(isPrime(50) == false);
        REQUIRE(isPrime(11) == true);
        REQUIRE(isPrime(79) == true);
        REQUIRE(isPrime(10) == false);
        REQUIRE(isPrime(197) == true);

        //ReallyLongInts
        ReallyLongInt one(1);
        ReallyLongInt zero(0);

        REQUIRE(isPrime(one) == false);
        REQUIRE(isPrime(zero) == false);

        ReallyLongInt fifty(50);
        ReallyLongInt elev(11);
        ReallyLongInt sn(79);
        ReallyLongInt ten(10);
        ReallyLongInt ons(197);
     
        REQUIRE(isPrime(fifty) == false);
        REQUIRE(isPrime(elev) == true);
        REQUIRE(isPrime(sn) == true);
        REQUIRE(isPrime(ons) == true);


        //proper ReallyLongInts 
        ReallyLongInt r1(21401);
        ReallyLongInt r2(27361);
        ReallyLongInt r3(99989);
        ReallyLongInt r4(106787);

        ReallyLongInt r5(1341337871);

        //ReallyLongInt r6(674132622419);
        //cout << r6 << endl; 

        //from string 
        string st = "674132615311";
        ReallyLongInt s(st);

        REQUIRE(isPrime(r1) == true);
        REQUIRE(isPrime(r2) == true);
        REQUIRE(isPrime(r3) == true);
        REQUIRE(isPrime(r4) == true);
        REQUIRE(isPrime(r5) == true);
        //REQUIRE(isPrime(r6) == true);

        //REQUIRE(isPrime(s) == true);


  
    }
    
    
    SECTION("TESTING extendedEuclid()"){

        ReallyLongInt x;
        ReallyLongInt y;
        ReallyLongInt r(888);
        ReallyLongInt r1(54);
        

        //extendedEuclid(r, r1, &x, &y);
        //REQUIRE(x == -2);
        //REQUIRE(y == 33);

        ReallyLongInt r2(5);
        ReallyLongInt r3(6);

        cout << extendedEuclid(r2, r3, &x, &y) << endl;
        REQUIRE(x.toLongLong() == -1);
        REQUIRE(y.toLongLong() == 1);
        
    } 
        
}
