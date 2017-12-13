#echo "Now generating the private key for Alice with the file name AlicePrivate.pem"
#openssl genpkey -algorithm RSA -out AlicePrivate.pem -pkeyopt rsa_keygen_bits:2048
#echo "Now generating the public key for Alice with the file name AlicePublic.pem"
#openssl rsa -pubout -in AlicePrivate.pem -out AlicePublic.pem

#echo

#echo "Now generating the private key for Bob with the file name BobPrivate.pem"
#openssl genpkey -algorithm RSA -out BobPrivate.pem -pkeyopt rsa_keygen_bits:2048
#echo "Now generating the public key for Bob with the file name BobPublic.pem"
#openssl rsa -pubout -in BobPrivate.pem -out BobPublic.pem

#echo

g++ main.cpp -o main -lcrypto

./main