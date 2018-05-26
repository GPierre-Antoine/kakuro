//
// Created by Pierre-Antoine on 26/05/2018.
//

#ifndef KAKURO_MAKE_UNIQUE_H
#define KAKURO_MAKE_UNIQUE_H

#include <memory>
#include <utility>

template<typename T, typename... Args> std::unique_ptr<T> make_unique(Args &&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


#endif //KAKURO_MAKE_UNIQUE_H
