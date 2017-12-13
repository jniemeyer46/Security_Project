#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <openssl/sha.h>

using namespace std;

int main()
{
	ifstream fin;
    unsigned char digest[SHA512_DIGEST_LENGTH];
    string AlicekeyFile, BobkeyFile, messageFile, message;
    char string[1024];

    /* TO DO:
		* Create the public-private key pair files and output the created file's name to the screen so that the user can easily enter it.

		* Open the message file and output the string just to make sure everything works correctly

		* 
    */


    // Obtain the file name with Alice's public-private key
    cout << "1. Enter the name of the file that contains Alice’s public-private key pair: " << endl;
    cin >> AlicekeyFile;

    // Obtain the file name with Bob's public-private key
    cout << "2. Enter the name of the file that contains Bob’s public-private key pair: " << endl;
    cin >> BobkeyFile;

    // Obtain the file name that has the message in it
	cout << "3. Enter the name of the file that contains Alice’s plaintext message: " << endl;
	cin >> messageFile;

	fin.open(messageFile);
	getline(fin, message);
	fin.close();

	cout << message << endl;

	// Obtain the file name that will store the authenticated message (plain text on first line and signature on second line).
	cout << "4. Enter the output file name to store Alice’s authenticated message: " << endl;

	// Obtain the file to store the verification step output
	cout << "5. Enter the output file name to store the verification steps performed by Bob: " << endl;

	// Obtain the file name to store the encrypted message
	cout << "6. Enter the output file name to store Alice’s encrypted message: " << endl;

	// Obtain the file name that will store the decryption of the plaintext message
	cout << "7. Enter the output file name to store Bob’s decryption of Alice’s plaintext message: " << endl;
    
    SHA512((unsigned char*)&string, strlen(string), (unsigned char*)&digest);    
 
    char mdString[SHA512_DIGEST_LENGTH*2+1];
 
    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
 
    printf("SHA512 digest: %s\n", mdString);
 
    return 0;
}