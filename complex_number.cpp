#ifndef _COMPLEX_NUMBERS_
#define _COMPLEX_NUMBERS_

#include <bits/stdc++.h>
#include <iomanip>

class complex_number{
    public:
        double imag, real;
        complex_number(double re = 0, double im = 0){
            imag = im;
            real = re;
        }
        complex_number(std::vector<double> doublet){
            if(doublet.size() == 2){
                imag = doublet[1];
                real = doublet[0];
            }
            else{
                throw doublet.size();
            }
        }
        void print_comp(){
            if(real == 0){
                if(imag == 0) std::cout << (0.0) << "\n";
                else std::cout << "(" <<  (double)imag << "i)\n";
            }
            else{
                if(imag > 0) std::cout << (double)real << " + " << (double)imag << "i" << "\n";
                if(imag < 0) std::cout << (double)real << " - " << -(double)imag << "i" << "\n";
                if(imag == 0) std::cout << (double)real << "\n";
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const complex_number& complex) {
            /*if(complex.real == 0){
                if(complex.imag == 0) os << "(" << 0.0 <<")";
                else os << "(" << (double)complex.imag << "i)";
            }
            else{
                if(complex.imag >= 0) os << "[" << std::setw(8) << (double)complex.real << " + " << (double)complex.imag << "i]";
                if(complex.imag <  0) os << "[" << std::setw(8) << (double)complex.real << " - " << -(double)complex.imag << "i]";
            }
            return os;*/
            if(complex.imag >= 0) os << "[" << std::setw(5) << (double)complex.real << " + " << std::setw(5) << (double)complex.imag << "i]";
            if(complex.imag <  0) os << "[" << std::setw(5) << (double)complex.real << " - " << std::setw(5) << -(double)complex.imag << "i]";
            return os;
        }
        double mod(){
            return sqrt(real*real + imag*imag);
        }
        double arguement(){
            return atan(imag/real);
        }
        double modded(){
            return (real*real + imag*imag);
        }
        complex_number operator-(){
            return {-real, -imag};
        }
        complex_number operator+(){
            return {real, imag};
        }
        complex_number operator+(complex_number const& other){
            return {real+other.real, imag+other.imag};
        }
        complex_number operator+=(complex_number const& other){return {real = real+other.real, imag = imag+other.imag};}
        complex_number operator- (complex_number const& other){return {real-other.real, imag-other.imag};}
        complex_number operator-=(complex_number const& other){return {real = real-other.real, imag = imag-other.imag};}
        complex_number operator* (complex_number const& other){return {(real * other.real) - (imag * other.imag), (real * other.imag) + (imag * other.real)};}
        complex_number operator*=(complex_number const& other){return {real = (real * other.real) - (imag * other.imag), imag = (real * other.imag) + (imag * other.real)};}
        complex_number operator/ (double const scalar){return {real/scalar, imag/scalar};}
        complex_number operator/=(double const scalar){return {real = real/scalar, imag = imag/scalar};}
        complex_number operator/ (complex_number other){return (*this) * (other^-1.0);}
        complex_number operator/=(complex_number other){return (*this) = (*this)*(other^-1.0);}
        complex_number operator~ (){return {real, -imag};}
        complex_number operator^ (double scalar){double angle = atan(imag/real);double mod = sqrt((real*real) + (imag*imag));return {pow(mod, scalar) * cos(scalar * angle), pow(mod, scalar) * sin(scalar * angle)};}
        friend complex_number operator/(double scalar, complex_number self){return (self)^-1;}
        friend complex_number operator*(double scalar, complex_number self){return {(self.real*scalar), (self.imag*scalar)};}
        friend std::istream& operator>>(std::istream& input, complex_number& c);
};

std::vector<std::string> split(const std::string& s, const std::string& e, std::string e2="") {
    std::vector<std::string> result;
    size_t start = 0;
    size_t next = 0;
    if(e2=="")e2=e;
    while ((next = std::min(s.find_first_of(e, start+1), s.find_first_of(e2, start+1))) != std::string::npos) {
        if (next != start) {
            result.push_back(s.substr(start, next - start));
        }
        start = next;
    }
    if (start < s.length()) {
        result.push_back(s.substr(start));
    }

    return result;
}

std::istream& operator>>(std::istream& input, complex_number& c) {
    std::string s;
    do{
        input >> s;
    }while(s.empty());

    if (s == "i" || s == "+i") {
        c.real = 0;
        c.imag = 1;
        return input;
    } else if (s == "-i") {
        c.real = 0;
        c.imag = -1;
        return input;
    }
    std::vector<std::string> parts = split(s, "+", "-");
    c.imag = 0;
    c.real = 0;
    for(int i = 0; i < parts.size(); i++){
        if(parts[i].find("i") == std::string::npos){
            std::istringstream(parts[i]) >> c.real;
        }
        else{
            parts[i].erase(std::remove(parts[i].begin(), parts[i].end(), 'i'), parts[i].end());
            if(parts[i].empty() || parts[i] == "+" || parts[i] == "-"){
                parts[i] = parts[i] + "1";
            }
            std::istringstream(parts[i]) >> c.imag;
        }
    }
    return input;
}

#endif