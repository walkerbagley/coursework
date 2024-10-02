#include <gmp.h>
#include <stdio.h>
#include <ctype.h>

void encrypt(mpz_t m, mpz_t c, mpz_t e, mpz_t d, mpz_t n);
void decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t p, mpz_t q);

int main(int argc, char** argv) {
    FILE *f;
    f = fopen("./input", "r");

    mpz_t input[5];
    mpz_t output[5];
    for (int i = 0; i < 5; i++){
        mpz_inits(input[i], output[i], NULL);
    }

    char buffer[BUFSIZ];
    char c;
    int index = 0;
    int n = 0;
    while ((c = getc(f)) != EOF) {
        if (!isdigit(c)) {
            buffer[index] = 0;
            index = 0;
            mpz_set_str(input[n], buffer, 10);
            n++;
            continue;
        }
        buffer[index++] = c;
    }
    fclose(f);

    mpz_set(output[4], input[0]);
    mpz_set(input[0], output[1]);

    encrypt(output[4], output[0], output[1], output[2], output[3]);
    decrypt(input[0], input[1], input[2], input[3], input[4]);
    mpz_set(output[4], input[0]);

    FILE *out;
    out = fopen("./output", "w+");
    for (int i = 0; i < 5; i++)
    {
        char buf[BUFSIZ];
        mpz_get_str(buf, 10, output[i]);
        fprintf(out, "%s", buf);
        if (i != 4)
            fprintf(out, ",");
    }
    fprintf(out, "\n");
    fclose(out);

    for (int i = 0; i < 5; i++){
        mpz_clears(input[i], output[i], NULL);
    }

    return 0;
}

void encrypt(mpz_t m, mpz_t c, mpz_t e, mpz_t d, mpz_t n) {
    mpz_t minN, p, q, phi, gcd;
    mpz_inits(minN, p, q, phi, gcd, NULL);

    gmp_randstate_t rand;
    gmp_randinit_mt(rand);
    mpz_rrandomb(minN, rand, 512);
    mpz_nextprime(p, minN);
    mpz_rrandomb(minN, rand, 512);
    mpz_nextprime(q, minN);

    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);

    mpz_set(e, phi);
    while (mpz_cmp_ui(gcd, 1) != 0) {
        mpz_urandomm(e, rand, phi);
        mpz_gcd(gcd, e, phi);
    }

    mpz_invert(d, e, phi);
    mpz_powm(c, m, e, n);

    mpz_clears(minN, p, q, phi, gcd, NULL);
    gmp_randclear(rand);
}

void decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t p, mpz_t q) {
    mpz_t n;
    mpz_init(n);
    mpz_mul(n, p, q);

    mpz_powm(m, c, d, n);

    mpz_clear(n);
}