#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_cdf.h> //for cdf 
#include <gsl/gsl_randist.h> //for pdf 

double prob_rain_more_than_n(const double * p, int size, int n)
{
	double mu = 0.0, sigma = 0.0, gamma = 0.0, sum_prob = 0.0;
	for(size_t i=0;i<size;i++)
	{
		mu += p[i];
		sigma += p[i]*( 1-p[i] );
		sum_prob += ( p[i]*(1-p[i])*(1-2*p[i]) );
	}
	sigma = sqrt(sigma);
	gamma = 1/(pow(sigma,3)) * sum_prob;
	
	double z = (n + 0.5 - mu) / sigma;
	double phi = gsl_ran_ugaussian_pdf( z );
	double Phi = gsl_cdf_ugaussian_P( z );

	double g = Phi + gamma*( 1 - pow(z,2) ) * phi/6;
	double F = g > 0.0 ? g : 0.0;
	
	printf("mu:%.3lf sigma:%.3lf z:%.3lf g:%.3lf F:%.3lf\n",mu,sigma,z,g,F);
	
	return 1 - F;
}

int main(int argc, char ** argv)
{
	double p[365];
	int n;
	
	srand(20250402); //todays' date, just to get replicable values.
	
	for(int i=0;i<365;i++)
		p[i] = rand()/(double)RAND_MAX;
	
	//n = rand() % 365;
	n=100;
	
	printf("n:%d Probabilities:\n",n);
	for(int i=0;i<365;i++)
		printf("%d:%.2lf ",i,p[i]);
	printf("\n");
	
	int size = sizeof(p)/sizeof(p[0]);
	double proba = prob_rain_more_than_n(p, size, n);
	
	printf("The probability of more than %d days  is:%.4lf\n",n,proba);
	
	return 0;
}