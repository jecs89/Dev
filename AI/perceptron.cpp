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

using namespace std;


int sgn(double x){
	return ( x > 0 ) ? 1 : 0;
}

double my_sum( double x_1, double x_2, double bias, double y, vector<vector<double>> w ){
	double val = x_1 * w[0][0] + x_2 * w[1][0] + bias * w[2][0];
	cout << val << endl;
	return sgn( val );
}


int main(int argc, char const *argv[]){

	//AND
	// int pattern [4][3] = { 0, 1, 0, 
	// 					   0, 0, 0, 
	// 					   1, 0, 0, 
	// 					   1, 1, 1 };


	double pattern [4][3] = { 1.5, 3, 0, 
						   3.5, 4, 1, 
						   1.0, 2, 0, 
						   4.0, 2, 1 };


	vector<vector<double>> W_1 ( 3, vector<double>(1));
	double bias = 1.0;

	//init
	default_random_engine rng( random_device{}() ); 		
	uniform_real_distribution<double> dist( 0, 1 ); 
	cout << "initial weigths\n";

	W_1[0][0] = 0.5;
	W_1[1][0] = -0.1;
	W_1[2][0] = 0.2;

	for (int i = 0; i < 3; ++i){
	//	W_1[i][0] = dist(rng);
		cout << W_1[i][0] << "\t";
	}
	cout << endl;

	double n = 0.9;

	double sum = 0.0;

	for (int i = 0; i < 4; ++i){
		cout << "pattern " << i << endl;

		sum = my_sum( pattern[i][0], pattern[i][1], bias, pattern[i][2], W_1 );
		cout << "sum: " << sum << "vs" << pattern[i][2] << endl;

		double my_error;
		if( sum != pattern[i][2] ){
			my_error = ( pattern[i][2] - sum );
			cout << "--" << my_error << endl;
			W_1[0][0] = W_1[0][0] + n * pattern[i][0] * my_error;
			W_1[1][0] = W_1[1][0] + n * pattern[i][1] * my_error;
			W_1[2][0] = W_1[2][0] + n * bias * my_error;
		}
		cout << "weigths " << setw(8) << W_1[0][0] << setw(8) << W_1[1][0] <<  setw(8) << W_1[2][0] << setw(8) << my_error << endl;
	}

		for (int i = 0; i < 4; ++i){
		cout << "pattern " << i << endl;

		sum = my_sum( pattern[i][0], pattern[i][1], bias, pattern[i][2], W_1 );
		cout << "sum: " << sum << "vs" << pattern[i][2] << endl;

		double my_error;
		if( sum != pattern[i][2] ){
			my_error = ( pattern[i][2] - sum );
			cout << "--" << my_error << endl;
			W_1[0][0] = W_1[0][0] + n * pattern[i][0] * my_error;
			W_1[1][0] = W_1[1][0] + n * pattern[i][1] * my_error;
			W_1[2][0] = W_1[2][0] + n * bias * my_error;
		}
		cout << "weigths " << setw(8) << W_1[0][0] << setw(8) << W_1[1][0] <<  setw(8) << W_1[2][0] << setw(8) << my_error << endl;
	}


	/* code */
	return 0;
}