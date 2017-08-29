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

double my_error( double x_1, double x_2, double y, vector<vector<double>> w ){

	double sum = 0.0;

	sum = x_1 * w[0][0] + x_2 * w[1][0];
	sum = sum * sum * 0.5;

	return sum;
}

int main(int argc, char const *argv[]){

	//AND
	int pattern [4][3] = { 0, 1, 0, 
						   0, 0, 0, 
						   1, 0, 0, 
						   1, 1, 1 };

	vector<vector<double>> W_1 ( 2, vector<double>(1));

	//init
	for (int i = 0; i < 2; ++i){
		W_1[i][0] = 0.5;
	}

	double sum = 0.0;
	for (int i = 0; i < 4; ++i){
		sum += my_error( pattern[i][0], pattern[i][1], pattern[i][2], W_1 );
	}

	cout << sum << endl;

	/* code */
	return 0;
}