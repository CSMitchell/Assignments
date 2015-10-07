/*
	Cody Mitchell
	Intro/Pattern Recognition Proj 1
	2 class Bayesian Decision Rule
*/


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include "Matrix.h"
#include "Pr.h"




using namespace std; 






double probability(Matrix covs, const Matrix &tedata, Matrix means, int d)
{
	double mdist = mah(tedata, covs, means); //squared Mahalanobis distance

	double param = -.5*mdist*mdist;
	double divisor = (2*M_PI)*sqrt(det(covs));
	double p = ((1/(divisor)))*exp(param);
	return p;
}

int discriminant(Matrix *covs, const Matrix &tedata, Matrix *means, const Matrix &Pw, int caseno, const Matrix &covsum, const Matrix &covavg)
{
	Matrix disc(1,2), sdisc(1,2), pos(1,2); 
	double mdist, edist;
	double varavg, sum = 0;
	int i;

	for(i=0; i<2; i++)
		sum+=covavg(i, i);
	varavg = sum/(double)2; 

	switch(caseno)
	{
	case 1:
		for(i=0; i<2; i++)
		{
			edist = euc(tedata, means[i]);  	//euclidian distance
			disc(0,i) = -edist*edist/(2*varavg) + log(Pw(i,0)); 
		}
	break; 
	case 2:
		for(i=0; i<2; i++)
		{
			mdist = mah(tedata, covavg, means[i]); 
			disc(0,i) = -0.5*mdist*mdist + log(Pw(i,0)); 
		}
	break;
	case 3:
		for(i=0; i<2; i++)
		{
			mdist = mah(tedata, covs[i], means[i]); 
			disc(0,i) = -0.5*mdist*mdist - 0.5*log(det(covs[i])) + log(Pw(i,0)); 
		}
	break;

	}
	insertsort(disc, sdisc, pos);//sort the discriminant function value in ascending order
	
	return (int)pos(0,1); //return the label of the class with the largest disc value; 
		
}

int main(int argc, char **argv)
{
	int nrTr, nrTe, nc, i, type; 
	double prob1, prob2; 
	Matrix Tr, Te;
	Matrix tmp, covsum, covavg;
	static Matrix *means, *covs; 
	
	int classes = 2; 
	int nf = 2; 

	//Read data in from the data file

	nc = nf + 1; 
	Tr = readData("synth.tr", nc); 
	nrTr = Tr.getRow(); 
	Te = readData("synth.te", nc); 
	nrTe = Te.getRow(); 

	
		
	means = (Matrix *) new Matrix [classes]; 	//calculate mean and covariance of classes
	for (i=0; i<classes; i++) 
		means[i].createMatrix(nf, 1); 
	covs = (Matrix *) new Matrix [classes];
	for (i=0; i<classes; i++)
		covs[i].createMatrix(nf, nf); 
	

	covsum.createMatrix(nf, nf);
	covavg.createMatrix(nf, nf);

	for (i=0; i<classes; i++)
	{	
		
		tmp = getType(Tr, i); 
		covs[i] = cov(tmp, nf);
		means[i] = mean(tmp, nf);
		covsum = covsum + covs[i]; 
	}
		
	Matrix Pw(classes, 1); //assign prior probability
	Pw(0,0) = .5; 		//declare equal prior prob, can be changed for testing
	Pw(1,0) = .5;

	covavg = covsum/(double)classes;
	int errorCount = 0; //used for calculating accuracy

	cout <<"mean" << endl;
	for (i=0; i<classes; i++)
	{	
		cout << means[i] << endl;
	}
	cout << "cov" << endl; 
	for (i=0; i<classes; i++)
	{
		cout << covs[i] << endl;
	}
	for(i=0; i<nrTe; i++)//Likelihood Ratio Loop
	{

		Matrix sample = transpose(subMatrix(Te, i, 0, i, nf-1)); //cut out a sample of data to use in the LR function
		prob1 = probability(covs[0], sample, means[0], nf); //p(x|w1)
		prob2 = probability(covs[1], sample, means[1], nf); //p(x|w2)
		
		if(prob1/prob2 > (Pw(0,0)/Pw(1,0)))
			type = 0; 
		else
			type = 1; 
		if(type != Te(i, nf))
		{
			errorCount++;
		}

	}
	double accuracy;
	accuracy = 100-(((double)errorCount/nrTe)*100); 
	cout << "Accuracy using LR: " << accuracy <<"%" << endl; 
	errorCount = 0;
	for(i=0; i<nrTe; i++)//check class 1
	{
		Matrix sample = transpose(subMatrix(Te, i, 0, i, nf-1));
		type = discriminant(covs, sample, means, Pw, 1, covsum, covavg); 
		if(type != Te(i, nf))
			errorCount++; 

		
	}
	accuracy = 100-(((double)errorCount/nrTe)*100); 

	cout << "Accuracy using Case1: " << accuracy <<"%" << endl; 
	
	errorCount =0;
	for(i=0; i<nrTe; i++)//check class 2
	{
		Matrix sample = transpose(subMatrix(Te, i, 0, i, nf-1));
		type = discriminant(covs, sample, means, Pw, 2, covsum, covavg); 
		if(type != Te(i, nf))
			errorCount++; 


		
	}
	accuracy = 100-(((double)errorCount/nrTe)*100); 
	
	cout << "Accuracy using Case2: " <<  accuracy << "%"<< endl; 
	errorCount =0;
	for(i=0; i<nrTe; i++)//check class 3
	{
		Matrix sample = transpose(subMatrix(Te, i, 0, i, nf-1));
		type = discriminant(covs, sample, means, Pw, 3, covsum, covavg); 
		if(type != Te(i, nf))
			errorCount++; 
	}

	accuracy = 100-(((double)errorCount/nrTe)*100); 
	cout << "Accuracy using Case3: " << accuracy<<"%" << endl; 



}
