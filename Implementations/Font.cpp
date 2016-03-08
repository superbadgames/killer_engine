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
		std::ifstream file;

		file.open(_fontFile.c_str());

		if(!file.is_open())
		{
			std::cout << "Failed to open file!\n" << _fontFile << std::endl; 
		}
		else
		{
			string line;

			 while(getline(file, line))
			 {
			 	std::cout << line << "\n";
			 }

			 file.close();
		}
			
	}
}