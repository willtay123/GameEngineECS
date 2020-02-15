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
		SceneManager();

		IScene* _scene;
		map<const char*, IScene*> _sceneMap;

	public:
		static SceneManager* GetInstance();
		SceneManager(const SceneManager& rhs) = delete;
		~SceneManager();
		SceneManager& operator=(const SceneManager& rhs) = delete;

		void Update(double dt);
		void Render();

		void AddScene(const char* sceneID, IScene* scene);
		void RemoveScene(const char* sceneID);
		bool HasScene(const char* sceneID);

		void SetScene(const char* sceneID);
		void SetScene(const char* sceneID, IScene* scene);

		static void End();
	};
}