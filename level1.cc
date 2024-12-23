#include "level1.h"

std::shared_ptr<Block> Level1::createBlock() {
    std::shared_ptr<Block> block = nullptr;
    int n = rand() % 12;
    if (n == 0) {
        block = std::make_shared<SBlock>(1);
    } else if (n == 1) {
        block = std::make_shared<ZBlock>(1);
    } else if (n == 2 || n == 3) {
        block = std::make_shared<IBlock>(1);
    } else if (n == 4 || n == 5) {
        block = std::make_shared<JBlock>(1);
    } else if (n == 6 || n == 7) {
        block = std::make_shared<LBlock>(1);
    } else if (n == 8 || n == 9) {
        block = std::make_shared<OBlock>(1);
    } else {
        block = std::make_shared<TBlock>(1);
    }
    return block;
}
