#include <iostream>
#include <vector>
#include <time.h>
#include <random>

using namespace std;

namespace algebra {
    //////////////////////////////////////////////////////////
    // CONSTANTS

    static const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!#@";

    template<class T>
    struct j{
        T Real, Complex;

        // Constructor
        j(T Real = 0, T Complex = 0)
            :Real(Real), Complex(Complex){}

        // Operator = 
        j& operator=(const j& b){
            Real = b.Real;
            Complex = b.Complex;
            return *this;
        }
        // Operator +
        j& operator+(const j& b){
            return j(b.Real + Real, b.Complex + Complex);
        }

        // Operator -
        j& operator-(const j& b) const{
            return j(Real - b.Real, Complex - b.Complex);
        }

        // Operator *
        j& operator*(const j& b) const{
            return j(b.Real*Real, b.Complex*Complex);
        }

        // cout operator
        friend ostream& operator<<(ostream& os, const j& a){
            os << "(" << a.Real << ", " << a.Complex << ")";
            return os;
        }

    };


    // Multiplication 
    template<class T>
    T dot(T* u, T* v, int length){
        T result = 0;
        for (int i = 0; i<length; i++){
            result += (*(u + i) * *(v + i));
        }
        return result;
    }

    //////////////////////////////////////////////////////////
    //    FUNCTIONS FOR MATRIX GENERATIONS   
    //////////////////////////////////////////////////////////


    /*******************************/
    //     V[] = generate_matrix(m, n, generator_function)
    //       
    //     Returns a vector of arrays, you must provide a generator
    //     function in order to populate the vector.
    //
    //     The generator function must return the same type
    /*******************************/
    template <class T>
    vector<T*>  generate_matrix(const int m, const int n, T(*gen)(void)){
        vector<T*> data;
        for (int i = 0; i<m; i++){

            auto row = new T[n];
            for (int j = 0; j<n; j++){
                *(row + j) = gen();
            }

            data.push_back(row);
        }

        return data;
    }

    template<class T>
    void display_matrix(vector<T*> matrix, int n){
        cout << "\n@ MATRIX ROWS \n";
        for (auto &rows : matrix){
            cout << "-----------\n";
            for (int i = 0; i<n; i++)
                cout << "  " << *(rows + i) << "\n";
        }
    }

    /* DEMO GENERATOR FUNCTIONS */

    int gen_int(){
        return rand() % 1000 + 1;
    }

    double gen_double(){
        const double min = 0.0000, max = 1000.0000;
        double result = double(rand()) / RAND_MAX;
        result = min + result * (max - min);
        return result;
    }

    char gen_char(){
        int length = sizeof(chars) - 1;
        return chars[rand() % length];
    }

    j<double> gen_jdouble(){
        return j<double>(gen_double(), gen_double());
    }

    j<int> gen_jint(){
        return j<int>(gen_int(), gen_int());

    }

    /* END GENERATOR FUNCTIONS */




}