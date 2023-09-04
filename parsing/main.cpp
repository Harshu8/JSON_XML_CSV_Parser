#include <iostream>
#include "CSVParser.h"
#include "XMLParser.h"
#include "JSONParser.h"
#include "InvalidInputException.h"
#include "InvalidFileException.h"

int getInput()
{
    int input;
    std::cin >> input;
    if (std::cin.fail() || std::cin.rdbuf()->in_avail() > 1)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInput();
    }
    return input;
}

void displayXML(rapidxml::xml_node<> *rootNode)
{
    for (rapidxml::xml_node<> *studentNode = rootNode->first_node("Student");
         studentNode; studentNode = studentNode->next_sibling())
    {
        std::cout << "\nStudent Type =   " << studentNode->first_attribute("student_type")->value();
        std::cout << std::endl;
        bool isTrue = true;

        for (rapidxml::xml_node<> *counterNode = studentNode->first_node("Name");
             counterNode; counterNode = counterNode->next_sibling())
        {
            if (isTrue)
            {
                isTrue = false;
                std::cout << "Student Name =   " << counterNode->value();
            }
            else
            {
                isTrue = true;
                std::cout << "Age =  " << counterNode->value();
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void displayJSON(rapidjson::Document document)
{
    if (document.IsArray())
    {
        for (rapidjson::SizeType counter = 0; counter < document.Size(); counter++)
        {
            const rapidjson::Value &object = document[counter];
            std::cout << "Name: " << object["name"].GetString() << std::endl;
            std::cout << "Age: " << object["age"].GetInt() << std::endl;
            std::cout << "City: " << object["city"].GetString() << "\n\n";
        }
    }
    else
    {
        std::cout << "File corrupt\n";
    }
}

void displayCSV(rapidcsv::Document document)
{
    std::vector<float> columnOpen = document.GetColumn<float>("Open");
    std::vector<float> columnHigh = document.GetColumn<float>("High");
    std::vector<float> columnLow = document.GetColumn<float>("Low");
    std::vector<float> columnClose = document.GetColumn<float>("Close");
    std::vector<int> columnVolume = document.GetColumn<int>("Volume");
    std::vector<float> columnAdjClose = document.GetColumn<float>("Adj Close");
    for (int i = 0; i < columnOpen.size(); i++)
    {
        std::cout << "\nOpen: " << columnOpen[i] << " \n"
                  << "High: " << columnHigh[i] << " \n"
                  << "Low: " << columnLow[i] << " \n"
                  << "Close: " << columnClose[i] << " \n"
                  << "Volume: " << columnVolume[i] << " \n"
                  << "Adj Close: " << columnAdjClose[i] << " \n";
    }
    return;
}

int main()
{
    std::cin.sync_with_stdio(false);
    while (true)
    {
        try
        {
            std::cout << "\nAvailable option: \n";
            std::cout << "1.Parse XML File\n2.Parse JSON File\n3.Parse CSV File\n-1.Exit\n";
            std::cout << "Enter you choice: ";
            int choice = getInput();
            if( choice == -1)
            {
                std::cout<<"Program Stopped.\n";
                return 0;
            }
            else if(choice < 1 || choice > 3)
            {
                std::cout<<"Enter a valid chocie.\n";
                continue;
            }

            std::string fileNameInput;
            std::cout << "Enter file name to parse: ";
            std::cin >> fileNameInput;
            std::string fileName = "sampleFile/" + fileNameInput;

            switch (choice)
            {
            case 1:
            {
                fileName = fileName + ".xml";
                XMLParser<rapidxml::xml_node<> *, std::string> xmlOject;
                rapidxml::xml_node<> *temp = xmlOject.parseDocument(fileName);
                displayXML(temp);
                std::cout << "\n\n";
                break;
            }
            case 2:
            {
                fileName = fileName + ".json";
                JSONParser<rapidjson::Document, std::string> jsonObject;
                displayJSON(jsonObject.parseDocument(fileName));
                std::cout << "\n\n";
                break;
            }
            case 3:
            {
                fileName = fileName + ".csv";
                CSVParser<rapidcsv::Document, std::string> csvObject;
                displayCSV(csvObject.parseDocument(fileName));
                std::cout << "\n\n";
                break;
            }
            }
        }
        catch (InvalidInput error)
        {
            std::cout << error.what() << std::endl;
            continue;
        }
        catch (InvalidFile error)
        {
            std::cout << error.what() << std::endl;
            continue;
        }
        catch (std::out_of_range error)
        {
            std::cout << "File corrupted." << std::endl;
            continue;
        }
        catch (rapidxml::parse_error error)
        {
            std::cout << "File corrupted." << std::endl;
            continue;
        }
    }
    return 0;
}