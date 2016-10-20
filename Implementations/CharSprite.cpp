#include <Engine/CharSprite.h>

namespace KillerEngine
{
	CharSprite::CharSprite(void) : _charX(0), _charY(0), _charWidth(0), _charHeight(0), _xoffset(0), _yoffset(0), _xadvance(0)
	{  }

	CharSprite::CharSprite(U32 x, U32 y, U32 width, U32 height, U32 xoffset, U32 yoffset, U32 xadvance) 
						     :_charX(0), _charY(0), _charWidth(0), _charHeight(0), _xoffset(0), _yoffset(0), _xadvance(0)
	{  }

//==========================================================================================================================
//
//Virtual Functions 	 	
//
//==========================================================================================================================
	void CharSprite::v_RenderSprite(void)
	{
		//if(Sprite::vertexUvs.size() > 0)
		//{
			//Make sure texture is loaded into OGL
			if(TextureManager::Instance()->GetCurrentTextureID() != Sprite::textureID)
			{
				Renderer::Instance()->Draw();
				TextureManager::Instance()->SetCurrentTextureID(Sprite::textureID);
			}

			Renderer::Instance()->AddTextureToBatch(Sprite::vertexPositions, Sprite::vertexUvs);
		//}
		
		//else if(Sprite::vertexColors.size() > 0)
		//	v_SetVertexPositions();
			//Renderer::Instance()->AddToBatch(Sprite::vertexPositions, Sprite::vertexColors);
	}


	void CharSprite::v_SetVertexPositions(void)
	{
		Sprite::vertexPositions.clear();

		F32 halfW = F32(Sprite::width / 2);
		F32 halfH = F32(Sprite::height / 2);
		F32 X = Sprite::position.GetX();
		F32 Y = Sprite::position.GetY();
		F32 Z = Sprite::position.GetZ();
		F32 W = Sprite::position.GetW();

		//=====Triangle1=====
		//=====top right=====
		Sprite::vertexPositions.push_back(X + halfW); //x
		Sprite::vertexPositions.push_back(Y + halfH); //y
		Sprite::vertexPositions.push_back(Z);		   //z
		Sprite::vertexPositions.push_back(W);		   //w
		

		//=====bottom right=====
		Sprite::vertexPositions.push_back(X + halfW);	//x
		Sprite::vertexPositions.push_back(Y - halfH);	//y
		Sprite::vertexPositions.push_back(Z);			//z
		Sprite::vertexPositions.push_back(W);			//w


		//=====bottom left=====
		Sprite::vertexPositions.push_back(X - halfW);	//x
		Sprite::vertexPositions.push_back(Y - halfH);	//y
		Sprite::vertexPositions.push_back(Z);			//z
		Sprite::vertexPositions.push_back(W);			//w


		//=====Triangle2=====
		//=====top right=====
		Sprite::vertexPositions.push_back(X + halfW);	//x
		Sprite::vertexPositions.push_back(Y + halfH);	//y
		Sprite::vertexPositions.push_back(Z);			//z
		Sprite::vertexPositions.push_back(W);			//w


		//=====top left=====
		Sprite::vertexPositions.push_back(X - halfW);	//x
		Sprite::vertexPositions.push_back(Y + halfH);	//y
		Sprite::vertexPositions.push_back(Z);			//z
		Sprite::vertexPositions.push_back(W);			//w


		//=====bottom left=====
		Sprite::vertexPositions.push_back(X - halfW);	//x
		Sprite::vertexPositions.push_back(Y - halfH);	//y
		Sprite::vertexPositions.push_back(Z);			//z
		Sprite::vertexPositions.push_back(W);			//w

	}
	
	void CharSprite::v_SetVertexColors(void)
	{
		Sprite::vertexColors.clear();

		F32 R = Sprite::color.GetRed();
		F32 G = Sprite::color.GetGreen();
 		F32 B = Sprite::color.GetBlue();
 		F32 A = Sprite::color.GetAlpha();

 		//=====Triangle1=====
		//=====top right=====
		Sprite::vertexColors.push_back(R);
		Sprite::vertexColors.push_back(G);
		Sprite::vertexColors.push_back(B);
		Sprite::vertexColors.push_back(A);

		//=====bottom right=====
		Sprite::vertexColors.push_back(R);
		Sprite::vertexColors.push_back(G);
		Sprite::vertexColors.push_back(B);
		Sprite::vertexColors.push_back(A);

		//=====bottom left=====
		Sprite::vertexColors.push_back(R);
		Sprite::vertexColors.push_back(G);
		Sprite::vertexColors.push_back(B);
		Sprite::vertexColors.push_back(A);

		//=====Triangle2=====
		//=====top right=====
		Sprite::vertexColors.push_back(R);
		Sprite::vertexColors.push_back(G);
		Sprite::vertexColors.push_back(B);
		Sprite::vertexColors.push_back(A);

		//=====top left=====
		Sprite::vertexColors.push_back(R);
		Sprite::vertexColors.push_back(G);
		Sprite::vertexColors.push_back(B);
		Sprite::vertexColors.push_back(A);

		//=====bottom left=====
		Sprite::vertexColors.push_back(R);
		Sprite::vertexColors.push_back(G);
		Sprite::vertexColors.push_back(B);
		Sprite::vertexColors.push_back(A);
	}

	void CharSprite::v_SetTextureCoords(const F32 top, const F32 bottom, const F32 right, const F32 left)
	{
		Sprite::vertexUvs.clear();

		//=====Vertices=====
		//=====Triangle1=====
		//top right
		Sprite::vertexUvs.push_back(right);
		Sprite::vertexUvs.push_back(top);

		//bottom right
		Sprite::vertexUvs.push_back(right);
		Sprite::vertexUvs.push_back(bottom);

		//bottom left
		Sprite::vertexUvs.push_back(left);
		Sprite::vertexUvs.push_back(bottom);

		//=====Triangle2=====
		//top right
		Sprite::vertexUvs.push_back(right);
		Sprite::vertexUvs.push_back(top);

		//top left
		Sprite::vertexUvs.push_back(left);
		Sprite::vertexUvs.push_back(top);

		//bottom left
		Sprite::vertexUvs.push_back(left);
		Sprite::vertexUvs.push_back(bottom);
	}

	void CharSprite::v_SetPosition(Vec2& position)
	{
		Sprite::position = position;

		v_SetVertexPositions();
	}

	void CharSprite::v_SetColor(Col& col)
	{
		Sprite::color = col;

		v_SetVertexColors();
	}
}