#include <iostream>

using namespace std;

// Function prototypes for arithmetic operations
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main() {
    double num1, num2;
    char operation;
    bool keepRunning = true;
    
    cout << "Simple Console-Based Calculator" << endl;
    cout << "Available operations: + (addition), - (subtraction), * (multiplication), / (division)" << endl;
    cout << "Enter 'q' to quit." << endl;

    while (keepRunning) {
        cout << "\nEnter the first number: ";
        cin >> num1;
        cout << "Enter an operation (+, -, *, /): ";
        cin >> operation;

        if (operation == 'q') {
            keepRunning = false;
            break;
        }

        cout << "Enter the second number: ";
        cin >> num2;

        switch (operation) {
            case '+':
                cout << "Result: " << add(num1, num2) << endl;
                break;
            case '-':
                cout << "Result: " << subtract(num1, num2) << endl;
                break;
            case '*':
                cout << "Result: " << multiply(num1, num2) << endl;
                break;
            case '/':
                if (num2 != 0) {
                    cout << "Result: " << divide(num1, num2) << endl;
                } else {
                    cout << "Error: Division by zero is not allowed." << endl;
                }
                break;
            default:
                cout << "Invalid operation. Please try again." << endl;
                break;
        }
    }

    cout << "Calculator exited." << endl;
    return 0;
}

// Function definitions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}
