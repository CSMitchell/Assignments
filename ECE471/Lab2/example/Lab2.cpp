#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "Matrix.h"
#include "Pr.h"

using namespace std; 

int main(int argc, char **argv)
{
	int i, j, nrTr, nrTe, nc; 
	Matrix X, nX; 
	Matrix *means, *covs;
	Matrix tmp; 
	int classes = 2; 
	int nf = 7;

	nc = nf + 1; //The data dimension; plus the one label column
	X = readData("pima.tr", nc); 
	nrTr = X.getRow(); 


	means = (Matrix *) new Matrix [classes];
	for(i=0; i<classes; i++)
	{
		means[i].createMatrix(nf,1);
	}
	
	covs = (Matrix *) new Matrix [classes];
	for(i=0; i<classes; i++)
	{
		covs[i].createMatrix(nf, nf); 
	}
	
	for(i=0; i<classes; i++)
	{
		tmp = getType(X,i); 
		covs[i] = cov(tmp, nf);
		means[i] = mean(tmp, nf);
	}

	cout << "Mean\n"; 
	for(i=0; i<classes; i++)
	{
		cout << means[i]<< endl;
	}
	cout << "Covs\n"; 
	for(i=0; i<classes; i++)
	{
		cout << covs[i] << endl;
	}
	cout << endl; 
	cout << X(0,1)<<endl;
}

