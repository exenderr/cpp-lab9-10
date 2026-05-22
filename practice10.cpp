#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

enum MType { GROCERY, HOME_GOODS, EVERYTHING };
enum BType { MAIN, AUXILIARY, FRANCHISE };

struct BusinessInfo {
    double marketValue;
    BType bType;
};

struct Marketplace {
    char name[50];
    int pvzCount;
    char city[50];
    MType mType;
    BusinessInfo biz;
};

void updateFromTextFile(Marketplace arr[], int size, const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) return;
    
    char tName[50];
    int val;
    
    while (fin >> tName >> val) {
        for (int i = 0; i < size; ++i) {
            if (strcmp(arr[i].name, tName) == 0) {
                arr[i].pvzCount = val;
                break;
            }
        }
    }
    fin.close();
}

void writeToBinary(Marketplace arr[], int size, const char* filename) {
    ofstream fout(filename, ios::binary);
    if (fout.is_open()) {
        fout.write((char*)arr, size * sizeof(Marketplace));
        fout.close();
    }
}

void readFromBinary(Marketplace arr[], int& size, const char* filename) {
    ifstream fin(filename, ios::binary);
    if (fin.is_open()) {
        fin.seekg(0, ios::end);
        int bytes = fin.tellg();
        size = bytes / sizeof(Marketplace);
        
        fin.seekg(0, ios::beg);
        fin.read((char*)arr, bytes);
        fin.close();
    }
}

int main() {
    Marketplace mps[3] = {
        {"Ozon", 100, "Moscow", EVERYTHING, {500.5, MAIN}},
        {"KazanExpress", 50, "Kazan", EVERYTHING, {50.0, MAIN}},
        {"Magnit", 200, "Krasnodar", GROCERY, {250.0, MAIN}}
    };

    ofstream tempOut("updates.txt");
    tempOut << "Ozon 999\nMagnit 777\n";
    tempOut.close();

    updateFromTextFile(mps, 3, "updates.txt");
    
    writeToBinary(mps, 3, "data.bin");

    Marketplace readMps[10];
    int readSize = 0;
    readFromBinary(readMps, readSize, "data.bin");

    for(int i = 0; i < readSize; i++) {
        cout << readMps[i].name << " - " << readMps[i].pvzCount << endl;
    }

    return 0;
}