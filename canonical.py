import numpy as np
import scipy.linalg as la
import math

def canonical_form(A, b, c, k, basis):
    """
    Return the canonical form of the objective function and the constraint function

        A: A matrix of integers
        b: A vector of integers
        c: A vector of integers
        k: A constant
        basis: A list of integers
    """

    # Reduce all the basis by 1 to fix the index
    basis = [x - 1 for x in basis]
    
    # A_B will be the matrix A with columns corresponding to the basis
    A_B = A[:, basis]
    print(A_B)

    # Multiply the inverse of A_B with Ax to get A'x
    A_prime = np.dot(la.inv(A_B), A)
    b_prime = np.dot(la.inv(A_B), b)

    # Round A_prime and b_prime to the nearest integer
    A_prime = np.around(A_prime, 1)
    b_prime = np.around(b_prime, 1)

    c_prime = c[basis].reshape((-1,1))
    print(c_prime.shape)

    # Find values of y
    y = np.dot(la.inv(A_B.T), (c[basis]).T)

    # Round y to the nearest integer
    y = np.around(y, 1)

    # Rewrite the canonical form of the objective function, from c^Tx to (c')^Tx + z
    z_x = (c - np.dot(y.T, A))
    z_k = k + np.dot(y.T, b)

    # Round z_x and z_k to the nearest integer
    z_x = np.around(z_x)
    z_k = np.around(z_k)

    print("The canonical form of the objective function is: ")
    print(z_x, "x +", z_k)

    print("The canonical form of the constraint function is: ")
    print(A_prime, "x =", b_prime)

def main():
    # Define the matrix A
    A = np.array([[1,1,2,0], [0,1,1,1]])

    # Define the vector b
    b = np.array([2, 5])

    # Define the vector c
    c = np.array([0, 1, 3, 0])

    # Define the constant k at the start
    k = 0

    # Define the new basis
    basis = [2,4]

    # Call the function
    canonical_form(A, b, c, k, basis)

if __name__ == "__main__":
    main()