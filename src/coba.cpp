#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Create and open a text file
    ofstream MyFile("../test/solution.txt");

    // Write to the file
    MyFile << "Files can be tricky, but it is fun enough!"<<endl;
    MyFile << "This is the second line.";   

    // Close the file
    MyFile.close();
}