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
	
	string name;
	cin >> name;

	vector<double> params;
	vector<vector<double>> pattern;

	reading_params(name,params,pattern);

	print("p\n", params);
	//print("p\n", pattern);

	//AND
/*	double pattern [4][3] = { 0, 0, 0, 
						   0, 1, 0, 
						   1, 0, 0, 
						   1, 1, 1 };
*/					

	   
	//XOR
	/*double pattern [4][4] = { 0.0, 0.0, 0.0, 0.0,
						      0.0, 1.0, 1.0, 0.0, 
						      1.0, 0.0, 0.0, 1.0,
						      1.0, 1.0, 0.0, 0.0};
						      */

	//Ordering pattern, the 1th col -> last col
	for( int i = 0 ; i < pattern.size() ; i++ ){
		double tmp = pattern[i][0];
		for( int j = 1 ; j < pattern[0].size() ; j++ ){
			pattern[i][j-1] = pattern[i][j];
		}
		pattern[i][pattern[0].size()-1] = tmp;
	}

	int nro_class = 3;

	//Adding columns to have a out neuron specialized
	vector<vector<double>> pattern_aug( pattern.size(), vector<double>( pattern[0].size() + nro_class - 1 ) );

	for( int i = 0 ; i < pattern_aug.size() ; i++ ){

		for( int j = 0 ; j < pattern[0].size() ; j++ ){
			pattern_aug[i][j] = pattern[i][j];
		}

		if( pattern_aug[i][pattern[0].size()-1] == 1 ){
			pattern_aug[i][pattern[0].size()] = 0;
			pattern_aug[i][pattern[0].size()+1] = 0;
		}
		else if( pattern_aug[i][pattern[0].size()-1] == 2 ){
			pattern_aug[i][pattern[0].size()-1] = 0;
			pattern_aug[i][pattern[0].size()]   = 1;
			pattern_aug[i][pattern[0].size()+1] = 0;
		}
		else if( pattern_aug[i][pattern[0].size()-1] == 3 ){
			pattern_aug[i][pattern[0].size()-1] = 0;
			pattern_aug[i][pattern[0].size()]   = 0;
			pattern_aug[i][pattern[0].size()+1] = 1;
		}
	}

	//print("p\n", pattern_aug);

	pattern = pattern_aug;

    int nro_pattern = params[0];
	int D = params[1] - params[2];
	int O = params[2];

	double n = 0.5;

	double sum = 0.0;

	int maxIter = atoi(argv[1]);
	int iter = 0;

	int n_hidden = D;

	vector<vector<double>> W ( D*n_hidden + 1, vector<double>(2) );

	default_random_engine rng( random_device{}() ); 		
	uniform_real_distribution<double> dist( -1, 1 ); 

	//cout << "initial weigths\n";

	
	for (int i = 0; i < W.size() ; ++i){
		for(int j = 0 ; j < W[0].size() ; j++){
			W[i][j] = dist(rng);
			//W[i][j] = 0.5;
			//cout << W[i][j] << "\t";
		}
		//cout << endl;
	}
	

	vector<double> z( n_hidden );
	vector<double> f_z( n_hidden );

	vector<double> y( O );
	vector<double> f_y( O );


	vector<vector<double>> upd_W ( W.size(), vector<double>(2));

	for (int i = 0; i < upd_W.size() ; ++i){
		for (int j = 0; j < upd_W[0].size() ; ++j){
			upd_W[i][j] = W[i][j];
		}
	}

	double max_error = 1e-6;

	double total_error = 0;

	while( iter < maxIter || total_error > max_error ){
		//cout << "Iteration " << iter << endl;

	 	for (int i = 0; i < nro_pattern; ++i){
	 		//cout << "pattern " << i << endl;

	 		//to manage indexes properly
	 		int i_w = 0;
	 		int i_w_lim = D;

	 		//Sum for hidden neurons
	 		for( int i_z = 0 ; i_z < z.size() ; i_z++ ){
	 			z[i_z] = 0;

	 			for( int i_p = 0 ; i_p < D ; i_p++  ){
	 				z[i_z] += pattern[i][i_p]*W[i_w][0];
	 				i_w++;
	 			}
	 			z[i_z] += 1.0*W[W.size()-1][0]; //Adding bias

	 			i_w = D;

	 			f_z[i_z] = sigmoid(z[i_z]); //saving function of z
	 		}

	 		i_w = 0;
	 		i_w_lim = n_hidden;

	 		//Sum for outputs neurons
	 		for( int i_o = 0 ; i_o < y.size() ; i_o++ ){
	 			y[i_o] = 0;
	 			for( int i_h = 0 ; i_h < z.size() ; i_h++ ){
	 				y[i_o] += f_z[i_h]*W[i_w][1];
	 				i_w++;
	 			}
	 			y[i_o] += 1.0*W[W.size()-1][1]; //adding bias

	 			i_w = D;

	 			f_y[i_o] = sigmoid(y[i_o]);
	 		}

	 		//cout << "Error\n";

	 		
	 		int k;
	 		for( int i_o = 0 , k = D ; i_o < y.size() && k < D+O; i_o++, k++){
	 			total_error += error2( pattern[i][k], f_y[i_o]);
	 		}
	 		//cout << total_error << endl;

	 		//Updating W from Z--O
	 		//cout << "Updating\n";
	 		//cout << "Output Layer\n";
	 		
	 		i_w = 0;


	 		//why the second index of pattern is [D+i_z]????
	 		//is it limited for hidden neurons????
	 		// the number of weights is H*O
			for( int i_o = 0; i_o < y.size() ; i_o++ ){

	 			//cout << "o neuron " << i_o+1 << endl;

		 		double delta_w = 1.0;
		 		for( int i_z = 0 ; i_z < z.size() ; i_z++ ){

		 			double sig_y = f_y[i_o];

		 			double tmp_y = f_z[i_z];

		 			delta_w = (sig_y - pattern[i][D+i_o]) * sig_y *(1.0 - sig_y) * tmp_y ;

		 			upd_W[i_w][1] = W[i_w][1] - n * delta_w;

	 				i_w++;
		 		}
	 		}

	 		//cout << "Hidden Layer\n";
	 		i_w = 0;

		 	int idx_w = 0;

			for( int i_z = 0; i_z < z.size() ; i_z++ ){

		 		double delta_w = 1.0;

		 		double factor = 0;


	 			for( int idx_o = 0 ; idx_o < O ; idx_o++ ){
	 				double sig_y = sigmoid(y[idx_o]);
	 				factor += (sig_y - pattern[i][D+idx_o]) * sig_y * (1.0-sig_y) * W[idx_w][1];
	 				idx_w+=2;
	 			}

	 			idx_w = 1;

	 			for( int i_x = 0 ; i_x < D ; i_x++ ){

	 				double sig_z = sigmoid(z[i_z]);

	 				delta_w = factor * sig_z * (1.0-sig_z) * pattern[i][i_x];

		 			upd_W[i_w][0] = W[i_w][0] - n * delta_w;

		 			i_w++;

	 			}
	 		}

	 		//print("\nf_y",f_y);

	 		W = upd_W;

	 	}
		iter++;

		cout << total_error << " ";

		total_error = 0;
	}

	cout << endl;

	//print("\nFinal weights\n", W);

	return 0;
}

void test_1(int maxIter){

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

	int iter = 0;

	int n_hidden = D;

	vector<double> z( n_hidden );
	vector<double> f_z( n_hidden );


	int n_out = O;
	vector<double> y( n_out );
	vector<double> f_y( n_out );


	vector<vector<double>> upd_W ( 5, vector<double>(2));

	for (int i = 0; i < upd_W.size() ; ++i){
		for (int j = 0; j < upd_W[0].size() ; ++j){
			upd_W[i][j] = W[i][j];
		}
	}



	while( iter < maxIter ){
		cout << "Iteration " << iter << endl;

	 	for (int i = 0; i < 1; ++i){
	 		//cout << "pattern " << i << endl;

	 		//sum = my_sum( pattern[i][0], pattern[i][1], bias, pattern[i][2], W_1 );

	 		//to manage indexes properly
	 		int i_w = 0;
	 		int i_w_lim = D;

	 		//Sum for hidden neurons
	 		for( int i_z = 0 ; i_z < z.size() ; i_z++ ){
	 			/*cout << "h neuron " << i_z << endl;
	 			*/
	 			z[i_z] = 0;

	 			for( int i_p = 0 ; i_p < D ; i_p++  ){
	 				z[i_z] += pattern[i][i_p]*W[i_w][0];
	 				//cout << "\tw " << i_w+1 << " " << pattern[i][i_p] << "*" << W[i_w][0] << "=" << pattern[i][i_p]*W[i_w][0] << endl;
	 				i_w++;
	 			}
	 			z[i_z] += 1.0*W[4][0]; //Adding bias
	 			//cout << 1.0*W[4][0] << endl;
	 			i_w = D;
	 			//i_w_lim = (i_z+2)*D; // DELETE?

	 			f_z[i_z] = sigmoid(z[i_z]); //saving function of z

	 			/*cout << "\tz " << z[i_z] << "\t sig " << f_z[i_z] << endl;
	 			*/
	 		}

	 		i_w = 0;
	 		i_w_lim = n_hidden;

	 		//Sum for outputs neurons
	 		for( int i_o = 0 ; i_o < y.size() ; i_o++ ){
	 			/*cout << "o neuron " << i_o << endl;
	 			*/
	 			y[i_o] = 0;
	 			for( int i_h = 0 ; i_h < z.size() ; i_h++ ){
	 				y[i_o] += f_z[i_h]*W[i_w][1];
	 				//cout << "\tw " << i_w+1 << " " << sigmoid(z[i_h]) << "*" << W[i_w][1] << "=" << sigmoid(z[i_h])*W[i_w][1] << endl;
	 				i_w++;
	 			}
	 			y[i_o] += 1.0*W[4][1]; //adding bias
	 			//cout << 1.0*W[4][1] << endl;

	 			i_w = D;
	 			//i_w_lim = (i_o+2)*n_hidden; //DELETE?

	 			f_y[i_o] = sigmoid(y[i_o]);

	 			/*cout << "\tz " << y[i_o] << "\t sig " << f_y[i_o] << endl;
	 			*/
	 		}

	 		cout << "Error\n";

	 		double total_error = 0;
	 		int k;
	 		for( int i_o = 0 , k = D ; i_o < y.size() && k < D+O; i_o++, k++){
	 			//cout << pattern[i][k] << "*" << sigmoid(y[i_o]) << "=";
	 			total_error += error2( pattern[i][k], f_y[i_o]);
	 			//cout << error2(pattern[i][k],sigmoid(y[i_o])) << endl;
	 		}
	 		cout << total_error << endl;
/*
	 		print("W\n",W);
	 		print("Z:\t", z);
	 		print("f(z):\t", f_z);
	 		print("Y:\t", y);
	 		print("f(y):\t", f_y);
*/
	 		//Updating W from Z--O
	 		/*cout << "Updating\n";
	 		cout << "Output Layer\n";
	 		*/
	 		i_w = 0;


	 		//why the second index of pattern is [D+i_z]????
	 		//is it limited for hidden neurons????
	 		// the number of weights is H*O
			for( int i_o = 0; i_o < y.size() ; i_o++ ){

	 			//cout << "o neuron " << i_o+1 << endl;

		 		double delta_w = 1.0;
		 		for( int i_z = 0 ; i_z < z.size() ; i_z++ ){
					//cout << i_z + 1 << endl;
		 			//cout << "w " << i_w+1 << endl;

		 			double sig_y = f_y[i_o];

		 			//cout << "p1 = " << sig_y << " - " << pattern[i][D+i_z] << "=" << sig_y - pattern[i][D+i_z] << endl;

		 			double tmp_y = f_z[i_z];

		 			//cout << "p2 = " << sig_y << " * " << (1 - sig_y) << "=" << sig_y *(1 - sig_y) << endl;
		 			//cout << "p3 " << f_z[i_o] << endl;

		 			///cout << setw(10) << "p1" << setw(10) << "p2" << setw(10) << "p3" << endl; 
		 			///cout << setw(10) << delta_w << setw(10) << sig_y *(1 - sig_y) << setw(10) << tmp_y << endl; 

		 			delta_w = (sig_y - pattern[i][D+i_o]) * sig_y *(1.0 - sig_y) * tmp_y ;

		 			//cout << "i_o " << i_o << "\t i_z " << i_z << endl;

		 			//cout << "\t" << delta_w << endl;
		 			//cout << "\t" << W[i_w][1] << "-" << "0.5 * "<< delta_w << endl;

		 			upd_W[i_w][1] = W[i_w][1] - 0.5 * delta_w;
	 				//cout << "\t" << "upd " << upd_W[i_w][1] << endl;

	 				i_w++;
		 		}
	 		}

	 		//print("W\n",W);

	 		//cout << "Hidden Layer\n";
	 		i_w = 0;

	 		//int i_p = 0;
		 		int idx_w = 0;

			for( int i_z = 0; i_z < z.size() ; i_z++ ){

				//cout << "i_z" << i_z << endl;
	 		//for( int i_x = 0 ; i_x < D ; i_x++ ){
	 			//cout << "o neuron " << i_x+1 << endl;

		 		double delta_w = 1.0;
				//for( int i_z = 0; i_z < z.size() ; i_z++ ){

		 		double factor = 0;

		 		//int idx_o = 0;

	 			for( int idx_o = 0 ; idx_o < O ; idx_o++ ){
	 				double sig_y = sigmoid(y[idx_o]);
	 				factor += (sig_y - pattern[i][D+idx_o]) * sig_y * (1.0-sig_y) * W[idx_w][1];
	 				//cout << "i_o " << idx_o << " W " << idx_w << endl;

	 				//cout <<  sig_y << "-" << pattern[i][D+idx_o] << endl;
	 				//cout << (sig_y - pattern[i][D+idx_o]) << " * " << sig_y * (1.0-sig_y) <<  "*" << W[idx_w][1] << endl;



	 				idx_w+=2;


	 				//idx_o++;
	 			}

	 			idx_w = 1;

	 			for( int i_x = 0 ; i_x < D ; i_x++ ){

	 				//cout << "i_x" << i_x << endl;

	 				double sig_z = sigmoid(z[i_z]);

	 				delta_w = factor * sig_z * (1.0-sig_z) * pattern[i][i_x];

	 				//cout << delta_w << endl;

		 			upd_W[i_w][0] = W[i_w][0] - 0.5 * delta_w;

	 				//cout << "\t" << "upd " << setprecision(10) <<  W[i_w][0] << endl;

		 			i_w++;

	 			}
	 			/*
	 			for (int i_o = 0; i_o < O; ++i_o){

					//cout << i_z << endl;
		 			//cout << "w " << i_w+1 << endl;

		 			double sig_y = f_y[i_z];
					double tmp_y = f_z[i_z];
		 			/*
		 			cout << "p1 = " << sig_y << " - " << pattern[i][D+i_p] << "=" << sig_y - pattern[i][D+i_p] << endl;
		 			cout << "p2 = " << sig_y << " * " << (1 - sig_y) << "=" << sig_y *(1 - sig_y) << endl;
		 			cout << "p3 " << W[i_w][1] << endl;
		 			cout << "p13 = " << (sig_y - pattern[i][D+i_p] ) * sig_y *(1 - sig_y) * W[i_w][1] << endl;
		 			*/
		 			//i_z = i_z + 1;

		 			/*cout << "p1' = " << f_y[i_z] << " - " << pattern[i][D+i_p+1] << "=" << f_y[i_z] - pattern[i][D+i_p+1] << endl;
		 			cout << "p2' = " << f_z[i_z] << " * " << (1 - f_z[i_z]) << "=" << f_z[i_z] *(1 - f_z[i_z]) << endl;
		 			cout << "p3' " << W[i_w+1][1] << endl;
		 			cout << "1p3' = " << (f_y[i_z] - pattern[i][D+i_p+1]) * f_z[i_z] *(1 - f_z[i_z]) * W[i_w+1][1] << endl;

		 			cout << "p4 = " << tmp_y << " * " << (1 - tmp_y) << "=" << tmp_y *(1 - tmp_y) << endl;
		 			cout << "p5 " << pattern[i][i_p] << endl;
					*/
		 			//delta_w = ( (sig_y - pattern[i][D+i_p]) * sig_y *(1 - sig_y) * W[i_w][1] + (f_y[i_z] - pattern[i][D+i_p+1]) * (f_z[i_z] *(1 - f_z[i_z])) *  W[i_w+1][1] ) * tmp_y *(1 - tmp_y) * pattern[i][i_p] ;

		 			/*cout << "\t" << delta_w << endl;
		 			cout << "\t" << W[i_w][0] << "-" << "0.5 * "<< delta_w << endl;
		 			*/
		 			//W[i_w][0] = W[i_w][0] - 0.5 * delta_w;
	 				/*cout << "\t" << "upd " << W[i_w][0] << endl;
	 				*/
		 		//}


		 		//i_p++;
	 		}


	 		//cout << "i_W " << i_w << endl;




	 		print("f_y",f_y);

	 		W = upd_W;

	 	}
		iter++;
	}

}