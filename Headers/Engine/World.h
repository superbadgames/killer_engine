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
#include <Engine/GameObject.hpp>
#include <Engine/Renderer.h>

//=====STL includes=====
#include <map>

//=====OGL includes
#include <GL/gl.h>
#include <GL/glu.h>

namespace KillerEngine 
{

	class World
	{
	private:
		ErrorManager* 			   _errorManager;
		Renderer* 				   _renderer;
		std::map<string, GameObject*> _worldObjects;
		
		S32   _mapWidth;
		S32   _mapHeight;
		Col _bgColor;

	public:
		World(void): _errorManager(ErrorManager::Instance()),
					 _renderer(Renderer::Instance()),
					 _mapWidth(0),
					 _mapHeight(0),
					 _bgColor() {  }
		
		~World(void) {  }

		virtual void InitWorld(S32 w, S32 h, Col& c)=0;
		
		virtual void Update(void)=0;
		
		virtual void Render(void)=0;

		//======Accessors=====
		void AddObjectToWorld(string objId, GameObject* obj);
		
		void RenderObjects(void) {
			for(auto i = _worldObjects.begin(); i!=_worldObjects.end(); ++i) {
				i->second->v_Render();
			}
		}
		
		void SetBackgroundColor(Col& c) { _bgColor = c; }
		
		void ActivateBackgroundColor(void) { _renderer->SetBackgroundColor(_bgColor); }
		
		S32  GetMapWidth(void)   { return _mapWidth; }
		
		S32  GetMapHeight(void)  { return _mapHeight; }
		
		void SetMapWidth(S32 w)  { _mapWidth = w; }
		
		void SetMapHeight(S32 h) { _mapHeight = h; }
		
		void SetMapDimensions(S32 w, S32 h) {
			_mapWidth  = w;
			_mapHeight = h;
	}
};
}//End namespace

#endif