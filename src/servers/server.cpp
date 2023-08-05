#include "server.hpp"

template <typename T, typename K>
Server<T, K>::Server() {}

template <typename T, typename K>
Server<T, K>::~Server() {}

template <typename T, typename K>
void Server<T, K>::Store(K key, T value) {}

template <typename T, typename K>
std::shared_ptr<T> Server<T, K>::Get(K key) {}

template <typename T, typename K>
void Server<T, K>::Delete(K key) {}

template <typename T, typename K>
void Server<T, K>::HasItem(K key) {}