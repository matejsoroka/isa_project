//
// Created by matthew on 30.10.19.
//

#include "Post.h"

#include <utility>

Post::Post(std::string message) {
    this->message = std::move(message);
}