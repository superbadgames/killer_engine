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
			 	std::cout << "new character:\n";
			 	if(first)
			 	{
			 		first = false;
			 		//use elements 0 - 7
			 		
			 		string id = results[0];
			 		id.erase(id.begin(), id.begin() + id.find_first_of("=")+1);

					string x = results[1];
			 		x.erase(x.begin(), x.begin() + x.find_first_of("=")+1);

			 		string y = results[2];
			 		y.erase(y.begin(), y.begin() + y.find_first_of("=")+1);

			 		string width = results[3];
			 		width.erase(width.begin(), width.begin() + width.find_first_of("=")+1);

			 		string height = results[4];
			 		height.erase(height.begin(), height.begin() + height.find_first_of("=")+1);

			 		string xoffset = results[5];
			 		xoffset.erase(xoffset.begin(), xoffset.begin() + xoffset.find_first_of("=")+1);

			 		string yoffset = results[6];
			 		yoffset.erase(yoffset.begin(), yoffset.begin() + yoffset.find_first_of("=")+1);

			 		string xadvance = results[7];
			 		xadvance.erase(xadvance.begin(), xadvance.begin() + xadvance.find_first_of("=")+1);			 		


			 		std::cout << id << '\n'
				 			  << x << '\n'
				 			  << y << '\n'
				 			  << width << '\n'
				 			  << height << '\n'
				 			  << xoffset << '\n'
				 			  << yoffset << '\n'
				 			  << xadvance << '\n';

				 	results.erase(results.begin(), results.begin()+9);
				 	continue;
			 	}
			 	//after first, use elements 1 - 8
			 	//need to skip char keyword
			 	string id = results[1];
			 		id.erase(id.begin(), id.begin() + id.find_first_of("=")+1);

					string x = results[2];
			 		x.erase(x.begin(), x.begin() + x.find_first_of("=")+1);

			 		string y = results[3];
			 		y.erase(y.begin(), y.begin() + y.find_first_of("=")+1);

			 		string width = results[4];
			 		width.erase(width.begin(), width.begin() + width.find_first_of("=")+1);

			 		string height = results[5];
			 		height.erase(height.begin(), height.begin() + height.find_first_of("=")+1);

			 		string xoffset = results[6];
			 		xoffset.erase(xoffset.begin(), xoffset.begin() + xoffset.find_first_of("=")+1);

			 		string yoffset = results[7];
			 		yoffset.erase(yoffset.begin(), yoffset.begin() + yoffset.find_first_of("=")+1);

			 		string xadvance = results[8];
			 		xadvance.erase(xadvance.begin(), xadvance.begin() + xadvance.find_first_of("=")+1);

			 		std::cout << id << '\n'
				 			  << x << '\n'
				 			  << y << '\n'
				 			  << width << '\n'
				 			  << height << '\n'
				 			  << xoffset << '\n'
				 			  << yoffset << '\n'
				 			  << xadvance << '\n';

			 	results.erase(results.begin(), results.begin() + 10);
			 }

			 file.close();
		}
			
	}
}