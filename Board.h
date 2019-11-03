//
// Created by Matej Soroka on 30.10.19.
//

#ifndef ISA_PROJECT_BOARD_H
#define ISA_PROJECT_BOARD_H

#include <string>
#include <vector>
#include "Post.h"

class Board {
public:

    /**
     * Initialize board with board name
     * @param board_name board name
     */
    explicit Board(std::string board_name);

    std::string board_name;    // name of board
    std::vector<Post *> posts; // vector of posts in board
};

#endif //ISA_PROJECT_BOARD_H
