#include <Engine/Font.h>

namespace KillerEngine
{
	Font::Font(void) : _fontName(), _fontFile()
	{  }

	void Font::InitFont(string fontName, string fontFile)
	{
		_fontName = fontName;

		_fontFile = fontFile;

		std::ifstream file;

		file.open(_fontFile.c_str());

		if(!file.is_open())
		{
			std::cout << "Failed to open file!\n" << _fontFile << std::endl; 
		}
		else
		{
			std::vector<string> results;

			 for(string token; getline(file, token, ' '); )
			 {
			 	if(token.find_first_not_of(' ') != std::string::npos) 
			 		results.push_back(std::move(token));
			 }

			 bool first = true;

			 results.erase(results.begin(), results.begin() + _headerSize);

			 //for(auto i = results.begin(); i != results.end(); ++i)
			 //95 is the number of characters in this sheet. 
			 //There will need to be a way to find this number
			 //from the sheet itself or something
			 //for(U32 i = 0; i <= results.size(); ++i )
			 while(results.size() > 1)
			 {		
			 	if(first)
			 	{
			 		first = false;
			 		//use elements 0 - 7
			 		
			 		string id = results[0];

					string x = results[1];

			 		string y = results[2];

			 		string width = results[3];

			 		string height = results[4];

			 		string xoffset = results[5];

			 		string yoffset = results[6];

			 		string xadvance = results[7];

			 		_AddNewCharacterData(id, x, y, width, height, xoffset, yoffset, xadvance);

				 	results.erase(results.begin(), results.begin()+9);
				 	continue;
			 	}
			 	//after first, use elements 1 - 8
			 	//need to skip char keyword
			 	string id = results[1];

				string x = results[2];

		 		string y = results[3];

		 		string width = results[4];

		 		string height = results[5];

		 		string xoffset = results[6];

		 		string yoffset = results[7];

		 		string xadvance = results[8];

		 		_AddNewCharacterData(id, x, y, width, height, xoffset, yoffset, xadvance);
		 
			 	results.erase(results.begin(), results.begin() + 10);
			 }

			 file.close();
		}
			
	}//CreateFont

	void Font::CreateRenderText(string text)
	{
		for(U32 i = 0; i <= text.length(); ++i)
		{
			U32 stringIndex = (int)text[i];
			std::cout << (char)_fontCharData[stringIndex].id;
		}
		std::cout << '\n';
	}

	void Font::_AddNewCharacterData(string id,      string x, 		string y,
							    string width,   string height,   string xoffset,
							    string yoffset, string xadvance)
	{
		//Make ID avilable first
 		id.erase(id.begin(), id.begin() + id.find_first_of("=")+1);
 		
 		U32 charID = std::stoi(id);

 		//Create CharacterData for the given character
 		_fontCharData[charID].id = std::stoi(id);

 		x.erase(x.begin(), x.begin() + x.find_first_of("=")+1);
 		_fontCharData[charID].x = std::stoi(x);
 		
 		y.erase(y.begin(), y.begin() + y.find_first_of("=")+1);
 		_fontCharData[charID].y = std::stoi(y);
 		
 		width.erase(width.begin(), width.begin() + width.find_first_of("=")+1);
 		_fontCharData[charID].width = std::stoi(width);
 		
 		height.erase(height.begin(), height.begin() + height.find_first_of("=")+1);
 		_fontCharData[charID].height = std::stoi(height);
 		
 		xoffset.erase(xoffset.begin(), xoffset.begin() + xoffset.find_first_of("=")+1);
 		_fontCharData[charID].xoffset = std::stoi(xoffset);
 		
 		yoffset.erase(yoffset.begin(), yoffset.begin() + yoffset.find_first_of("=")+1);
 		_fontCharData[charID].yoffset = std::stoi(yoffset);
 		
 		xadvance.erase(xadvance.begin(), xadvance.begin() + xadvance.find_first_of("=")+1);
 		_fontCharData[charID].xadvance = std::stoi(xadvance);
	}
}