#include <Engine/RenderText.h>
#include <iostream>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
	RenderText::RenderText(void) : _text(), _font(), _totalWidth(0), _totalHeight(0), _center(0.0f)
	{
		GameObject2D::SetID();
	}

	RenderText::RenderText(Font& font) : _text(), _font(font), _totalWidth(0), _totalHeight(0), _center(0.0f)
	{
		GameObject2D::SetID();
	}

	RenderText::RenderText(string text, Font& font) : _text(text), _font(font), _totalWidth(0), _totalHeight(0), _center(0.0f)
	{
		AddText(_text);
	}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void RenderText::v_Render(void)
	{
		for(CharSprite* sprite : _spriteList)
		{
			sprite->v_RenderSprite();
		}
	}

//==========================================================================================================================
//
//RenderText Functions
//
//==========================================================================================================================
	void RenderText::AddText(string text)
	{
		_spriteList.clear();

		_text = text;

		F32 currentX = GameObject2D::GetPosition().GetX();
		F32 currentY = GameObject2D::GetPosition().GetY();

		Texture& texture = TextureManager::Instance()->GetTexture(_font.GetTextureID());


		for(char& c : text)
		{
			CharSprite* sprite = _font.CreateCharacter(c);

			F32 xOffset = F32(sprite->GetXOffset() / 2);
			F32 yOffset = F32(sprite->GetYOffset() / 2);

			sprite->SetPosition(Vec2(currentX + xOffset, currentY - yOffset));			

			currentX += F32(sprite->GetXAdvance()) * _widthScaleFactor;

			F32 charWidth  	  = F32(sprite->GetCharWidth());
			F32 charHeight 	  = F32(sprite->GetCharHeight());
			F32 charX 	 	  = F32(sprite->GetCharX());
			F32 charY 	 	  = F32(sprite->GetCharY());
			F32 textureWidth  = F32(texture.GetWidth());
			F32 textureHeight = F32(texture.GetHeight());

			F32 rightCoord   = (charX / textureWidth);
			F32 topCoord    = charY / textureHeight;
			F32 leftCoord  = rightCoord + charWidth / textureWidth;
			F32 bottomCoord = topCoord + charHeight / textureHeight;

			//std::cout << "Top=" << topCoord << "\nBottom=" << bottomCoord << "\nrRight=" << rightCoord << "\nLeft=" << leftCoord << "\n";

			sprite->SetTexture(_font.GetTextureID(), topCoord, bottomCoord, rightCoord, leftCoord);

			F32 totalCharWidth = charWidth * _widthScaleFactor;
			F32 totalCharHeight = charHeight * _heightScaleFactor;

			sprite->SetDimensions(totalCharWidth, totalCharHeight);

			_totalWidth += totalCharWidth;
			if(_totalHeight <= totalCharHeight) { _totalHeight = totalCharHeight; } 

			_spriteList.push_back(sprite);
		}

		_center = Vec2(_totalWidth / 2.0f, _totalHeight / 2.0f);
	}//End AddText

	void RenderText::SetTextPosition(Vec2& pos)
	{
		F32 currentX = pos.GetX();
		F32 currentY = pos.GetY();

		for(CharSprite* sprite : _spriteList)
		{
			F32 xOffset = F32(sprite->GetXOffset() / 2);
			F32 yOffset = F32(sprite->GetYOffset() / 2);

			sprite->SetPosition(Vec2(currentX + xOffset, currentY - yOffset));			

			currentX += F32(sprite->GetXAdvance()) * _widthScaleFactor;
		}
	}

	void RenderText::SetTextColor(Col& col)
	{
		for(CharSprite* sprite : _spriteList)
		{
			sprite->SetColor(col);
		}
	}

}//End Namespace