#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstddef>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>

int main(int argc, char* argv[])
{
	const int BRAINFUCK_MEM_SIZE = 30000;
	const char* program_file = argc == 2 ? argv[1] : "brainfuck_program.txt";
	std::ifstream file(program_file);
	if (!file.is_open()) {
		std::cerr << "Cannot open a " << program_file << " file" << std::endl;
		return -1;
	}

	std::string content;
	content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	
	std::vector<unsigned char> memory(BRAINFUCK_MEM_SIZE);
	int index = 0;
	auto inc = [&] ()
	{
		++index;
		if (index >= BRAINFUCK_MEM_SIZE)
			index = 0;
	};

	auto dec = [&]()
	{
		--index;
		if (index < 0)
			index = BRAINFUCK_MEM_SIZE - 1;
	};

	auto print = [&]()
	{
		std::cout << (char)memory[index];
	};
	auto input = [&]()
	{
		memory[index] = std::cin.get();
	};
	
	for (int ci = 0, nc = content.size(); ci < nc; ++ci)
	{
		const char c = content[ci];
		if (c == '>') {
			inc();
		}
		else if (c == '<') {
			dec(); 
		}
		else if (c == '+') {
			++memory[index];
		}
		else if (c == '-') {
			--memory[index];
		}
		else if (c == '.') {
			print();
		}
		else if (c == ',') {
			input();
		}
		else if (c == '[') {
			if (!memory[index]) {
				int open = 0;
				do 
				{
					const char c = content[ci];
					if (c == '[')
						++open;
					else if (c == ']') 
					{
						--open;
						if (!open)
							break;
					}
					++ci;
				} while (ci < nc);
			}
		}
		else if (c == ']') {
			if (memory[index]) {
				int close = 0;
				while ( ci >= 0 ) 
				{
					const char c = content[ci--];
					if (c == ']')
						++close;
					else if (c == '[')
					{
						--close;
						if (close == 0)
							break;
					}
				}

			}
		}
		else {
			//skip
		}
	}

	std::cerr << "FINISHED" << std::endl;
}