#include"Gui.h"
#include<iostream>
#include<conio.h>
void Gui::CommandLine::Decentralization(int argc, char* argv[])
{
	Bll::DataToHex *dataToHex = new Bll::DataToHex;
	Bll::FileHandler *fileHandler = new Bll::FileHandler;
	Bll::CommandLine *commandLine = new Bll::CommandLine;
	Gui::Readme* readme = new Gui::Readme;
	//commandLine->returnOrderFunction(argc, argv)
	switch (commandLine->returnOrderFunction(argc, argv))
	{
		/*
	* 1. Read for help
	* 2. Transfer with no sort
	* 3. Transfer with Id sort and Ascending Order
	* 4. Transfer with Time sort and Ascending Order
	* 5. Transfer with Id sort and Descending Order
	* 6. Transfer with Time sort and Descending Order
	* Notice: all Error can be found in Readme.txt or SendingData -m
	*/
	case -1:
		std::cout << "Error E001: Unknown command. Type \"SendingData - m\" for help." << std::endl;
	break;
	case -2:
		std::cout << "Error E002: Do not allow more than 6 arguments in the same command. Type \"SendingData - m\" for help." << std::endl;
		break;
	case -3:
		std::cout << "Error E003: Missing arguments. Type \"SendingData - m\" for help." << std::endl;
		break;
	case -6:
		std::cout << "Error E005: " << fileHandler->returnInputFileWithExtension(argv[1]) << " could not be opened. Nothing has been done." << std::endl;
		break;
	case -9:
		std::cout << "Error E009: File name could not be started with number." << std::endl;
		break;
	case -10:
		std::cout << "Error E010: File name just to have character, number, \".\" or \"_\"." << std::endl;
		break;
	case -11:
		std::cout << "Error E011: Input File and Output File is the same." << std::endl;
		break;
	case 1:
		readme->ReadmeFile();
		break;
	case 2:
		if (fileHandler->isFileExist(fileHandler->returnOutputFileWithExtension(argv[2])) == true)
		{
			std::cout << "Warning: " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists.Do you wish to overwrite(y, n) ? : ";
			char c = _getch();
			std::cout << c;
			if (c == 'y')
			{
				dataToHex->DataToHexFunction(argv[1], argv[2], Type::nothing, Order::Nothing);
				std::cout << std::endl << "Convert succesfull. " << std::endl;
			}
			else if (c == 'n')
			{
				std::cout << std::endl << "E006 " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists. Nothing has been done." << std::endl;
			}
			else
			{
				std::cout << std::endl << "Invalid Value.";
			}
		}
		else
		{
			dataToHex->DataToHexFunction(argv[1], argv[2], Type::nothing, Order::Nothing);
			std::cout << std::endl << "Convert succesfull. " << std::endl;
		}
		break;
	case 3:
		if (fileHandler->isFileExist(fileHandler->returnOutputFileWithExtension(argv[2])) == true)
		{
			std::cout << "Warning: " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists.Do you wish to overwrite(y, n) ? : ";
			char c = _getch();
			std::cout << c;
			if (c == 'y')
			{
				dataToHex->DataToHexFunction(argv[1], argv[2], Type::Id, Order::Ascending);
				std::cout << std::endl << "Convert succesfull. " << std::endl;
			}
			else if (c == 'n')
			{
				std::cout << std::endl << "E006 " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists. Nothing has been done." << std::endl;
			}
			else
			{
				std::cout << std::endl << "Invalid Value.";
			}
		}
		else
		{
			dataToHex->DataToHexFunction(argv[1], argv[2], Type::nothing, Order::Nothing);
			std::cout << std::endl << "Convert succesfull. " << std::endl;
		}
		break;
	case 4:
		if (fileHandler->isFileExist(fileHandler->returnOutputFileWithExtension(argv[2])) == true)
		{
			std::cout << "Warning: " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists.Do you wish to overwrite(y, n) ? : ";
			char c = _getch();
			std::cout << c;
			if (c == 'y')
			{
				dataToHex->DataToHexFunction(argv[1], argv[2], Type::Time, Order::Ascending);
				std::cout << std::endl << "Convert succesfull. " << std::endl;
			}
			else if (c == 'n')
			{
				std::cout << std::endl << "E006 " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists. Nothing has been done." << std::endl;
			}
			else
			{
				std::cout << std::endl << "Invalid Value.";
			}
		}
		else
		{
			dataToHex->DataToHexFunction(argv[1], argv[2], Type::nothing, Order::Nothing);
			std::cout << std::endl << "Convert succesfull. " << std::endl;
		}
		break;
	case 5:
		if (fileHandler->isFileExist(fileHandler->returnOutputFileWithExtension(argv[2])) == true)
		{
			std::cout << "Warning: " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists.Do you wish to overwrite(y, n) ? : ";
			char c = _getch();
			std::cout << c;
			if (c == 'y')
			{
				dataToHex->DataToHexFunction(argv[1], argv[2], Type::Id, Order::Descending);
				std::cout << std::endl << "Convert succesfull. " << std::endl;
			}
			else if (c == 'n')
			{
				std::cout << std::endl << "E006 " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists. Nothing has been done." << std::endl;
			}
			else
			{
				std::cout << std::endl << "Invalid Value.";
			}
		}
		else
		{
			dataToHex->DataToHexFunction(argv[1], argv[2], Type::nothing, Order::Nothing);
			std::cout << std::endl << "Convert succesfull. " << std::endl;
		}
		break;
	//"D:\\input.txt", "D:\\output.txt"
	case 6:
		if (fileHandler->isFileExist(fileHandler->returnOutputFileWithExtension(argv[2])) == true)
		{
			std::cout << "Warning: " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists.Do you wish to overwrite(y, n) ? : ";
			char c = _getch();
			std::cout << c;
			if (c == 'y')
			{
				dataToHex->DataToHexFunction(argv[1], argv[2], Type::Time, Order::Descending);
				std::cout << std::endl << "Convert succesfull. " << std::endl;
			}
			else if (c == 'n')
			{
				std::cout << std::endl << "E006 " << fileHandler->returnOutputFileWithExtension(argv[2]) << " already exists. Nothing has been done." << std::endl;
			}
			else
			{
				std::cout << std::endl << "Invalid Value.";
			}
		}
		else
		{
			dataToHex->DataToHexFunction(argv[1], argv[2], Type::nothing, Order::Nothing);
			std::cout << std::endl << "Convert succesfull. " << std::endl;
		}
		break;
	}
}
void Gui::Readme::ReadmeFile()
{
	std::list<std::string> List;
	Bll::Readme* readme = new Bll::Readme;
	readme->GetDataReadme(List);
	std::list <std::string> ::iterator Head;
	for (Head = List.begin(); Head != List.end(); Head++)
	{
		std::cout << *Head << std::endl;
	}
	readme->SaveReadme(List);
}