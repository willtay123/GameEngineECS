#pragma once
#include <memory>
#include <map>

#include "Interfaces/IScene.h"
#include "Scenes/DefaultScene.h"
#include "Tools/Logger.h"

using std::map;

namespace EngineECS {
	class SceneManager {
	private:
		static SceneManager* Instance;
		string _currentSceneID;
		IScene* _currentScene; // Be careful with this, do not call delete
		map<string, std::unique_ptr<IScene>> _sceneMap;

		SceneManager();

	public:
		~SceneManager();
		static SceneManager& GetInstance();

		void Update(double dt);
		void Render();

		void AddScene(const string& sceneID, std::unique_ptr<IScene> scene);
		bool RemoveScene(const string& sceneID);
		bool HasScene(const string& sceneID);

		int GetSceneCount() const { return (int)_sceneMap.size(); }

		void SetScene(const string& sceneID);
		void SetScene(const string& sceneID, std::unique_ptr<IScene> scene);
	};
}