#include <Engine/SqrSprite.h>

namespace KillerEngine
{
	SqrSprite::SqrSprite(void)
	{ _textureManager = TextureManager::Instance(); }

//==========================================================================================================================
//
//Virtual Functions 	 	
//
//==========================================================================================================================
	void SqrSprite::v_RenderSprite(const Vec& pos, F32 w, F32 h, const Col& col)
	{
		v_SetVertexPositions(pos, w, h);
		v_SetVertexColors(col);

		_renderer->AddToBatch(_vertexPositions, _vertexColors);
	}

	void SqrSprite::RenderTexture(const Vec& pos, F32 w, F32 h, const Col& col, Texture& tex)
	{
		//Make sure texture is loaded into memory
		if(_textureManager->GetCurrentTextureId() != tex.GetId())
		{
			_renderer->Draw();
			_textureManager->SetCurrentTextureId(tex.GetId());
		}

		v_SetVertexPositions(pos, w, h);
		v_SetVertexUvs();

		_renderer->AddTextureToBatch(_vertexPositions, _vertexUvs);
	}

	void SqrSprite::v_SetVertexPositions(const Vec& p, const F32 w, const F32 h)
	{
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
	
	void SqrSprite::v_SetVertexColors( const Col& col)
	{
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

	void SqrSprite::v_SetVertexUvs(void)
	{
		_vertexUvs.clear();

		//=====Vertices=====
		//=====Triangle1=====
		//top right
		_vertexUvs.push_back(1.0f);
		_vertexUvs.push_back(1.0f);

		//bottom right
		_vertexUvs.push_back(1.0f);
		_vertexUvs.push_back(0.0f);

		//bottom left
		_vertexUvs.push_back(0.0f);
		_vertexUvs.push_back(0.0f);

		//=====Triangle2=====
		//top right
		_vertexUvs.push_back(1.0f);
		_vertexUvs.push_back(1.0f);

		//top left
		_vertexUvs.push_back(0.0f);
		_vertexUvs.push_back(1.0f);

		//bottom left
		_vertexUvs.push_back(0.0f);
		_vertexUvs.push_back(0.0f);
	}
}