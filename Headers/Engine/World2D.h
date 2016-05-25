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
#include <Engine/GameObject2D.hpp>
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
		World2D(void): _errorManager(ErrorManager::Instance()),
					 _renderer(Renderer::Instance()),
					 mapWidth(0),
					 mapHeight(0),
					 bgColor() {  }
		
		~World2D(void) {  }

		virtual void InitWorld(S32 w, S32 h, Col& c)=0;
		
		virtual void Update(void)=0;
		
		virtual void Render(void)=0;

		//======Accessors=====
		void AddObjectToWorld(string objId, GameObject2D* obj);
		
		void RenderObjects(void) {
			for(auto i = _worldObjects.begin(); i!=_worldObjects.end(); ++i) {
				i->second->v_Render();
			}
		}
		
		void SetBackgroundColor(Col& c) { bgColor = c; }
		
		void ActivateBackgroundColor(void) { _renderer->SetBackgroundColor(bgColor); }
		
		S32  GetMapWidth(void)   { return mapWidth; }
		
		S32  GetMapHeight(void)  { return mapHeight; }
		
		void SetMapWidth(S32 w)  { mapWidth = w; }
		
		void SetMapHeight(S32 h) { mapHeight = h; }
		
		void SetMapDimensions(S32 w, S32 h) { mapWidth  = w; mapHeight = h; }
		
		void SetTopBorder(S32 top) { mapTopBorder = top; }

		void SetBottomBorder(S32 bottom) { mapBottomBorder = bottom; }

		void SetRigthBorder(S32 right) { mapRightBorder = right; }

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

	protected:
		S32   mapWidth;
		S32   mapHeight;
		S32   mapTopBorder;
		S32   mapBottomBorder;
		S32   mapLeftBorder;
		S32   mapRightBorder;
		Col   bgColor;

	private:
		ErrorManager* 			   _errorManager;
		Renderer* 				   _renderer;
		std::map<string, GameObject2D*> _worldObjects;
	};
}//End namespace

#endif