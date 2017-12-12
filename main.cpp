#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>

using namespace std;

int main()
{
    unsigned char digest[SHA512_DIGEST_LENGTH];
    string keyAlice, keyBob, messageFile;
    char string[1024];

    // Obtain the file name with Alice's public-private key
    cout << "1. Enter the name of the file that contains Alice’s public-private key pair: " << endl;
    cin >> keyAlice;

    // Obtain the file name with Bob's public-private key
    cout << "2. Enter the name of the file that contains Bob’s public-private key pair: " << endl;
    cin >> keyBob;

    // Obtain the file name that has the message in it
	cout << "3. Enter the name of the file that contains Alice’s plaintext message: " << endl;
	cin >> messageFile;

	// Obtain the file name that will store the authenticated message (plain text on first line and signature on second line).
	cout << "4. Enter the output file name to store Alice’s authenticated message: " << endl;

	// Obtain the file to store the verification step output
	cout << "5. Enter the output file name to store the verification steps performed by Bob: " << endl;

	// Obtain the file name to store the encrypted message
	cout << "6. Enter the output file name to store Alice’s encrypted message: " << endl;

	// Obtain the file name that will store the decryption of the plaintext message
	cout << "7. Enter the output file name to store Bob’s decryption of Alice’s plaintext message: " << endl;
    



    cout << message << endl;
    
    SHA512((unsigned char*)&string, strlen(string), (unsigned char*)&digest);    
 
    char mdString[SHA512_DIGEST_LENGTH*2+1];
 
    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
 
    printf("SHA512 digest: %s\n", mdString);
 
    return 0;
}