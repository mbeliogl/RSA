#### RSA

###### RSA encryption for text (.txt) files 

---

Learn how [RSA](https://www.di-mgt.com.au/rsa_alg.html) works!

For now, the implementation works on the following alphabet with a total of 27 characters: 
[_, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z] where _ represents the "space" character

A _ReallyLongInt_ is a type used to represent large keys and other values calculated by the algorithm.
It is defined in _ReallyLongInt.cpp_ and is essentially an array of digits representing the value. 
i.e. 123987 -> [1,2,3,9,8,7] 

A _ReallyLongInt_ has the following properties:

1. isNeg: indicates if the value is negative
2. numDigits: number of digits in the _ReallyLongInt_

A _ReallyLongInt_ also supports the following operations with symbolic operators overriden: 

1. Multiplication * 
2. Division / 
3. Subtratction - 
4. Addition - 
5. Comparison <, >, <=, >= 
6. Modulo % 
7. Negation - 
8. Equivalence = 

---

The _makefile_ contains all necessary compilation commands. 
Use _make all_ to compile the entire application. 

---

###### Generate a key pair: 

1. Pick two prime number (p, q) and run the following command: 

   _Ex: 173 149 publicKey.txt privateKey.txt_ 

   This will output two files. One with the private key (d, n). One with the public key (e, n). 

###### Encrypt 

1. Run the following command to encrypt a text (.txt) file: 

   _Ex: encrypt.exe publicKey.txt plaintext.txt encryptedtext.txt_ 

   Plaintext represents the file you wish to encrypt. 

   Encyrptedtext will contain the encrypted plaintext. 

###### Decrypt

1. Run the following command to decrypt a text (.txt) file: 

   _Ex: decrypt.exe privateKey.txt encryptedtext.txt decryptedtext.txt_

   Encryptedtext is the output of the **encrypt** operation.

   Decryptedtext is the output of **decrypt** and will match the original **plaintext**. 

---

###### Improvements and extra functionality will be added over time.