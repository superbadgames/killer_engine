#include <Engine/TriSprite.h>
#include <iostream>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	TriSprite::TriSprite(void) {  }

	TriSprite::~TriSprite(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void TriSprite::v_RenderSprite(void)
	{
		//v_SetVertexPositions();

		Array ver = Sprite::GetVertices();

		//std::cout << "Sprite ver: " << ver[0] << ":" << ver[1] << ":" << ver[2] << "\n";

		Renderer::Instance()->AddToBatch(Sprite::GetVertices(), Sprite::GetVertexColors());
	}

	void TriSprite::v_SetVertexPositions(void)
	{
		std::cout << "vertices called\n";

		Array vertices = Sprite::GetVertices();

		vertices.clear();

		F32 xOffset = Sprite::GetWidth() / 2;
		F32 yOffset = Sprite::GetHeight() / 2;
		F32 xPos = Sprite::GetPosition().GetX();
		F32 yPos = Sprite::GetPosition().GetY();
		F32 zPos = Sprite::GetPosition().GetZ();
		F32 wPos = Sprite::GetPosition().GetW();

		//=====Top=====		
		vertices.push_back(xPos);
		vertices.push_back(yPos + yOffset);
		vertices.push_back(zPos);
		vertices.push_back(wPos);

		//=====Bottom Left=====
		vertices.push_back(xPos - xOffset);
		vertices.push_back(yPos - yOffset);
		vertices.push_back(zPos);
		vertices.push_back(wPos);

		//=====Bottom Right=====
		vertices.push_back(xPos + xOffset);
		vertices.push_back(yPos - yOffset);
		vertices.push_back(zPos);
		vertices.push_back(wPos);

		Sprite::SetVertices(vertices);
	}

	void TriSprite::v_SetVertexColors(void)
	{
		Array colors = Sprite::GetVertexColors();
		colors.clear();

		F32 R = Sprite::GetColor().GetRed();
		F32 G = Sprite::GetColor().GetGreen();
		F32 B = Sprite::GetColor().GetBlue();
		F32 A = Sprite::GetColor().GetAlpha();

		//=====Top=====
		colors.push_back(R);
		colors.push_back(G);
		colors.push_back(B);
		colors.push_back(A);

		//=====Bottom Left=====
		colors.push_back(R);
		colors.push_back(G);
		colors.push_back(B);
		colors.push_back(A);

		//=====Bottom Right=====
		colors.push_back(R);
		colors.push_back(G);
		colors.push_back(B);
		colors.push_back(A);

		Sprite::SetVertexColors(colors);
	}

	void TriSprite::v_SetPosition(Vec2& position)
	{
		Sprite::SetPosition(position);
		v_SetVertexPositions();
	}

	void TriSprite::v_SetColor(Col& col)
	{
		Sprite::SetColor(col);
		v_SetVertexColors();
	}
	
}//end namespace
