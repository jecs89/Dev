#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <random>
#include "iomanip"
#include <sstream>
#include <algorithm>
#include <thread>

#include "lib_fun.h"

using namespace std;


int sgn(double x){
	return ( x > 0 ) ? 1 : 0;
}

double sigmoid(double a){
	return 1.0/( 1.0 + exp(-a) );
}

double my_sum( double x_1, double x_2, double bias, double y, vector<vector<double>> w ){
	double val = x_1 * w[0][0] + x_2 * w[1][0] + bias * w[2][0];
//	cout << val << endl;
	return sgn( val );
}


int main(int argc, char const *argv[]){
	
	/*string name;
	cin >> name;
*/
	vector<double> params(2);
	vector<vector<double>> patterns;

	//reading_params(name,params,patterns);

	//AND
	double pattern [4][3] = { 0, 1, 0, 
						   0, 0, 0, 
						   1, 0, 0, 
						   1, 1, 1 };


	//Artificial Pattern
	// double pattern [4][3] = { 1.5, 3, 0, 
	// 					   3.5, 4, 1, 
	// 					   1.0, 2, 0, 
	// 					   4.0, 2, 1 };


	vector<vector<double>> W ( 3, vector<double>(2));
	vector<vector<double>> bias (3, vector<double>(2));

	//init
	default_random_engine rng( random_device{}() ); 		
	uniform_real_distribution<double> dist( 0, 1 ); 
	cout << "initial weigths\n";

	for (int i = 0; i < 3; ++i){
		for(int j = 0 ; j < W[0].size() ; j++){
			W[i][j] = dist(rng);
			bias[i][j] = 1.0;
			cout << W[i][j] << "\t";
		}
		cout << endl;
	}
	

	double n = 0.5;

	double sum = 0.0;

	int maxIter = 1;
	int iter = 0;

	int n_hidden = 3;

	vector<double> z( n_hidden );


	while( iter < maxIter ){
		cout << "Iteration " << iter << endl;

	 	for (int i = 0; i < 4; ++i){
	 		cout << "pattern " << i << endl;

	 		//sum = my_sum( pattern[i][0], pattern[i][1], bias, pattern[i][2], W_1 );

	 		//Sum for hidden neurons
	 		for( int i_z = 0 ; i_z < z.size() ; i_z++ ){
	 			cout << "h neuron " << i_z << endl;
	 			z[i_z] = 0;
	 			for( int i_p = 0 ; i_p < 2 ; i_p++ ){
	 				z[i_z] += pattern[i][i_p]*W[i_z][0];
	 			}
	 			z[i_z] += 1.0*W[2][0];

	 			cout << z[i_z] << endl;
	 		}



	// 		//cout << "sum: " << sum << "vs" << pattern[i][2] << endl;

	// 		double my_error;
	// 		if( sum != pattern[i][2] ){
	// 			my_error = ( pattern[i][2] - sum );
	// 			//cout << "--" << my_error << endl;
	// 			W_1[0][0] = W_1[0][0] + n * pattern[i][0] * my_error;
	// 			W_1[1][0] = W_1[1][0] + n * pattern[i][1] * my_error;
	// 			W_1[2][0] = W_1[2][0] + n * bias * my_error;
	// 		}
	// 		//cout << "weigths " << setw(10) << W_1[0][0] << setw(10) << W_1[1][0] << setw(10) << W_1[2][0] << setw(4) << my_error << endl;
	 	}
		iter++;
	}

	/* code */
	return 0;
}