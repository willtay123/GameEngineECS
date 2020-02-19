#pragma once
#include <string>

using namespace std;

namespace EngineECS {
	class IScene {
	private:

	protected:
		string _name;

	public:
		virtual ~IScene() = 0;

		const string& GetName() const { return _name; };

		virtual void Initialise() = 0;

		virtual void Render() = 0;
		virtual void Update(double dt) = 0;

		virtual void Close() = 0;
	};
}