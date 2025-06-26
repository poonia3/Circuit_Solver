Copy and paste the sample input when trying out
To test it compile test.cpp

Input:

Number of nodes and branches

Connection list (branch to node mapping)

Branch impedances (supports complex values like 4+3i, -2i, etc.)

Voltage and current sources

Process:

Builds an incidence matrix A

Constructs a diagonal conductance matrix y = 1/Z

Computes system matrix Y = A * y * Aᵀ

Solves Vn = inv(Y) * A * (y * Vs + Is) for nodal voltages

Back-substitutes to get branch currents

Output:

Displays all intermediate matrices

Shows nodal voltages and branch voltage drops

