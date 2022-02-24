#pragma once
#include<List>
#include<String>
namespace Dto
{
	class SensingData
	{
	public:
		int Id;
		std::string Time;
		float Temperature;
		int Humidity;
	public:
		SensingData()
		{
			Id = -1;
			Time = "";
			Temperature = 100;
			Humidity = 100;
		}
		void Reset()
		{
			Id = -1;
			Time = "";
			Temperature = 100;
			Humidity = 100;
		}
	};
}
