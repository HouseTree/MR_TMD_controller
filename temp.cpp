
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

//int main() {

//        double array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//        double* out;
//        double* err;
//        int i, size = 10;

//        fftw_complex* out_cpx;

//        fftw_plan fft;
//        fftw_plan ifft;
//        out_cpx = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * size);
//        out = (double*)malloc(size * sizeof(double));
//        if (out == NULL) {
//                exit(1);
//        }
//        err = (double*)malloc(size * sizeof(double));
//        if (err == NULL) {
//                exit(1);
//        }

//        fft = fftw_plan_dft_r2c_1d(size, array, out_cpx, FFTW_ESTIMATE);  //Setup fftw plan for fft
//        ifft = fftw_plan_dft_c2r_1d(size, out_cpx, out, FFTW_ESTIMATE);   //Setup fftw plan for ifft

//        fftw_execute(fft);
//        fftw_execute(ifft);

//        for (i = 0; i < size; i++) {
//                err[i] = (array[i] - out[i]);
//                printf("%f\t%f\n", (array[i]), out[i] / size);//需要做归一化处理
//        }

//        fftw_destroy_plan(fft);
//        fftw_destroy_plan(ifft);
//        fftw_free(out_cpx);
//        free(err);
//        free(out);

//        system("pause");
//        return 0;
//}
