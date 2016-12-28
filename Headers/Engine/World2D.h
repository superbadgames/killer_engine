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
#include <Engine/Renderer.h>

//=====STL includes=====
#include <map>

//=====OGL includes
#include <GL/gl.h>
#include <GL/glu.h>

namespace KillerEngine 
{

	class World2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		World2D(void);

		~World2D(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================

		virtual void InitWorld(U32 id, S32 w, S32 h, Col& c)=0;
		
		virtual void Update(void)=0;
		
		virtual void Render(void)=0;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void AddObjectToWorld(GameObject2D* obj);
		
		void RemoveObjectFromWorld(U32 id);

		void RenderObjects(void) {
			for(auto i = _worldObjects.begin(); i!=_worldObjects.end(); ++i) {
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

	private:
		S32 _mapWidth;
		S32 _mapHeight;
		S32 _mapTopBorder;
		S32 _mapBottomBorder;
		S32 _mapRightBorder;
		S32 _mapLeftBorder;
		Col _bgColor;
		U32 _ID;
		std::map<U32, GameObject2D*> 	_worldObjects;
	};
}//End namespace

#endif