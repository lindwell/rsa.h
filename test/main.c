#include <primesieve.h>
#include <stdio.h>

uint32_t modular_inverse(uint32_t a, uint16_t b) {
    uint32_t inv;
    uint32_t q, r, r1 = a;
    uint16_t r2 = b;
    uint32_t t, t1 = 0;
    uint32_t t2 = 1;
     
    while (r2 > 0) {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
                                                     
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;

    }
         
    if (r1 == 1) {
        inv = t1;
    }
         
    if (inv < 0) {
        inv = inv + a;
    }
                 
    return inv;
}

int inverse(int a, int b) {
    int inv;
    int q, r, r1 = a, r2 = b, t, t1 = 0, t2 = 1;
             
    while (r2 > 0) {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
                                                             
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;

        printf("q: %d\n", q);
        printf("r: %d\n", r);
        printf("r1: %d\n", r1);
        printf("r2: %d\n", r2);

        printf("t: %d\n", t);
        printf("t1: %d\n", t1);
        printf("t2: %d\n", t2);


    }
    
                 
    if (r1 == 1) {
        inv = t1;
        printf("1: %d\n", inv);
    }
                 
    if (inv < 0) {
        inv = inv + a;
        printf("2: %d\n", inv);
    }
                     
    return inv;
}

uint32_t findD(uint32_t a, uint16_t b) {
    uint32_t eprev, dprev, d = 1, etemp, dtemp;

    eprev = a, dprev = a;
    while (b != 1) {
        etemp = b;
        dtemp = d;
        b = eprev - eprev / etemp * b;
        d = dprev - eprev / etemp * d;
        eprev = etemp;
        dprev = dtemp;
        while (d < 0)
            d += a;
    }
                
    return d;
}

int main2(void) {
    uint64_t start = 0;
    uint64_t stop = 1000;
    size_t size;

    /* Get an array with the primes inside [start, stop] */
    int* primes = (int*) primesieve_generate_primes(start, stop, &size, INT_PRIMES);

    for (size_t i = 0; i < size; i++)
        printf("%i\n", primes[i]);
    printf("%u", size);

    primesieve_free(primes);
    return 0;
}

int main(void) {

    uint32_t uint_inverse = modular_inverse(3, 7);
    printf("%u\n", uint_inverse);

    int int_inverse = inverse(3, 7);
    printf("%d\n", int_inverse);


    uint32_t fuckyou = findD(3, 7);
    printf("%u\n", fuckyou);

    return 0;
}
