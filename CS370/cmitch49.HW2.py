#!/usr/bin/python


#Cody Mitchell
#cs370
#Homework 2


####################################################################
# problem2_1_15  (Problem Set 2.1, No. 15 on page 53 of textbook)
# This problem requires the LUdecomp.py module (provided).
#
# Fill in the following template. First, determine the value for
# the tolerance variable TOL.  Then, add the code that creates the
# Matrix (a) and the vector (b). Finally, add the code that computes
# the LU decomposition and produces a solution vector (see the
# provided LUdecomp.py module for correct function calls to do that).
####################################################################

from numpy import zeros, ones, array, float64, inf
from numpy import linalg
from LUdecomp import *

norm = linalg.norm  # Python allows you to rename functions.
                    # Here, 'linalg.norm' is renamed to just 'norm'.
# PROVIDE A VALUE FOR THE VARIABLE TOL THAT MATCHES THE SPECIFICATIONS OF
# THE PROBLEM
TOL = 1.e-6	#ensures that the result is accurate to 6 decimal places
err = 0		
n = 0
while err < TOL:	#breaks when result is not accurate to 6 decimal places
  n +=1
  a = zeros((n,n),dtype=float64)	#initialize Hilbert Matrix and solution vector
  b = zeros((n),dtype=float64)
  soln = ones((n), dtype=float64) 	# The correct solution is all 1's

  # USE THE LOOPS BELOW TO DEFINE THE MATRIX 'a' AND THE VECTOR 'b':
  for i in range(n):
    for j in range(n):
      a[i,j] = (1/(i+j+1))
      b[i] += a[i,j]

  # CALL APPROPRIATE FUNCTIONS FROM THE LUdecomp.py MODULE TO
  # SOLVE THE EQUATIONS A x = b: 
  a = LUdecomp(a)	#A=LU
  b = LUsolve(a,b)

  # Your solution should be stored in 'b' (if you used a different variable name,
  # modify the code below accordingly).
  #
  print("\n", n, " equations. ", "The solution is:\n", b)
  err = norm(b-soln, ord=inf)
  print("Error (inf-norm of difference)): ", err)

print("^^^(Greater than TOL = ", TOL, ")^^^\n")
print("********************************************\n")
print("Max number of equations while error remains less than ", TOL, " is: ", n-1, "\n") 
print("********************************************")
