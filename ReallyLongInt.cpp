#include "ReallyLongInt.hpp"
#include <string>
#include <array>
#include <iostream>
#include <cmath>
#include <climits>
using namespace std; 

/* ----------- CONSTRUCTORS START HERE ----------- */

/* Default Constuctor */
ReallyLongInt::ReallyLongInt(){

    isNeg = false;
    numDigits = 1;
    unsigned* arr = new unsigned[numDigits];
    arr[0] = 0;
    digits = arr;
}


/* Constructor from String */
ReallyLongInt::ReallyLongInt(const string& numStr){
    
    //if num is just 0 
    if(numStr[0] == '0' && numStr.size() == 1){
        isNeg = false;
        numDigits = numStr.size();
        unsigned* a = new unsigned[numDigits];

        int ascii = numStr[0];
        int digit = ascii - 48;
        a[0] = digit;

        if(numDigits == 0 && a[0] == 0){
            isNeg = false;
        }

        removeLeadingZeros(a, numDigits);
        digits = a; 
    }

    //if num is negative
    else if (numStr[0] == '-'){
        isNeg = true;
        numDigits = numStr.size() - 1;
        unsigned* a = new unsigned[numDigits];

        for(unsigned int i = 0; i < numDigits; i++){
            int ascii = numStr[i+1];
            int digit = ascii - 48;
            a[i] = digit;
        }

        if(numDigits == 0 && a[0] == 0){
            isNeg = false;
        }

        removeLeadingZeros(a, numDigits);
        digits = a;  
    }

    //if num is positive 
    else{
        isNeg = false;
        numDigits = numStr.size();
        unsigned* a = new unsigned[numDigits];

        for(unsigned int i = 0; i < numDigits; i++){
            int ascii = numStr[i];
            int digit = (int) ascii - 48;
            a[i] = digit;
        }

        if(numDigits == 0 && a[0] == 0){
            isNeg = false;
        }

        removeLeadingZeros(a, numDigits);
        digits = a;      
    }  
}


/* Constructor from Number*/
ReallyLongInt::ReallyLongInt(long long num){
    long long last;

    if(num == 0){
        isNeg = false;
        numDigits = 1;
        unsigned* arr = new unsigned[numDigits];
        arr[0] = 0;
        digits = arr;       
    }
   

    else if(num < 0){
        isNeg = true;
        num = num * -1;
        numDigits = log10(num) + 1;

        unsigned* array = new unsigned[numDigits];
        
        for(int i = numDigits - 1; i >= 0; i--){

            last = num % 10;
            num = num / 10;
            array[i] = last;
        }
        digits = array;
    }

    else{
        isNeg = false;
        numDigits = log10(num) + 1;

        unsigned* array = new unsigned[numDigits];
        
        for(int i = numDigits - 1; i >= 0; i--){

            last = num % 10;
            num = num / 10;
            array[i] = last;
        }
        digits = array;
    }
}


/* Constructor from ReallyLongInt (copy constructor) */
ReallyLongInt::ReallyLongInt(const ReallyLongInt& other){
    isNeg = other.isNeg;
    numDigits = other.numDigits;

    unsigned* arrCopy = new unsigned[numDigits];
    
    for(unsigned int i = 0; i < numDigits; i++){
        arrCopy[i] = other.digits[i];
    }
    digits = arrCopy;
}


/** Constructor from specified inputs:

 *  digitsArr: array containing the digits 
 *  arrSize: length of the digitsArr 
 *  isNeg: psoitive/negative property  
 */ 
ReallyLongInt::ReallyLongInt(unsigned* digitsArr, unsigned arrSize, bool isNeg){
    removeLeadingZeros(digitsArr, arrSize);
    digits = digitsArr;
    numDigits = arrSize; 
    
    this->isNeg = isNeg;

    /*
    if(numDigits == 0 && digits[0] == 0){
        this->isNeg = false;
    }*/
    
}


/* Removing a ReallyLongInt */
ReallyLongInt::~ReallyLongInt()
{
    delete [] digits;
}





/* ----------- METHODS START HERE ----------- */


/* Return ReallyLongInt as a string */
string ReallyLongInt::toString() const{
    string a;
    if(isNeg == true){
         a = "-";
    }
    for(unsigned int i = 0; i < numDigits; i++){
            int c = (int) digits[i];
            a += to_string(c);
    }
    return a;
}


/* Return ReallyLongInt as a long long */
long long ReallyLongInt::toLongLong() const{
   
    //convert this to string 
    string str = this->toString();

    //use std::stoll to convert to longlong 
    long long ll = std::stoll (str,0);
    
    return ll;

}

/** Remove leading '0' 
 *  e.g. "000123" -> "123"
*/
void ReallyLongInt::removeLeadingZeros(unsigned* x, unsigned& xSize) const{
    unsigned xSize1 = xSize;
    for(unsigned int i = 0; i < xSize1; i++){
        if(x[0] == 0){
            if(xSize == 1){
                x[i] = 0;
            }
            else{
            for(unsigned int j = 0; j < xSize1; j++){
                x[j] = x[j+1];
            }
            xSize = xSize - 1;
            }
        }
    }    
}

/* Return true if ReallyLongInts are equal, false otherwise */
bool ReallyLongInt::equal(const ReallyLongInt& other) const{
    if(numDigits != other.numDigits){
        return false;
    }
    if(isNeg == true && other.isNeg == false){
        return false; 
    }
    if(isNeg == false && other.isNeg == true){
        return false;
    }
    
    for(unsigned int i = 0; i < numDigits; i++){
        if(digits[i] != other.digits[i]){
            return false;
        }
    }
    return true;
}


/* Return true if *this absolute value > *other absolute value (ignoring sign), false otherwise */
bool ReallyLongInt::absGreater(const ReallyLongInt& other) const{
    if(numDigits > other.numDigits){
        return true;
    }

    if(other.numDigits > numDigits){
        return false;
    }
    
    if(numDigits == other.numDigits && digits[0] > other.digits[0]){
        return true;
    }

    if(numDigits == other.numDigits && other.digits[0] > digits[0]){
        return false;
    }
   
    if (numDigits == other.numDigits){
            for(unsigned int i = 0; i < numDigits; i++){

                if(digits[i] > other.digits[i]){ return true; }

                if(other.digits[i] > digits[i]){ return false; }
                }
            return false;
            }   
    return false;
    }


/* Return true if *this > *other (taking sign into account), false otherwise */
 bool ReallyLongInt::greater(const ReallyLongInt& other) const{

     if(equal(other)){
         return false;
     }

     if(isNeg == true && other.isNeg == false){
         return false;
     }

     if(isNeg == false && other.isNeg == true){
         return true;
     }

     if(isNeg == false && other.isNeg == false){
         return absGreater(other);
     }

     //reversing absGreater() if both are negative   
     if(isNeg == true && other.isNeg == true){
         if(absGreater(other) == false){
             return true;
         }

         if(absGreater(other) == true){
             return false;
         } 
     }
    return false; //for compiler 
 }


/* Addition ignoring sign */
 ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const{

    int extra = 0;
    long long sum = 0;

    unsigned longer = 0;; 
    unsigned shorter = 0;
    unsigned diff = 0; //longer - shorter 

    unsigned* digitsCopy;
    unsigned* result; 
     
    //if other is longer  
    if(other.numDigits > numDigits){
        longer = other.numDigits;
        shorter = numDigits;
        diff = longer - shorter;

        digitsCopy = new unsigned[longer];
        
        for(unsigned int i = 0; i < longer; i ++){
            digitsCopy[i] = 0;
        }

        for(unsigned int i = diff; i < longer; i++){
            digitsCopy[i] = digits[i - diff];
        }

        unsigned resultNumDigits = longer;
        unsigned* tempResult = new unsigned[longer];

        for(int i = longer-1; i >= 0; i--){
            sum = digitsCopy[i] + other.digits[i] + extra;
            
            if(sum > 9){
                extra = 1;
                tempResult[i] = sum % 10;
            }
            if(sum <= 9){
                tempResult[i] = sum;
                extra = 0;
            }
            if((digitsCopy[0] + other.digits[0] + extra) > 9){
                resultNumDigits = longer + 1;
            }
        }
        
        result = new unsigned[resultNumDigits];

        if(resultNumDigits > longer){
            result[0] = 1;
            for(unsigned int i = 1; i < resultNumDigits; i ++){
                result[i] = tempResult[i-1];
            }
        }
        else{
            for(unsigned int i = 0; i < resultNumDigits; i ++){
                result[i] = tempResult[i];
            }
        }

        return ReallyLongInt(result, resultNumDigits, false); //invoking constructor from variables 
        delete [] result;
        delete [] digitsCopy;
        delete [] tempResult;
    }

    //if this is longer
    if(numDigits > other.numDigits){
        longer = numDigits;
        shorter = other.numDigits;
        diff = longer - shorter;

        digitsCopy = new unsigned[longer];
        
        for(unsigned int i = 0; i < longer; i ++){
            digitsCopy[i] = 0;
        }

        for(unsigned int i = diff; i < longer; i++){
            digitsCopy[i] = other.digits[i - diff];
        }

        unsigned resultNumDigits = longer;
        unsigned* tempResult = new unsigned[longer];

        for(int i = longer-1; i >= 0; i--){
            sum = digitsCopy[i] + digits[i] + extra;
        
            if(sum > 9){
                extra = 1;
                tempResult[i] = sum % 10;
            }
            if(sum <= 9){
                tempResult[i] = sum;
                extra = 0;
            }
            if((digitsCopy[0] + digits[0] + extra) > 9){
                resultNumDigits = longer + 1;
            }
        }
        
        result = new unsigned[resultNumDigits];

        if(resultNumDigits > longer){
            result[0] = 1;
            for(unsigned int i = 1; i < resultNumDigits; i ++){
                result[i] = tempResult[i-1];
            }
        }
        else{
            for(unsigned int i = 0; i < resultNumDigits; i ++){
                result[i] = tempResult[i];
            }
        }
        return ReallyLongInt(result, resultNumDigits, false); //invoking constructor from variables 
        delete [] result;
        delete [] digitsCopy;
        delete [] tempResult;
    }

    //if lengths are equal 
    if(numDigits == other.numDigits){
        longer = numDigits;
        shorter = longer;
        diff = longer - shorter;

        unsigned resultNumDigits = longer;
        unsigned* tempResult = new unsigned[longer];

        for(int i = longer-1; i >= 0; i--){
            sum = other.digits[i] + digits[i] + extra;
            
            if(sum > 9){
                extra = 1;
                tempResult[i] = sum % 10;
            }
            if(sum <= 9){
                tempResult[i] = sum;
                extra = 0;
            }
            if((other.digits[0] + digits[0] + extra) > 9){
                resultNumDigits = longer + 1;
            }
        }

        result = new unsigned[resultNumDigits];

        if(resultNumDigits > longer){
            result[0] = 1;
            for(unsigned int i = 1; i < resultNumDigits; i ++){
                result[i] = tempResult[i-1];
            }
        }
        else{
            for(unsigned int i = 0; i < resultNumDigits; i ++){
                result[i] = tempResult[i];
            }
        }

        return ReallyLongInt(result, resultNumDigits, false);
        delete [] result;
        delete [] tempResult;
    }
    return ReallyLongInt(); //for compiler 
 }
 


/* Addition with sign */
 ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const{
     if(isNeg == true && other.isNeg == false && absGreater(other) == false){
         return other.absSub(*this);
     }
     if(isNeg == true && other.isNeg == false && absGreater(other) == true){
         ReallyLongInt r(absSub(other));
         r.flipSign();
         return r;

     }
     if(isNeg == false && other.isNeg == true && other.absGreater(*this) == false){
        return absSub(other);
     }
     if(isNeg == false && other.isNeg == true && other.absGreater(*this) == true){
         ReallyLongInt r(other.absSub(*this));
         r.flipSign();
         return r;
     }
     if(isNeg == true && other.isNeg == true){
         ReallyLongInt r(absAdd(other));
         r.flipSign();
         return r;
     }
     return absAdd(other);
 }

/* Subtraction ignoring sign */ 
ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const{

    int borrow = 0;
    unsigned longer = 0;; 
    int diff = 0;
    unsigned shorter = 0;

    if((numDigits >= other.numDigits && absGreater(other) == true) || equal(other) == true){   
        longer = numDigits;
        shorter = other.numDigits;
        
        unsigned* temp = new unsigned[longer];
        unsigned* result = new unsigned[longer];

        for(unsigned int i = 0; i < longer; i++){
            temp[i] = 0;
        }

        for(unsigned int i = longer - shorter; i < longer; i++){
            temp[i] = other.digits[i - (longer-shorter)];
        }

        for(int i = longer-1; i >= 0; i--){
            diff = digits[i] - temp[i] + borrow;

            if(diff < 0){
                diff += 10;
                result[i] = diff;
                borrow = -1;
            }
            else if(diff >= 0){
                result[i] = diff;
                borrow = 0;
            }
        }
        return ReallyLongInt(result,longer, false);
        delete [] result;
        delete [] temp;
    }

    if(other.numDigits > numDigits || other.absGreater(*this) == true){   
        longer = other.numDigits;
        shorter = numDigits;
        
        unsigned* temp = new unsigned[longer];
        unsigned* result = new unsigned[longer];

        for(unsigned int i = 0; i < longer; i++){
                temp[i] = 0;
        }

        for(unsigned int i = longer - shorter; i < longer; i++){
            temp[i] = digits[i - (longer-shorter)];
        }

        for(int i = longer-1; i >= 0; i--){
            diff = other.digits[i] - temp[i] + borrow;

            if(diff < 0){
                diff += 10;
                result[i] = diff;
                borrow = -1;
            }
            else if(diff >= 0){
                result[i] = diff;
                borrow = 0;
            }
        }
        return ReallyLongInt(result,longer, true);
        delete [] result;
        delete [] temp;
    }
    return ReallyLongInt(); //for compiler
}


/* Subtraction with sign */ 
ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const{

    //both negative, this is biger 
    if(isNeg == true && other.isNeg == true && absGreater(other) == true){
        ReallyLongInt r(absSub(other));
        r.flipSign();
        return r;
    }

    //both negative, other is bigger 
    if(isNeg == true && other.isNeg == true && other.absGreater(*this) == true){
        ReallyLongInt r(other.absSub(*this));
        return r;
    }

    //both positive, this is bigger 
    if(isNeg == false && other.isNeg == false && absGreater(other) == true){
        return absSub(other);
    }

    //both positive, other is bigger 
    if(isNeg == false && other.isNeg == false && other.absGreater(*this) == true){
         ReallyLongInt r(other.absSub(*this));
         r.flipSign();
         return r; 
    }

    //this is negative, other is positive, this is bigger
    if(isNeg == true && other.isNeg == false && absGreater(other) == true){
        ReallyLongInt r(absAdd(other));
        r.flipSign();
        return r;
    }

    //this is negative, other is positive, other is bigger
    if(isNeg == true && other.isNeg == false && other.absGreater(*this) == true){
        ReallyLongInt r(absAdd(other));
        r.flipSign();
        return r;
    }

    //both are positive, this is bigger
    if(isNeg == false && other.isNeg == false && absGreater(other) == true){
       return absSub(other);
    }

    //both are positive, other is bigger
    if(isNeg == false && other.isNeg == false && other.absGreater(*this) == true){
        ReallyLongInt r(other.absSub(*this));
        r.flipSign();
        return r;
    }

    //this is positive, other is negative, this is bigger
    if(isNeg == false && other.isNeg == true && absGreater(other) == true){
        return absAdd(other);
    }

    //this is positive, other is negative, other is bigger
    if(isNeg == false && other.isNeg == true && other.absGreater(*this) == true){
        return absAdd(other);
    }

    //all other cases (if equal)
    else{
        return absSub(other);
    }
}

/* Assignment operator '=' */ 
ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other){
    swap(other);
    return *this;
}

/* Helper method for assignment operator (swaps values) */
void ReallyLongInt::swap(ReallyLongInt other){
    bool isNegTemp;
    unsigned numDigitsTemp;
    const unsigned* digitsTemp = digits;

    numDigitsTemp = other.numDigits;
    other.numDigits = numDigits;
    numDigits = numDigitsTemp;

    isNegTemp = other.isNeg;
    other.isNeg = isNeg;
    isNeg = isNegTemp;

    digitsTemp = other.digits;
    other.digits = digits;
    digits = digitsTemp;

}

/* Helper method to reverse isNeg value*/
void ReallyLongInt::flipSign(){
    if(numDigits == 1 && digits[0] == 0){
        isNeg = false;
    }
    else if(isNeg == false){
        isNeg = true;
    }
    else if(isNeg == true){
        isNeg = false;
    }
}

/* Negation operator '-' */
ReallyLongInt ReallyLongInt::operator-() const{

    /*
    unsigned* temp = new unsigned[numDigits];
    for(int i = 0; i < numDigits; i++){
        temp[i] = digits[i];
    }
    ReallyLongInt r1(temp, numDigits, isNeg);
    r1.flipSign();
    return r1; */

    ReallyLongInt r1(*this);
    r1.flipSign();
    return r1;
}


/* ----- NON-CLASS FUNCTIONS ----- */

ostream& operator<<(ostream& out, const ReallyLongInt& x){
    string s = x.toString();
    out << s;
    
    return out;
}

/* Overloading Comparison Operators */
bool operator==(const ReallyLongInt& x, const ReallyLongInt& y){
    return x.equal(y);
}

bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y){
    if(x.equal(y) == false){
        return true;
    }
    return false;
}

bool operator>(const ReallyLongInt& x, const ReallyLongInt& y){
    return  x.greater(y);
}

bool operator<(const ReallyLongInt& x, const ReallyLongInt& y){
    if(x.greater(y) == false && x.equal(y) == false){
        return true;
    }
    return false;
}
bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y){
    if(x.greater(y) == true || x.equal(y) == true){
        return true;
    }
    return false;
}
bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y){
    if(y.greater(x) == true || y.equal(x) == true){
        return true;
    }
    return false;
}

/* Overloading Arithmetic Operators */
ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y){
    return x.add(y);
}
ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y){
    return x.sub(y);
}
ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other){  
    *this = *this + other;
    return *this;
}
ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other){
    *this = *this - other;
    return *this;
}
ReallyLongInt& ReallyLongInt::operator++(){
    ReallyLongInt r(1);
    *this = *this + r;
    return *this;
}
ReallyLongInt& ReallyLongInt::operator--(){
    ReallyLongInt r(1);
    *this = *this - r;
    return *this;
}
ReallyLongInt ReallyLongInt::operator++(int dummy){
    ReallyLongInt r(*this);
    ReallyLongInt r1(1);
    *this = *this + r1;
    return r;
}
ReallyLongInt ReallyLongInt::operator--(int dummy){
    ReallyLongInt r(*this);
    ReallyLongInt r1(1);
    *this = *this - r1;
    return r;
}



/* Multiplication without sign (absolute values) */ 
ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const{ 

    //if '0'
    if(this->toLongLong() == 0 || other.toLongLong() == 0){
        ReallyLongInt x(0);
        return x;
    }

    long long thisNum = this->toLongLong();
    long long otherNum = other.toLongLong();
   
    //negating if negative (this is absolute multiplication)
    if(this->isNeg == true){
        thisNum = (-*this).toLongLong();
    }
    if(other.isNeg == true){
        otherNum = -other.toLongLong();
    }

    //length of result 
    unsigned newLength = floor((log10(thisNum) + log10(otherNum))) + 1;

    int idx1 = 0;
    int idx2 = 0;

    unsigned* result = new unsigned[newLength];

    //if only one digit 
    if(numDigits == 1 && other.numDigits == 1){
        if((digits[0] * other.digits[0]) > 9){
            newLength = 2;
        }
        if((digits[0] * other.digits[0]) < 9){
            newLength = 1;
        }
    }
    
    //fill result with '0'
    for(unsigned int i = 0; i <newLength; i++){
        result[i] = 0;
    }

    //main loop 
    for(int i = numDigits - 1; i >= 0; i--){
        int carry = 0;
        int x = digits[i];
        idx2 = 0;

        for(int j = other.numDigits - 1; j >= 0; j--){
            int y = other.digits[j];
            int z = result[idx1+idx2];
            int temp = x*y + carry + z;
    
            result[idx1 + idx2] = temp % 10;
            carry = temp / 10;
            idx2++;
        }

        if(carry > 0){
            result[idx1 + idx2] += carry;
        }
        idx1++;
    }

    //reversing result array 
    int x;
    for (unsigned int i = 0; i < newLength/2; i++) {
        x = result[newLength-i-1];
        result[newLength-i-1] = result[i];
        result[i] = x;
    }

    return ReallyLongInt(result, newLength, false);
    delete [] result;
}


/* Multiplication with sign */
ReallyLongInt ReallyLongInt::mult(const ReallyLongInt& other) const{

    //one is neg, one is pos
    if((isNeg == true && other.isNeg == false) || (other.isNeg == true && isNeg == false)){
        ReallyLongInt r(absMult(other));
        r.flipSign();
        return r;
    }
    else if((isNeg == true && other.isNeg == true) || (isNeg == false && other.isNeg == false)){
        return absMult(other);
    }

    return ReallyLongInt(); //for compiler 

}

/* Overloading multiplication operators */
ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y){
    return x.mult(y);
}
ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt& other){
    *this = *this * other;
    return *this;
}


/* Division without sign (absolute values) */
void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const{ 
    unsigned d = 0;
    ReallyLongInt ten(10);
   
    unsigned* temp = new unsigned[numDigits]; 

    for(unsigned int i = 0; i < numDigits; i ++){
        temp[i] = 0;
    }

    for(unsigned int i = 0; i < numDigits; i ++){

        ReallyLongInt xi(digits[i]);
        remainder = remainder * ten;
        remainder = remainder + xi;
        d = 0;

        while(remainder.equal(other) || remainder.absGreater(other)){
            remainder = remainder.absSub(other); 
            d++;
        }
        temp[i] = d;
    }

    ReallyLongInt q(temp, numDigits, false);
    quotient = q;

    //delete [] temp;     
}



/* Division with sign */
void ReallyLongInt::div(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const{ 

    //*this is '0'
    if(*this == 0){
        ReallyLongInt zero;
        quotient = zero; 
        remainder = zero;
    }

    //other is '0' (division by 0)
    if(other == 0){
        cout << "Attempt to divide " << *this << " by " << other << endl;  
        cerr << "Division by '0' is an undefined operation" << endl;
        cerr << "EXITING....." << endl;
        exit(EXIT_FAILURE);
    }

    if(isNeg == true && other.isNeg == false){

        absDiv(other, quotient, remainder);
        quotient.flipSign();
        remainder = other.absSub(remainder);
    }

    if(isNeg == false && other.isNeg == true){

        absDiv(other, quotient, remainder);
        quotient.flipSign();
        remainder = other.absSub(remainder);
        remainder.flipSign();
    }

    if(isNeg == false && other.isNeg == false){
        absDiv(other, quotient, remainder);
    }

    if(isNeg == true && other.isNeg == true){
        absDiv(other, quotient, remainder);
        remainder.flipSign();
    }
}

/* Overloading division operators */
ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y){
    ReallyLongInt q;
    ReallyLongInt r;
    x.div(y,q,r);
    return q;
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y){ 
    ReallyLongInt q;
    ReallyLongInt r;
    x.div(y,q,r);
    return r;
}

ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other){
    *this = *this/other;
    return *this;
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other){
    *this = *this%other;
    return *this;

}



