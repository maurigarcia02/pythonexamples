

//Holaaaa


complex* FFT_simple(complex* x, int N /* must be a power of 2 */);


complex* FFT_simple(complex* x, int N /* must be a power of 2 */) {
    complex* X = (complex*) malloc(sizeof(struct complex_t) * N);

    complex * d, * e, * D, * E;
    int k;
    if (N == 1) {
        X[0] = x[0];
        return X;
    }
    e = (complex*) malloc(sizeof(struct complex_t) * N/2);
    d = (complex*) malloc(sizeof(struct complex_t) * N/2);
    
    for(k = 0; k < N/2; k++) {
        e[k] = x[2*k];
        d[k] = x[2*k + 1];
    }
    E = FFT_simple(e, N/2);
    D = FFT_simple(d, N/2);
    free(e);
    free(d);
    for(k = 0; k < N/2; k++) {
        /* Multiply entries of D by the twiddle factors e^(-2*pi*i/N * k) */
        D[k] = complex_mult(complex_from_polar(1, -2.0*PI*k/N), D[k]);
    }
    for(k = 0; k < N/2; k++) {
        X[k]       = complex_add(E[k], D[k]);
        X[k + N/2] = complex_sub(E[k], D[k]);
    }
    free(D);
    free(E);
    return X;
}
