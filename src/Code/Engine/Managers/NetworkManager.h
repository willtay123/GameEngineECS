#pragma once

#pragma comment(lib, "ws2_32.lib")

#include <string>

#define BUFFER_SIZE 2

using std::string;


namespace EngineECS {
	enum class NetworkState {
		Off,
		Failed,
		Running
	};

	class NetworkManager {
	private:
		static NetworkManager* Instance;

		NetworkState _networkState;
		unsigned int _socket;
		char _bufferData[BUFFER_SIZE];

		NetworkManager();
	public:

		~NetworkManager();
		static NetworkManager& GetInstance();

		bool EnableNetworking(const string& targetIP);
		void CloseConnection();

		void SendPacket(); // Use string or create a network packet object
	};
}