#include <iostream>
#include <cstring>

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

void printSingle(const Marketplace& m) {
    cout << m.name << " | PVZ: " << m.pvzCount << " | City: " << m.city << endl;
}

void printArray(Marketplace arr[], int size) {
    for (int i = 0; i < size; ++i) {
        printSingle(arr[i]);
    }
    cout << "-----------------------\n";
}

int copyGrocery(Marketplace src[], int srcSize, Marketplace dest[]) {
    int count = 0;
    for (int i = 0; i < srcSize; ++i) {
        if (src[i].mType == GROCERY) {
            dest[count++] = src[i];
        }
    }
    return count;
}

void bubbleSortByPVZ(Marketplace arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j].pvzCount > arr[j + 1].pvzCount) {
                Marketplace temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printByName(Marketplace arr[], int size, const char* target) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(arr[i].name, target) == 0) {
            printSingle(arr[i]);
            return;
        }
    }
}

void printTop3(Marketplace arr[], int size) {
    Marketplace temp[20];
    for (int i = 0; i < size; ++i) temp[i] = arr[i];
    
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (temp[j].pvzCount < temp[j + 1].pvzCount) {
                Marketplace t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }
    
    for (int i = 0; i < 3 && i < size; ++i) {
        printSingle(temp[i]);
    }
    cout << "-----------------------\n";
}

void editMarketplace(Marketplace arr[], int size, const char* targetName, int newPvz) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(arr[i].name, targetName) == 0) {
            arr[i].pvzCount = newPvz;
            return;
        }
    }
}

int filterNotMoscow(Marketplace src[], int srcSize, Marketplace dest[]) {
    int count = 0;
    for (int i = 0; i < srcSize; ++i) {
        if (strcmp(src[i].city, "Moscow") != 0) {
            dest[count++] = src[i];
        }
    }
    return count;
}

void printWrapper(Marketplace arr[], int size, int (*filterFunc)(Marketplace[], int, Marketplace[])) {
    Marketplace filtered[20];
    int newSize = filterFunc(arr, size, filtered);
    printArray(filtered, newSize);
}

int main() {
    Marketplace mps[20] = {
        {"Ozon", 15000, "Moscow", EVERYTHING, {500.5, MAIN}},
        {"VkusVill", 1200, "Moscow", GROCERY, {100.2, MAIN}},
        {"KazanExpress", 500, "Kazan", EVERYTHING, {50.0, MAIN}},
        {"Samokat", 2000, "SPb", GROCERY, {200.0, MAIN}},
        {"YandexMarket", 10000, "Moscow", EVERYTHING, {450.0, MAIN}},
        {"Wildberries", 25000, "Moscow", EVERYTHING, {1000.0, MAIN}},
        {"SberMarket", 800, "Moscow", GROCERY, {150.0, MAIN}},
        {"LeroyMerlin", 100, "Moscow", HOME_GOODS, {300.0, MAIN}},
        {"Hoff", 50, "SPb", HOME_GOODS, {80.0, MAIN}},
        {"Lenta", 300, "SPb", GROCERY, {120.0, MAIN}},
        {"Magnit", 4000, "Krasnodar", GROCERY, {250.0, MAIN}},
        {"Pyaterochka", 5000, "Moscow", GROCERY, {280.0, FRANCHISE}},
        {"VseInstrumenti", 200, "Moscow", HOME_GOODS, {90.0, MAIN}},
        {"AliExpress", 1000, "Moscow", EVERYTHING, {600.0, MAIN}},
        {"DNS", 1500, "Vladivostok", HOME_GOODS, {350.0, MAIN}},
        {"Citilink", 800, "Moscow", HOME_GOODS, {200.0, MAIN}},
        {"MVideo", 400, "Moscow", HOME_GOODS, {180.0, MAIN}},
        {"Eldorado", 350, "Moscow", HOME_GOODS, {160.0, MAIN}},
        {"Avito", 0, "Moscow", EVERYTHING, {800.0, MAIN}},
        {"Perekrestok", 600, "Moscow", GROCERY, {140.0, MAIN}}
    };
Marketplace groceryMps[20];
    int grocerySize = copyGrocery(mps, 20, groceryMps);
    
    bubbleSortByPVZ(groceryMps, grocerySize);
    printArray(groceryMps, grocerySize);

    printByName(mps, 20, "KazanExpress");
    cout << "-----------------------\n";

    printTop3(mps, 20);

    editMarketplace(mps, 20, "Ozon", 16000);

    printWrapper(mps, 20, filterNotMoscow);

    return 0;
}