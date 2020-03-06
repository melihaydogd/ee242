This program is coded to solve any given polynomial by using secant, bisection and hybrid algorithms.
Bisection algorithm is used for the first two iterations of hybrid algorithm and secant algorithm is used
for the rest of the iterations.

The program uses command line arguments to get the inputs. The first two inputs are the initial guesses and the first
initial guess must be smaller than second initial guess. The third input is the tolerance value and the rest of 
the inputs are the coefficients of the polynomial.
The order of the inputs is like this:
Lower-initial-guess Higher-initial-guess Tolerance The-coefficients-of-the-polynomial

For example, 1.5 1.8 0.001 2 2 -7 1 -7
1.5 -> Lower initial guess
1.8 -> Higher initial guess
0.001 -> Tolerance
2x^4 + 2x^3 - 7x^2 + x - 7 -> The polynomial

***How to Use the Program***
"source.cpp" file must be opened. The inputs must be entered by clicking Execute then Parameters in Dev-C++.
After entering the inputs, by clicking F9, we compile the program and then, we run the program by clicking F10.
The outputs will be printed on the screen.

Another way is to use command prompt. In this way, the command prompt must be opened and the location of 
the "source.cpp" must be opened by using "cd" command. 
After that, "g++ -o source source.cpp" must be written.
Then, "source Lower-initial-guess Higher-initial-guess Tolerance The-coefficients-of-the-polynomial" must be written.
For example, "source 1.5 1.8 0.001 2 2 -7 1 -7" should be written. There should be one space between inputs. After that, 
the outputs will be printed on the command prompt.

Important points about the program:
1-For the bisection method, when the signs of initial guesses are the same, the algoritm will not work. It gives an error
and does not applies bisection method.
2-Tolerance value is calculated by finding the difference between the iteration values.