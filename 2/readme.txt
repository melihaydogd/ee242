This program is coded to find the largest and the smallest eigenvalues and their corresponding 
eigenvectors of a two dimensional matrix. After finding these values the results will be written on an output file.

***How to Use the Program***
First, an input file must be created and the matrix A must be written in this file. This file must
be in the location of "source.cpp". Then, "source.cpp" file must be opened. The main function will use 3
inputs and these inputs must be entered by clicking Execute then Parameters in Dev-C++. The first one is 
the name of input file (for example A.txt), the second one is the value of tolerance (for example 1e-6)
and the last one is the name of output file (for example b.txt). These 3 must be written like this : A.txt 1e-6 b.txt.
There should one space between inputs. After doing these, by clicking F9, we compile the program and then, 
we run the program by clicking F10.

Another way is to use command prompt. In this way, an input file where the matrix A will be written
must be created, too. Then, the command prompt must be opened and the location of the "source.cpp" must be 
opened by using "cd" command. 
After that, "g++ -o source source.cpp" must be written.
Then, "source the-first-input the-second-input the-third-input" must be written.
For example, "source A.txt 1e-6 b.txt" should be written. There should be one space between inputs. After that, 
the eigenvalues and the eigenvectors will be written in "b.txt" file.

The first input -> The name of the file that the matrix is read from.
The second input -> The tolerance.
The third input -> The name of the output file.

Important points about the program;
1-If input file cannot be opened properly, the program will give an error "Unable to open input file !" in the output 
file and quit.
2-If the matrix is singular, the largest eigenvalue and its corresponding eigenvector can be found. However, its
smallest eigenvalue and its corresponding eigenvector cannot be found. In this case, "Inverse iteration cannot 
be applied because the matrix is singular !" will be written in the output file.
