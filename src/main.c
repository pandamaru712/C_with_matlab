#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "matrix.h"
#include "tmwtypes.h"
#define  BUFSIZE 2048

int main()

{
	Engine *ep;
	char buffer[BUFSIZE+1] = {'\0'};
	mxArray *mx_x = NULL;
	mxArray *mx_fval = NULL;
	mx_x = mxCreateDoubleMatrix(1, 36, mxREAL);

	double *x, *fval;

	if (!(ep = engOpen(""))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}

	double f[36] = {-1, -4, -45, -51, -29, -42, -16, -1, -25, -39, -24, -35, -3, -23, -1, -56, -78, -10, -11, -34, -22, -1, -7, -67, -45, -23, -65, -55, -1, -76, -12, -6, -95, -67, -52, -1};
	mxArray *mx_f = NULL;
	mx_f = mxCreateDoubleMatrix(1, 36, mxREAL);
	memcpy((void *)mxGetPr(mx_f), (void *)f, sizeof(f));

	double dummyA[10][36] =
		{{0, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   	 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   	 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   	 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0, -1, 0, 0, 0, 0, 0, 0},
   	 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, 0},
   	 {0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0},
   	 {0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0},
   	 {0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0},
   	 {0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0},
   	 {0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0}};
	double A[10][36];
	int i, j, no;
	for(j=0; j<36; j++){
		for(i=0; i<10; i++){
			no = 10 * j + i + 1;
			if(no%36!=0){
				A[no/36][no%36-1] = dummyA[i][j];
			}else{
				A[no/36-1][35] = dummyA[i][j];
			}
		}
	}
	mxArray *mx_A = NULL;
	mx_A = mxCreateDoubleMatrix(10, 36, mxREAL);
	memcpy((void *)mxGetPr(mx_A), (void *)A, sizeof(A));

	double b[10] = {-5, -10, -12.5, -7.5, -15, -10, -22.5, -2.5, -7.5, -7.5};
	mxArray *mx_b = NULL;
	mx_b = mxCreateDoubleMatrix(1, 10, mxREAL);
	memcpy((void *)mxGetPr(mx_b), (void *)b, sizeof(b));

	double dummyAeq[2][36] =
		{{0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
       {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}};
	double Aeq[2][36];
	for(j=0; j<36; j++){
		for(i=0; i<2; i++){
			no = 2 * j + i + 1;
			if(no%36!=0){
				Aeq[no/36][no%36-1] = dummyAeq[i][j];
			}else{
				Aeq[no/36-1][35] = dummyAeq[i][j];
			}
		}
	}
	mxArray *mx_Aeq = NULL;
	mx_Aeq = mxCreateDoubleMatrix(2, 36, mxREAL);
	memcpy((void *)mxGetPr(mx_Aeq), (void *)Aeq, sizeof(Aeq));

	double beq[2] = {100, 0};
	mxArray *mx_beq = NULL;
	mx_beq = mxCreateDoubleMatrix(1, 2, mxREAL);
	memcpy((void *)mxGetPr(mx_beq), (void *)beq, sizeof(beq));

	double lb[36] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	mxArray *mx_lb = NULL;
	mx_lb = mxCreateDoubleMatrix(1, 36, mxREAL);
	memcpy((void *)mxGetPr(mx_lb), (void *)lb, sizeof(lb));

	engPutVariable(ep, "mx_f", mx_f);
	engPutVariable(ep, "mx_A", mx_A);
	engPutVariable(ep, "mx_b", mx_b);
	engPutVariable(ep, "mx_Aeq", mx_Aeq);
	engPutVariable(ep, "mx_beq", mx_beq);
	engPutVariable(ep, "mx_lb", mx_lb);

	engOutputBuffer(ep, buffer, BUFSIZE);

	//engEvalString(ep, "mx_A");
	//printf("%s", buffer);

	engEvalString(ep, "[x, fval] = linprog(mx_f, mx_A, mx_b, mx_Aeq, mx_beq, mx_lb, []);");
	//printf("%s", buffer);
	engEvalString(ep, "x = x ./ 100;");
	//printf("%s", buffer);

	engEvalString(ep, "fval = fval / (-100);");
	//printf("%s", buffer);

	//printf("Hit return to continue\n\n");
	//fgetc(stdin);

	mx_x = engGetVariable(ep, "x");
	//((void *)x, (void *)mxGetPr(mx_x), sizeof(mxGetPr(mx_x)));
	x = mxGetPr(mx_x);
	mx_fval = engGetVariable(ep, "fval");
	fval = mxGetPr(mx_fval);

	printf("\n-----Optimization terminated.-----\n");
	for(i=0; i<36; i++){
		if(x[i]>0.00001){
			printf("   x[%d] = %f\n", i, x[i]);
		}
	}
	printf("   fval = %f\n\n", *fval);

	mxDestroyArray(mx_f);
	mxDestroyArray(mx_A);
	mxDestroyArray(mx_b);
	mxDestroyArray(mx_Aeq);
	mxDestroyArray(mx_beq);
	mxDestroyArray(mx_lb);
	mxDestroyArray(mx_x);
	engEvalString(ep, "close;");

	engClose(ep);

	return EXIT_SUCCESS;
}
