#include <stdio.h>
#include <iostream>
#include <string.h>
#include <openssl/sha.h>

using namespace std;

int main()
{
    unsigned char digest[SHA512_DIGEST_LENGTH];
    string message;
    char string[1024];

    cout << "1. Enter the name of the file that contains Alice’s public-private key pair: " << endl;
    cin >> message;

    cout << message << endl;
    
    SHA512((unsigned char*)&string, strlen(string), (unsigned char*)&digest);    
 
    char mdString[SHA512_DIGEST_LENGTH*2+1];
 
    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
 
    printf("SHA512 digest: %s\n", mdString);
 
    return 0;
}