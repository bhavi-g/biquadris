#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"

class Level1: public Level {
    public:
        Level1(): Level(1) {}
        std::shared_ptr<Block> createBlock() override;
};
#endif
