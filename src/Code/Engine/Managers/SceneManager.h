#pragma once
#include <stack>

#include "Interfaces/IScene.h"
#include "Scenes/DefaultScene.h"
#include "Tools/Logger.h"
#include "CleverPointers.h"

using std::stack;

namespace EngineECS {
	class SceneManager {
	private:
		static SceneManager* Instance;

		stack<unique_ptr<IScene>> _scenes;

		SceneManager();

	public:
		~SceneManager();
		static SceneManager& GetInstance();

		void Update(double dt);
		void Render();

		void AddScene(unique_ptr<IScene> scene);
		void RemoveScene();
		void SwapScene(unique_ptr<IScene> scene);
		void ClearScenes();

		int GetSceneCount() const { return static_cast<int>(_scenes.size()); }
		const string& GetCurrentSceneID() const { return _scenes.top()->GetName(); }
	};
}