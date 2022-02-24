#include"Bll.h"
namespace Gui
{
	enum Type
	{
		nothing = 0,
		Id = 1,
		Time = 2
	};
	typedef enum Type Type;
	enum Order
	{
		Nothing = 1,
		Ascending = 1,
		Descending = 2
	};
	typedef enum Order Order;
	class CommandLine
	{
	public:
		void Decentralization(int, char*[]);
	};
	class Readme
	{
	public:
		void ReadmeFile();
	};
}