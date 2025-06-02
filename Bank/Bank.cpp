#include <iostream>
using namespace std;

void printNumbersAddresses(
    const int* NUMBERS_ADDRESS,
    const int NUMBER_COUNT
) {
    cout << "Addresses are:\n";
    for (int index = 0; index < NUMBER_COUNT; ++index)
        cout << NUMBERS_ADDRESS + index << endl;
}

void printNumbersValues(
    const int* NUMBERS_ADDRESS,
    const int NUMBER_COUNT
) {
    cout << "Values are: \n";
    for (int index = 0; index < NUMBER_COUNT; ++index)
        cout << *(NUMBERS_ADDRESS + index) << endl;
}
void sayHello() {
    cout << "Hello!" << endl;
}


int main() {
    string colors[] = { "red", "blue", "green" };
    string* colorsAddress = colors; // يشير إلى أول عنصر
    void (*funcPtr)() = sayHello;
    funcPtr(); 
        float floatNumber = 10.5;
        int integerNumber = 50;
        void * b = &integerNumber;
        cout <<  endl;
        void* voidPointer = &floatNumber;
        //cout << voidPointer << endl;
        cout << *static_cast<float*>(voidPointer) << endl;

        voidPointer = &integerNumber;
        //cout << voidPointer << endl;
        cout << *static_cast<int*>(voidPointer);
    
    cout << *(colorsAddress + 1); // يعادل colors[1] ويطبع "blue"

    const int NUMBER_COUNT = 4;
    const int NUMBERS[NUMBER_COUNT] = { 10, 20, 30, 40 };
    const int* NUMBERS_ADDRESS = NUMBERS;

    printNumbersAddresses(
        NUMBERS_ADDRESS,
        NUMBER_COUNT
    );

    cout << endl;

    printNumbersValues(
        NUMBERS_ADDRESS,
        NUMBER_COUNT
    );
}