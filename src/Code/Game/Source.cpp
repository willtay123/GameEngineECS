
#include "Externals.h"
#include <iostream>
#include "Managers/CollisionManager.h"
using namespace std;
using namespace EngineECS;

int main(int argc, char* argv[]) {

	CollisionManager::ClearCollisions();
	cout << "game" << endl;
	char ch;
	cin >> ch;
}