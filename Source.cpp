#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>

#define TIMEOUT 2000

unsigned long str_to_ulong(const std::string& str)
{
	try
	{
		unsigned long i{ std::stoul(str) };
		return i;
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout	<< "INVALID TYPE: " << std::string(str) << '\n'
					<< "    Value must be unsigned integer\n\n" 
					<< ex.what() << '\n';
	}
	catch (std::out_of_range const& ex)
	{
		std::cout	<< "OUT OF RANGE: N = " << std::string(str) << "\n\n" 
					<< ex.what() << '\n';
	}
	Sleep(TIMEOUT);
	_exit(EXIT_FAILURE);
}

void random_file(const unsigned& columns, const unsigned& row, const unsigned& max_value, const std::string& filename)  
{
	try
	{
		std::ofstream file;
		file.exceptions(std::ofstream::badbit);
		file.open(filename);

		std::mt19937 ran;
		unsigned n = 0;
		for (unsigned i = 0; i < columns; i++)
		{
			for (unsigned j = 0; j < row; j++)
			{
				ran.seed(++n);
				file << ran() % max_value;
				file << ' ';
			}
			file << '\n';
		}

		file.close();
	}
	catch (std::ios_base::failure const& ex)
	{
		std::cout << "WRITING ERROR: " << ex.what() << '\n';
		Sleep(TIMEOUT);
		_exit(EXIT_FAILURE);
	}
}

int main(int argc, char** argv)
{
	system("title Random Matrix");

	if ((argc == 2 && std::string(argv[1]) == "-help") || argc > 5)
	{
		std::cout << "Specify columns, rows, max possible value, output file\n\n"
			<< "EXAMPLE:\n"
			<< "    .../RandomMarix.exe <columns> <rows> <max_value> <output_file>\n";
		Sleep(TIMEOUT);
		_exit(EXIT_FAILURE);
	}

	unsigned columns, rows, max_value;
	std::string str;
	if (argc == 5)
	{
		columns		= str_to_ulong(argv[1]);
		rows		= str_to_ulong(argv[2]);
		max_value	= str_to_ulong(argv[3]);
		str			= argv[4];
	}
	else
	{
		std::cout << "  Columns: ";
		std::cin >> str;
		columns = str_to_ulong(str);

		std::cout << "     Rows: ";
		std::cin >> str;
		rows = str_to_ulong(str);

		std::cout << "Max value: ";
		std::cin >> str;
		max_value = str_to_ulong(str);

		std::cout << "\nLocate path to output file? (Y/N)";
		int key = 0;
		do
		{
			key = _getch();
			key = toupper(key);
		} while (key != 'Y' && key != 'N');
		std::cout << "\r                                    ";
		if (key == 'Y')
		{
			std::cout << "\rLocate path to output file: ";
			std::cin >> str;
		}
		else
			str = "output.txt";
	}

	std::cout << "\rWriting random matrix to [" << str << "]...\r";
	random_file(columns, rows, max_value, str);
	std::cout << "\r                                ";
	for (size_t i = str.size(); i > 0; i--)
		std::cout << ' ';

	std::cout << "\rSaved matrix in file [" << str << "]\n\n";
	Sleep(TIMEOUT);
	return 0;
}