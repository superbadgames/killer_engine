#include <Engine/RenderText.h>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
	RenderText::RenderText(void) : _text(), _font()
	{  }

	RenderText::RenderText(Font& font) : _text(), _font(font)
	{  }

	RenderText::RenderText(string text, Font& font) : _text(text), _font(font)
	{
		AddText(_text);
	}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void RenderText::v_Update(void)
	{
		for(auto &sprite : _spriteList)
		{
			sprite->v_SetVertexPositions();
		}
	}

	void RenderText::v_Render(void)
	{
		for(auto &sprite : _spriteList)
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

		F32 currentX = __position.GetX();
		F32 currentY = __position.GetY();

		Texture& texture = _font.GetTexture();


		for(char& c : text)
		{
			CharSprite* sprite = _font.CreateCharacter(c);

			F32 xOffset = F32(sprite->GetXOffset() / 2);
			F32 yOffset = F32(sprite->GetYOffset() / 2);

			sprite->SetPosition(Vec2(currentX + xOffset, currentY - yOffset));

			

			currentX += F32(sprite->GetXAdvance());

			F32 charWidth  	  = F32(sprite->GetCharWidth());
			F32 charHeight 	  = F32(sprite->GetCharHeight());
			F32 charX 	 	  = F32(sprite->GetCharX());
			F32 charY 	 	  = F32(sprite->GetCharY());
			F32 textureWidth  = F32(texture.GetWidth());
			F32 textureHeight = F32(texture.GetHeight());

			sprite->SetDimensions(charWidth / _charWidth, charHeight / _charHeight);

			F32 rightCoord   = charX / textureWidth;
			F32 topCoord    = charY / textureHeight;
			F32 leftCoord  = rightCoord + charWidth / textureWidth;
			F32 bottomCoord = topCoord + charHeight / textureHeight;

			sprite->SetTexture(texture, topCoord, bottomCoord, rightCoord, leftCoord);

			_spriteList.push_back(sprite);
		}
	}

}