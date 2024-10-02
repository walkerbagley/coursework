#include <gmp.h>
#include <stdio.h>
#include <ctype.h>

void getP(mpz_t p, mpz_t q, gmp_randstate_t rand);
void getG(mpz_t p, mpz_t g, gmp_randstate_t rand);
void encrypt(mpz_t c1, mpz_t c2, mpz_t x, mpz_t p, mpz_t g, mpz_t m, gmp_randstate_t rand);

int main(int argc, char** argv) {
    // Set x
    mpz_t x;
    mpz_init_set_str(x, "1234567890123456789012345678901234567890", 10);

    // Initialize necessary mpz integers
    mpz_t message, p, g, q;
    mpz_inits(message, p, g, q, NULL);
    mpz_t e[3][2];
    for (int i = 0; i < 2; i++)
        mpz_inits(e[0][i], e[1][i], e[2][i], NULL);

    // Get message from input file
    FILE *f;
    f = fopen("./input", "r");

    char buffer[BUFSIZ];
    int index = 0;
    char c;
    while ((c = getc(f)) != EOF && isdigit(c))
        buffer[index++] = c;
    
    mpz_set_str(message, buffer, 10);
    fclose(f);

    // Setup random state
    gmp_randstate_t rand;
    gmp_randinit_mt(rand);

    // Get appropriate p, q, g
    getP(p, q, rand);
    getG(p, g, rand);

    // Perform 3 encryptions
    for (int i = 0; i < 3; i++)
        encrypt(e[i][0], e[i][1], x, p, g, message, rand);

    // Write ciphertext and p to output file
    FILE *out;
    out = fopen("./output", "w+");
    for (int i = 0; i < 3; i++) {
        char buf[BUFSIZ];
        mpz_get_str(buf, 10, e[i][0]);
        fprintf(out, "%s", buf);
        fprintf(out, ",");
        mpz_get_str(buf, 10, e[i][1]);
        fprintf(out, "%s", buf);
        fprintf(out, ",");
        mpz_get_str(buf, 10, p);
        fprintf(out, "%s", buf);
        fprintf(out, "\n");
    }
    fclose(out);

    // Free mpz integers and random state
    gmp_randclear(rand);
    mpz_clears(message, x, p, g, q, NULL);
    for (int i = 0; i < 2; i++)
        mpz_clears(e[0][i], e[1][i], e[2][i], NULL);

    return 0;
}

// Gets an appropriate prime p of the form p = 2q + 1 where p is over 2000 bits and q is prime
void getP(mpz_t p, mpz_t q, gmp_randstate_t rand) {
    mpz_t minQ;
    mpz_init(minQ);

    while (1) {
        mpz_rrandomb(minQ, rand, 2001);
        mpz_nextprime(q, minQ);
        mpz_mul_ui(p, q, 2);
        mpz_add_ui(p, p, 1);
        if (mpz_probab_prime_p(p, 15) > 0)
            break;
    }

    mpz_clear(minQ);
}

// Gets a generator that avoids QR/QNR attacks
void getG(mpz_t p, mpz_t g, gmp_randstate_t rand) {
    // while (1) {
    //     mpz_urandomm(g, rand, p);
    //     if (mpz_legendre(g, p) == 1)
    //         break;
    // }
    mpz_urandomm(g, rand, p);
    mpz_powm_ui(g, g, 2, p);
}

// Performs the encryption algorithm with the necessary information
void encrypt(mpz_t c1, mpz_t c2, mpz_t x, mpz_t p, mpz_t g, mpz_t m, gmp_randstate_t rand) {
    mpz_t h, r, hr;
    mpz_inits(h, r, hr, NULL);
    mpz_urandomm(r, rand, p);

    mpz_powm(h, g, x, p);
    mpz_powm(hr, h, r, p);
    mpz_powm(c1, g, r, p);
    mpz_mul(c2, m, hr);
    mpz_mod(c2, c2, p);

    mpz_clears(h, r, hr, NULL);
}