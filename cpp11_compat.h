//
// Created by Pierre-Antoine on 20/05/2018.
//

#ifndef KAKURO_CPP11_COMPAT_H
#define KAKURO_CPP11_COMPAT_H

#include <utility>
#include <memory>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //KAKURO_CPP11_COMPAT_H
