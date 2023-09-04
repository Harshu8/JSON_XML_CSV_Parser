#include <iostream>
#include <gtest/gtest.h>
#include "JsonTest.h"

class JSONParserTestFixture : public ::testing::Test
{
public:
    JSONParser<rapidjson::Document, std::string> obj;
};

TEST_F(JSONParserTestFixture, whenWeGetCorrectOutput)
{
    std::string fileName = "../sampleFile/jsonsampleFile1.json";
    rapidjson::Document document = obj.parseDocument(fileName);
    std::vector<std::string> name;
    std::vector<int> age;
    std::vector<std::string> city;
    if (document.IsArray())
    {
        for (rapidjson::SizeType counter = 0; counter < document.Size(); counter++)
        {
            const rapidjson::Value &object = document[counter];
            name.push_back(object["name"].GetString());
            age.push_back(object["age"].GetInt());
            city.push_back(object["city"].GetString());
        }
    }

    std::vector<std::string> expectedName = {"Harsh", "Abhishek verma", "Sachin"};
    std::vector<int> expectedAge = {20, 22, 20};
    std::vector<std::string> expectedCity = {"Agra", "Mathura", "Tundla"};

    for (int counter = 0; counter < name.size(); counter++)
    {
        EXPECT_EQ(true, !strcmp(expectedName[counter].c_str(), name[counter].c_str()));
        EXPECT_EQ(expectedAge[counter], age[counter]);
        EXPECT_EQ(true, !strcmp(expectedCity[counter].c_str(), city[counter].c_str()));
    }
}

TEST_F(JSONParserTestFixture, whenWeGetInorrectOutput)
{
    std::string fileName = "../sampleFile/jsonsampleFile1.json";
    rapidjson::Document document = obj.parseDocument(fileName);
    std::vector<std::string> name;
    std::vector<int> age;
    std::vector<std::string> city;
    if (document.IsArray())
    {
        for (rapidjson::SizeType counter = 0; counter < document.Size(); counter++)
        {
            const rapidjson::Value &object = document[counter];
            name.push_back(object["name"].GetString());
            age.push_back(object["age"].GetInt());
            city.push_back(object["city"].GetString());
        }
    }

    std::vector<std::string> expectedName = {"Abhishek verma", "Sachin", "Harsh"};
    std::vector<int> expectedAge = {21, 12, 12};
    std::vector<std::string> expectedCity = {"Mathura", "Tundla", "Agra"};

    for (int counter = 0; counter < name.size(); counter++)
    {
        EXPECT_NE(true, !strcmp(expectedName[counter].c_str(), name[counter].c_str()));
        EXPECT_NE(expectedAge[counter], age[counter]);
        EXPECT_NE(true, !strcmp(expectedCity[counter].c_str(), city[counter].c_str()));
    }
}

TEST_F(JSONParserTestFixture, whenTheFileIsFoundItWillNotThrowsAnyException)
{
    std::string fileName = "../sampleFile/jsonsampleFile1.json";
    EXPECT_NO_THROW(obj.parseDocument(fileName));
}

TEST_F(JSONParserTestFixture, whenTheFileIsNotFoundItThrowsException)
{
    std::string fileName = "../SampleFile/jsonsampleFi le2.json";
    EXPECT_THROW(obj.parseDocument(fileName), InvalidFile);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}