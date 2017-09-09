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

/*double sigmoid(double a){
	return 1.0/( 1.0 + exp(-a) );
}*/

double sigmoid(double a){
	return 1.7159 * tanh(0.6666*a) ;
}

double activator(double val){
	return ( val > 0 ) ? 1.0:-1.0;
}

// vector<double> v_activator(vector<double>& val){
// 	vector<double> _val;
// 	_val = val;
// 	for (int i = 0; i < val.size(); ++i){
// 		_val[i] = ( _val[i] > 0 ) ? 1.0:-1.0;
// 	}
// 	return _val;
// }

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

pair<double,double> get_limits(vector<vector<double>>& data, int col){
	double max = -10e-10;
	double min = 10e+10;
	for (int i = 0; i < data.size(); ++i){
		min = (data[i][col] < min) ? data[i][col] : min;
		max = (data[i][col] > max) ? data[i][col] : max;
	}
	return pair<double,double>(min,max);
}

void shuffling_dataset(vector<vector<double>>& data){

	default_random_engine rng( random_device{}() ); 		
	uniform_real_distribution<double> dist( 0, 1 ); 

	for (int i = 0; i < data.size()/2; ++i){
		if( dist(rng) > 0.5 ){
			data[i].swap(data[data.size()-1-i]);
		}
	}
}

void prepare_dataset(vector<vector<double>>& pattern){
		//Ordering pattern, the 1th col -> last col
	for( int i = 0 ; i < pattern.size() ; i++ ){
		double tmp = pattern[i][0];
		for( int j = 1 ; j < pattern[0].size() ; j++ ){
			pattern[i][j-1] = pattern[i][j];
		}
		pattern[i][pattern[0].size()-1] = tmp;
	}

	//print("pattern\n",pattern);

	/*
	for( int i = 0 ; i < pattern.size() ; i++ ){
		for( int j = 1 ; j < pattern[0].size() ; j++ ){
			cout << pattern[i][j] <<",";
		} cout << endl;
	}

	cout << endl;
	*/

	int nro_class = 3;

	//Adding columns to have a out neuron specialized
	vector<vector<double>> pattern_aug( pattern.size(), vector<double>( pattern[0].size() + nro_class - 1 ) );

	for( int i = 0 ; i < pattern_aug.size() ; i++ ){

		for( int j = 0 ; j < pattern[0].size() ; j++ ){
			pattern_aug[i][j] = pattern[i][j];
		}

		if( pattern_aug[i][pattern[0].size()-1] == 1 ){
			pattern_aug[i][pattern[0].size()] = -1;
			pattern_aug[i][pattern[0].size()+1] = -1;
		}
		else if( pattern_aug[i][pattern[0].size()-1] == 2 ){
			pattern_aug[i][pattern[0].size()-1] = -1;
			pattern_aug[i][pattern[0].size()]   = 1;
			pattern_aug[i][pattern[0].size()+1] = -1;
		}
		else if( pattern_aug[i][pattern[0].size()-1] == 3 ){
			pattern_aug[i][pattern[0].size()-1] = -1;
			pattern_aug[i][pattern[0].size()]   = -1;
			pattern_aug[i][pattern[0].size()+1] = 1;
		}
	}
	/*
	for( int i = 0 ; i < pattern_aug.size() ; i++ ){
		for( int j = 1 ; j < pattern_aug[0].size() ; j++ ){
			cout << pattern_aug[i][j] <<",";
		} cout << endl;
	}

	cout << endl;
	*/

	//Getting limits
	vector<pair<double,double>> v_limits;

	for( int j = 0 ; j < (pattern_aug[0].size()-3) ; j++ ){
		pair<double,double> limits = get_limits(pattern_aug,j);
		cout << j << " " << limits.first << "\t" << limits.second << endl;
		v_limits.push_back(limits);
	}

	//Normalizing data

	double a = 0.0;
	double b = 1.0;

	for( int i = 0 ; i < pattern_aug.size() ; i++ ){
		for( int j = 0 ; j < (pattern_aug[0].size()-3) ; j++ ){
			pattern_aug[i][j] = (pattern_aug[i][j] - v_limits[j].first) / ( v_limits[j].second - v_limits[j].first ) * (b-a) + a  ;
		}
	}
	/*
	for( int i = 0 ; i < pattern_aug.size() ; i++ ){
		for( int j = 1 ; j < pattern_aug[0].size() ; j++ ){
			cout << pattern_aug[i][j] <<",";
		} cout << endl;
	}

	cout << endl;
	*/

	pattern = pattern_aug;
	shuffling_dataset(pattern);
	//print("p\n", pattern_aug);
}


int main(int argc, char const *argv[]){
	
	string name = "wine.data";
	//cin >> name;

	vector<double> params;
	vector<vector<double>> pattern;

	cout << "reading\n";
	reading_params(name,params,pattern);
	cout << "reading\n";

	print("p\n", params);
	//print("p\n", pattern);

	prepare_dataset(pattern);

	params[1] = 13 + 3;
	params[2] = 1 + 2;

	print("P\n", params);

	//print("p\n", pattern);

    int nro_pattern = params[0];
	int D = params[1] - params[2];
	int O = params[2];

	double n = 0.0025;
	double momentum = -0.005;
	int maxIter = atoi(argv[1]);
	int iter = 0;

	int n_hidden = D;

	vector<vector<double>> W ( D*n_hidden + 1, vector<double>(2) );
	vector<vector<double>> W_t ( D*n_hidden + 1, vector<double>(2) );

	default_random_engine rng( random_device{}() ); 
	double rnd_limit = 4.0 * (sqrt(6)/sqrt(13+3));
	uniform_real_distribution<double> dist( -rnd_limit, rnd_limit ); 

	for (int i = 0; i < W.size() ; ++i){
		for(int j = 0 ; j < W[0].size() ; j++){
			W_t[i][j] = 0;
		}
	}

	//cout << "initial weigths\n";
	//output layer
	for (int i = 0; i < W.size() ; ++i){
		//for(int j = 0 ; j < W[0].size() ; j++){
			//W[i][j] = dist(rng);
			W[i][1] = dist(rng);
			//W[i][j] = 0.5;
		//}
	}

	//hidden layer
	for (int i = 0; i < W.size() ; ++i){
			W[i][0] = dist(rng);
			//W[i][j] = 0.5;
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
	
		int precision = 0;
		//n = n / double(iter+1);

		cout << "Iteration --> " << iter << " ";

	 	for (int i = 0; i < nro_pattern; ++i){
	 		//cout << "pattern " << i << " ";

	 		//print( "", pattern[i], 13,16 );

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

	 		//Printing the output layer
	 		// for (int i = 0; i < f_y.size(); ++i){
	 		// 	cout << setw(8) << activator(f_y[i]);
	 		// }
	 		// cout << endl;
	 		
	 		int k;

	 		//cout << total_error << endl;
	 		for( int i_o = 0 , k = D ; i_o < y.size() && k < D+O; i_o++, k++){
	 			total_error += error2( pattern[i][k], activator(f_y[i_o]));
	 			//total_error += error2( pattern[i][k], f_y[i_o]);
	 			//cout << "error: " << pattern[i][k] << " "<< f_y[i_o] << " " << activator(f_y[i_o]) << endl;
	 			//cout << total_error << "\n";
	 		}

	 		if( total_error == 0 ){
	 			precision++;
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

		 			delta_w = (sig_y - pattern[i][D+i_o]) * 1.14393 * (1.0-tanh(y[i_o])*tanh(y[i_o])) * tmp_y ;

		 			upd_W[i_w][1] = W[i_w][1] - n * delta_w + momentum * ( W[i_w][1] - W_t[i_w][1] ) ;

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
	 				factor += (sig_y - pattern[i][D+idx_o]) * 1.14393 * (1.0-tanh(y[idx_o])*tanh(y[idx_o])) * W[idx_w][1];
	 				idx_w+=2;
	 			}

	 			idx_w = 1;

	 			for( int i_x = 0 ; i_x < D ; i_x++ ){

	 				double sig_z = sigmoid(z[i_z]);

	 				delta_w = factor * 1.14393 * (1.0-tanh(z[i_z])*tanh(z[i_z])) * pattern[i][i_x];

		 			upd_W[i_w][0] = W[i_w][0] - n * delta_w + momentum * ( W[i_w][0] - W_t[i_w][0] );

		 			i_w++;

	 			}
	 		}

	 		//cout << pattern[i][D] << " " << pattern[i][D+1] << " " << pattern[i][D+2] << endl;

	 		//if( iter % 1000 == 0 ) 
	 			//print("\nf_y",f_y);

	 		W = upd_W;

	 		W_t = W;

	 	}

		iter++;

		cout << total_error << " ";
		cout << (precision*100.0)/pattern.size() << endl;

		total_error = 0;
	}

	cout << endl;

	//print("\nFinal weights\n", W);

	return 0;
}