#include "complex_number.cpp"
#include "matrix.cpp"
#include <limits.h>

void generate_incidence_matrix(std::vector<std::pair<int, int>> connections, matrix<complex_number>& A){
//void generate_incidence_matrix(std::vector<std::pair<int, int>> connections, matrix<double>& A){
    for(int i = 0; i < connections.size(); i++){
        if(connections[i].first)  A[connections[i].first  - 1][i] =  1;
        if(connections[i].second) A[connections[i].second - 1][i] = -1;
    }
}
/*
template <typename T>
std::pair<int, int> contains(std::vector<std::vector<T>> list, T element){
    for(int i = 0; i < list.size(); i++){
    for(int j = 0; j < list[i].size(); j++){

    }
    }
    return {-1, -1};
}

void generate_links_and_twigs(std::vector<std::pair<int, int>> branches, std::pair<std::vector<int>, std::vector<int>>& indices){
    std::vector<std::vector<int>> merging_trees;
    for(int i = 0; i < branches.size(); i++){
        if(contains(merging_trees, branches) != std::pair{-1, -1})
    }
}
*/

int main(){
    int nodes=0, branches=0;
    std::cin>>nodes>>branches;
    std::vector<std::pair<int, int>> connections;
    matrix<complex_number>  A(nodes-1, branches);   //incidence_matrix
    matrix<complex_number>  y(branches, branches);  //conductance_matrix
    matrix<complex_number> Vs(branches, 1);         //source_voltage_matrix
    matrix<complex_number> Is(branches, 1);         //source_current_matrix
    matrix<complex_number>  Y(nodes-1, nodes-1);    
    matrix<complex_number> Vn(nodes-1, nodes-1);
    
    //matrix<double>  A(nodes-1, branches);   //incidence_matrix
    //matrix<double>  y(branches, branches);  //conductance_matrix
    //matrix<double> Vs(branches, 1);         //source_voltage_matrix
    //matrix<double> Is(branches, 1);         //source_current_matrix
    //matrix<double>  Y(nodes-1, nodes-1);    
    //matrix<double> Vn(nodes-1, nodes-1);

    std::cout << "Enter the branches (0 is reference node): \n";
    int a,b;
    for(int i = 0; i < branches; i++){
        std::cout << "Branch - "<< i+1 << ": "; 
        std::cin >> a >> b;
        connections.push_back({a,b});
    }

    std::cout << "Enter the impedences: \n";
    complex_number temp;
    for(int i = 0; i < branches; i++){//ENTER IMPEDENCES
        std::cin >> temp;
        if(temp.real == 0 && temp.imag == 0) y[i][i] = {1e10, 1e10};
        else y[i][i] = 1/temp;
    }

    //y[0][0] = 1/complex_number( 3.8, 0);
    //y[1][1] = 1/complex_number( 2, 0);
    //y[2][2] = 1/complex_number( 3, 0);

    //y[0][0] = {0,0};
    //y[1][1] = {1e10,0};//1/complex_number( 2, 0);
    //y[2][2] = 1/complex_number( 1, 0);
    //y[3][3] = 1/complex_number( 1, 0);//{1e10, 0};
    //y[4][4] = 1/complex_number( 0,-2);
    //y[5][5] = 1/complex_number( 1, 0);

    std::cout << "Enter the source voltages: \n";
    for(int i = 0; i < branches; i++){//ENTER SOURCE VOLTAGES
        std::cin >> Vs[i][0];
    }

    //Vs[0][0] = complex_number(-5, 0);
    //Vs[1][0] = complex_number( 0, 0);
    //Vs[2][0] = complex_number( 0, 0);

    //Vs[0][0] = { 0, 0};
    //Vs[1][0] = {-6, 0};
    //Vs[2][0] = { 0, 0};
    //Vs[3][0] = { 0, 0};
    //Vs[4][0] = { 0, 0};
    //Vs[5][0] = { 0, 0};

    std::cout << "Enter the source currents: \n";
    for(int i = 0; i < branches; i++){//ENTER SOURCE CURRENTS
        std::cin >> Is[i][0];
    }

    //Is[0][0] = ( 0, 0);
    //Is[1][0] = ( 0, 0);
    //Is[2][0] = ( 0, 0);

    //Is[0][0] = {-2, 0};
    //Is[1][0] = { 0, 0};
    //Is[2][0] = { 0, 0};
    //Is[3][0] = { 0, 0};
    //Is[4][0] = { 0, 0};
    //Is[5][0] = {-4, 0};

    generate_incidence_matrix(connections, A);
    //std::cout << A << "\n";

    Y = A*y*A.Tr();
    Vn = inverse(Y) * A * (y * Vs + Is);

    std::cout << A << "\n" ;
    std::cout << y  << " =  " << y.Dt() << "\n";
    std::cout << Y  << " =  " << Y.Dt() << "\n";
    std::cout << y * Vs << "\n";
    std::cout << y * Vs + Is << "\n";
    std::cout << A * (y * Vs + Is) << "\n";
    std::cout << inverse(Y)<< " =  " << inverse(Y).Dt() << "\n";
    std::cout << "ANSWER: \n" << Vn << "\n";
    std::cout << "ANSWER: \n" << A.Tr()*Vn << "\n";
}