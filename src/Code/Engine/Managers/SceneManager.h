#pragma once
#include <map>

#include "Interfaces/IScene.h"
#include "Scenes/DefaultScene.h"
#include "Tools/Logger.h"

using std::map;

namespace EngineECS {
	class SceneManager {
	private:
		static SceneManager* Instance;
		IScene* _scene;
		map<string, IScene*> _sceneMap;

		SceneManager();
		~SceneManager();

	public:
		static SceneManager* GetInstance();

		void Update(double dt);
		void Render();

		void AddScene(string& sceneID, IScene* scene);
		void RemoveScene(string& sceneID);
		bool HasScene(string& sceneID);

		void SetScene(string& sceneID);
		void SetScene(string& sceneID, IScene* scene);

		static void End();
	};
}