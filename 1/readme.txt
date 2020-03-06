This program is coded to solve Ax=b equation for matrices and to solve Ax=b equation, 
-the matrix A should be written in "A.txt".
-the vector b should be written in "b.txt".
After entering the matrices in the mentioned files, "source.cpp" should be opened. 
By clicking F9, we compile the program and after that, we run the program by clicking F10.
The result will be written in the "x.txt" file and also, it is printed on the screen.

Important points about the program:
1- If "A.txt" or "b.txt" files cannot be opened properly, the program will give an error
"Unable to open A.txt file !" or "Unable to open b.txt file !" and quit. If both of them cannot be
opened properly, the program will give an error "Unable to open A.txt and b.txt files !" and quit.
2- If the matrix A is a 2 x 2 matrix, its condition numbers will be calculated 
using 1-norm and infinity-norm. Then, they are printed on the screen.
3- If the matrix is singular, the result x cannot be calculated. Thus, the program will give an
error "The matrix A is singular !!" and quit.

***The Case of High Condition Numbers***

A: 1.000 1.000       b1: 2.000       x1: 2.000	
   1.000 1.001		 2.000		 0.000

A: 1.000 1.000	     b2: 2.000       x2: 1.000		
   1.000 1.001	         2.001		 1.000

The result is completey different even tough there is a small change in vector b.
The condition numbers for matrix A is 4004 and this is a very high number. 
From both condition numbers and big difference in the result, we can understand that
the matrix A is ill-conditioned.