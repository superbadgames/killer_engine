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

	RenderText::RenderText(Font* font) : _text(), _font(font)
	{  }

	RenderText::RenderText(string text, Font* font) : _text(text), _font(font)
	{
		AddText(_text);
	}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void RenderText::v_Render(void)
	{  }

//==========================================================================================================================
//
//RenderText Functions
//
//==========================================================================================================================
	void RenderText::AddText(string text)
	{
		_spriteList.clear();

		F32 currentX = __position.GetX();
		F32 currentY = __position.GetY();

		Texture& texture = _font->GetTexture();


		for(char& c : text)
		{
			CharSprite* sprite = _font->CreateCharacter(c);

			F32 xOffset = sprite->GetXOffset() / 2;
			F32 yOffset = sprite->GetYOffset() / 2;

			sprite->SetPosition(Vec2(currentX+xOffset, currentY-yOffset));

			currentX += sprite->GetXAdvance();

			F32 spriteWidth  = sprite->GetWidth();
			F32 spriteHeight = sprite->GetHeight();
			F32 spriteX 	 = sprite->GetX();
			F32 spriteY 	 = sprite->GetY();
			F32 textureWidth = F32(texture.GetWidth());
			F32 textureHeight = F32(texture.GetHeight());

			F32 leftCoord = spriteX / textureWidth;
			F32 topCoord  = spriteY / textureHeight;
			F32 rightCoord = leftCoord + (spriteWidth / textureWidth);
			F32 bottomCoord = topCoord + (spriteHeight / textureHeight);

			sprite->SetTexture(texture, topCoord, bottomCoord, rightCoord, leftCoord);

			_spriteList.push_back(sprite);
		}
	}

}