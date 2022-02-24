#pragma once
#include"Dal.h"
#include"Dto.h"
namespace Bll
{
	union IEEE754
	{
		float f;
		unsigned int temp;
	};
	typedef union IEEE754 IEEE754;
	class DataToHex
	{
	public:
		std::string TransferData(Dto::SensingData);
		void SeperateRawData(Dto::SensingData&, std::string, bool &);
		void DataToHexFunction(std::string, std::string, int, int);
	};
	class Convert
	{
	public:
		char HashTable[17] = {};
		
	public:
		Convert()
		{
			HashTable[0] = '0';
			HashTable[1] = '1';
			HashTable[2] = '2';
			HashTable[3] = '3';
			HashTable[4] = '4';
			HashTable[5] = '5';
			HashTable[6] = '6';
			HashTable[7] = '7';
			HashTable[8] = '8';
			HashTable[9] = '9';
			HashTable[10] = 'a';
			HashTable[11] = 'b';
			HashTable[12] = 'c';
			HashTable[13] = 'd';
			HashTable[14] = 'e';
			HashTable[15] = 'f';
		}
		int HashFunction(std::string);
		std::string FloatToHex(float);
		std::string IntToHex(int, int);
		std::string TimeToHex(std::string);
		int HexToDecimal(std::string);
		std::string ToString(int);
		void deleteExtraBlank(std::string&);
	};
	class Sort
	{
	public:
		void IdSort(std::list<Dto::SensingData>&);
		void TimeSort(std::list<Dto::SensingData>&);
	};
	class CommandLine
	{
	public:
		int returnOrderFunction(int, char* []);
	};
	class FileHandler
	{
	public:
		int	checkErrorFileName(std::string);
		bool isFileExist(std::string);
		std::string returnInputFileWithExtension(std::string);
		std::string returnOutputFileWithExtension(std::string);
		std::string returnFileWithoutExtension(std::string);
	};
	class Readme
	{
	public:
		void SaveReadme(std::list<std::string>);
		void GetDataReadme(std::list<std::string>&);
	};
	class TimeHandler
	{
	public:
		std::string returnTime();
		std::string returnDate();
	};
	class LogFileHandler
	{
	public:
		void CreateLogFile(std::list<std::string>, std::string, std::string);
		std::string CreateLogFileName(std::string, std::string);
	};
}