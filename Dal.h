#pragma once
#include"Dto.h"
#include<fstream>
namespace Dal
{
	class GetSensingData
	{
	public:
		void GetData(std::list<std::string> &, std::string);
		void SaveData(std::list<std::string>, std::string);
	};
	class Readme
	{
	public:
		void GetReadme(std::list<std::string>&);
		void SaveReadme(std::list<std::string>);
	};
	class LogFile
	{
	public:
		void SaveLogFile(std::list<std::string>, std::string);
	};
}