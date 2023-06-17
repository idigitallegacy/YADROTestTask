#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>

#include "Service/Table/TableExecutor.cpp"

typedef int TestDataType;

int stringToIntMapper(const std::string &stringValue) {
    return std::stoi(stringValue);
}

std::string intToStringMapper(const int *intValue) {
    return std::to_string(*intValue);
}

TEST(TableData, DefaultTest) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\DefaultTest.csv)";
    std::ifstream fin(pathToTest);
    std::string out = TableExecutor<TestDataType>(fin, &stringToIntMapper).getTable(&intToStringMapper);
    fin.close();
    EXPECT_STREQ(
            ",A,B,Cell\n"
            "1,1,0,1\n"
            "2,2,6,0\n"
            "30,0,1,5\n",
            out.c_str());
}

TEST(TableData, TestData1) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\Data\TestData1.csv)";
    std::ifstream fin(pathToTest);
    std::string out = TableExecutor<TestDataType>(fin, &stringToIntMapper).getTable(&intToStringMapper);
    fin.close();
    EXPECT_STREQ(
            ",A,B,C,D,E,F,G,H,I,J,K,L,M,N\n"
            "2,223,219,233,221,0,22,1,0,-21,-10,-2,-8,0,0\n"
            "3,0,0,242,221,0,0,0,0,0,-19,-2,-17,0,0\n"
            "4,0,0,252,222,0,0,0,0,0,-29,-3,-26,1,1\n"
            "5,0,0,258,223,0,0,0,0,0,-35,-4,-31,1,1\n"
            "6,0,0,268,224,0,0,0,0,0,-45,-5,-40,1,1\n",
            out.c_str());
}

TEST(TableData, TestData2) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\Data\TestData2.csv)";
    std::ifstream fin(pathToTest);
    std::string out = TableExecutor<TestDataType>(fin, &stringToIntMapper).getTable(&intToStringMapper);
    fin.close();
    EXPECT_STREQ(
            ",A,B,C,D,E,F,G,H,I,J,K,L,M,N\n"
            "2,223,219,233,221,0,22,1,0,1,223,219,223,223,223\n"
            "3,0,0,242,221,0,0,0,0,0,223,0,223,223,223\n"
            "4,0,0,252,222,0,0,0,0,0,223,0,223,223,223\n"
            "5,0,0,258,223,0,0,0,0,0,223,0,223,223,223\n"
            "6,0,0,268,224,0,0,0,0,0,223,0,223,223,223\n",
            out.c_str());
}

TEST(TableIO, EmptyHeader) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\WrongInput\WrongHeader1.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), EmptyDataException);
    fin.close();
}

TEST(TableIO, WrongHeader) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\WrongInput\WrongHeader2.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), InvalidDataPatternException);
    fin.close();
}

TEST(TableIO, WrongCellsAmount) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\WrongInput\WrongCellsAmount.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), EmptyDataException);
    fin.close();
}

TEST(TableIO, WrongCellValue) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\WrongInput\WrongCellValue.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), InvalidDataPatternException);
    fin.close();
}

TEST(TableIO, WrongOperator) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\WrongInput\WrongOperator.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), InvalidDataPatternException);
    fin.close();
}

TEST(TableDataSize, EmptyTable) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\DataSize\EmptyTable.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_NO_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper));
    fin.close();
}

TEST(TableDataSize, EmptyRows) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\DataSize\EmptyRows.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_NO_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper));
    fin.close();
}

TEST(TableDataSize, EmptyCols) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\DataSize\EmptyCols.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_NO_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper));
    fin.close();
}

TEST(TableDataSize, InequalSize1) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\DataSize\InequalSize1.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_NO_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper));
    fin.close();
}

TEST(TableDataSize, InequalSize2) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\DataSize\InequalSize2.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_NO_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper));
    fin.close();
}

TEST(TableDataSize, BigTable) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\DataSize\InequalSize1.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_NO_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper));
    fin.close();
}

TEST(TableLogic, InvalidRequestedCell) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\Logic\InvalidRequestedCell.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), InvalidCellAddressException);
    fin.close();
}

TEST(TableLogic, DirectSelfReference) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\Logic\DirectSelfReference.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), SelfReferenceException);
    fin.close();
}

TEST(TableLogic, IndirectSelfReference1) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\Logic\IndirectSelfReference1.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), SelfReferenceException);
    fin.close();
}

TEST(TableLogic, IndirectSelfReference2) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\Logic\IndirectSelfReference2.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), SelfReferenceException);
    fin.close();
}

TEST(TableLogic, ZeroDivision) {
    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\Logic\ZeroDivision.csv)";
    std::ifstream fin(pathToTest);

    EXPECT_THROW(TableExecutor<TestDataType>(fin, &stringToIntMapper), ZeroDivisionException);
    fin.close();
}

TEST(TablePerformance, BigTable) {
    clock_t t;

    std::string pathToTest = R"(C:\Users\elfxe\CLionProjects\New\YadroTestTask\TestData\DataSize\BigTable.csv)";
    std::ifstream fin(pathToTest);

    t = clock();
    TableExecutor<TestDataType> executor = TableExecutor<TestDataType>(fin, &stringToIntMapper);
    t = clock() - t;

    EXPECT_LE(t / CLOCKS_PER_SEC, 2);
}