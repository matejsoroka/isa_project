//
// Created by matthew on 30.10.19.
//

#ifndef ISA_PROJECT_BOARD_H
#define ISA_PROJECT_BOARD_H

#include <string>
#include <vector>
#include "Post.h"

class Board {
public:
    Board(std::string board_name);

    std::string board_name;
    std::vector<Post *> posts;
};

#endif //ISA_PROJECT_BOARD_H
