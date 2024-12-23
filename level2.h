#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"

class Level2: public Level {
    public:
        Level2(): Level(2) {}
        std::shared_ptr<Block> createBlock() override;
        
};
#endif
