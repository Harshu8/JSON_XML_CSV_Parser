#include <iostream>
#include <gtest/gtest.h>
#include "CsvTest.h"

class CSVParserTestFixture : public ::testing::Test
{
public:
    CSVParser<rapidcsv::Document, std::string> obj;
};

TEST_F(CSVParserTestFixture, whenWeGetCorrectOutput)
{
    std::string filename = "../sampleFile/csvSampleFile1.csv";
    rapidcsv::Document doc = obj.parseDocument(filename);

    std::vector<float> columnOpen = doc.GetColumn<float>("Open");
    std::vector<float> columnHigh = doc.GetColumn<float>("High");
    std::vector<float> columnLow = doc.GetColumn<float>("Low");
    std::vector<float> columnClose = doc.GetColumn<float>("Close");
    std::vector<int> columnVolume = doc.GetColumn<int>("Volume");
    std::vector<float> columnAdjClose = doc.GetColumn<float>("Adj Close");

    std::vector<float> expectedColumnOpen = {61.13, 62.22, 63.33, 64.41, 65.57, 66.61, 67.77};
    std::vector<float> expectedColumnHigh = {14.1, 24.23, 34.39, 44.45, 54.59, 64.65, 74.79};
    std::vector<float> expectedColumnLow = {64.14, 64.19, 64.05, 64.45, 64.3, 64.45, 64.3};
    std::vector<float> expectedColumnClose = {64.62, 64.62, 64.36, 64.49, 64.62, 64.49, 64.62};
    std::vector<int> expectedColumnVolume = {21705200, 20235200, 19259700, 19384900, 21234600, 19384900, 21234600};
    std::vector<float> expectedColumnAdjClose = {64.63, 64.61, 64.38, 64.42, 64.62, 64.49, 64.62};

    for (int counter = 0; counter < columnOpen.size(); counter++)
    {
        EXPECT_FLOAT_EQ(expectedColumnOpen[counter], columnOpen[counter]);
        EXPECT_FLOAT_EQ(expectedColumnHigh[counter], columnHigh[counter]);
        EXPECT_FLOAT_EQ(expectedColumnLow[counter], columnLow[counter]);
        EXPECT_FLOAT_EQ(expectedColumnClose[counter], columnClose[counter]);
        EXPECT_EQ(expectedColumnVolume[counter], columnVolume[counter]);
        EXPECT_FLOAT_EQ(expectedColumnAdjClose[counter], columnAdjClose[counter]);
    }
}

TEST_F(CSVParserTestFixture, whenWeGetIncorrectOutput)
{
    std::string filename = "../sampleFile/csvSampleFile1.csv";
    rapidcsv::Document doc = obj.parseDocument(filename);

    std::vector<float> columnOpen = doc.GetColumn<float>("Open");
    std::vector<float> columnHigh = doc.GetColumn<float>("High");
    std::vector<float> columnLow = doc.GetColumn<float>("Low");
    std::vector<float> columnClose = doc.GetColumn<float>("Close");
    std::vector<int> columnVolume = doc.GetColumn<int>("Volume");
    std::vector<float> columnAdjClose = doc.GetColumn<float>("Adj Close");

    std::vector<float> expectedColumnOpen = {161.3, 62.22, 65.33, 62.41, 85.57, 76.61, 97.77};
    std::vector<float> expectedColumnHigh = {114.2, 214.23, 314.39, 414.45, 541.59, 614.65, 714.79};
    std::vector<float> expectedColumnLow = {164.13, 164.15, 614.05, 614.45, 614.3, 614.45, 11164.3};
    std::vector<float> expectedColumnClose = {64462, 612.62, 164.36, 164.49, 64.162, 64.491, 641.62};
    std::vector<int> expectedColumnVolume = {25200, 25200, 199700, 184900, 212340, 19900, 234600};
    std::vector<float> expectedColumnAdjClose = {651.63, 641.61, 64.138, 64.142, 64.162, 641.49, 614.62};

    for (int counter = 0; counter < columnOpen.size(); counter++)
    {
        EXPECT_NE(expectedColumnOpen[counter], columnOpen[counter]);
        EXPECT_NE(expectedColumnHigh[counter], columnHigh[counter]);
        EXPECT_NE(expectedColumnLow[counter], columnLow[counter]);
        EXPECT_NE(expectedColumnClose[counter], columnClose[counter]);
        EXPECT_NE(expectedColumnVolume[counter], columnVolume[counter]);
        EXPECT_NE(expectedColumnAdjClose[counter], columnAdjClose[counter]);
    }
}

TEST_F(CSVParserTestFixture, whenTheFileIsNotFoundItThrowsException)
{
    std::string fileName = "../sampleFile/csvSample File1.csv";
    EXPECT_THROW(obj.parseDocument(fileName), InvalidFile);
}

TEST_F(CSVParserTestFixture, whenTheFileIsFoundItWillNotThrowsAnyException)
{
    std::string fileName = "../sampleFile/csvSampleFile1.csv";
    EXPECT_NO_THROW(obj.parseDocument(fileName));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}