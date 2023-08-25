#include "server.hpp"

template <typename K, typename T>
void Server<K, T>::Store(K key, T* value) {
    data.emplace(key, data);
}

template <typename K, typename T>
std::shared_ptr<T> Server<K, T>::Get(K key) {
    return data[key];
}

template <typename K, typename T>
void Server<K, T>::Delete(K key) {
    data.erase(key);
}

// Program server

std::shared_ptr<Program> ProgramServer::GetForMaterial(Material material) {
    return Server::Get(material.GetBits());
}
