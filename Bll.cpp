#define _CRT_SECURE_NO_WARNINGS
#include"Bll.h"
#include<iostream>
#include<string>
#include<list>
#include<ctime>

void Bll::DataToHex::SeperateRawData(Dto::SensingData &sensingData, std::string RawData, bool& isHaveError)
{
    std::string temp = "";
    Bll::Convert *convert = new Bll::Convert;
    convert->deleteExtraBlank(RawData);
    bool checkId = 1, checkTime = 1, checkTemp = 1, checkHumid = 1;
    temp = RawData.substr(0, RawData.find(","));
    if (temp == "")
    {
        isHaveError = true;
        checkId = 0;
    }
    else
    {
        if (temp.find('.') != -1)
        {
            isHaveError = true;
            checkId = 0;
        }
        if (atoi(temp.c_str()) < 0)
        {
            isHaveError = true;
            checkId = 0;
        }
        if(checkId == true)
            sensingData.Id = std::atoi(temp.c_str());
    }
    RawData = RawData.substr(RawData.find(",") + 1);
    temp = RawData.substr(0, RawData.find(","));
    if (temp == "" || temp.length() != 19)
    {
        isHaveError = true;
        checkTime = 0;
    }
    else
    {
        int Year, Month, Day, Hour, Minute, Second = 0;
        Year = std::atoi(temp.substr(0, 4).c_str());
        if (Year <= 0)
        {
            isHaveError = true;
            checkTime = 0;
        }
        Month = std::atoi(temp.substr(5, 2).c_str());
        if (Month <= 0 || Month > 12)
        {
            isHaveError = true;
            checkTime = 0;
        }
        Day = std::atoi(temp.substr(8, 2).c_str());
        if (Month == 2)
        {
            if (Day > 29)
            {
                isHaveError = true;
                checkTime = 0;
            }
        }
        if (Day <= 0 || Day > 31)
        {
            isHaveError = true;
            checkTime = 0;
        }
        Hour = std::atoi(temp.substr(11, 2).c_str());
        if (Hour < 0 || Hour >= 24)
        {
            isHaveError = true;
            checkTime = 0;
        }
        Minute = std::atoi(temp.substr(14, 2).c_str());
        if (Minute < 0 || Minute >= 60)
        {
            isHaveError = true;
            checkTime = 0;
        }
        Second = std::atoi(temp.substr(17, 4).c_str());
        if (Second < 0 || Second >= 60)
        {
            isHaveError = true;
            checkTime = 0;
        }
        if(checkTime == true)
            sensingData.Time = temp;
    }
    RawData = RawData.substr(RawData.find(",") + 1);
    temp = RawData.substr(0, RawData.find(","));
    if (temp == "")
    {
        isHaveError = true;
        checkTemp = 0;
    }
    else
    {
        if (atof(temp.c_str()) < -10.0 || atof(temp.c_str()) > 51.0)
        {
            isHaveError = true;
            checkTemp = 0;
        }
        if (checkTemp == true)
            sensingData.Temperature = std::atof(temp.c_str());
    }
    RawData = RawData.substr(RawData.find(",") + 1);
    temp = RawData;
    if (temp == "")
    {
        isHaveError = true;
        checkHumid = 0;
    }
    else
    {
        if (atoi(temp.c_str()) < 40 || atoi(temp.c_str()) > 95)
        {
            isHaveError = true;
            checkHumid = 0;
        }
        if(checkHumid == true)
            sensingData.Humidity = std::atoi(temp.c_str());
    }
}

void Bll::DataToHex::DataToHexFunction(std::string inputFile, std::string outputFile, int type, int order)
{
    bool isHaveError = false;
    Bll::FileHandler *fileHandler = new Bll::FileHandler;
    inputFile = fileHandler->returnInputFileWithExtension(inputFile);
    outputFile = fileHandler->returnOutputFileWithExtension(outputFile);
    std::list<std::string> ErrorList;
    Dal::GetSensingData* getSensingData = new Dal::GetSensingData;
    std::list<std::string> RawData;
    getSensingData->GetData(RawData, inputFile);
    std::list <std::string> ::iterator Head;
    std::list <Dto::SensingData> ::iterator HeadForSensingList;
    std::list<std::string> HexList;
    std::list<Dto::SensingData> sensingDataList;
    Bll::Convert* convert = new Bll::Convert;
    Bll::Sort* sort = new Bll::Sort;
    int Line = 1;
    Dto::SensingData sensingData;
    for (Head = RawData.begin(); Head != RawData.end(); Head++)
    {
        Bll::DataToHex::SeperateRawData(sensingData, *Head, isHaveError);
        sensingDataList.push_back(sensingData);
        if (isHaveError == true)
        {
            ErrorList.push_back("Error 007: Invalid data in row " + convert->ToString(Line));
        }
        isHaveError = false;
        Line++;
        sensingData.Reset();
    }
    
    if (type == 1 && order == 1) // Id sort && ascending order
    {
        sort->IdSort(sensingDataList);
    }
    if (type == 2 && order == 1)
    {
        sort->TimeSort(sensingDataList);
    }
    if (type == 1 && order == 2)
    {
        sort->IdSort(sensingDataList);
        sensingDataList.reverse();
    }
    if (type == 2 && order == 2)
    {
        sort->TimeSort(sensingDataList);
        sensingDataList.reverse();
    }
    for (HeadForSensingList = sensingDataList.begin(); HeadForSensingList != sensingDataList.end(); HeadForSensingList++)
    {
        HexList.push_back(Bll::DataToHex::TransferData(*HeadForSensingList));
    }
    getSensingData->SaveData(HexList, outputFile);
    if (ErrorList.size() != 0)
    {
        Bll::LogFileHandler *logFileHandler = new Bll::LogFileHandler;
        logFileHandler->CreateLogFile(ErrorList, inputFile, outputFile);
    }
}
std::string Bll::DataToHex::TransferData(Dto::SensingData sendingData)
{
    std::string Data = "";
    Bll::Convert* convert = new Bll::Convert;
    std::string HexOfId, HexOfTime, HexOfTemp, HexOfHumid = "";
    if (sendingData.Id != -1)
    {
        HexOfId = convert->IntToHex(sendingData.Id, 8);
    }
    if (sendingData.Time != "")
    {
        HexOfTime = convert->TimeToHex(sendingData.Time);
    }
    if (sendingData.Temperature != 100)
    {
        HexOfTemp = convert->FloatToHex(sendingData.Temperature);
    }
    if (sendingData.Humidity != 100)
    {
        HexOfHumid = convert->IntToHex(sendingData.Humidity, 8);
    }
    Data = HexOfId + " " + HexOfTime + " " + HexOfTemp + " " + HexOfHumid;
    if (Data == "   ")
        return "";
    convert->deleteExtraBlank(Data);
    std::string HexOfPaketLength = convert->IntToHex((Data.length() + 13) / 3, 8);
    Data = HexOfPaketLength + " " + Data;
    int checkSum = 0;
    for (int i = 0; i < convert->HexToDecimal(HexOfPaketLength) - 4; i++)
    {
        checkSum += convert->HexToDecimal(Data.substr(0, 2));
        Data = Data.substr(3);
    }
    checkSum += convert->HexToDecimal(Data);
    std::string HexOfCheckSum = convert->IntToHex(1024- checkSum,8);
    Data = "00 " + HexOfPaketLength + " " + HexOfId + " " + HexOfTime + " " + HexOfTemp + " " + HexOfHumid + " " + HexOfCheckSum + " ff";
    convert->deleteExtraBlank(Data);
    return Data;
}
int Bll::Convert::HashFunction(std::string Bits)
{
    int hashValue = (Bits[0] - 48) * 8 + (Bits[1] - 48) * 4 + (Bits[2] - 48) * 2 + (Bits[3] - 48);
    return hashValue;
}
std::string Bll::Convert::IntToHex(int Element,int Nbit)
{
    int Index;
    std::string temp = "";
    for (Index = Nbit - 1; Index >= 0; Index--) {
        if ((Element >> Index) & 1)
            temp.push_back('1');
        else
            temp.push_back('0');
    }
    std::string hexValue = "";
    for (int i = 0; i < temp.length(); i += 4)
    {
        hexValue.push_back(Bll::Convert::HashTable[Bll::Convert::HashFunction(temp.substr(i, 4))]);
    }
    if(hexValue.length()%2!=0)
        hexValue = "0" + hexValue;
    temp = "";
    int length = hexValue.length();
    for (int i = 0; i < length/2-1; i++)
    {
        temp.append(hexValue.substr(0, 2) + " ");
        hexValue = hexValue.substr(2);
    }
    temp.append(hexValue);
    return temp;
}
std::string Bll::Convert::FloatToHex(float Element)
{
	Bll::IEEE754 temp;
	temp.f = Element;
	return Bll::Convert::IntToHex(temp.temp,32);
}
std::string Bll::Convert::TimeToHex(std::string Time)
{
    struct tm t;
    time_t TimeStamp;
    t.tm_year =  std::atoi(Time.substr(0,4).c_str())- 1900;  // Year - 1900
    t.tm_mon = std::atoi(Time.substr(5, 2).c_str())-1;           // Month, where 0 = jan
    t.tm_mday = std::atoi(Time.substr(8, 2).c_str());          // Day of the month
    t.tm_hour = std::atoi(Time.substr(11, 2).c_str());
    t.tm_min = std::atoi(Time.substr(14, 2).c_str());
    t.tm_sec = std::atoi(Time.substr(17, 4).c_str());
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    TimeStamp = mktime(&t);
    return Bll::Convert::IntToHex(TimeStamp,32);
}
int Bll::Convert::HexToDecimal(std::string HexCode)
{
    int len = HexCode.size();
    int base = 1;
    int decValue = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (HexCode[i] >= '0' && HexCode[i] <= '9') {
            decValue += (int(HexCode[i]) - 48) * base;
            base = base * 16;
        }
        else if (HexCode[i] >= 'a' && HexCode[i] <= 'f')
        {
            decValue += (int(HexCode[i]) - 87) * base;
            base = base * 16;
        }
    }
    return decValue;
}
std::string Bll::Convert::ToString(int Value)
{
    std::string Temp = std::to_string(Value);
    if (Value < 10)
        Temp = "0" + Temp;
    return Temp;
}
void Bll::Convert::deleteExtraBlank(std::string& Text)
{
    while (true)
    {
        int Index = Text.find("  ");
        if (Index == -1)
        {
            break;
        }
        Text = Text.substr(0, Index) + " " + Text.substr(Index + 2);
    }
    if (Text[0] == ' ')
        Text = Text.substr(1);
    if (Text[Text.length() - 1] == ' ')
        Text.pop_back();
}
void Bll::Sort::IdSort(std::list<Dto::SensingData>& sensingData)
{
    bool Check = false;
    std::list<Dto::SensingData>::iterator Head;
    std::list<Dto::SensingData>::iterator Next;
    while (true)
    {
        Check = false;
        Next = sensingData.begin();
        for (Head = sensingData.begin();; Head++)
        {
            Next++;
            if (Next == sensingData.end())
                break;
            if (Head->Id > Next->Id)
            {
                Check = true;
                Dto::SensingData Temp = *Head;
                *Head = *Next;
                *Next = Temp;
            }
            if (Head->Id == Next->Id)
            {
                if (Head->Time > Next->Time)
                {
                    Check = true;
                    Dto::SensingData Temp = *Head;
                    *Head = *Next;
                    *Next = Temp;
                }
            }
        }
        if (Check == false)
            return;
    }
}
void Bll::Sort::TimeSort(std::list<Dto::SensingData>& sensingData)
{
    bool Check = false;
    std::list<Dto::SensingData>::iterator Head;
    std::list<Dto::SensingData>::iterator Next;
    while (true)
    {
        Check = false;
        Next = sensingData.begin();
        for (Head = sensingData.begin();; Head++)
        {
            Next++;
            if (Next == sensingData.end())
                break;
            if (Head->Time > Next->Time)
            {
                Check = true;
                Dto::SensingData Temp = *Head;
                *Head = *Next;
                *Next = Temp;
            }
            if (Head->Time == Next->Time)
            {
                if (Head->Id > Next->Id)
                {
                    Check = true;
                    Dto::SensingData Temp = *Head;
                    *Head = *Next;
                    *Next = Temp;
                }
            }
        }
        if (Check == false)
            return;
    }
}

bool Bll::FileHandler::isFileExist(std::string fileName)
{
    std::ifstream f;
    f.open(fileName.c_str(), std::ios::in);
    if (f.is_open() == true)
        return true;
    return false;
}
int Bll::FileHandler::checkErrorFileName(std::string FileName)
{
    bool Check = false;
    if (FileName[0] >= '1' && FileName[0] <= '9')
        return 0;//File name could not be started with number
    if (FileName[0] == '-')
        return 1;//Missing Argument
    for (int i = 0; i < FileName.length(); i++)
    {
        Check = false;
        if (FileName[i] >= 'A' && FileName[i] <= 'z')
            Check = true;
        else if (FileName[i] >= '1' && FileName[i] <= '9')
            Check = true;
        else if (FileName[i] == '_')
            Check = true;
        else if (FileName[i] == '.')
            Check = true;
        else if (FileName[i] == '\\')
            Check = true;
        else if (FileName[i] == ':')
            Check = true;
        else {};
        if (Check == false)
            return 2;//File name just to have character, number, "." or "_" 
    }
    return 3;
}
std::string Bll::FileHandler::returnInputFileWithExtension(std::string fileName)
{
    if (fileName.find(".") == -1)
    {
        return fileName + ".csv";
    }
    return fileName;
}
std::string Bll::FileHandler::returnOutputFileWithExtension(std::string fileName)
{
    if (fileName.find(".") == -1)
    {
        return fileName + ".txt";
    }
    return fileName;
}
std::string Bll::FileHandler::returnFileWithoutExtension(std::string fileName)
{
    for (int i = fileName.length(); i >= 0; i--)
    {
        if (fileName[i] == '\\')
            fileName = fileName.substr(i + 1);
    }
    for (int i = fileName.length(); i >= 0; i--)
    {
        if (fileName[i] == '.')
            fileName = fileName.substr(0,i);
    }
    return fileName;
}
int Bll::CommandLine::returnOrderFunction(int argc, char* argv[])
{
    //Notice: all Error id are presented in Readme.txt or morse -h

    if (argc > 6)
        return -2;//E002
    if (argc == 4)
        return -3;//E003
    Bll::FileHandler* fileHandler = new Bll::FileHandler;
    std::string Text[6];
    Text[0] = Text[1] = Text[2] = Text[3] = Text[4] = Text[5] = "";
    for (int i = 0; i < argc; i++)
    {
        Text[i].append(argv[i]);
    }
    if (argc == 1)
    {
        return -1;//E001
    }
    if (argc == 2)
    {
        if (Text[1] == "-m")
        {
            return 1;//Read for help
        }
        else
            return -1;//E001
    }
    
    if (argc >= 3)
    {
        //input file 
        if (fileHandler->checkErrorFileName(argv[1]) == 0)
        {
            return -9; // E009
        }
        if (fileHandler->checkErrorFileName(argv[1]) == 1)
        {
            return -3; //E003
        }
        if (fileHandler->checkErrorFileName(argv[1]) == 2)
        {
            return -10; //E010
        }
        if (fileHandler->isFileExist(fileHandler->returnInputFileWithExtension(argv[1])) == false)
        {
            return -6; //E006
        }
        //output file 
        if (fileHandler->checkErrorFileName(argv[2]) == 0)
        {
            return -9; // E009                                                                                                                                                                    
        }
        if (fileHandler->checkErrorFileName(argv[2]) == 1)
        {
            return -3; //E003
        }
        if (fileHandler->checkErrorFileName(argv[2]) == 2)
        {
            return -10; //E010
        }
        if (Text[1] == Text[2])
        {
            return -11;//E011
        }
        if (argc == 3)
        {
            return 2; // Transfer with no sort
        }
        if (argc == 5)
        {
            if (Text[3] != "-s")
            {
                return -1;//E001
            }
            else
            {
                if (Text[4] == "-id")
                {
                    return 3; //Transfer with Id sort and Ascending Order
                }
                if (Text[4] == "-ti")
                {
                    return 4; //Transfer with Time sort and Ascending Order
                }
            }
        }
        if (argc == 6)
        {
            if (Text[3] != "-s")
            {
                return -1;//E001
            }
            else
            {
                if (Text[4] == "-id")
                {
                    if(Text[5] == "-asc")
                        return 3; //Transfer with Id sort and Ascending Order
                    if (Text[5] == "-des")
                        return 5; //Transfer with Id sort and Descending Order
                    else
                        return -1;//E001
                }
                if (Text[4] == "-ti")
                {
                    if (Text[5] == "-asc")
                        return 4; //Transfer with Time sort and Ascending Order
                    if (Text[5] == "-des")
                        return 6; //Transfer with Time sort and Descending Order
                    else
                        return -1;//E001
                }
                else
                    return - 1; //E001
            }
        }
    }
    return -1;//E001
}

//Function for Readme (for help)
void Bll::Readme::GetDataReadme(std::list<std::string>& List)
{
    Dal::Readme* readme = new Dal::Readme;
    readme->GetReadme(List);
}
void Bll::Readme::SaveReadme(std::list<std::string>List)
{
    Dal::Readme* readme = new Dal::Readme;
    readme->SaveReadme(List);
}

std::string Bll::TimeHandler::returnTime()
{
    Bll::Convert *convert = new Bll::Convert;
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    return convert->ToString(ptr->tm_hour) + convert->ToString(ptr->tm_min) + convert->ToString(ptr->tm_sec);
}
std::string Bll::TimeHandler::returnDate()
{
    Bll::Convert* convert = new Bll::Convert;
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    return convert->ToString(ptr->tm_year + 1900) + convert->ToString(ptr->tm_mon + 1) + convert->ToString(ptr->tm_mday);
}

std::string Bll::LogFileHandler::CreateLogFileName(std::string inputFile, std::string outputFile)
{
    Bll::FileHandler *fileHandler = new Bll::FileHandler;
    Bll::TimeHandler *timeHandler = new Bll::TimeHandler;
    std::string fileName = fileHandler->returnFileWithoutExtension(inputFile) + "_" 
        + fileHandler->returnFileWithoutExtension(outputFile) + "_" + timeHandler->returnDate() + "_" + timeHandler->returnTime();
    return fileName;
}
void Bll::LogFileHandler::CreateLogFile(std::list<std::string> list, std::string inputFile, std::string outputFile)
{
    Dal::LogFile *logFile = new Dal::LogFile;
    logFile->SaveLogFile(list, CreateLogFileName(inputFile, outputFile));
}