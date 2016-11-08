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
		
		void SetBackgroundColor(Col& c) { bgColor = c; }
		
		void ActivateBackgroundColor(void) { Renderer::Instance()->SetBackgroundColor(bgColor); }
		
		S32  GetMapWidth(void)   { return mapWidth; }
		
		S32  GetMapHeight(void)  { return mapHeight; }
		
		void SetMapWidth(S32 w)  { mapWidth = w; }
		
		void SetMapHeight(S32 h) { mapHeight = h; }
		
		void SetMapDimensions(S32 w, S32 h) { mapWidth  = w; mapHeight = h; }
		
		void SetTopBorder(S32 top) { mapTopBorder = top; }

		void SetBottomBorder(S32 bottom) { mapBottomBorder = bottom; }

		void SetRightBorder(S32 right) { mapRightBorder = right; }

		void SetLeftBorder(S32 left) { mapLeftBorder = left; }

		void SetMapBorders(S32 top, S32 bottom, S32 left, S32 right)
		{
			mapTopBorder = top;
			mapBottomBorder = bottom;
			mapLeftBorder = left;
			mapRightBorder = right;
		}
		
		S32 GetTopBorder(void) { return mapTopBorder; }

		S32 GetBottomBorder(void)  { return mapBottomBorder; }
		
		S32 GetLeftBorder(void) { return mapLeftBorder; }

		S32 GetRightBorder(void) { return mapRightBorder; }

		void SetID(U32 id) { _ID = id; }

		U32 GetID(void) { return _ID; }

	protected:
		S32   mapWidth;
		S32   mapHeight;
		S32   mapTopBorder;
		S32   mapBottomBorder;
		S32   mapLeftBorder;
		S32   mapRightBorder;
		Col   bgColor;

	private:
		std::map<U32, GameObject2D*> 	_worldObjects;
		U32								_ID;
		//static U32						_nextID;
	};
		//U32 World2D::_nextID = 1;
}//End namespace

#endif