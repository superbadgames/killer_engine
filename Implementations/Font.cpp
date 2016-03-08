#include <Engine/Font.h>

namespace KillerEngine
{
	Font::Font(void)
	{  }

	Font::Font(string fontName) : _fontName(fontName)
	{  }
	

	Font::Font(string fontName, string fontFile) : _fontName(fontName),
												   _fontFile(fontFile)
	{  }

	void Font::CreateFont(void)
	{
		//std::ifstream file;

		//file.open(_fontFile.c_str());

		FILE * file = fopen(_fontFile.c_str(), "r");

		//if(!file.is_open())
		if(file == NULL)
		{
			std::cout << "Failed to open file!\n" << _fontFile << std::endl; 
		}
		else
		{
			//string line;
			char line[1024];

			 //while(getline(file, line))
			 while(fgets(line, 1024, file))
			 {
			 	std::cout << line << "\n";
			 }

			 //file.close();
			 fclose(file);
		}
			
	}
}