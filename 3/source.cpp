#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

class Polynomial {
		//The coefficients of the polynomial.
		double *polynom;
		//Lower and higher initial values.
		double *low_high;
		//Given tolerance value.
		double tolerance;
	public:
		//polynom, low_high and tolerance values are set.
		int setValues(int,char**);
		//This function finds the results of the polynomial.
		double polynomMult(double,int);
		//This function makes one bisection iteration.
		double *bisection(double,double,int);
		//This function makes one secant iteration.
		double secant(double,double,int);
		//This function applies Bisection Method.
		void bisectionMethod(int,char**);
		//This function applies Secant Method.
		void secantMethod(int,char**);
		//This function applies Hybrid Method.
		void hybridMethod(int,char**);
		//This function deletes the values in the object.
		void delPolynom(int);
};

int Polynomial::setValues(int argc, char** argv) {
	//Lower initial value and higher initial value are kept in low_high.
	low_high = new double [2];
	low_high[0] = atof(argv[1]);
	low_high[1] = atof(argv[2]);

	//atof(argv[3]) is the tolerance value.
	tolerance = atof(argv[3]);

	//n is the number of coefficients.
	int n = argc - 4;

	//Inputs of the polynom are in the polynom variable.
	polynom = new double [n];
	for (int i = 0; i < n; i++) {
		polynom[i] = atof(argv[4+i]);
	}
	return n;
}

double Polynomial::polynomMult(double x, int n) {
	//This function finds the results of the polynomial and returns.
	double result = 0;
	for(int i = 0; i < n; i++) {
		result = result + polynom[i] * pow(x, n-1-i);
	}
	return result;
}

double* Polynomial::bisection(double low, double high, int n) {
	//This function makes one bisection iteration.

	double *result;
	result = new double [2];
	//Average value of low and high values.
	double average = (low + high) / 2;
	//The function value of average value.
	double value = polynomMult(average,n);
	//According to function values of low and high values, the values are updated differently.
	if(polynomMult(low,n) < polynomMult(high,n)) {
		if(value > 0) {
			result[0] = low;
			result[1] = average;
			return result;
		} else if(value < 0) {
			result[0] = average;
			result[1] = high;
			return result;
		} else {
			//If the average value is a root of the polynomial, then 0s returns.
			cout << "The root is " << average << ".\n";
			result[0] = 0;
			result[1] = 0;
			return result;
		}
	} else {
		if(value < 0) {
			result[0] = low;
			result[1] = average;
			return result;
		} else if(value > 0) {
			result[0] = average;
			result[1] = high;
			return result;
		} else {
			//If the average value is a root of the polynomial, then 0s returns.
			cout << "The root is " << average << ".\n";
			result[0] = 0;
			result[1] = 0;
			return result;
		}
	}
}

double Polynomial::secant(double low, double high, int n) {
	//This function makes one secant iteration.
	double a = polynomMult(high, n);
	double b = polynomMult(low, n);
	double c = high - low;
	return high - ((a*c)/(a-b));
}

void Polynomial::bisectionMethod(int n, char** argv) {
	//This function applies Bisection Method.

	//Determining the function values of the initial guesses.
	double low_value = polynomMult(low_high[0],n);
	double high_value = polynomMult(low_high[1],n);

	cout << "Bisection method:\n";
	if((low_value < 0 && high_value < 0) || (low_value > 0 && high_value > 0)) {
		//If the signs of initial guesses are the same, then program gives an error.
		cout << "Error! The signs of initial guesses are the same.\n";
	} else if(low_value == 0) {
		//If the lower initial guess is a root of the polynomial, there is no need to iteration.
		cout << "The root is " << low_high[0] << ".\n";
		cout << "Number of iterations is 0.\n";
	} else if(high_value == 0) {
		//If the higher initial guess is a root of the polynomial, there is no need to iteration.
		cout << "The root is " << low_high[1] << ".\n";
		cout << "Number of iterations is 0.\n";
	} else {
		//Bisection Method is applied.
		double tol = 1;
		int counter = 0;
		int flag = 0;
		//Tolerance value determines when the loop will end.
		while(tol > tolerance) {
			//If the number of iterations exceeds 15, the program terminates.
			if(counter == 15) {
				//Flag value controls whether the number of iterations is higher than 15.
				flag = 1;
				break;
			}
			//Bisection iteration is applied on higher and lower values. And the values are updated.
			low_high = bisection(low_high[0],low_high[1],n);
			//If 0s returns from bisection function, this means the root is found.
			if(low_high[0] == 0 && low_high[1] == 0) {
				counter = counter + 1;
				break;
			}
			//Tolerance value is the difference between higher and lower values.
			tol = low_high[1] - low_high[0];
			if(tol < 0) {
				//Tolerance value must be positive.
				tol = tol*-1;
			}
			//The number of iterations.
			counter = counter + 1;
		}
		if(flag == 0) {
			if(low_high[0] != 0 && low_high[1] != 0) {
				//Determining the function values of final values.
				low_value = polynomMult(low_high[0],n);
				high_value = polynomMult(low_high[1],n);
				//Which function values is closer to 0 is determined and the approximate root is found.
				if(low_value*-1 > high_value) {
					cout << "The root is " << low_high[1] << ".\n";
				} else if(low_value*-1 < high_value) {
					cout << "The root is " << low_high[0] << ".\n";
				} else {
					cout << "The root is " << low_high[1] << ".\n";
				}
			}
			//Number of iterations is printed.
			cout << "Number of iterations is " << counter << ".\n";
		} else if(flag == 1) {
			//If the number of iterations exceeds 15.
			cout << "The number of iterations exceeds 15.\n";
		}
		//Lower and higher initial values are reseted.
		low_high[0] = atof(argv[1]);
		low_high[1] = atof(argv[2]);
	}
}

void Polynomial::secantMethod(int n, char** argv) {
	//This function applies Secant Method.

	//Determining the function values of the initial guesses.
	double low_value = polynomMult(low_high[0],n);
	double high_value = polynomMult(low_high[1],n);

	cout << "Secant method:\n";
	if(low_value == 0) {
		//If the lower initial guess is a root of the polynomial, there is no need to iteration.
		cout << "The root is " << low_high[0] << ".\n";
		cout << "Number of iterations is 0.\n";
	} else if(high_value == 0) {
		//If the higher initial guess is a root of the polynomial, there is no need to iteration.
		cout << "The root is " << low_high[1] << ".\n";
		cout << "Number of iterations is 0.\n";
	} else {
		//Secant Method is applied.
		double tol = 1;
		int counter = 0;
		int flag = 0;
		//Tolerance value determines when the loop will end.
		while(tol > tolerance) {
			//If the number of iterations exceeds 15, the program terminates.
			if(counter == 15) {
				flag = 1;
				break;
			}
			//Secant iteration is applied on higher and lower values. And the values are updated.
			double temp = low_high[1];
			low_high[1] = secant(low_high[0], low_high[1], n);
			low_high[0] = temp;
			//Tolerance value is the difference between higher and lower values.
			tol = low_high[1] - low_high[0];
			if(tol < 0) {
				//Tolerance value must be positive.
				tol = tol * -1;
			}
			//The number of iterations.
			counter = counter + 1;
		}
		if(flag == 0) {
			//Determining the function values of final values.
			low_value = polynomMult(low_high[0],n);
			high_value = polynomMult(low_high[1],n);
			//Which function values is closer to 0 is determined and the approximate root is found.
			if(low_value*-1 > high_value) {
				cout << "The root is " << low_high[1] << ".\n";
			} else if(low_value*-1 < high_value) {
				cout << "The root is " << low_high[0] << ".\n";
			} else {
				cout << "The root is " << low_high[1] << ".\n";
			}
			//Number of iterations is printed.
			cout << "Number of iterations is " << counter << ".\n";
		} else if(flag == 1) {
			//If the number of iterations exceeds 15.
			cout << "The number of iterations exceeds 15.\n";
		}
		//Lower and higher initial values are reseted.
		low_high[0] = atof(argv[1]);
		low_high[1] = atof(argv[2]);
	}
}

void Polynomial::hybridMethod(int n,char** argv) {
	//This function applies Hybrid Method.

	//Determining the function values of the initial guesses.
	double low_value = polynomMult(low_high[0],n);
	double high_value = polynomMult(low_high[1],n);

	cout << "Hybrid method:\n";
	if((low_value < 0 && high_value < 0) || (low_value > 0 && high_value > 0)) {
		//If the signs of initial guesses are the same, then program gives an error.
		//Because bisection method is used at the first two iterations.
		cout << "Error! The signs of initial guesses are the same.\n";
	} else if(low_value == 0) {
		//If the lower initial guess is a root of the polynomial, there is no need to iteration.
		cout << "The root is " << low_high[0] << ".\n";
		cout << "Number of iterations is 0.\n";
	} else if(high_value == 0) {
		//If the higher initial guess is a root of the polynomial, there is no need to iteration.
		cout << "The root is " << low_high[1] << ".\n";
		cout << "Number of iterations is 0.\n";
	} else {
		//Hybrid method is applied.
		double tol = 1;
		int counter = 0;
		int flag = 0;
		//Tolerance value determines when the loop will end.
		while(tol > tolerance) {
			//Bisection method is applied on the first two iterations.
			low_high = bisection(low_high[0],low_high[1],n);
			//If the average value is a root of the polynomial, then 0s returns.
			if(low_high[0] == 0 && low_high[1] == 0) {
				counter = counter + 1;
				break;
			}
			//Tolerance value is the difference between higher and lower values.
			tol = low_high[1] - low_high[0];
			if(tol < 0) {
				//Tolerance value must be positive.
				tol = tol*-1;
			}
			//The number of iterations.
			counter = counter + 1;
			//Loop ends after 2 iterations.
			if(counter == 2) {
				break;
			}
		}
		if(low_high[0] != 0 && low_high[1] != 0) {
			//Tolerance value determines when the loop will end.
			while(tol > tolerance) {
				//If the number of iterations exceeds 15, the program terminates.
				if(counter == 15) {
					flag = 1;
					break;
				}
				//Secant iteration is applied on higher and lower values. And the values are updated.
				double temp = low_high[1];
				low_high[1] = secant(low_high[0], low_high[1], n);
				low_high[0] = temp;
				//Tolerance value is the difference between higher and lower values.
				tol = low_high[1] - low_high[0];
				if(tol < 0) {
					//Tolerance value must be positive.
					tol = tol * -1;
				}
				//The number of iterations.
				counter = counter + 1;
			}
		}
		if(flag == 0) {
			if(low_high[0] != 0 && low_high[1] != 0) {
				//Determining the function values of final values.
				low_value = polynomMult(low_high[0],n);
				high_value = polynomMult(low_high[1],n);
				//Which function values is closer to 0 is determined and the approximate root is found.
				if(low_value*-1 > high_value) {
					cout << "The root is " << low_high[1] << ".\n";
				} else if(low_value*-1 < high_value) {
					cout << "The root is " << low_high[0] << ".\n";
				} else {
					cout << "The root is " << low_high[1] << ".\n";
				}
			}
			//Number of iterations is printed.
			cout << "Number of iterations is " << counter << ".\n";
		} else if(flag == 1) {
			//If the number of iterations exceeds 15.
			cout << "The number of iterations exceeds 15.\n";
		}
		//Lower and higher initial values are reseted.
		low_high[0] = atof(argv[1]);
		low_high[1] = atof(argv[2]);
	}
}

void Polynomial::delPolynom(int n) {
	//Deleting the values inside the object.
	delete[] polynom;
	delete[] low_high;
}


int main(int argc, char* argv[]) {

	//Object is created.
	Polynomial polynom;

	//n value is determined and the values are set.
	int n = polynom.setValues(argc,argv);

	//Bisection Method
	polynom.bisectionMethod(n,argv);
	//Secant Method
	polynom.secantMethod(n,argv);
	//Hybrid Method
	polynom.hybridMethod(n,argv);
	
	//Deleting the values inside the object in order not to take up useless space.
	polynom.delPolynom(n);

	return 0;

}
