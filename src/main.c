#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "matrix.h"
#include "tmwtypes.h"
#define  BUFSIZE 1024

int main()

{
	Engine *ep;
	char buffer[BUFSIZE+1] = {'\0'};

	if (!(ep = engOpen(""))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}

	double f[] = {-1, -4, -45, -51, -29, -42, -16, -1, -25, -39, -24, -35, -3, -23, -1, -56, -78, -10, -11, -34, -22, -1, -7, -67, -45, -23, -65, -55, -1, -76, -12, -6, -95, -67, -52, -1};
	mxArray *mx_f = NULL;
	mx_f = mxCreateDoubleMatrix(1, 36, mxREAL);
	memcpy((void *)mxGetPr(mx_f), (void *)f, sizeof(f));

	double A[10][36] = {{0, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0, -1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, 0},
    {0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0},
    {0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0},
    {0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0},
    {0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0}};
	mxArray *mx_A = NULL;
	mx_A = mxCreateDoubleMatrix(10, 36, mxREAL);
	memcpy((void *)mxGetPr(mx_A), (void *)A, sizeof(A));

	double b[] = {-5, -10, -12.5, -7.5, -15, -10, -22.5, -2.5, -7.5, -7.5};
	mxArray *mx_b = NULL;
	mx_b = mxCreateDoubleMatrix(1, 10, mxREAL);
	memcpy((void *)mxGetPr(mx_b), (void *)b, sizeof(b));

	double Aeq[2][36] = {{0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
       {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}};
	mxArray *mx_Aeq = NULL;
	mx_Aeq = mxCreateDoubleMatrix(2, 36, mxREAL);
	memcpy((void *)mxGetPr(mx_Aeq), (void *)Aeq, sizeof(Aeq));

	double beq[] = {100, 0};
	mxArray *mx_beq = NULL;
	mx_beq = mxCreateDoubleMatrix(1, 2, mxREAL);
	memcpy((void *)mxGetPr(mx_beq), (void *)beq, sizeof(beq));

	double lb[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	mxArray *mx_lb = NULL;
	mx_lb = mxCreateDoubleMatrix(1, 36, mxREAL);
	memcpy((void *)mxGetPr(mx_lb), (void *)f, sizeof(lb));

	engPutVariable(ep, "mx_f", mx_f);
	engPutVariable(ep, "mx_A", mx_A);
	engPutVariable(ep, "mx_b", mx_b);
	engPutVariable(ep, "mx_Aeq", mx_Aeq);
	engPutVariable(ep, "mx_beq", mx_beq);
	engPutVariable(ep, "mx_lb", mx_lb);

	engEvalString(ep, "[x, fval] = linprog(mx_f, mx_A, mx_b, mx_Aeq, mx_beq, mx_lb, []);");
	engOutputBuffer(ep, buffer, BUFSIZE);
	engEvalString(ep, "x = x ./ 100");
	printf("%s", buffer);

	engEvalString(ep, "fval = fval / (-100)");
	printf("%s", buffer);

	printf("Hit return to continue\n\n");
	fgetc(stdin);

	printf("Done for optimization.\n");
	mxDestroyArray(mx_f);
	mxDestroyArray(mx_A);
	mxDestroyArray(mx_b);
	mxDestroyArray(mx_Aeq);
	mxDestroyArray(mx_beq);
	mxDestroyArray(mx_lb);
	engEvalString(ep, "close;");

	engClose(ep);

	return EXIT_SUCCESS;
}
