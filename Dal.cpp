#include"Dal.h"

void Dal::GetSensingData::GetData(std::list<std::string> &List, std::string inputFile)
{
    std::ifstream f;
    int count = 0;
    std::string temp = "";
    f.open(inputFile.c_str(), std::ios::in);
    std::getline(f, temp);
    while (true)
    {
        if (f.eof() == true)
            break;
        std::getline(f, temp);
        List.push_back(temp);
    }
    f.close();
}
void Dal::GetSensingData::SaveData(std::list<std::string> List, std::string outputFile)
{
    std::ofstream f;
    f.open(outputFile.c_str(), std::ios::out);
    std::list <std::string> ::iterator Head;
    for (Head = List.begin(); Head != List.end(); Head++)
    {
		if(*Head != "")
			f << *Head << std::endl;
    }
    f.close();
}

void Dal::Readme::GetReadme(std::list<std::string>& List)
{
	List.push_back("Format for a command: MorseSendingData* Input* Output* -s <type> <order>");
	List.push_back("Input: single input file name or path together (Exp D:\Filename.txt)");
	List.push_back("Output: single output file name or path together (Exp D:\Filename.txt)");
	List.push_back("Type: \"-ti\" Time sort, \"-id\" Id sort");
	List.push_back("Order: \"-asc\" Ascending order, \"des\" Descending order");
	List.push_back("Notice: \"*\" is compulsory.");
	List.push_back("Error E001: Unknown command. Type \"SendingData -m\" for help.");
	List.push_back("Error E001: Unknown command. Type \"SendingData -m\" for help.");
	List.push_back("Error E003: Missing arguments. Type \"SendingData -m\" for help.");
	List.push_back("Error E004: Changing order of appearance. Type \"SendingData -m\" for help.");
	List.push_back("Error E005: (File name) could not be opened.");
	List.push_back("Error E006: (File name) already exists. Nothing has been done.");
	List.push_back("Error E007: Invalid data in row XX.");
	List.push_back("Error E008: Invalid hex code in row XX.");
	List.push_back("Error E009: File name could not be started with number.");
	List.push_back("Error E010: File name just to have character, number, \".\" or \"_\".");
	List.push_back("Error E011: Input File and Output File is the same.");
}
void Dal::Readme::SaveReadme(std::list<std::string>List)
{
	std::ofstream f;
	f.open("Readme.txt", std::ios::out);
	std::list <std::string> ::iterator Head;
	for (Head = List.begin(); Head != List.end(); Head++)
	{
		f << *Head << std::endl;
	}
	f.close();
}

void Dal::LogFile::SaveLogFile(std::list<std::string> List, std::string fileName)
{
	std::ofstream f;
	fileName = fileName + ".log";
	f.open(fileName.c_str(), std::ios::out);
	std::list <std::string> ::iterator Head;
	for (Head = List.begin(); Head != List.end(); Head++)
	{
		f << *Head << std::endl;
	}
	f.close();
}