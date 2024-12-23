#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>

#include "block.h"
#include "tblock.h"
#include "iblock.h"
#include "jblock.h"
#include "sblock.h"
#include "lblock.h"
#include "oblock.h"
#include "zblock.h"

class Level {
    protected:
        int level_num;
    public:
        Level(int lv): level_num(lv) {}
        virtual ~Level() = default;
        virtual std::shared_ptr<Block> createBlock() = 0; //generates blocks
        virtual void makeRandom() {}
        virtual void removeRandom(std::string file) {}
        //getter
        int getLevel() const { return level_num; }
};

#endif
