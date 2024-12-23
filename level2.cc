#include "level2.h"

std::shared_ptr<Block> Level2::createBlock() {
    std::shared_ptr<Block> block = nullptr;
    int n = rand() % 7;
    if (n == 0) {
        block = std::make_shared<SBlock>(2);
    } else if (n == 1) {
        block = std::make_shared<ZBlock>(2);
    } else if (n == 2) {
        block = std::make_shared<IBlock>(2);
    } else if (n == 3) {
        block = std::make_shared<JBlock>(2);
    } else if (n == 4) {
        block = std::make_shared<LBlock>(2);
    } else if (n == 5) {
        block = std::make_shared<OBlock>(2);
    } else {
        block = std::make_shared<TBlock>(2);
    }
    return block;
}
