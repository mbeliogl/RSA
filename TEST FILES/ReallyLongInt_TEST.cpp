#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ReallyLongInt.hpp"
#include <string>
#include <iostream>

TEST_CASE("Testing ReallyLongInt Class")
{
    
    /* ----- CONSTRUCTOR TESTING ----- */
    
    SECTION("TESTING: default constructor"){
        ReallyLongInt r;
        REQUIRE(r.toString() == "0");
        //r.~ReallyLongInt();
    }

    /** Also testing class methods: 
     *  removeLeadingZeros(): called at the end of constructor 
     *  toString(): transform ReallyLongInt to string 
    */ 
       
    SECTION("TESTING: constructor from String"){
        ReallyLongInt r1("123456");
        ReallyLongInt r2("000123456");
        ReallyLongInt r3("0");
        ReallyLongInt r4("-123");

        REQUIRE(r1.toString() == "123456");
        REQUIRE(r2.toString() == "123456");
        REQUIRE(r3.toString() == "0");
        REQUIRE(r4.toString() == "-123");

        //r1.~ReallyLongInt();
        //r2.~ReallyLongInt();
        //r3.~ReallyLongInt();
        //r4.~ReallyLongInt();
    } 
    
    SECTION("TESTING: constructor from Number"){
        long long num1 = 19975;
        long long num2 = -1997;
        long long num3 = 0;

        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);
        ReallyLongInt r3(num3);

        REQUIRE(r1.toString() == "19975");
        REQUIRE(r2.toString() == "-1997");
        REQUIRE(r3.toString() == "0");

        REQUIRE(r1.toLongLong() == 19975);
        REQUIRE(r2.toLongLong() == -1997);
        REQUIRE(r3.toLongLong() == 0);

        //r1.~ReallyLongInt();
        //r2.~ReallyLongInt();
        //r3.~ReallyLongInt();
    }

    SECTION("TESTING: copy constructor"){
        ReallyLongInt r("123");
        ReallyLongInt rCopy(r);

        ReallyLongInt r1("000123456");
        ReallyLongInt r1Copy(r1);

        ReallyLongInt r2("0");
        ReallyLongInt r2Copy(r2);

        ReallyLongInt r3("-123");
        ReallyLongInt r3Copy(r3);

        REQUIRE(rCopy.toString() == "123");
        REQUIRE(r1Copy.toString() == "123456");
        REQUIRE(r2Copy.toString() == "0");
        REQUIRE(r3Copy.toString() == "-123");

        //r.~ReallyLongInt();
        //r1.~ReallyLongInt();
        //r2.~ReallyLongInt();
        //r3.~ReallyLongInt();

        //rCopy.~ReallyLongInt();
        //r1Copy.~ReallyLongInt();
        //r2Copy.~ReallyLongInt();
        //r3Copy.~ReallyLongInt();

    }

    /* ----- METHOD TESTING ----- */
      
    SECTION("TESTING: equal()"){
        ReallyLongInt r1("123456");
        ReallyLongInt r2("000123456");
        ReallyLongInt r3("0");
        ReallyLongInt r4("-123");

        ReallyLongInt r5("123456");
        ReallyLongInt r6("000123456");
        ReallyLongInt r7("0");
        ReallyLongInt r8("-123");

        REQUIRE(r1.equal(r5) == true);
        REQUIRE(r2.equal(r6) == true);
        REQUIRE(r3.equal(r7) == true);
        REQUIRE(r4.equal(r8) == true);

        REQUIRE(r1.equal(r6) == true); //reg vs leading 0 

        long long num1 = 19;
        long long num2 = -19;
        long long num3 = 0;

        long long num4 = 19;
        long long num5 = -19;
        long long num6 = 0;

        ReallyLongInt r9(num1);
        ReallyLongInt r10(num2);
        ReallyLongInt r11(num3);

        ReallyLongInt r12(num4);
        ReallyLongInt r13(num5);
        ReallyLongInt r14(num6);

        REQUIRE(r9.equal(r12) == true);
        REQUIRE(r9.toString() == "19");
        REQUIRE(r12.toString() == "19");
        REQUIRE(r10.equal(r13) == true);
        REQUIRE(r11.equal(r14) == true);

        ReallyLongInt r15("0");
        REQUIRE(r15.equal(r14));   //string vs long 

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        r5.~ReallyLongInt();
        r6.~ReallyLongInt();
        r7.~ReallyLongInt();
        r8.~ReallyLongInt();
        r9.~ReallyLongInt();
        r10.~ReallyLongInt();
        r11.~ReallyLongInt();
        r12.~ReallyLongInt();
        r13.~ReallyLongInt();
        r14.~ReallyLongInt();
        r15.~ReallyLongInt(); 
        */
    }
    
    SECTION("TESTING: absGreater()"){

        //different # of digits
        long long num1 = 10; 
        long long num2 = -100;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);
        
        REQUIRE(r1.absGreater(r2) == false);
        REQUIRE(r2.absGreater(r1) == true);

        //first digit different 
        long long num3 = 100;
        long long num4 = -200;
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        REQUIRE(r3.absGreater(r4) == false);
        REQUIRE(r4.absGreater(r3) == true);

        //different digit (any)
        long long num5 = 555;
        long long num6 = -565;
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);

        REQUIRE(r5.absGreater(r6) == false);
        REQUIRE(r6.absGreater(r5) == true);

        //same number 
        long long num7 = 777;
        long long num8 = -777;
        ReallyLongInt r7(num7);
        ReallyLongInt r8(num8);

        REQUIRE(r7.absGreater(r8) == false);
        REQUIRE(r8.absGreater(r7) == false);

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        r5.~ReallyLongInt();
        r6.~ReallyLongInt();
        r7.~ReallyLongInt();
        r8.~ReallyLongInt();
        */
    }
    
    SECTION("TESTING: greater()"){
        
        //one positive, one negative 
        long long num1 = -10; 
        long long num2 = 10;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE(r1.greater(r2) == false);
        REQUIRE(r2.greater(r1) == true);

        //both positive
        long long num3 = 10; 
        long long num4 = 15;
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        REQUIRE(r3.greater(r4) == false);
        REQUIRE(r4.greater(r3) == true);

        //both negative 
        long long num5 = -10; 
        long long num6 = -15;
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);

        REQUIRE(r5.greater(r6) == true);
        REQUIRE(r6.greater(r5) == false);

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        r5.~ReallyLongInt();
        r6.~ReallyLongInt();
        */
    }

    SECTION("TESTING: absAdd()"){

        //same length positive 
        long long num1 = 10;
        long long num2 = 15;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE(r1.absAdd(r2).toLongLong() == 25);
        REQUIRE(r2.absAdd(r1).toLongLong() == 25);
 
        //different length positive 
        long long num3 = 100;
        long long num4 = 15;
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        REQUIRE(r3.absAdd(r4).toString() == "115");
        REQUIRE(r4.absAdd(r3).toString() == "115");

        //one is negative 
        long long num5 = -10;
        long long num6 = 15;
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);

        REQUIRE(r5.absAdd(r6).toString() == "25");
        REQUIRE(r6.absAdd(r5).toString() == "25");

        //both are negative
        long long num7 = -10;
        long long num8 = -15;
        ReallyLongInt r7(num7);
        ReallyLongInt r8(num8);

        REQUIRE(r7.absAdd(r8).toString() == "25");
        REQUIRE(r8.absAdd(r7).toString() == "25");
        
        //different # of digits 
        long long num9 = 73;
        long long num10 = 99999;
        ReallyLongInt r9(num9);
        ReallyLongInt r10(num10);
        REQUIRE(r9.absAdd(r10).toString() == "100072");
        REQUIRE(r10.absAdd(r9).toLongLong() == 100072);

        //results in a different number of digits 
        long long num11 = 8;
        long long num12 = 5;
        ReallyLongInt r11(num11);
        ReallyLongInt r12(num12);

        REQUIRE(r11.absAdd(r12).toString() == "13");
        REQUIRE(r11.absAdd(r12).toLongLong() == 13);

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        r5.~ReallyLongInt();
        r6.~ReallyLongInt();
        r7.~ReallyLongInt();
        r8.~ReallyLongInt();
        r9.~ReallyLongInt();
        r10.~ReallyLongInt();
        r11.~ReallyLongInt();
        r12.~ReallyLongInt();
        */
    }
   
    SECTION("TESTING: add()"){

        //negative + positive (other is bigger)
        long long num1 = -5;
        long long num2 = 10;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE(r1.add(r2) == 5);
        REQUIRE(r2.add(r1).toString() == "5");

        //negative + positive (this is bigger)
        long long num3 = -5;
        long long num4 = 2;
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        REQUIRE(r3.add(r4) == -3);
        REQUIRE(r4.add(r3).toString() == "-3");

        //this is positive and bigger
        long long num5 = 10;
        long long num6 = -5;
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);

        REQUIRE(r5.add(r6) == 5);
        REQUIRE(r6.add(r5).toString() == "5");

        //this is positive and smaller 
        long long num7 = 5;
        long long num8 = -10;
        ReallyLongInt r7(num7);
        ReallyLongInt r8(num8);

        REQUIRE(r7.add(r8) == -5);
        REQUIRE(r8.add(r7).toString() == "-5");

        //both negative 
        long long num9 = -5;
        long long num10 = -10;
        ReallyLongInt r9(num9);
        ReallyLongInt r10(num10);

        REQUIRE(r9.add(r10) == -15);
        REQUIRE(r10.add(r9).toString() == "-15");

        //both positive 
        long long num11 = 55;
        long long num12 = 65;
        ReallyLongInt r11(num11);
        ReallyLongInt r12(num12);

        REQUIRE(r11.add(r12).toLongLong() == 120);
        REQUIRE(r12.add(r11).toString() == "120");

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        r5.~ReallyLongInt();
        r6.~ReallyLongInt();
        r7.~ReallyLongInt();
        r8.~ReallyLongInt();
        r9.~ReallyLongInt();
        r10.~ReallyLongInt();
        r11.~ReallyLongInt();
        r12.~ReallyLongInt();
        */
    }
    
    SECTION("TESTING: absSub()"){

        //this has more digits than other 
        long long num1 = 10; 
        long long num2 = 5; 
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE(r1.absSub(r2).toLongLong() == 5);

        //same number of digits, this is bigger 
        long long num3 = 11; 
        long long num4 = 10; 
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        REQUIRE(r3.absSub(r4).toLongLong() == 1);

        //equal
        long long num5 = 12; 
        long long num6 = 12; 
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);

        REQUIRE(r5.absSub(r6).toLongLong() == 0);

        //this has less digits than other
        long long num7 = 5; 
        long long num8 = 10; 
        ReallyLongInt r7(num7);
        ReallyLongInt r8(num8);

        REQUIRE(r7.absSub(r8).toLongLong() == -5);


        //same number if digis, other is bigger
        long long num9 = 12; 
        long long num10 = 13; 
        ReallyLongInt r9(num9);
        ReallyLongInt r10(num10);

        REQUIRE(r9.absSub(r10).toLongLong() == -1);

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        r5.~ReallyLongInt();
        r6.~ReallyLongInt();
        r7.~ReallyLongInt();
        r8.~ReallyLongInt();
        r9.~ReallyLongInt();
        r10.~ReallyLongInt();
        */
    }
    
    SECTION("TESTING: sub()"){

        //both negative 
        long long num1 = -5;
        long long num2 = -3;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE(r1.sub(r2).toLongLong() == -2);
        REQUIRE(r2.sub(r1).toLongLong() == 2);
    
        
        //both positive 
        long long num3 = 10;
        long long num4 = 5;
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        REQUIRE(r3.sub(r4).toLongLong() == 5);
        REQUIRE(r4.sub(r3).toLongLong() == -5);
    
        
        //this negative, other positive 
        long long num5 = -8;
        long long num6 = 5;
        long long num7 = -2;
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);
        ReallyLongInt r7(num7);

        REQUIRE(r5.sub(r6).toLongLong() == -13);
        REQUIRE(r7.sub(r6).toLongLong() == -7);

        
        //both positive
        long long num8 = 12;
        long long num9 = 5;
        ReallyLongInt r8(num8);
        ReallyLongInt r9(num9);

        REQUIRE(r8.sub(r9).toLongLong() == 7);
        REQUIRE(r9.sub(r8).toLongLong() == -7);
    
        
        //this positive, other negative
        long long num10 = 8;  
        long long num11 = -3;
        long long num12 = 7;
        long long num13 = -9;
        ReallyLongInt r10(num10);
        ReallyLongInt r11(num11);
        ReallyLongInt r12(num12);
        ReallyLongInt r13(num13);

        REQUIRE(r10.sub(r11).toLongLong() == 11);
        REQUIRE(r12.sub(r13).toLongLong() == 16);
    
        
        //equal positive
        long long num14 = 11;
        long long num15 = 11;
        ReallyLongInt r14(num14);
        ReallyLongInt r15(num15);

        REQUIRE(r14.sub(r15).toLongLong() == 0);
        
        //equal negative
        long long num16 = -3;
        long long num17 = -3;
        ReallyLongInt r16(num16);
        ReallyLongInt r17(num17);

        REQUIRE(r16.sub(r17).toLongLong() == 0); 

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        r5.~ReallyLongInt();
        r6.~ReallyLongInt();
        r7.~ReallyLongInt();
        r8.~ReallyLongInt();
        r9.~ReallyLongInt();
        r10.~ReallyLongInt(); 
        r11.~ReallyLongInt();
        r12.~ReallyLongInt();
        r13.~ReallyLongInt();
        r14.~ReallyLongInt();
        r15.~ReallyLongInt();
        r16.~ReallyLongInt();
        r17.~ReallyLongInt(); 
        */     
    }
    
    SECTION("TESTING: operator '=' swap()"){
        long long num1 = 10; 
        long long num2 = 5;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        r1 = r2;

        REQUIRE(r1.toLongLong() == 5);
        
        long long num3 = 12345; 
        ReallyLongInt r3(num3);

        r2 = r3; 

        REQUIRE(r2.toLongLong() == 12345);
        REQUIRE(r3.toLongLong() == 12345);

        r3 = r1;

        REQUIRE(r3.toLongLong() == 5);

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        */
    }

    SECTION("TESTING: operator '-' flipSign() "){
        long long num1 = 10; 
        long long num2 = -5;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE(-r1.toLongLong() == -10);
        REQUIRE(-r2.toLongLong() == 5);

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        */
    }

    SECTION("TESTING: operator '<<' out stream "){
        long long num1 = 123456789; 
        ReallyLongInt r1(num1);

        string str1 = "987456321";
        ReallyLongInt r2(str1);

        //cout << r1 << endl;
        //cout << r2 << endl;
        //r1.~ReallyLongInt();
        //r2.~ReallyLongInt();
    }

    SECTION("TESTING: Comparison Operators: "){
        long long num1 = 10; 
        long long num2 = -5;
        long long num3 = 10;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);
        ReallyLongInt r3(num3);

        REQUIRE((r1 == r2) == false);
        REQUIRE((r1 == r3) == true);

        REQUIRE((r1 != r2) == true);
        REQUIRE((r1 != r3) == false);

        REQUIRE((r1 > r2) == true);
        REQUIRE((r1 > r3) == false);

        REQUIRE((r1 < r2) == false);
        REQUIRE((r1 < r3) == false);
        REQUIRE((r2 < r3) == true);

        REQUIRE((r1 >= r2) == true);
        REQUIRE((r2 >= r1) == false);
        REQUIRE((r1 >= r3) == true);

        REQUIRE((r1 <= r2) == false);
        REQUIRE((r1 <= r3) == true);
        REQUIRE((r2 <= r1) == true);

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        */
    }

    SECTION("TESTING: Arithmetic Operators: "){
        long long num1 = 10; 
        long long num2 = -5;
        long long num3 = 7; 
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);
        ReallyLongInt r3(num3);

        //cout << r1 + r2 << endl;
        //cout << r1 - r2 << endl;

        r1 += r2; 
        //cout << r1 << endl; 

        r3 -= r1; 
        //cout << r3 << endl;

        long long num4 = -123456;
        ReallyLongInt r4(num4);

        r4 ++; 
        //cout << r4 << endl; 

        r4 --; 
        //cout << r4 << endl; 

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        */
    }

    SECTION("TESTING: absmult()"){

        //multiplication by 0 
        long long num1 = 0; 
        long long num2 = -123662226; 
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE((r1.absMult(r2)).toLongLong() == 0);
        REQUIRE((r2.absMult(r1)).toLongLong() == 0);

        long long num3 = -4; 
        long long num4 = -935045;
        long long num5 = 3;
        long long num6 = 8;  

        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);

        REQUIRE((r3.absMult(r4).toLongLong() == 3740180));
        REQUIRE((r5.absMult(r6).toLongLong() == 24));

        /*
        r1.~ReallyLongInt();
        r2.~ReallyLongInt();
        r3.~ReallyLongInt();
        r4.~ReallyLongInt();
        r5.~ReallyLongInt();
        r6.~ReallyLongInt();
        */
    }

    SECTION("TESTING: mult()"){

        //both pos 
        long long num1 = 333;
        long long num2 = 777;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE(r1.mult(r2).toLongLong() == 258741);

        //both neg
        long long num3 = -435;
        long long num4 = -500;
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        REQUIRE(r3.mult(r4).toLongLong() == 217500);
        
        //one pos, one neg
        long long num5 = -6472;
        long long num6 = 123;
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);

        REQUIRE(r5.mult(r6).toLongLong() == -796056);
        REQUIRE(r6.mult(r5).toLongLong() == -796056);   
    }

    SECTION("TESTING: multiplication operators"){
        long long num1 = 333;
        long long num2 = 777;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        REQUIRE((r1*r2).toLongLong() == 258741);
        //cout << r1 * r2 << endl;

        long long num3 = -435;
        long long num4 = -500;
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        REQUIRE((r3*r4).toLongLong() == 217500);
        //cout << r3 * r4 << endl;

        long long num5 = -6472;
        long long num6 = 123;
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);

        REQUIRE((r5*r6).toLongLong() == -796056);
        //cout << r5 * r6 << endl;

        //*= 
        r1 *= r2; 
        REQUIRE(r1.toLongLong() == 258741);
        //cout << r1 << endl;

        r3 *= r6; 
        REQUIRE(r3.toLongLong() == -53505);
        //cout << r3 << endl;
    }

    SECTION("TESTING: absDiv()"){

        long long num1 = 63798;
        long long num2 = -5794; 
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);

        ReallyLongInt q; 
        ReallyLongInt r; 
        
        r1.absDiv(r2, q, r);
        //cout << r1.toString() << endl;
        //cout << "Q: " << q << endl;
        //cout << "R: " << r << endl;
    }

    SECTION("TESTING: div()"){

        ReallyLongInt q;
        ReallyLongInt r; 
        
        //if one is '0'
        long long num1 = 0;
        long long num2 = 345; 
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);
        //r2.div(r1,q,r);

        //one neg, one pos
        long long num3 = 5; 
        long long num4 = -4; 
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);
        //r3.div(r4,q,r);

        //both positive 
        long long num5 = 175945;
        long long num6 = 7458;
        ReallyLongInt r5(num5);
        ReallyLongInt r6(num6);
        //r5.div(r6,q,r);

        //both negative
        long long num7 = -175945;
        long long num8 = -7458;
        ReallyLongInt r7(num7);
        ReallyLongInt r8(num8);
        //r7.div(r8,q,r); 
    }

    SECTION("TESTING: division operators"){

        long long num1 = 7654757;
        long long num2 = 14634;
        ReallyLongInt r1(num1);
        ReallyLongInt r2(num2);
        //cout << r1/r2 << endl;
        //cout << r1%r2 << endl;

        long long num3 = -5478;
        long long num4 = 189;
        ReallyLongInt r3(num3);
        ReallyLongInt r4(num4);

        //r3 /= r4;
        //r3 %= r4; 
        //cout << r3 << endl; 
    }
}
    

