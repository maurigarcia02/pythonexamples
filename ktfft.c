
#include <math.h>

typedef struct complex_t {
    double re;
    double im;
} complex;

complex complex_from_polar(double r, double theta_radians);
double  complex_magnitude(complex c);
complex complex_add(complex left, complex right);
complex complex_sub(complex left, complex right);
complex complex_mult(complex left, complex right);


complex complex_from_polar(double r, double theta_radians) {
    complex result;
    result.re = r * cos(theta_radians);
    result.im = r * sin(theta_radians);
    return result;
}
double complex_magnitude(complex c) {
    return sqrt(c.re*c.re + c.im*c.im);
}
complex complex_add(complex left, complex right) {
    complex result;
    result.re = left.re + right.re;
    result.im = left.im + right.im;
    return result;
}
complex complex_sub(complex left, complex right) {
    complex result;
    result.re = left.re - right.re;
    result.im = left.im - right.im;
    return result;
}
complex complex_mult(complex left, complex right) {
    complex result;
    result.re = left.re*right.re - left.im*right.im;
    result.im = left.re*right.im + left.im*right.re;
    return result;
}



//Funcion de fft
complex* FFT_simple(complex* x, int N /* must be a power of 2 */) {
    complex* X = (complex*) malloc(sizeof(struct complex_t) * N);

    complex * d, * e, * D, * E;
    int k;

    if (N == 1) {
        X[0] = x[0];
        return X; // Breakpoint
    }
    //Asignar espacio * el tamano del array
    e = (complex*) malloc(sizeof(struct complex_t) * N/2);
    d = (complex*) malloc(sizeof(struct complex_t) * N/2);
    
    // Separar el array en pares e impares
     for(k = 0; k < N/2; k++) {
        e[k] = x[2*k];
        d[k] = x[2*k + 1];
    }

    // Recursion hasta llegar a N=1
    E = FFT_simple(e, N/2);
    // Media recursion --------------------------

    D = FFT_simple(d, N/2);

    //Final de recursion ------------------------

    // Liberar espacio, ya que devolvieron el valor.
    free(e);
    free(d);

    // Odd DFT 
    for(k = 0; k < N/2; k++) {
        /* Multiply entries of D by the twiddle factors e^(-2*pi*i/N * k) */
        D[k] = complex_mult(complex_from_polar(1, -2.0*PI*k/N), D[k]);
    }

    // Encontrar valores de Xk
    for(k = 0; k < N/2; k++) {
        X[k]       = complex_add(E[k], D[k]);
        X[k + N/2] = complex_sub(E[k], D[k]);
    }

    free(D);
    free(E);
    return X;
}   

