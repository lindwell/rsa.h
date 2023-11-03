#define RSA_IMPLEMENTATION
#include "rsa.h"
#include <time.h>

int main(void) {

    srand(time(0));

    char message[100];
    char decrypted[100];

    Rsa_data encrypted;

    printf("Enter message.(Maximum string length is 100 bytes.)\nmessage>");
    fgets(message, 100, stdin);
    printf("Original contents: %s",message);

    Rsa_encrypt(&encrypted, message, 100, 10000, true);
    Rsa_print(encrypted);
    
    //decrypted = Rsa_decrypt(&encrypted, true);
    //printf("%s", decrypted);
 

    return 0;
}
