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

    
    /**
     * Reading and assigning values for (e, n) from publicKey
     * */
    string e,n;
    ifstream fin(argv[1]); //publicKey.txt
    fin >> e;
    fin >> n;

    ReallyLongInt e1(e);
    ReallyLongInt n1(n);

    //cout << "e1: " << e1 << endl;
    //cout << "n1: " << n1 << endl;
    
    /**
     * Reading chars in block of 3 and calculating value for each block 
     * of characters as such: 
     *      'ATT' = 1 * 27^2 + 20 * 27^1 + 20 --> 1289
     *      'ZZZ' is the maximum value of a block --> 20439
     * */
    FILE* inFile; 
    inFile = fopen(argv[2], "r");

    // Character count of the text 
    int charCount = 0; 
    char c; 
    for(c = getc(inFile); c != EOF; c = getc(inFile)){
        charCount ++; 
    }

    fclose(inFile);
    inFile = fopen(argv[2], "r");
    
    // Array representation of the plain text 
    char* textArray = new char[charCount];
    for(int i = 0; i < charCount; i++){
        c = getc(inFile);
        textArray[i] = c;
   }


    /**
     * Total # of blocks = charCount/3
     *  1. Read 3 characters 
     *  2. Put them in a block 
     *  3. Put the block into arrayOfBlocks
     */
    char* block = new char[3];
    char arrayOfBlocks[charCount/3][3];

    cout << "arrayOfBlocks: " << endl;
    for(int i = 0; i < charCount/3; i++){
        int textArrayIdx = i * 3;
        for(int j = 0; j < 3; j++){
            arrayOfBlocks[i][j] = textArray[textArrayIdx];
            textArrayIdx++; 
        }
    }

    for(int i = 0; i < charCount/3; i++){
        cout << "Block " << i << ": ";
        for(int j = 0; j < 3; j++){
            cout << arrayOfBlocks[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;


    
    /** Repeating for each block: 
     * The algorithm for calculating the value of an individual block 
     *  1. For each letter in the block, we find the alphabet entry (key, value)
     *  2. We calculate each letter using formula: value*27^pos of letter 
     *      e.g. A in 'ATT' = 1*27^2
     *  3. Add all 3 letters to represent the value of the block (blockValue)
     * */
    ReallyLongInt* arrayOfBlockValues = new ReallyLongInt[charCount/3];

    for(int b = 0; b < charCount/3; b++){
        int blockValue = 0;
        ReallyLongInt rlBlockValue; 
        int first, second, third = 0;

        block = arrayOfBlocks[b];
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 27; j++){
                if(block[i] == alphabet[j].key){

                    if(i == 0){
                        first = alphabet[j].val * pow(float(27), float(2));
                    }

                    if(i == 1){
                        second = alphabet[j].val * pow(float(27), float(1)); 
                    }

                    if(i == 2){
                        third = alphabet[j].val;
                    }
                }
            }

            blockValue = first + second + third;
            rlBlockValue = blockValue;
        }
        arrayOfBlockValues[b] = rlBlockValue;
        cout << "blockValue: " << rlBlockValue << endl;
    }

    cout << endl;

    for(int i = 0; i < charCount/3; i++){
        cout << arrayOfBlockValues[i] << " ";
    }

    cout << endl;



    /** 
     * Encrypting the block values using: 
     * c = m^e mod n 
     */
    ofstream fout(argv[3]); //encryptedtext.txt
    ReallyLongInt* cipherText = new ReallyLongInt[charCount/3];
    ReallyLongInt cipher; 

    for(int i = 0; i < charCount/3; i++){
        cipher = modPower(arrayOfBlockValues[i], e1, n1);
        cipherText[i] = cipher;
        fout << cipherText[i] << endl;
    }

    cout << endl;

    delete[] alphabet;
    delete[] cipherText;
    delete[] arrayOfBlockValues;
    delete[] textArray;
    delete[] block; 
 }