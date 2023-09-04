#include <iostream>
#include <gtest/gtest.h>
#include "XmlTest.h"

class XMLParserTestFixture : public ::testing::Test
{
public:
    XMLParser<rapidxml::xml_node<> *, std::string> obj;
};

TEST_F(XMLParserTestFixture, whenWeGetCorrectOutput)
{
    std::string filename = "../SampleFile/xmlsampleFile1.xml";
    rapidxml::xml_node<> *rootNode = obj.parseDocument(filename);
    std::vector<std::string> studentType;
    std::vector<std::string> studentName;
    std::vector<std::string> studentAge;

    for (rapidxml::xml_node<> *studentNode = rootNode->first_node("Student"); studentNode; studentNode = studentNode->next_sibling())
    {
        studentType.push_back(studentNode->first_attribute("student_type")->value());
        bool isTrue = true;
        for (rapidxml::xml_node<> *studentNameNode = studentNode->first_node("Name"); studentNameNode; studentNameNode = studentNameNode->next_sibling())
        {
            if (isTrue)
            {
                isTrue = false;
                studentName.push_back(studentNameNode->value());
            }
            else
            {
                isTrue = true;
                studentAge.push_back(studentNameNode->value());
            }
        }
    }

    std::vector<std::string> expectedStudentType = {"Part-time", "Full-time", "Part-time", "No-time"};
    std::vector<std::string> expectedStudentName = {"John", "Sean", "Sarah", "Sachin"};
    std::vector<std::string> expectedStudentAge = {"10", "20", "30", "40"};

    for (int i = 0; i < studentType.size(); i++)
    {
        EXPECT_EQ(true, !strcmp(expectedStudentType[i].c_str(), studentType[i].c_str()));
        EXPECT_EQ(true, !strcmp(expectedStudentName[i].c_str(), studentName[i].c_str()));
        EXPECT_EQ(true, !strcmp(expectedStudentAge[i].c_str(), studentAge[i].c_str()));
    }
}

TEST_F(XMLParserTestFixture, whenWeGetIncorrectOutput)
{
    std::string filename = "../SampleFile/xmlsampleFile1.xml";
    rapidxml::xml_node<> *rootNode = obj.parseDocument(filename);
    std::vector<std::string> studentType;
    std::vector<std::string> studentName;
    std::vector<std::string> studentAge;

    for (rapidxml::xml_node<> *studentNode = rootNode->first_node("Student"); studentNode; studentNode = studentNode->next_sibling())
    {
        studentType.push_back(studentNode->first_attribute("student_type")->value());
        bool isTrue = true;
        for (rapidxml::xml_node<> *studentNameNode = studentNode->first_node("Name"); studentNameNode; studentNameNode = studentNameNode->next_sibling())
        {
            if (isTrue)
            {
                isTrue = false;
                studentName.push_back(studentNameNode->value());
            }
            else
            {
                isTrue = true;
                studentAge.push_back(studentNameNode->value());
            }
        }
    }

    std::vector<std::string> expectedStudentType = {"Full-time", "Part-time", "No-time", "Part-time"};
    std::vector<std::string> expectedStudentName = {"Sean", "Sarah", "Sachin", "John"};
    std::vector<std::string> expectedStudentAge = {"20", "30", "40", "10"};

    for (int i = 0; i < studentType.size(); i++)
    {
        EXPECT_NE(true, !strcmp(expectedStudentType[i].c_str(), studentType[i].c_str()));
        EXPECT_NE(true, !strcmp(expectedStudentName[i].c_str(), studentName[i].c_str()));
        EXPECT_NE(true, !strcmp(expectedStudentAge[i].c_str(), studentAge[i].c_str()));
    }
}


TEST_F(XMLParserTestFixture, whenTheFileIsFoundItWillNotThrowsAnyException)
{
    std::string fileName = "../SampleFile/xmlsampleFile1.xml";
    EXPECT_NO_THROW(obj.parseDocument(fileName));
}

TEST_F(XMLParserTestFixture, whenTheFileIsNotFoundItThrowsException)
{
    std::string fileName = "../SampleFile/xmlsampleFi le2.xml";
    EXPECT_THROW(obj.parseDocument(fileName), InvalidFile);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}