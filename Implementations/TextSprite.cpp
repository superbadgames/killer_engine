#include <Engine/TextSprite.h>

namespace KillerEngine
{
	TextSprite::TextSprite(void)
	{
		_textureManager = TextureManager::Instance();
	}

	void TextSprite::v_RenderSprite(const point& pos, F32 w, F32 h, const color& col, const Texture& tex)
	{
		if(_textureManager->GetCurrentTextureId() != tex.GetId())
		{
			_renderer->Draw();
			_textureManager->SetCurrentTextureId(tex.GetId());
		}

		v_SetVertexPositions(pos, w, h);
		v_SetVertexUvs();

		_renderer->AddToBatch(_vertexPositions, _vertexUvs);
	}

	void TextSprite::v_SetVertexPositions(const point& p, const F32 w, const F32 h)
	{
		//=====This is the same Algorithm from an SqrSprite=====
		F32 halfW = w / 2;
		F32 halfH = h / 2;
		F32 X = p.GetX();
		F32 Y = p.GetY();
		F32 Z = p.GetZ();
		F32 W = p.GetW();

 		_vertexPositions.clear();

		//=====Triangle1=====
		//=====top right=====
		_vertexPositions.push_back(X + halfW); //x
		_vertexPositions.push_back(Y + halfH); //y
		_vertexPositions.push_back(Z);		   //z
		_vertexPositions.push_back(W);		   //w
		

		//=====bottom right=====
		_vertexPositions.push_back(X + halfW);	//x
		_vertexPositions.push_back(Y - halfH);	//y
		_vertexPositions.push_back(Z);			//z
		_vertexPositions.push_back(W);			//w


		//=====bottom left=====
		_vertexPositions.push_back(X - halfW);	//x
		_vertexPositions.push_back(Y - halfH);	//y
		_vertexPositions.push_back(Z);			//z
		_vertexPositions.push_back(W);			//w


		//=====Triangle2=====
		//=====top right=====
		_vertexPositions.push_back(X + halfW);	//x
		_vertexPositions.push_back(Y + halfH);	//y
		_vertexPositions.push_back(Z);			//z
		_vertexPositions.push_back(W);			//w


		//=====top left=====
		_vertexPositions.push_back(X - halfW);	//x
		_vertexPositions.push_back(Y + halfH);	//y
		_vertexPositions.push_back(Z);			//z
		_vertexPositions.push_back(W);			//w


		//=====bottom left=====
		_vertexPositions.push_back(X - halfW);	//x
		_vertexPositions.push_back(Y - halfH);	//y
		_vertexPositions.push_back(Z);			//z
		_vertexPositions.push_back(W);			//w
	}

	void TextSprite::v_SetVertexColors( const color& col)
	{
		//=====This is the same Algorithm from an SqrSprite=====
		F32 R = col.GetRed();
		F32 G = col.GetGreen();
 		F32 B = col.GetBlue();
 		F32 A = col.GetAlpha();

 		_vertexColors.clear();

 		//=====Triangle1=====
		//=====top right=====
		_vertexColors.push_back(R);
		_vertexColors.push_back(G);
		_vertexColors.push_back(B);
		_vertexColors.push_back(A);

		//=====bottom right=====
		_vertexColors.push_back(R);
		_vertexColors.push_back(G);
		_vertexColors.push_back(B);
		_vertexColors.push_back(A);

		//=====bottom left=====
		_vertexColors.push_back(R);
		_vertexColors.push_back(G);
		_vertexColors.push_back(B);
		_vertexColors.push_back(A);

		//=====Triangle2=====
		//=====top right=====
		_vertexColors.push_back(R);
		_vertexColors.push_back(G);
		_vertexColors.push_back(B);
		_vertexColors.push_back(A);

		//=====top left=====
		_vertexColors.push_back(R);
		_vertexColors.push_back(G);
		_vertexColors.push_back(B);
		_vertexColors.push_back(A);

		//=====bottom left=====
		_vertexColors.push_back(R);
		_vertexColors.push_back(G);
		_vertexColors.push_back(B);
		_vertexColors.push_back(A);
	}

	void TextSprite::v_SetVertexUvs(const Texture& text)
	{
		_vertexUvs.clear();

		//=====Vertices=====
		//=====Triangle1=====
		//top right

		//bottom right

		//bottom left

		//=====Triangle2=====
		//top right

		//top left

		//bottom left
	}
}