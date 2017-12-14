#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

using namespace std;

bool generate_key(int e, int n, int d, string file1, string file2)
{
    int             ret = 0;
    RSA             *r = NULL;
    BIGNUM          *bne = e;
    BIO             *bp_public = NULL, *bp_private = NULL;
 
    int             bits = 2048;
    unsigned long   da = RSA_F4;
 
    // 1. generate rsa key
    bne = BN_new();
    ret = BN_set_word(bne,da);
 
    r = RSA_new();
    ret = RSA_generate_key_ex(r, bits, bne, NULL);

 
    // 2. save public key
    bp_public = BIO_new_file(file1.c_str(), "w+");
    ret = PEM_write_bio_RSAPublicKey(bp_public, r);

 
    // 3. save private key
    bp_private = BIO_new_file(file2.c_str(), "w+");
    ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);
 

    // 4. free
	free_all:
 
    BIO_free_all(bp_public);
    BIO_free_all(bp_private);
    RSA_free(r);
    BN_free(bne);
 
    return (ret == 1);
}

int main()
{
	ifstream fin;
    unsigned char digest[SHA512_DIGEST_LENGTH];
    string AlicekeyFile, BobkeyFile, messageFile, message;
    int e, n, d;
    char string[1024];

    // Obtain the file name with Alice's public-private key
    cout << "1. Enter the name of the file that contains Alice’s public-private key pair: " << endl;
    cin >> AlicekeyFile;

    // Open the file and parse line by line
    fin.open(AlicekeyFile.c_str());
    fin >> e >> n >> d;
    fin.close();

    generate_key(static_cast<BIGNUM>(e), static_cast<int>(n), static_cast<int>(d), "AlicePrivKey.pem", "AlicePubKey.pem");

    cout << e << " " << n << " " << d << endl;

    // Obtain the file name with Bob's public-private key
    cout << "2. Enter the name of the file that contains Bob’s public-private key pair: " << endl;
    cin >> BobkeyFile;

    // Open the file and parse line by line
    fin.open(BobkeyFile.c_str());
    fin >> e >> n >> d;
    fin.close();

    generate_key(static_cast<int>(e), static_cast<int>(n), static_cast<int>(d), "BobPrivKey.pem", "BobPubKey.pem");

    cout << e << " " << n << " " << d << endl;

    // Obtain the file name that has the message in it
	cout << "3. Enter the name of the file that contains Alice’s plaintext message: " << endl;
	cin >> messageFile;

	// Open the message file and store the string into a variable
	fin.open(messageFile.c_str());
	getline(fin, message);
	fin.close();

	cout << message << endl;

	//system(openssl dgst -sha512 -sign privatekey.pem -out signature.sign messageFile);

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