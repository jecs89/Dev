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

vector<double> vsigmoid(vector<double> a){
	vector<double> y(a.size());
	for (int i = 0; i < y.size(); ++i){
		y[i] = sigmoid(y[i]);
	}
	return y;
}

double my_sum( double x_1, double x_2, double bias, double y, vector<vector<double>> w ){
	double val = x_1 * w[0][0] + x_2 * w[1][0] + bias * w[2][0];
//	cout << val << endl;
	return sgn( val );
}

double error2(double x, double y){
	return (x-y)*(x-y)*0.5;

}


int main(int argc, char const *argv[]){
	
	/*string name;
	cin >> name;
*/
	vector<double> params(2);
	vector<vector<double>> patterns;

	//reading_params(name,params,patterns);

	//AND
	/*double pattern [4][3] = { 0, 1, 0, 
						   0, 0, 0, 
						   1, 0, 0, 
						   1, 1, 1 };
*/


	int D = 2;
	int O = 2;

	double pattern [1][4] = { 0.05, 0.1, 0.01, 0.99};

	//Artificial Pattern
	// double pattern [4][3] = { 1.5, 3, 0, 
	// 					   3.5, 4, 1, 
	// 					   1.0, 2, 0, 
	// 					   4.0, 2, 1 };


	vector<vector<double>> W ( 5, vector<double>(2));
	vector<vector<double>> bias (3, vector<double>(2));

	//init
	default_random_engine rng( random_device{}() ); 		
	uniform_real_distribution<double> dist( 0, 1 ); 
	cout << "initial weigths\n";

	W[0][0] = .15;
	W[1][0] = .20;
	W[2][0] = .25;
	W[3][0] = .30;
	W[4][0] = .35;
	 
	W[0][1] = .40;
	W[1][1] = .45;
	W[2][1] = .50;
	W[3][1] = .55;
	W[4][1] = .60;

	/*
	for (int i = 0; i < 3; ++i){
		for(int j = 0 ; j < W[0].size() ; j++){
			//W[i][j] = dist(rng);
			//W[i][j] = 0.5;
			bias[i][j] = 1.0;
			cout << W[i][j] << "\t";
		}
		cout << endl;
	}
	*/

	double n = 0.5;

	double sum = 0.0;

	int maxIter = 1;
	int iter = 0;

	int n_hidden = D;

	vector<double> z( n_hidden );

	int n_out = O;
	vector<double> y( n_out );


	while( iter < maxIter ){
		cout << "Iteration " << iter << endl;

	 	for (int i = 0; i < 1; ++i){
	 		cout << "pattern " << i << endl;

	 		//sum = my_sum( pattern[i][0], pattern[i][1], bias, pattern[i][2], W_1 );

	 		int i_w = 0;
	 		int i_w_lim = D;

	 		//Sum for hidden neurons
	 		for( int i_z = 0 ; i_z < z.size() ; i_z++ ){
	 			cout << "h neuron " << i_z << endl;
	 			z[i_z] = 0;

	 			for( int i_p = 0 ; i_p < D ; i_p++  ){
	 				z[i_z] += pattern[i][i_p]*W[i_w][0];
	 				//cout << "\tw " << i_w+1 << " " << pattern[i][i_p] << "*" << W[i_w][0] << "=" << pattern[i][i_p]*W[i_w][0] << endl;
	 				i_w++;
	 			}
	 			z[i_z] += 1.0*W[4][0];
	 			//cout << 1.0*W[4][0] << endl;

	 			i_w = D;
	 			i_w_lim = (i_z+2)*D;

	 			cout << "\tz " << z[i_z] << "\t sig " << sigmoid(z[i_z]) << endl;
	 		}

	 		i_w = 0;
	 		i_w_lim = n_hidden;

	 		//Sum for outputs neurons
	 		for( int i_o = 0 ; i_o < y.size() ; i_o++ ){
	 			cout << "o neuron " << i_o << endl;
	 			y[i_o] = 0;
	 			for( int i_h = 0 ; i_h < z.size() ; i_h++ ){
	 				y[i_o] += sigmoid(z[i_h])*W[i_w][1];
	 				//cout << "\tw " << i_w+1 << " " << sigmoid(z[i_h]) << "*" << W[i_w][1] << "=" << sigmoid(z[i_h])*W[i_w][1] << endl;
	 				i_w++;
	 			}
	 			y[i_o] += 1.0*W[4][1];
	 			//cout << 1.0*W[4][1] << endl;

	 			i_w = D;
	 			i_w_lim = (i_o+2)*n_hidden;

	 			cout << "\tz " << y[i_o] << "\t sig " << sigmoid(y[i_o]) << endl;
	 		}

	 		cout << "Error\n";

	 		double total_error = 0;
	 		int k;
	 		for( int i_o = 0 , k = D ; i_o < y.size() && k < D+O; i_o++, k++){
	 			//cout << pattern[i][k] << "*" << sigmoid(y[i_o]) << "=";
	 			total_error += error2( pattern[i][k], sigmoid(y[i_o]));
	 			//cout << error2(pattern[i][k],sigmoid(y[i_o])) << endl;
	 		}
	 		//cout << total_error << endl;

	 		print("W\n",W);
	 		print("Z:\t", z);
	 		//print("Y:\t", vsigmoid(y));

	 		//Updating W from Z--O
	 		cout << "Updating\n";

	 		i_w = 0;
	 		for( int i_z = 0 ; i_z < z.size() ; i_z++ ){
	 			cout << "o neuron " << i_z+1 << endl;

		 		double delta_w = 1.0;
				for( int i_o = 0; i_o < y.size() ; i_o++ ){
					cout << i_o << endl;
		 			cout << "w " << i_w+1 << endl;

		 			double sig_y = sigmoid(y[i_o]);
		 			//delta_w = sig_y - pattern[i][D+i_o];

		 			cout << "p1 = " << sig_y << " - " << pattern[i][D+i_z] << "=" << sig_y - pattern[i][D+i_z] << endl;

		 			double tmp_y = sigmoid(z[i_o]);

		 			cout << "p2 = " << sig_y << " * " << (1 - sig_y) << "=" << sig_y *(1 - sig_y) << endl;
		 			cout << "p3 " << sigmoid(z[i_o]) << endl;

		 			//cout << setw(10) << "p1" << setw(10) << "p2" << setw(10) << "p3" << endl; 
		 			//cout << setw(10) << delta_w << setw(10) << sig_y *(1 - sig_y) << setw(10) << tmp_y << endl; 


		 			delta_w = (sig_y - pattern[i][D+i_z]) * sig_y *(1 - sig_y) * tmp_y ;

		 			cout << "\t" << delta_w << endl;

		 			cout << "\t" << W[i_w][1] << "-" << "0.5 * "<< delta_w << endl;

		 			W[i_w][1] = W[i_w][1] - 0.5 * delta_w;

	 				cout << "\t" << "upd " << W[i_w][1] << endl;

	 				i_w++;
		 		}
	 		}
	 	}
		iter++;
	}

	/* code */
	return 0;
}