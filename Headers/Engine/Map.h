/*========================================================================
A world is what the different states of game will be. Each world re-
presents  

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef WORLD_H
#define WORLD_H

//===Killer1 includes===
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/GameObject2D.h>
#include <Engine/GameObject3D.h>
#include <Engine/Renderer.h>
#include <Engine/TextureManager.h>
#include <Engine/EnvironmentObject.h>

//=====STL includes=====
#include <map>
#include <fstream>
#include <algorithm>

#include <TinyXML/tinyxml2.h>

//=====OGL includes
#include <GL/gl.h>
#include <GL/glu.h>

namespace KillerEngine 
{
	class Map
	{
	protected:
		enum ObjectType
		{
			BACKGROUND,
			ENVIRONMENT,
			PLAYER,
			ENEMY,
			END
		};

	private:
		
		struct TileData
		{
			int tileID;
			int width;
			int height;
			string texturePath;
			ObjectType type;
			int textureID;
			int posX;
		};

		struct MapData
		{
			int mapWidth;
			int mapHeight;
			int tileWidth;
			int tileHeight;
			Col color;
		};
			

	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Map(void);

		~Map(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================

		virtual void v_InitMap(U32 id, S32 w, S32 h, Col& c)=0;

		virtual void v_InitMap(U32 id, string tmxFilePath)
		{
			SetID(id);
			Importer2D(tmxFilePath);
		}
		
		virtual void v_Update(void)=0;
		
		virtual void v_Render(void) { RenderObjects(); }

/*		virtual GameObject2D* v_CreateObject(ObjectType type, Vec2& pos, F32 w, F32 h) 
		{
			ErrorManager::Instance()->SetError(EC_Game, "CreateObject not defined in your Map");
			return NULL; 
		}
*/
		virtual GameObject2D* v_CreateObject(ObjectType type, Vec2& pos, U32 textureID, F32 w, F32 h)=0;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void AddObjectToMap(GameObject2D* obj);

		void AddObjectToMap(GameObject3D* obj);
		
		void Remove2DObjectFromMap(U32 id);

		void Remove3DObjectFromMap(U32 id);

		void RenderObjects(void) {
			for(auto i = _2DWorldObjects.begin(); i!=_2DWorldObjects.end(); ++i) 
			{
				i->second->v_Render();
			}

			for(auto i = _3DWorldObjects.begin(); i!=_3DWorldObjects.end(); ++i)
			{
				i->second->v_Render();
			}
		}
		
		void SetBackgroundColor(Col& c) { _bgColor = c; }
		
		void ActivateBackgroundColor(void) { Renderer::Instance()->SetBackgroundColor(_bgColor); }
		
		S32  GetMapWidth(void) const { return _mapWidth; }
		
		S32  GetMapHeight(void) const { return _mapHeight; }
		
		void SetMapWidth(S32 w)  { _mapWidth = w; }
		
		void SetMapHeight(S32 h) { _mapHeight = h; }
		
		void SetMapDimensions(S32 w, S32 h) { _mapWidth  = w; _mapHeight = h; }
		
		void SetTopBorder(S32 top) { _mapTopBorder = top; }

		void SetBottomBorder(S32 bottom) { _mapBottomBorder = bottom; }

		void SetRightBorder(S32 right) { _mapRightBorder = right; }

		void SetLeftBorder(S32 left) { _mapLeftBorder = left; }

		void SetMapBorders(S32 top, S32 bottom, S32 right, S32 left)
		{
			_mapTopBorder = top;
			_mapBottomBorder = bottom;
			_mapLeftBorder = left;
			_mapRightBorder = right;
		}
		
		S32 GetTopBorder(void) const { return _mapTopBorder; }

		S32 GetBottomBorder(void) const { return _mapBottomBorder; }
		
		S32 GetLeftBorder(void) const { return _mapLeftBorder; }

		S32 GetRightBorder(void) const { return _mapRightBorder; }

		void SetID(U32 id) { _ID = id; }

		U32 GetID(void) const { return _ID; }

	protected:
		void Importer2D(string tmxFilePath);

		virtual ObjectType v_StringToTileData(string s);

	private:
		S32 _mapWidth;
		S32 _mapHeight;
		S32 _mapTopBorder;
		S32 _mapBottomBorder;
		S32 _mapRightBorder;
		S32 _mapLeftBorder;
		Col _bgColor;
		U32 _ID;
		std::map<U32, GameObject2D*> _2DWorldObjects;
		std::map<U32, GameObject3D*> _3DWorldObjects;
		std::map<U32, TileData> _2DTileData;

		void _AddTile(TileData data);
	};
}//End namespace

#endif