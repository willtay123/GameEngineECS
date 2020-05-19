#include "NetworkManager.h"

#include <winsock2.h>
#include <ws2tcpip.h>

#include "Tools/Logger.h"

using namespace EngineECS;
using namespace std;


NetworkManager* NetworkManager::Instance = nullptr;

NetworkManager::NetworkManager() :
	_networkState(NetworkState::Off),
	_socket(0),
	_bufferData("") {

}

NetworkManager::~NetworkManager() {

}

NetworkManager& NetworkManager::GetInstance() {
	if (!Instance) {
		Instance = new NetworkManager();
	}
	return *Instance;
}

bool NetworkManager::EnableNetworking(const string& targetIP) {
	// Create version identifier
	WORD wVersionRequested = MAKEWORD(2, 0);

	// Startup windows sockets
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData)) {
		Logger::LogError("Networking", "Socket initialisation failed");
		_networkState = NetworkState::Failed;
		return false;
	}

	// Create socket data space
	sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(9171);
	inet_pton(peer.sin_family, targetIP.c_str(), &peer.sin_addr);

	// Create transfer socket
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == INVALID_SOCKET) {
		Logger::LogError("Create socket failed with " + WSAGetLastError());
		_networkState = NetworkState::Failed;
		return false;
	}
	else if (connect(_socket, (sockaddr*)&peer, sizeof(peer)) == SOCKET_ERROR) {
		Logger::LogError("Connect to peer failed with " + WSAGetLastError());
		_networkState = NetworkState::Failed;
		return false;
	}
	else {
		// Mark as enabled
		_networkState = NetworkState::Running;
		return true;
	}
}

void NetworkManager::CloseConnection() {
	if (_socket != 0) {
		closesocket(_socket);
	}
}

void NetworkManager::SendPacket() {
	if (_networkState == NetworkState::Running) {
		if (send(_socket, "t", 1, 0) == SOCKET_ERROR) {
			Logger::LogError("Send failed with " + WSAGetLastError());
		}
		else if (recv(_socket, _bufferData, BUFFER_SIZE, 0) == SOCKET_ERROR) {
			Logger::LogError("Receive failed with " + WSAGetLastError());
		}
		else {
			string message("ACK = ");
			message += _bufferData;
			Logger::LogInfo("Networking", message);
		}
	}
	else {
		Logger::LogWarning("Networking", "Attempted to send packet with networking turned off");
	}
}