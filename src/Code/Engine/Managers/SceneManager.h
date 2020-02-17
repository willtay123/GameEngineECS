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

	public:
		~SceneManager();
		static SceneManager& GetInstance();

		void Update(double dt);
		void Render();

		void AddScene(const string& sceneID, IScene* scene);
		void RemoveScene(const string& sceneID);
		bool HasScene(const string& sceneID);

		void SetScene(const string& sceneID);
		void SetScene(const string& sceneID, IScene* scene);

		static void End();
	};
}