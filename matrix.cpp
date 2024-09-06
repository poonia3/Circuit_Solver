#ifndef _MATRIX_
#define _MATRIX_
#include <bits/stdc++.h>
#include "complex_number.cpp"

template <typename T>
class matrix{
public:
    int rows,columns;
    std::vector<T> data;
    matrix(){}
    matrix(int r, int c):rows(r), columns(c) {
        data.resize(r*c);
    }
    matrix(std::vector<std::vector<T>> d){
        if(d.empty()){
            rows = 0;columns=0;data = {};
            return;
        }
        columns = d[0].size(), rows = d.size();
        for(int i = 0; i < rows; i++){
            columns = std::max(columns, int(d[i].size()));
        }
        for(int i = 0; i < rows; i++){
            d[i].resize(columns);
            data.insert(data.end(), d[i].begin(), d[i].end());
        }
    }

    matrix(std::vector<T> d){
        rows = d.size();
        columns = 1;
        data = d;
    }
    
    auto operator[](int i){
        return data.begin() + columns * i;
    }
    
    matrix operator-(matrix b){
        if (rows != b.rows || columns != b.columns) {
            std::stringstream ss;
            ss << "Illegal subtraction (" << rows << ", " << columns << ") != (" << b.rows << ", " << b.columns << ")";
            throw std::runtime_error(ss.str());
        }
        else{
            matrix result(rows, columns);
            for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                result[i][j] = (data[i*columns + j] - b[i][j]);
            }
            }
            return result;
        }
    }

    matrix operator-(){
        matrix result(rows, columns);
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            result[i][j] = -data[i*columns + j];
        }
        }
        return result;
    }
    
    matrix operator+(matrix b){
        if (rows != b.rows || columns != b.columns) {
            std::stringstream ss;
            ss << "Illegal sum (" << rows << ", " << columns << ") != (" << b.rows << ", " << b.columns << ")";
            throw std::runtime_error(ss.str());
        }
        else{
        matrix result(rows, columns);
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            result[i][j] = (data[i*columns + j] + b[i][j]);   
        }
        }
        return result;
        }
    }

    matrix operator*(matrix b){
        if (columns != b.rows) {
            std::stringstream ss;
            ss << "Illegal product " << rows << "x" << columns << " and " << b.rows << "x" << b.columns ;
            throw std::runtime_error(ss.str());
        }
        else{
        matrix result(rows, b.columns);
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < b.columns; j++){
        for(int k = 0; k < columns; k++) 
            result[i][j] += data[columns*i + k] * b[k][j];
        }
        }
        return result;
        }
    }
    
    matrix<T> operator*(T scalar){
        matrix<T> result(rows, columns);
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            result[i][j] = scalar * data[i*columns + j];
        }
        }
        return result;
    }
    matrix<T> operator*(std::vector<T> v){
        matrix<T> result(rows, 1);
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            result[i][0] += v[j] * data[i*columns + j];
        }
        }
        return result;
    }

    friend matrix<T> operator*(T scalar, matrix<T> a){
        matrix<T> result(a.rows, a.columns);
        for(int i = 0; i < a.rows; i++){
        for(int j = 0; j < a.columns; j++){
            result[i][j] = scalar * a[i][j];
        }
        }
        return result;
    }

    matrix<T> operator/(T scalar){
        matrix<T> result(rows, columns);
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            result[i][j] = data[i*columns + j]/scalar;
        }
        }
        return result;
    }
    
    T Dt(){//Determinant
        if(rows != columns){
            throw std::runtime_error("Bad size for a determinant");
        }
        else{
        if(rows==1){
            return data[0];
        }
        if(rows == 2){
            return data[0]*data[3] - data[1]*data[2];
        }
        else{
            T result = 0;
            for(int l = 0; l < columns; l++){
            matrix a(rows-1, columns-1);
            for(int i = 1, I=0; i < rows; i++){
            for(int j = 0, J=0; j < columns; j++){
                if(j == l) continue;
                else{
                    a[I][J++] = data[i * columns + j];
                    if(J >= columns-1){J=0;I++;}
                }
            }
            result += (2*((l+1)%2) - 1) * data[l] * a.Dt();
            }
            }
            return result;
        }
        }
    }

    matrix<T> Tr(){//Transpose
        matrix<T> result(columns, rows);
        for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            result[i][j] = (*this)[j][i];
        }
        }
        return result;
    }

    void print(){
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            std::cout << std::setw(2) << data[i*columns + j] << " ";
        }
        std::cout << "\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const matrix<T>& matrix) {
        for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            out << std::setw(2) << matrix.data[i * matrix.columns + j] << " ";
        }
        out << "\n";
        }
        return out;
    }
};

template <typename T>
matrix<T> adjoint(matrix<T> a){
    int size = a.rows;
    if(a.rows != a.columns){
        throw std::runtime_error("Wrong error");
    }
    matrix<T> result(size, size);
    for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
        matrix<T> x(size-1, size-1);
        int K = 0, L = 0;
        for(int I = 0; I < size-1; I++){
        for(int J = 0; J < size-1; J++){
            while(j == L){L++;if(L>=size){L=0;K++;}}
            while(i == K){K++;if(K>=size){K=0;}}
            //std::cout << I << " " << J << " = " << K << " " << L << " : " << a[L][K] << "\n";
            x[I][J] = a[K][L++];
            if(L>=size){L=0;K++;}
        }
        }
        //std::cout << x <<"\n";
        result[j][i] = (2*((i+j+1)%2) -1 ) * x.Dt();
    }
    }
    return result;
}

template <typename T>
matrix<T> inverse(matrix<T> a){
    if(a.rows == 1 && a.columns == 1){
        matrix<T> result(1,1);
        result[0][0] = 1/a[0][0];
        return result;
    }
    return adjoint(a) / a.Dt();
}

template <typename T>
matrix<T> ones(int size){
    matrix<T> result(size, size);
    for(int i = 0; i < size; i++){
        result[i][i] = 1;
    }
    return result;
}

#endif