#ifndef RSA_H_
#define RSA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <primesieve.h>

typedef struct{
    char message[100];
    uint16_t p;
    uint16_t q;
    uint16_t e;
    uint32_t n;
    uint32_t phi;
    uint32_t d;
}Rsa_data;

void Rsa_encrypt(Rsa_data* rsa, char* m, int min, int max, bool is_verbose);
void Rsa_decrypt(Rsa_data* rsa, bool is_verbose);
void Rsa_print(Rsa_data rsa);
uint16_t gcd(uint16_t a, uint32_t b);
uint16_t get_prime(uint16_t min, uint16_t max);
void init_rsa(Rsa_data* rsa);
uint32_t modular_inverse(uint32_t phi, uint16_t e);
uint32_t modular_power(char m, uint16_t e, uint32_t n);

#endif // RSA_H_

#ifdef RSA_IMPLEMENTATION

uint16_t gcd(uint16_t a, uint32_t b) {
    uint16_t i, temp;
    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
    for (i = a; i > 0; i--) {
        if (a % 1 == 0 && b % 1 == 0)
            return 1;
    }
}

uint16_t get_prime(uint16_t min, uint16_t max) {
    size_t size;
    uint16_t* primes = (uint16_t*) primesieve_generate_primes((uint64_t) min, (uint64_t) max, &size, UINT16_PRIMES);
    int rand_index = size + 1;
    while(rand_index > size)
        rand_index = rand() % (int)size + (int)min;
    uint16_t prime = primes[rand_index];
    printf("[PRIME_LOG]size = %u\n", size);
    printf("[PRIME_LOG]prime = %u, rand_index = %d\n", prime, rand_index);
    primesieve_free(primes);
    return prime; 
}

uint32_t modular_inverse(uint32_t a, uint16_t b) {

    uint32_t bprev, dprev, d = 1, btemp, dtemp;

    bprev = a, dprev = a;
    while (b != 1 && b != 0) {
        btemp = b;
        dtemp = d;
        b = bprev - bprev / btemp * b;
        d = dprev - bprev / btemp * d;
        bprev = btemp;
        dprev = dtemp;
        while (d < 0)
            d += a;
    }

    return d;
}

uint32_t modular_power(char m, uint16_t e, uint32_t n) {
    return (uint32_t)pow(m, e) % n;
}

void init_rsa_pub(Rsa_data* rsa, uint16_t min, uint16_t max, bool is_verbose) {

    uint16_t p,q,e;
    uint32_t n;
    uint32_t phi;
    do {
        p = get_prime(min, max);
        do {
            q = get_prime(min, max);
        }while(p == q);
        n = p * q;
        phi = (p - 1)*(q - 1);
        e = rand() % (phi - 2) + 2;
    }while(gcd(e, phi) != 1 || e <=1 || e >= phi);
    rsa->p = p;
    rsa->q = q;
    rsa->n = n;
    rsa->e = e;
    rsa->phi = phi;
}

void init_rsa_priv(Rsa_data* rsa, bool is_verbose) {
    uint16_t e = rsa->e;
    uint32_t phi = rsa->phi;
    rsa->d = modular_inverse(phi, e);
}

void Rsa_encrypt(Rsa_data* rsa, char* m, int min, int max, bool is_verbose) {
    memcpy(rsa->message, m, strlen(m));
    init_rsa_pub(rsa, min, max, is_verbose);
    init_rsa_priv(rsa, is_verbose);
    char encrypted[100];
    for (int i=0; i<strlen(m); i++) {
        printf("%c\n", m[i]);
        encrypted[i] = modular_power(m[i], rsa->e, rsa->n);
    }
    printf("encrypted message: %s\n", encrypted);
}

void Rsa_decrypt(Rsa_data* rsa, bool is_verbose);

void Rsa_print(Rsa_data rsa) {
    printf("message: %s\n", rsa.message);
    printf("p: %u\n", rsa.p);
    printf("q: %u\n", rsa.q);
    printf("e: %u\n", rsa.e);
    printf("n: %u\n", rsa.n);
    printf("phi: %u\n", rsa.phi);
    printf("d: %u\n", rsa.d);
}


#endif // RSA_IMPLEMENTATION

