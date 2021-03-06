#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

using namespace std;

/*
I don't know what to do other than use the console command to create the public private keys, I can't figure out how to convert a string
to a bignum to make it work with the following function, and I also don't see where the d and the n come into play with this.
So in order to get something done I am just generating the public and private keys with the openssl command line commands...  Sorry.

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
*/

int main() {
	ifstream fin;
	ofstream fout;
    unsigned char digest[SHA512_DIGEST_LENGTH];
    string AlicekeyFile, BobkeyFile, messageFile, authenticationFile, verificationFile, encryptedFile, decryptedFile;
    string message, signature;
    int e, n, d;
    char string[1024];


    /*------Read In Key File text------*/
    // Obtain the file name with Alice's public-private key
    cout << "1. Enter the name of the file that contains Alice’s public-private key pair: " << endl;
    cin >> AlicekeyFile;

    // Open the file and parse line by line
    fin.open(AlicekeyFile.c_str());
    fin >> e >> n >> d;
    fin.close();

    // Would be used to generate public private key
    //generate_key(e, n, d, "AlicePrivKey.pem", "AlicePubKey.pem");


    /*------Read In Key File text------*/
    // Obtain the file name with Bob's public-private key
    cout << "2. Enter the name of the file that contains Bob’s public-private key pair: " << endl;
    cin >> BobkeyFile;

    // Open the file and parse line by line
    fin.open(BobkeyFile.c_str());
    fin >> e >> n >> d;
    fin.close();

    // Would be used to generate public private key
    //generate_key(e, n, d, "BobPrivKey.pem", "BobPubKey.pem");


    /*------Read In Plain text------*/
    // Obtain the file name that has the message in it
	cout << "3. Enter the name of the file that contains Alice’s plaintext message: " << endl;
	cin >> messageFile;

	// Open the message file and store the string into a variable
	fin.open(messageFile.c_str());
	getline(fin, message);
	fin.close();

	/*------Make A Signature------*/
	// Uses the openssl command line command to create a signature
	system(("openssl dgst -sha512 -sign AlicePrivate.pem -out signature.sign " + messageFile).c_str());


	/*------Create the Authentication File------*/
	// Obtain the file name that will store the authenticated message (plain text on first line and signature on second line).
	cout << "4. Enter the output file name to store Alice’s authenticated message: " << endl;
	cin >> authenticationFile;


	// Open signature file
	fin.open("signature.sign");

	// Create the authentication file with the appropriate format
	fout.open(authenticationFile.c_str());
	fout << message << endl;
	while(fin) {
		getline(fin, signature);
		fout << signature;
	}

	// Close the fstreams
	fin.close();
	fout.close();

	// Obtain the file to store the verification step output
	cout << "5. Enter the output file name to store the verification steps performed by Bob: " << endl;
	cin >> verificationFile;


	/*------Verify the contents of the file------*/
	system(("openssl dgst -sha512 -verify AlicePublic.pem -signature signature.sign " + messageFile + " > " + verificationFile).c_str());


	/*------Encrypt Message------*/
	// Obtain the file name to store the encrypted message
	cout << "6. Enter the output file name to store Alice’s encrypted message: " << endl;
	cin >> encryptedFile;

	system(("openssl enc -aes-128-cbc -k ThisIsJustAPassword -in " + messageFile + " -out " + encryptedFile).c_str());


	/*------Decrypt Message------*/
	// Obtain the file name that will store the decryption of the plaintext message
	cout << "7. Enter the output file name to store Bob’s decryption of Alice’s plaintext message: " << endl;
	cin >> decryptedFile;

	system(("openssl enc -d -aes-128-cbc -k ThisIsJustAPassword -in " + encryptedFile + " -out " + decryptedFile).c_str());
 
    return 0;
}