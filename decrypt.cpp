#include <fstream>
#include <iostream>
#include "numberTheory.hpp"
#include "ReallyLongInt.hpp"
using namespace std;

int main(int argc, char** argv){

    /** Defining Alphabet 
     * Alphabet is a dict where (key, value) = (Letter, num)
     * i.e. (' ', 0), ('A', 1).... ('Z', 26) 
    */
    struct Letter{
        char key; 
        int val; 
    };

    char list_of_letters[27] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    Letter* alphabet = new Letter[27];

    for(int i = 0; i < 27; i++){
        struct Letter let; 
        let.key = list_of_letters[i];
        let.val = i;

        alphabet[i] = let;
        //cout << alphabet[i].key << " " << alphabet[i].val << endl; 
    };


    string d;
    string n;
    string num;

    ifstream fin(argv[1]); //privatekey.txt
    fin >> d;
    fin >> n;

    ReallyLongInt d1(d);
    ReallyLongInt n1(n);

    ifstream inFile(argv[2]); //encryptedtext.txt


    /**
     * Reading encyrpted.txt to determine the number of blocks 
     * Populating the cipherText array with the blocks read
     */
    string s; 
    int sTotal; 
    while(!inFile.eof()){
        getline(inFile, s);
        sTotal++;
    }
    sTotal -= 1;
    inFile.close();

    ReallyLongInt* cipherText = new ReallyLongInt[sTotal];
    ReallyLongInt* messageAsBlockArray = new ReallyLongInt[sTotal];

    ifstream encrypted(argv[2]); //encrypted.txt
    string str; 

    cout << "cipherText: " << endl;
    for(int i = 0; i < sTotal; i++){
        getline(encrypted, str);
        ReallyLongInt r(str);
        cipherText[i] = r;
        messageAsBlockArray[i] = modPower(r, d1, n1);
        cout << cipherText[i] << " ";
    }
    cout << endl;

    cout << "messageAsBlockArray: " << endl;
    for(int i = 0; i < sTotal; i++){
        cout << messageAsBlockArray[i] << " ";
    }
    cout << endl;


    /**
     * Writing decrypted characters to decrypted.txt 
     * Inversing the operation such as: 
     * 16187 ÷ 27^2 = 16187 ÷ 729 = 22 rem 149, 22 → 'V' 
     * 149   ÷ 27^1 = 149   ÷ 27  = 5 rem 14,    5 → 'E'
     * 14    ÷ 27^0 = 14    ÷ 1   = 14 rem 0,   14 → 'N'
     */
    ofstream outFile(argv[3]); //decryptedtext.txt

    ReallyLongInt m;
    ReallyLongInt q; 
    ReallyLongInt r; 
    for(int i = 0; i < sTotal; i++){
        m = messageAsBlockArray[i];
        q = m / pow(float(27), float(2));
        r = m % pow(float(27), float(2));
        long long q1 = q.toLongLong();
        outFile << alphabet[q1].key;
        cout << alphabet[q1].key;  

        q = r / pow(float(27), float(1));
        r = r % pow(float(27), float(1));
        long long q2 = q.toLongLong();
        outFile << alphabet[q2].key;
        cout << alphabet[q2].key;   

        q = r / 1;
        r = r % 1;
        long long q3 = q.toLongLong();
        outFile << alphabet[q3].key;
        cout << alphabet[q3].key;   
    }

  



    delete[] cipherText;
    delete[] messageAsBlockArray;
    
}