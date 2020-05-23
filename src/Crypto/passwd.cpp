#include "passwd.h"

void PASSWD::show_hex_buff(unsigned char buf[])
{
    int i;
    for (uint8_t i=0; i < crypto_secretstream_xchacha20poly1305_KEYBYTES; i++) 
        printf("%02X ", buf[i]);
    printf("\n");
}

const unsigned char* PASSWD::hash(QString password)
{
    /*std::string data = password.toStdString();
    
    unsigned char hash[crypto_generichash_BYTES];

    crypto_generichash(hash, sizeof hash,
                    (const unsigned char*)data.c_str(), data.size(),
                    NULL, 0);

    //qDebug() << PASSWD::convertToHexString(hash);
    return (const unsigned char*)hash;*/

    int length = password.length();
     
    char *sequence = NULL;
    sequence = new char[length+1];
    strncpy(sequence, password.toLocal8Bit(), length +1);

    #define MESSAGE ((const unsigned char *) sequence)
    #define MESSAGE_LEN length

    qDebug()<<"Generating cryptographic key from password: " <<sequence;
    unsigned char * hash= new unsigned char[crypto_secretstream_xchacha20poly1305_KEYBYTES];
    crypto_generichash(hash, sizeof hash, MESSAGE, MESSAGE_LEN, NULL, 0);
    qDebug()<<"secret key generated:\n";
    PASSWD::show_hex_buff(hash);
    return hash;
}