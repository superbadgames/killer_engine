#include <Engine/CharSprite.h>

namespace KillerEngine
{
	CharSprite::CharSprite(void) : _x(0), _y(0), _width(0), _height(0), _xoffset(0), _yoffset(0), _xadvance(0)
	{ _textureManager = TextureManager::Instance(); }

	CharSprite::CharSprite(U32 x, U32 y, U32 width, U32 height, U32 xoffset, U32 yoffset, U32 xadvance) 
						     :_x(0), _y(0), _width(0), _height(0), _xoffset(0), _yoffset(0), _xadvance(0)
	{ _textureManager = TextureManager::Instance(); }

//==========================================================================================================================
//
//Virtual Functions 	 	
//
//==========================================================================================================================
	void CharSprite::v_RenderSprite(void)
	{
		//if(_vertexUvs.size() > 0)
		//{
			//Make sure texture is loaded into OGL
			if(_textureManager->GetCurrentTextureId() != _texture.GetId())
			{
				_renderer->Draw();
				_textureManager->SetCurrentTextureId(_texture.GetId());
			}

			_renderer->AddTextureToBatch(_vertexPositions, _vertexUvs);
		//}
		
		//else if(_vertexColors.size() > 0)
		//	_renderer->AddToBatch(_vertexPositions, _vertexColors);
	}


	void CharSprite::v_SetVertexPositions(void)
	{
		_vertexPositions.clear();

		F32 halfW = _width / 2;
		F32 halfH = _height / 2;
		F32 X = _position.GetX();
		F32 Y = _position.GetY();
		F32 Z = _position.GetZ();
		F32 W = _position.GetW();

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
	
	void CharSprite::v_SetVertexColors(void)
	{
		_vertexColors.clear();

		F32 R = _color.GetRed();
		F32 G = _color.GetGreen();
 		F32 B = _color.GetBlue();
 		F32 A = _color.GetAlpha();

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

	void CharSprite::v_SetTextureCoords(const F32 top, const F32 bottom, const F32 right, const F32 left)
	{
		_vertexUvs.clear();

		//=====Vertices=====
		//=====Triangle1=====
		//top right
		_vertexUvs.push_back(right);
		_vertexUvs.push_back(top);

		//bottom right
		_vertexUvs.push_back(right);
		_vertexUvs.push_back(bottom);

		//bottom left
		_vertexUvs.push_back(left);
		_vertexUvs.push_back(bottom);

		//=====Triangle2=====
		//top right
		_vertexUvs.push_back(right);
		_vertexUvs.push_back(top);

		//top left
		_vertexUvs.push_back(left);
		_vertexUvs.push_back(top);

		//bottom left
		_vertexUvs.push_back(left);
		_vertexUvs.push_back(bottom);
	}

	void CharSprite::SetPosition(Vec2& position)
	{
		_position = position;

		v_SetVertexPositions();
	}

	void CharSprite::SetColor(Col& col)
	{
		_color = col;

		v_SetVertexColors();
	}

	void CharSprite::SetTexture(Texture& texture, const F32 top, const F32 bottom, const F32 right, const F32 left)
	{
		_texture = texture;

		v_SetTextureCoords(top, bottom, left, right);
	}
}