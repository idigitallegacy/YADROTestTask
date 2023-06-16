#include <iostream>
#include "Datatype/TableHeader/ColumnHeader.cpp"

#include "Service/IOReader/File/FileReader.cpp"
#include "Service/IOReader/StringArray/StringArrayReader.cpp"
#include "Service/Table/TableExecutor.cpp"

#include <fstream>
#include <string>
#include <random>

void generateBigTestData() {
    // Test size limit 100, because of slow output. This test is being completed in 1 second. Cell references are excluded.
    std::ofstream fout("TestData/DataSize/BigTable.csv");

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(65.0, 90.0);
    std::uniform_real_distribution<double> indexDist(0.0, 5000000.0);
    for (int i = 0; i < 100; ++i) {
        fout << ',';
        for (int j = 0; j < 7; ++j) {
            fout << (char) dist(mt);
        }
    }

    fout << '\n';

    for (int i = 0; i < 100; ++i) {
        fout << (int) indexDist(mt);
        fout << ',';
        for (int j = 0; j < 100; ++j) {
            fout << j;
            if (j != 99)
                fout << ',';
            else
                fout << '\n';
        }
    }

    fout.close();
}

int stringToIntMapper(const std::string &stringValue) {
    return std::stoi(stringValue);
}

std::string intToStringMapper(const int *intValue) {
    return std::to_string(*intValue);
}

typedef int TestDataType;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "No filename provided.";
        return 1;
    }

    std::cout << argc;
    std::string filename = argv[1];
    std::ifstream fin(filename);
    TableExecutor<TestDataType>(fin, &stringToIntMapper).writeTableToConsole(&intToStringMapper);
    fin.close();

    return 0;
}
