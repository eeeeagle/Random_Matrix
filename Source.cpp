#include <random>
#include <iostream>
#include <fstream>
#include <string>

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
				file << ran() % max_value << ' ';
			}
			file << '\n';
		}

		file.close();
	}
	catch (std::ios_base::failure const& ex)
	{
		std::cout << "WRITING ERROR: " << ex.what() << '\n';
		_exit(EXIT_FAILURE);
	}
}

int main(int argc, char** argv)
{
	system("title Random Matrix");

	if (argc != 5 || (argc == 2 && strcmp(argv[1], "--help") == 0))
	{
		std::cout	<< "Specify number of rows, columns, max possible value and locate path to output file\n\n"
					<< "EXAMPLE:\n"
					<< "    .../RandomMarix.exe <rows> <columns> <max_value> <output_file>\n";
		_exit(EXIT_FAILURE);
	}

	const unsigned columns		= str_to_ulong(argv[1]);
	const unsigned rows			= str_to_ulong(argv[2]);
	const unsigned max_value	= str_to_ulong(argv[3]);
	const std::string str		= argv[4];

	std::cout << "Writing random matrix to [" << str << "]...";
	random_file(columns, rows, max_value, str);
	std::cout << std::string(str.size() + 40, ' ');

	std::cout << "\rSaved matrix in file [" << str << "]\n\n";
	return 0;
}