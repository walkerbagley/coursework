#include <string.h>
#include <pbc.h>

#define aparam "type a\nq 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\nh 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\nr 730750818665451621361119245571504901405976559617\nexp2 159\nexp1 107\nsign1 1\nsign0 1"

int main(int argc, const char* argv[]) {

    // Setup pairing from a.param
    pairing_t pairing;
    pairing_init_set_str(pairing, aparam);

    // Initialize elements we need
    element_t g1, sk, h, sigma;
    element_init_G1(g1, pairing);
    element_init_Zr(sk, pairing);
    element_init_G1(h, pairing);
    element_init_G1(sigma, pairing);

    // Begin reading input text
    FILE *infile;
    infile = fopen("./input", "r");

    // Get g1 as an element
    char line[BUFSIZ];
    fgets(line, BUFSIZ, infile);
    element_set_str(g1, line, 10);

    // Get message to be signed
    char message[BUFSIZ];
    fgets(message, BUFSIZ, infile);

    // Get secret key
    fgets(line, BUFSIZ, infile);
    element_set_str(sk, line, 10);

    fclose(infile);

    // Find the hash of our message
    element_from_hash(h, message, strlen(message));

    // Find the signature of the signed message
    element_pow_zn(sigma, h, sk);

    // Handle output
    FILE *outfile;
    outfile = fopen("./output", "w+");
    element_fprintf(outfile, "%B\n", sigma);
    fclose(outfile);

    // Cleanup elements
    element_clear(g1);
    element_clear(sk);
    element_clear(sigma);
    element_clear(h);
    pairing_clear(pairing);

    return 0;
}