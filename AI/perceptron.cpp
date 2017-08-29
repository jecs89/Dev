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
	return ( x > 1 ) ? 1 : 0;
}

double my_sum( double x_1, double x_2, double y, vector<vector<double>> w ){

	return sgn( x_1 * w[0][0] + x_2 * w[1][0] );
}


int main(int argc, char const *argv[]){

	//AND
	int pattern [4][3] = { 0, 1, 0, 
						   0, 0, 0, 
						   1, 0, 0, 
						   1, 1, 1 };

	vector<vector<double>> W_1 ( 2, vector<double>(1));

	//init
	cout << "initial weigths\n";
	for (int i = 0; i < 2; ++i){
		W_1[i][0] = 0.5;
		cout << W_1[i][0] << "\t";
	}
	cout << endl;

	double n = 0.5;

	double sum = 0.0;
	for (int i = 0; i < 4; ++i){
		cout << "pattern " << i << endl;

		sum = my_sum( pattern[i][0], pattern[i][1], pattern[i][2], W_1 );

		if( sum != pattern[i][2] ){
			double my_error = ( pattern[i][2] - sum );
			my_error = my_error * my_error * 0.5;
			W_1[0][0] = W_1[0][0] + n * pattern[i][0] * my_error;
			W_1[1][0] = W_1[1][0] + n * pattern[i][1] * my_error;
		}
		cout << "weigths " << W_1[0][0] << "\t" << W_1[0][1] << endl;
	}

	/* code */
	return 0;
}