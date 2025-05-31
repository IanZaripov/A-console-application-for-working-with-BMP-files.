#include <iostream>
#include <fstream>
#include "BMP.h"
#include <string>

using namespace std;



int main() {
    string input_file_name, output_file_name;
    cout << "Enter input BMP File name: \n";
    cin >> input_file_name;
    BMP bmp(input_file_name);
    try {
        bmp.LoadFile();
        bmp.DrawImage();
        cout << endl;
        bmp.MakeCross();
        bmp.DrawImage();
        cout << "Enter output BMP File name: \n";
        cin >> output_file_name;
        bmp.Save(output_file_name);
        cout << "Image successfully saved in: " << output_file_name << '\n';
    }
    catch (exception& e) {
        cerr << e.what() << "\n";
    }
    return 0;
}


