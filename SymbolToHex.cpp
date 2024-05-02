#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

static constexpr const char* const DELIMITER = "00";//me delimiter :3

enum Selection
{
	Console = '0',
	File
};

std::string ConvertLineToHex(const std::string& text, const char* delimiter)
{
	std::stringstream text_hex;
	for (char c : text)
	{
		text_hex << std::hex << static_cast<int>(c);
	}
	text_hex << delimiter;

	return text_hex.str();
}

int main()
{
	bool isRunning = true;

	while (isRunning)
	{
		char selection_char = NULL;
		std::string read_text = "";
		std::string text_to_save = "";
		do
		{
			system("cls");
			std::cout << "Convert from: \n\r[0]Console input\n\r[1]File" << std::endl;
			selection_char = getchar();

		} while (selection_char != Console && selection_char != File);

		if (selection_char == File)
		{
			try
			{
				std::string	file_path = "";
				std::cout << "Enter the path to input file:" << std::endl;
				std::cin >> file_path;

				std::ifstream infile(file_path);
				text_to_save = "00";
				while (getline(infile, read_text))
				{
					text_to_save.append(ConvertLineToHex(read_text, DELIMITER));
				}
				std::cout << "Output:\n" << text_to_save << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << "An error has occured while reading from file, check if the file path is correct." << std::endl;
				std::cout << e.what();
				break;
			}
		}
		else
		{
			std::cin.ignore();
			std::cout << "Enter text:" << std::endl;
			std::getline(std::cin, read_text);
			text_to_save = ConvertLineToHex(read_text, DELIMITER);
			std::cout << text_to_save << std::endl;
		}

		std::ofstream outfile;
		std::string file_path;
		try
		{
			std::cout << "Enter the path to output file:" << std::endl;
			std::cin >> file_path;

			outfile.open(file_path, std::ios_base::trunc);
			outfile << text_to_save;
			outfile.close();
		}
		catch (const std::exception& e)
		{
			std::cout << "Given file location is non accessible, please try again." << std::endl;
			std::cout << e.what();
			break;
		}
		std::cout << "The file has been saved succesfully.\n" << std::endl;
		
		char exit = NULL;
		std::cout << "Do you want to exit the program [y/n]:";
		do
		{
			exit = getchar();
		} while (exit != 'y' && exit != 'n');
		
		isRunning = exit == 'y' ? false : true;
	}
}
