#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// User defined Complex Class
class Complex {
public:
    long long real;
    long long imag;
    
    // Constructor (default included)
    Complex(long long r = 0, long long i = 0) : real(r), imag(i) {}
    
    // + operator overloading
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    // - operator overloading
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    // * operator overloading
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    // += operator overloading
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    // -= operator overloading
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }
    
    // Taking input for a complex number
    friend istream& operator>>(istream& is, Complex& c) {
        return is >> c.real >> c.imag;
    }
    
    // Outputting a complex number
    friend ostream& operator<<(ostream& os, const Complex& c) {
        return os << c.real << " " << c.imag;
    }
};

// Taking input for a polynomial of type T
template<typename T>
vector<T> read_poly(int degree) {
    vector<T> coeffs(degree);
    for (int i = 0; i < degree; ++i) {
        cin >> coeffs[i];
    }
    return coeffs;
}

// Multiplying two polynomials
template<typename T>
class Multiplication {
    vector<T> coef; // Coefficient vector
    
public:
    // Constructor which takes input from user
    Multiplication() {
        int N;
        cin >> N;
        coef = read_poly<T>(N); // Setting coef vector to input vector
    }
    Multiplication(vector<T> coef): coef(coef) {} // Constructs a polynomial with a given coefficient vector
    
    // Brute force for smaller degrees of polynomials a and b
    vector<T> simple_multiply(const vector<T>& a, const vector<T>& b) {
        size_t n = a.size();
        size_t m = b.size();
        vector<T> result(n + m - 1, T()); // T() is default constructor of type T
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                result[i + j] += a[i] * b[j]; // Convolution
            }
        }
        return result;
    }
    
    vector<T> karatsuba(const vector<T>& a, const vector<T>& b) {
        size_t n = a.size();
        size_t m = b.size();
        
        if (n <= 4 || m <= 4) {
            return simple_multiply(a, b); // Use brute force for base case
        }
        
        size_t half = n / 2;
        
        vector<T> a_low(a.begin(), a.begin() + half); // First half of vector a = A
        vector<T> a_high(a.begin() + half, a.end()); // Second half of vector a = B
        vector<T> b_low(b.begin(), b.begin() + min(half, m)); // First half of vector b if m > n / 2 else the whole vector b = C
        vector<T> b_high(b.begin() + min(half, m), b.end()); // Second half of vector b if m > n /2 else empty = D
        
        // Using the Divide and conquer technique
        vector<T> z0 = karatsuba(a_low, b_low); // A * C
        vector<T> z2 = karatsuba(a_high, b_high); // B * D
        
        vector<T> a_sum(a_low); // Compute A + B
        if (a_sum.size() < a_high.size()) 
            a_sum.resize(a_high.size(), T()); // Add default elements to a_sum to get to the size of a_high
        for (size_t i = 0; i < a_high.size(); ++i) {
            a_sum[i] += a_high[i]; // Computing the sum of both the elements
        }
        
        vector<T> b_sum(b_low); // Compute C + D
        if (b_sum.size() < b_high.size())
            b_sum.resize(b_high.size(), T()); // Add default elements to b_sum to get to the size of b_high
        for (size_t i = 0; i < b_high.size(); ++i) {
            b_sum[i] += b_high[i]; // Computing the sum of both the elements
        }
        
        vector<T> z1 = karatsuba(a_sum, b_sum); // (A + B) * (C + D)
        
        // A * B + C * D = (A + B) * (C + D) - A * C - B * D
        // Result Polynomial = (B * D) * (x ^ half) + (A * B + C * D) * (x ^ (half / 2)) + (A * C)
        // Combining the solutions from above
        vector<T> result(n + m - 1, T());
        for (size_t i = 0; i < z0.size(); ++i) {
            result[i] += z0[i];
            if (i < z1.size()) 
                z1[i] -= z0[i];
        }
        // Shifting the iterator by 2 * half to account for the exponent
        for (size_t i = 0; i < z2.size(); ++i) {
            result[i + 2 * half] += z2[i];
            if (i < z1.size()) 
                z1[i] -= z2[i];
        }
        // z1 = A * B + C * D
        // Shifting the iterator by 2 * half to account for the exponent
        for (size_t i = 0; i < z1.size(); ++i) {
            result[i + half] += z1[i];
        }
        
        return result;
    }
    
    // Getting the product polynomial and returning it through * operator overloaded function
    Multiplication<T> operator*(Multiplication<T>& other) {
        vector<T> result = karatsuba(this->coef, other.coef);
        Multiplication<T> product(result);
        return product;
    }
    
    // Print the polynomial
    void print() {
        for (size_t i = 0; i < coef.size(); ++i) {
            cout << coef[i];
            if (i != coef.size() - 1) cout << " ";
        }
        cout << endl;
    }
};

template<typename T>
class Evaluation {
    vector<T> coef;
    T value;
    int x;
public:
    // Constructor which takes input from user
    Evaluation() {
        int N;
        cin >> N;
        coef = read_poly<T>(N);
        cin >> x;
        evaluate();
    }
    
    void evaluate() {
        value = T(); // Set value to default value
        for (int i = coef.size() - 1; i >= 0; --i) {
            value = value * x + coef[i]; // Horner's method to evaluate a polynomial
            // Iterate through the vector backwards and add the coefficient after multiplying the value with x
        }
    }
    
    // Print the polynomial
    void print() {
        cout << value << endl;
    }
};

// Strings works differently from integers and floats here such that initialising value will be difficult with a common template
// So use a separate overloaded function which overrides the common template function for strings alone
template<>
void Evaluation<string>::evaluate() {
    // Value stores each coefficient's product in the descending order of their indices
    value = "";
    vector<string> parts(coef.size()); // Ues this vector to store the product of each coefficient with the corresponding power of x
    int y = 1;
    for (size_t i = 0; i < coef.size(); i++) {  
        string repeated = "";
        for (int j = 0; j < y; j++) {
            repeated += coef[i]; 
        }
        parts[i] = repeated;
        y *= x;
    }

    // Add strings in the descending order to get the correct evaluated value
    for (int i = coef.size() - 1; i >= 0; i--) {
        value += parts[i];
    }
}

template<typename T>
class Differentiation {
    vector<T> coef;
    
public:
    // Constructor which takes input from user
    Differentiation() {
        int N;
        cin >> N;
        coef = read_poly<T>(N);
        differentiate();
    }
    
    void differentiate() {
        for (size_t i = 0; i < coef.size() - 1; ++i) {
            // The coefficient at index i becomes the coefficient at index i + 1 multiplied by i + 1 after differentiation
            coef[i] = coef[i + 1] * (i + 1); 
        }
        if (!coef.empty()) { // Pop an element only when the vector is not empty
            coef.pop_back(); // Remove the last term as it vanishes after differentiation
        }
    }
    
    // Print the polynomial
    void print() {
        for (size_t i = 0; i < coef.size(); ++i) {
            cout << coef[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(6);
    
    int q;
    cin >> q;
    
    while (q--) {
        int op;
        cin >> op;
        string datatype;
        cin >> datatype;
        
        // Taking input through constructors avoids code redundancy here
        if (op == 1) {
            if (datatype == "integer") {
                Multiplication<long long> M1;
                Multiplication<long long> M2;
                (M1 * M2).print();
            } else if (datatype == "float") {
                Multiplication<long double> M1;
                Multiplication<long double> M2;
                (M1 * M2).print();
            } else {
                Multiplication<Complex> M1;
                Multiplication<Complex> M2;
                (M1 * M2).print();
            }
        } else if (op == 2) {
            if (datatype == "integer") {
                Evaluation<long long> E;
                E.print();
            } else if (datatype == "float") {
                Evaluation<long double> E;
                E.print();
            } else {
                Evaluation<string> E;
                E.print();
            }
        } else {
            if (datatype == "integer") {
                Differentiation<long long> D;
                D.print();
            } else {
                Differentiation<long double> D;
                D.print();
            }
        }
    }
    
    return 0;
}