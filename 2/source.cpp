#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Matrix {
		//Two dimensional matrix class.
		double **A;
	public:
		//Filling matrix A and finding dimension of matrix
		int setMatrix(ifstream&);
		//Solving the Ax=b equation
		double *solvingLinearEq(double*,int);
		//Matrix multiplication
		double *multiplication(double*, int);
		//Finding the largest eigenvalue
		void largestEigenvalue(Matrix&,int,char**);
		//Finding the smallest eigenvalue
		void smallestEigenvalue(Matrix&,int,char**);
		//Deleting the matrix A
		void delMatrix(int);
};


int Matrix::setMatrix(ifstream& file) {
	//This function fills the matrix A by using input file and find the dimension of the matrix A.

	//Getting the value of n for an n x n matrix
	int n = 0;
	string line;
	while (file.eof()==0) {		//When reading is at the end of the file the loop ends.
		getline(file,line);		//The n value increases for every line.
		n = n + 1;				//At the end, n will equal the total line number.
	}

	//Returning at the beginning of the file because we got to the end of the file while determining the n value.
	file.seekg(0);

	//Creating the matrix A by using dynamically allocated memory
	A = new double *[n];
	for(int i = 0; i < n; i++) {
		A[i] = new double [n];
	}

	//The matrix A is filled with the values in the file which is the input of the function.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			file >> A[i][j];
		}
	}

	//Returning the value of n
	return n;
}

double *Matrix::solvingLinearEq(double *b, int n) {
	//This function solves the Ax=b equation.

	//Creating the matrix A by using dynamically allocated memory
	double **r;
	r = new double *[n];
	for(int i = 0; i < n; i++) {
		r[i] = new double [n];
	}

	//The matrix r is the same as the matrix A.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			r[i][j] = A[i][j];
		}
	}
	//Matrix r is created because matrix A should not change in order to get correct answer.
	//Operations are applied on r matrix in this function.


	//The variables used while applying Gaussian elimination with partial pivoting.
	double mult;
	double temp;
	double max;
	int m;

	//Gaussian Elimination with Partial Pivoting
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {		//"j" starts from "i" because the values above the diagonals does not concern us.

			//Partial Pivoting: Choosing the entry of largest magnitude on or below the diagonal as pivot.
			if(i == j) {					//To apply Gaussian elimination with partial pivonting, we must be on the diagonal.
				max = r[i][j];				//The diagonal is accepted as maximum value.
				m = i;						//Maximum entry's row number is kept.
				for(int k = i+1; k < n ; k++) {								//While we move down the matrix, the process number will decrease.
					if((r[k][i] > max && r[k][i] != 0) || max == 0) {		//The entries belove the diagonal should be bigger than maximum entry and not be 0.
						max = r[k][i];										//Also, maximum entry cannot be 0. When the criteria is met the maximum entry will be updated
						m = k;												//and its row number will be kept.
					}
				}
				for (int k = 0; k < n; k++) {  			//Before this part, the maximum entry's row number is kept.
					temp = r[m][k];						//In this part, the row exchange is applied to matrix r.
					r[m][k] = r[i][k];
					r[i][k] = temp;
				}
				temp = b[m];							//To solve the equation correctly, the rows of the vector b should exchange, too.
				b[m] = b[i];
				b[i] = temp;

				//Gaussian Elimination: To get an upper triangle matrix, the entries below the diagonals is eliminated.
				for (int k = 1; k < n - j; k++) {					//Before this part, partial pivoting is applied to matrix r and vector b.
					mult = r[j+k][i] / r[j][i]; 					//While we move down the matrix, the process number will decrease.
					for (int l = 0; l < n; l++) {					//While "k" is increasing, the entries below the diagonal is divided by diagonal and "mult" is determined.
						r[j+k][l] = r[j+k][l] - r[j][l]*mult;		//Then, the whole column which is below the diagonal is updated.
					}												//This is done by subtracting the product of the entry on the diagonal's row and "mult" from the entry below the diagonal.
					b[j+k] = b[j+k] - b[j]*mult;					//To solve the equation correctly, the vector b is updated, too.
				}
			}
		}
	}

	//Singularity Test
	int sing = 1;									//"sing" is an flag variable for singularity control.
	double product = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {				//After generating the upper triangle matrix by using
			if(i == j) {      						//Gaussian elimination with partial pivoting,
				product = product * r[i][j];		//the diagonals are multiplied with each other.
			}										//If "product" is zero, that means the matrix is singular.
		}
	}
	if(product < 0.000001 && product > -0.000001) {    //Machine Precision: To be more precise,
		sing = 0;									 //when "product" is very close to 0,
	}												 //the matrix is still considered to be singular.
	//If "product" is 0 or very close to 0, then the flag variable is equal to 0.

	//Back Substitution
	if(sing == 0) {									 //If flag variable is equal to 0, then the function returns 0.
		return 0;									 //If flag variable is equal to 1, then
	} else {										 //the function continues to back substution.

		//Creating the x matrix by using dynamically allocated memory
		double *x;
		x = new double [n];

		//Filling the x matrix with back substution
		double eq;									 //"eq" represents the values in the b matrix.
		for (int i = n - 1; i >= 0; i--) {			 //To apply back substution, the loop is started at n-1.
			eq = b[i];								 //"eq" is updated, every time the first loop repeats.
			for(int k = i + 1; k < n; k++) {      	 //k = i + 1, because the loop started at the end and
				eq = eq - x[k] * r[i][k];			 //there will be more process while "i" decreases.
			}										 //"eq" is updated by back substution in the second loop and
			x[i] = eq / r[i][i];					 //to find the values of x, "eq" is divided by the diagonal which is on the same row.
		}
		return x;									 //Returning matrix x
	}

}

double *Matrix::multiplication(double *b, int n) {
	//This function carries out A*b process and return the output.
	double *x;
	x = new double [n];

	for(int i = 0; i < n; i++) {
		x[i] = 0;
	}

	double temp;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			temp = A[i][j] * b[j];
			x[i] = x[i] + temp;
		}
	}

	return x;
}

void Matrix::largestEigenvalue(Matrix& mat,int n,char** argv) {
	//This function calculates the largest eigenvalue and its corresponding eigenvector.
	
	//Creating the vectors that will be used to find the eigenvalue and eigenvector.
	double *ctrl;
	ctrl = new double [n];
	double *eigenvector;
	eigenvector = new double [n];

	//A nonzero vector
	for(int i = 0; i < n; i++) {
		eigenvector[i] = 1;
	}

	double norm = 1;
	double eigenvalue;

	//Normalized power iteration
	while(norm > atof(argv[2])) {										//atof(argv[2]) is tolerance value and it determines when the loop will end.
		
		//Multiplying the nonzero vector repeatedly every time the loop starts.
		eigenvector = mat.multiplication(eigenvector,n);

		//Normalization		
		eigenvalue = eigenvector[0];
		for(int i = 0; i < n; i++) {
			if((eigenvector[i] > eigenvalue && eigenvector[i] != 0) || eigenvalue == 0) {			
				eigenvalue = eigenvector[i];							//This part finds the largest nonzero value of the vector.
			}
		}
		for(int i = 0; i < n; i++) {
			eigenvector[i] = eigenvector[i] / eigenvalue;				//The vector is divided by the largest nonzero value.
		}

		//To control whether (A*eigenvector - eigenvalue*eigenvector) is converging to 0.
		for(int i = 0; i < n; i++) {
			ctrl[i] = mat.multiplication(eigenvector,n)[i] - eigenvalue * eigenvector[i];
		}

		//Calculating infinity norm of the matrix ctrl.
		for(int i = 0; i < n; i++) {
			if(ctrl[i] < 0) {
				ctrl[i] = ctrl[i] * -1;
			}
		}
		norm = ctrl[0];
		for(int i = 0; i < n; i++) {
			if(ctrl[i] > norm) {
				norm = ctrl[i];
			}
		}

	}
	
	//Deleting the matrix ctrl in order not to take up useless space
	delete[] ctrl;

	//The eigenvalue and its corresponding eigenvector is written on an output file.
	ofstream myfile1 (argv[3]);
	myfile1 << "The largest eigenvalue:" << eigenvalue << "\r\n" << "Corresponding eigenvector:" << "\r\n";
	for(int i = 0; i < n; i++) {
		myfile1 << eigenvector[i] << "\r\n";
	}

	//The file is closed.
	myfile1.close();
	//Deleting the matrix eigenvector in order not to take up useless space
	delete[] eigenvector;
}

void Matrix::smallestEigenvalue(Matrix& mat,int n,char** argv) {
	//This function calculates the smallest eigenvalue and its corresponding eigenvector.
	
	//Creating the vectors that will be used to find the eigenvalue and eigenvector.
	double *y;
	y = new double [n];
	double *ctrl;
	ctrl = new double [n];
	double *eigenvector;
	eigenvector = new double [n];

	//A nonzero vector
	for(int i = 0; i < n; i++) {
		eigenvector[i] = 1;
	}

	double temp;
	double norm = 1;
	double eigenvalue;

	int flag = 1;
	int a;

	//Normalized inverse power iteration
	while(norm > atof(argv[2])) {								//atof(argv[2]) is tolerance value and it determines when the loop will end.
		
		//Solving the A*x = eigenvector equation
		eigenvector = mat.solvingLinearEq(eigenvector,n);
		//If the matrix is singular then the flag variable will be zero and the loop ends.
		if(eigenvector == 0) {
			flag = 0;
			break;
		}
		
		//Normalization
		eigenvalue = eigenvector[0];
		for(int i = 0; i < n; i++) {
			if((eigenvector[i] > eigenvalue && eigenvector[i] != 0) || eigenvalue == 0) {
				eigenvalue = eigenvector[i];							//This part finds the largest nonzero value of the vector.
			}
		}
		for(int i = 0; i < n; i++) {
			eigenvector[i] = eigenvector[i] / eigenvalue;				//The vector is divided by the largest nonzero value.
		}

		//Finding the eigenvalue because by using inverse iteration, the eigenvector can be found. However, the eigenvalue cannot be found directly.
		for(int i = 0; i < n; i++) {
			if(eigenvector[i] != 0) {
				temp = eigenvector[i];									//In case of having 0 in eigenvector, 
				a = i;													//a nonzero value and its index are found in this loop.
				break;
			}
		}
		y = mat.multiplication(eigenvector,n);							//The matrix is multiplied by eigenvector.
		eigenvalue = y[a] / temp;										//Eiganvalue is found.

		//To control whether (A*eigenvector - eigenvalue*eigenvector) is converging to 0.
		for(int i = 0; i < n; i++) {
			ctrl[i] = mat.multiplication(eigenvector,n)[i] - eigenvalue * eigenvector[i];
		}

		//Calculating infinity norm of the matrix ctrl.
		for(int i = 0; i < n; i++) {
			if(ctrl[i] < 0) {
				ctrl[i] = ctrl[i] * -1;
			}
		}
		norm = ctrl[0];
		for(int i = 0; i < n; i++) {
			if(ctrl[i] > norm) {
				norm = ctrl[i];
			}
		}
	}
	
	//Deleting the matrix y and ctrl in order not to take up useless space
	delete[] y;
	delete[] ctrl;

	if(flag == 1) {
		
		//If the matrix is nonsingular, the eigenvalue and its corresponding eigenvector is written on an output file.
		ofstream myfile2 (argv[3], ios::app);
		myfile2 << "The smallest eigenvalue:" << eigenvalue << "\r\n" << "Corresponding eigenvector:" << "\r\n";
		for(int i = 0; i < n; i++) {
			myfile2 << eigenvector[i] << "\r\n";
		}
		//The file is closed.
		myfile2.close();
		//Deleting the matrix eigenvector in order not to take up useless space
		delete[] eigenvector;
		
	} else {
		
		//If the matrix is singular, the eigenvalue and its corresponding eigenvector cannot be found by inverse iteration.
		ofstream myfile2 (argv[3], ios::app);
		myfile2 << "Inverse iteration cannot be applied because the matrix is singular !";
		//The file is closed.
		myfile2.close();
		
	}
}

void Matrix::delMatrix(int n) {
	//Deleting the matrix inside the object
	for(int i = 0; i < n; i++) {
		delete[] A[i];
	}
	delete[] A;
}

int main(int argc, char* argv[]) {

	//Opening file to read the matrices
	ifstream myfile (argv[1]);

	//Checking if the file is opened correctly
	if (myfile.is_open() == 0) {					
		ofstream myfile3 (argv[3]);
		myfile3 << "Unable to open input file !";		
		//The file is closed.
		myfile3.close();
	} else {

		//Creating the object
		Matrix mat;
		//The object is filled with the values in "myfile" and the dimension of matrix is determined.
		int n = mat.setMatrix(myfile);
		//myfile is closed because the values in it is now in the object.
		myfile.close();

		//Finding the largest eigenvalue and its corresponding eigenvector.
		mat.largestEigenvalue(mat,n,argv);
		//Finding the smallest eigenvalue and its corresponding eigenvector.
		mat.smallestEigenvalue(mat,n,argv);

		//Deleting the matrix inside the object in order not to take up useless space.
		mat.delMatrix(n);

	}
	return 0;
}
