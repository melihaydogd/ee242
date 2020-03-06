#include <iostream>
#include <fstream>

using namespace std;

void findCondition(double **m, double **inv, int n) {
	//This function finds the condition numbers of a 2 x 2 matrix by using 1-norm and infinity-norm.

	//To calculate 1-norm and infinity-norm, every value in the matrix m should be absolute value.
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(m[i][j] < 0) {
				m[i][j] = m[i][j] * -1;
			}
		}
	}
	//To calculate 1-norm and infinity-norm, every value in the inverse matrix m should be absolute value.
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(inv[i][j] < 0) {
				inv[i][j] = inv[i][j] * -1;
			}
		}
	}

	//The variables which keep 1-norm and infinity-norm values
	double norm1_m;
	double norm1_inv;
	double norminf_m;
	double norminf_inv;

	//Finding 1-norms of the matrix m and the inverse matrix m
	if(m[0][0] + m[1][0] > m[0][1] + m[1][1]) {				 //The columns of the matrix m is summed and then, compared.
		norm1_m = m[0][0] + m[1][0];						 //1-norm of the matrix m is the biggest summation of the columns.
	} else {
		norm1_m = m[0][1] + m[1][1];
	}
	if(inv[0][0] + inv[1][0] > inv[0][1] + inv[1][1]) {		 //The columns of the inverse matrix m is summed and then, compared.
		norm1_inv = inv[0][0] + inv[1][0];					 //1-norm of the inverse matrix m is the biggest summation of the columns.
	} else {
		norm1_inv = inv[0][1] + inv[1][1];
	}

	//Finding infinity-norms of the matrix m and the inverse matrix m
	if(m[0][0] + m[0][1] > m[1][0] + m[1][1]) {				 //The rows of the matrix m is summed and then, compared.
		norminf_m = m[0][0] + m[0][1];						 //Infinity-norm of the matrix m is the biggest summation of the rows.
	} else {
		norminf_m = m[1][0] + m[1][1];
	}
	if(inv[0][0] + inv[0][1] > inv[1][0] + inv[1][1]) {	 	 //The rows of the inverse matrix m is summed and then, compared.
		norminf_inv = inv[0][0] + inv[0][1];				 //Infinity-norm of the inverse matrix m is the biggest summation of the rows.
	} else {
		norminf_inv = inv[1][0] + inv[1][1];
	}

	//The 1-Norm Condition Number is equal to product of the 1-norm of the matrix m and 1-norm of the inverse matrix m.
	cout << "1-Norm Condition Number = " << norm1_m * norm1_inv << "\n";

	//The Infinity-Norm Condition Number is equal to product of the infinity-norm of the matrix m and infinity-norm of the inverse matrix m.
	cout << "Infinity-Norm Condition Number = " << norminf_m * norminf_inv << "\n";
}



int main() {

	//Opening files to read the matrices
	ifstream myfile1 ("A.txt");
	ifstream myfile2 ("b.txt");

	//Checking if the files are opened correctly
	if (myfile1.is_open() == 0 && myfile2.is_open() == 0) {
		cout << "Unable to open A.txt and b.txt files !";		//File control
	} else if (myfile1.is_open() == 0) {
		cout << "Unable to open A.txt file !";					//File control
	} else if (myfile2.is_open() == 0) {
		cout << "Unable to open b.txt file !";					//File control
	} else {

		//Getting the value of n for an n x n matrix
		int n = 0;
		string line;
		while (myfile1.eof()==0) {		//When reading is at the end of the file the loop ends.
			getline(myfile1,line);		//The n value increases for every line.
			n = n + 1;					//At the end, n will equal the total line number.
		}

		//Returning at the beginning of the file because we got to the end of the file while determining the n value.
		myfile1.seekg (0);

		//Creating the matrix A by using dynamically allocated memory
		double **A;
		A = new double *[n];
		for (int i = 0; i < n; i++) {
			A[i] = new double [n];
		}

		//The matrix A is filled with the values in the myfile1 which is "A.txt".
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				myfile1 >> A[i][j];
			}
		}

		//myfile1 is closed because the values in it is now in the matrix A.
		myfile1.close();

		//Creating the vector b by using dynamically allocated memory
		double *b;
		b = new double [n];

		//The vector b is filled with the values in the myfile2 which is "b.txt".
		for (int i = 0; i < n; i++) {
			myfile2 >> b[i];
		}

		//myfile2 is closed because the values in it is now in the vector b.
		myfile2.close();



		//For 2 x 2 matrices, calculating the condition numbers
		if(n == 2) {
			double det = (A[1][1]*A[0][0]) - (A[0][1]*A[1][0]);					//Calculating determinant
			if(det < 0.00001 && det > -0.00001) {								//Using precision to control singularity
				cout << "1-Norm Condition Number = Infinite" << "\n";			//If a matrix singular,
				cout << "Infinity-Norm Condition Number = Infinite" << "\n";	//then its condition numbers are infinite.
			} else {

				//Creating the inverse matrix by using dynamically allocated memory
				double **inv;
				inv = new double *[n];
				for (int i = 0; i < n; i++) {
					inv[i] = new double [n];
				}

				//The inverse matrix is filled by using simple 2 x 2 inverse matrix method.
				inv[0][0] = A[1][1];
				inv[1][1] = A[0][0];
				inv[0][1] = A[0][1] * -1;
				inv[1][0] = A[1][0] * -1;
				for(int i = 0; i < n; i++) {
					for(int j = 0; j < n; j++) {
						inv[i][j] = inv[i][j] / det;	//All the values are divided by determinant.
					}
				}

				//This function calculates and prints the condition numbers using 1-norm and infinity-norm.
				findCondition(A,inv,n);

				//Not to take up useless space, the inverse matrix is deleted.
				for(int i = 0; i < n; i++) {
					delete[] inv[i];
				}
				delete[] inv;
			}
		}



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
					max = A[i][j];				//The diagonal is accepted as maximum value.
					m = i;						//Maximum entry's row number is kept.
					for(int k = i+1; k < n ; k++) {								//While we move down the matrix, the process number will decrease.
						if((A[k][i] > max && A[k][i] != 0) || max == 0) {		//The entries belove the diagonal should be bigger than maximum entry and not be 0.
							max = A[k][i];										//Also, maximum entry cannot be 0. When the criteria is met the maximum entry will be updated
							m = k;												//and its row number will be kept.
						}
					}
					for (int k = 0; k < n; k++) {  			//Before this part, the maximum entry's row number is kept.
						temp = A[m][k];						//In this part, the row exchange is applied to matrix A.
						A[m][k] = A[i][k];
						A[i][k] = temp;
					}
					temp = b[m];							//To solve the equation correctly, the rows of the vector b should exchange, too.
					b[m] = b[i];
					b[i] = temp;

					//Gaussian Elimination: To get an upper triangle matrix, the entries below the diagonals is eliminated.
					for (int k = 1; k < n - j; k++) {					//Before this part, partial pivoting is applied to matrix A and vector b.
						mult = A[j+k][i] / A[j][i]; 					//While we move down the matrix, the process number will decrease.
						for (int l = 0; l < n; l++) {					//While "k" is increasing, the entries below the diagonal is divided by diagonal and "mult" is determined.
							A[j+k][l] = A[j+k][l] - A[j][l]*mult;		//Then, the whole column which is below the diagonal is updated.
						}												//This is done by subtracting the product of the entry on the diagonal's row and "mult" from the entry below the diagonal.
						b[j+k] = b[j+k] - b[j]*mult;
							for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << A[i][j] << " ";
			}
			cout << "\n";
		}	
		cout << "\n";			//To solve the equation correctly, the vector b is updated, too.
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
					product = product * A[i][j];		//the diagonals are multiplied with each other.
				}										//If "product" is zero, that means the matrix is singular.
			}
		}
		if(product < 0.000001 && product > -0.000001) {    //Machine Precision: To be more precise,
			sing = 0;									 //when "product" is very close to 0,
		}												 //the matrix is still considered to be singular.
		//If "product" is 0 or very close to 0, then the flag variable is equal to 0.



		//Back Substitution								 //If flag variable is equal to 0, then
		if(sing == 0) {									 //the program gives an error and quits.
			cout << "The matrix A is singular !";		 //If flag variable is equal to 1, then
		} else {										 //the program continues to back substution.

			//Creating the x matrix by using dynamically allocated memory
			double *x;
			x = new double [n];

			//Filling the x matrix with back substution
			double eq;									 //"eq" represents the values in the b matrix.
			for (int i = n - 1; i >= 0; i--) {			 //To apply back substution, the loop is started at n-1.
				eq = b[i];								 //"eq" is updated, every time the first loop repeats.
				for(int k = i + 1; k < n; k++) {      	 //k = i + 1, because the loop started at the end and
					eq = eq - x[k] * A[i][k];			 //there will be more process while "i" decreases.
				}										 //"eq" is updated by back substution in the second loop and
				x[i] = eq / A[i][i];					 //to find the values of x, "eq" is divided by the diagonal which is on the same row.
			}

			//Opening the file to write the x matrix on it
			ofstream myfile3 ("x.txt");

			//Writing the x matrix on myfile3 which is "x.txt"
			for(int i = 0; i < n; i++) {
				myfile3 << x[i] << "\n";
			}

			//myfile3 is closed because the values of x is now written in it and its job is done.
			myfile3.close();

			//Printing the vector x on the screen
			for(int i = 0; i < n; i++) {
				cout << x[i] << "\n";
			}

			//Not to take up useless space, the x matrix is deleted after writing it to "x.txt".
			delete[] x;
		}

		//Not to take up useless space, the A and b matrices are deleted at the end of the program.
		for(int i = 0; i < n; i++) {
			delete[] A[i];
		}
		delete[] A;
		delete[] b;
	}

	return 0;
}

