/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*
* Walker Bagley
*/

#include "../src/HEAAN.h"
#include <stdlib.h>
#include <iostream>


using namespace std;
using namespace heaan;
using namespace NTL;

/**
  * This file is for test HEAAN library
  * You can find more in src/TestScheme.h
  * "./TestHEAAN Encrypt" will run Encrypt Test
  * There are Encrypt, EncryptSingle, Add, Mult, iMult, RotateFast, Conjugate Tests
  */
int main(int argc, char **argv) {

	long logq = 160; ///< Log of the ciphertext modulus q.
	long logp = 30; ///< Real message will be quantized by multiplying 2^30. This is the log of the Delta in the CKKS scheme.
    /// Decryption suceeds with sufficient precision/accuracy only when logp is much smaller than logq (e.g., smaller by 10).
    
    long logn = 0; ///< log2(The number of slots) <-- Students may ignore this parameter.
    long n = 1 << logn; ///  <-- Students may ignore this parameter.
    long logq_bootstrap = 40; ///  <-- Students may ignore this parameter.
    long logT = 4; ///< this means that we use Taylor approximation in [-1/T,1/T] with double angle fomula  <-- Students may ignore this parameter.
    
    srand(time(NULL));
    SetNumThreads(4);
    Ring ring;
    SecretKey secretKey(ring);
    Scheme scheme(secretKey, ring); /// <-- This is where the scheme is set up, the secretKey is chosen, and the public key and the evaluation key is chosen. All public parameters are included in the class object "scheme".
    scheme.addBootKey(secretKey, logn, logq_bootstrap + 4); /// <-- This is where the bootstrapping key (i.e., encrypted secretKey and other auxiliary parameters) is added to the scheme.
    
    complex<double>* mval = new complex<double>[n]; /// <-- This is the value to encrypt.
    complex<double>* mresult = new complex<double>[n]; /// <-- This will store the desired result.
    for(long i = 0; i < n; i++) {
        mval[i] = atof(argv[1]); /// <-- My grading program will provide the input to be encrypted as argv[1]
    }
    
    
    
    Ciphertext cipher;
    
    scheme.encrypt(cipher, mval, n, logp, logq); /// <-- mval, i.e., the initial value, is encrypted here.
    

    /*
     
     Student input starts.
     
     */

    Ciphertext x_original;
    Ciphertext x3;
    Ciphertext x17;

    x_original.copy(cipher);

    scheme.squareAndEqual(cipher);
    scheme.reScaleByAndEqual(cipher, logp);

    x3.copy(cipher);

    scheme.squareAndEqual(cipher);
    scheme.reScaleByAndEqual(cipher, logp);
    scheme.bootstrapAndEqual(cipher, logq_bootstrap, logQ, logT);

    scheme.squareAndEqual(cipher);
    scheme.reScaleByAndEqual(cipher, logp);

    scheme.squareAndEqual(cipher);
    scheme.reScaleByAndEqual(cipher, logp);
    scheme.bootstrapAndEqual(cipher, logq_bootstrap, logQ, logT);

    x17.copy(cipher);

    scheme.squareAndEqual(cipher);
    scheme.reScaleByAndEqual(cipher, logp);

    scheme.squareAndEqual(cipher);
    scheme.reScaleByAndEqual(cipher, logp);
    scheme.bootstrapAndEqual(cipher, logq_bootstrap, logQ, logT);
    
    scheme.squareAndEqual(cipher);
    scheme.reScaleByAndEqual(cipher, logp);

    scheme.multAndEqual(x17, x_original);
    scheme.reScaleByAndEqual(x17, logp);
    scheme.multByConstAndEqual(x17, 2.0, logp);
    scheme.reScaleByAndEqual(x17, logp);
    scheme.bootstrapAndEqual(x17, logq_bootstrap, logQ, logT);

    scheme.multAndEqual(x3, x_original);
    scheme.reScaleByAndEqual(x3, logp);
    scheme.multByConstAndEqual(x3, -3.0, logp);
    scheme.reScaleByAndEqual(x3, logp);
    scheme.bootstrapAndEqual(x3, logq_bootstrap, logQ, logT);

    scheme.addAndEqual(cipher, x17);
    scheme.addAndEqual(cipher, x3);

    /*
     
     Student input ends.
     
     */
    
    
    complex<double>* dresult = scheme.decrypt(secretKey, cipher); /// <-- This will decrypt the final cipher
    StringUtils::compare(mresult, dresult, n, "result"); /// <-- This will compare mresult (the polynomial that was computed with plaintext data) and dresult (the outcome of the decryption). The difference is calculated and shown as eresult, which needs to be small enough to pass the grading.
    
    
    ofstream fout;
    fout.open("output");
    fout << dresult[0];
    fout.close();
    
    

	return 0;
     
}
