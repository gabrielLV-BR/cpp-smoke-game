#include "server.hpp"

template <typename T>
Server<T>::Server() {}

template <typename T>
Server<T>::~Server() {}

template <typename T>
Server<T>::Key Server<T>::Store(T value) {
    data.push_back(value);

    return static_cast<Key>(data.size() - 1);
}

template <typename T>
std::shared_ptr<T> Server<T>::Get(Key key) {
    if (key >= data.size())
        return NULL;

    return data[key];
}

template <typename T>
void Server<T>::Delete(Key key) {
    data.erase(key);
}

//

std::shared_ptr<Program> ProgramServer::Get(Material material) {
    Key key = static_cast<Key>(material.GetBits());
    return Server<Program>::Get(key);
}
