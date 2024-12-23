#include "level4.h"
#include <fstream>

Level4::Level4(std::string &seqfile): Level(4), currentBlock(0), isRandom(true) { readSeqFile(seqfile); }
void Level4::readSeqFile(std::string &seqfile) {
    std::ifstream f{seqfile};
    char block;
    if (f) {
        while (f >> block) {
            blockSequence.emplace_back(block);
        }
    } else {
        throw std::invalid_argument("File not found");
    }
}
std::shared_ptr<Block> Level4::createBlock() {
    std::shared_ptr<Block> block = nullptr;
    if (!isRandom) {
        if (currentBlock >= blockSequence.size()) {
            currentBlock = 0;
        }
        char b = blockSequence[currentBlock];
        
        switch(b){
            case 'J' : block = std::make_shared<JBlock>(true,4); break;
            case 'O' : block = std::make_shared<OBlock>(true,4); break;
            case 'L' : block = std::make_shared<LBlock>(true,4); break;
            case 'I' : block = std::make_shared<IBlock>(true,4); break;
            case 'S' : block = std::make_shared<SBlock>(true,4); break;
            case 'Z' : block = std::make_shared<ZBlock>(true,4); break;
            case 'T' : block = std::make_shared<TBlock>(true,4); break;  
        }
        currentBlock += 1;
        return block;
    } else {
        int n = rand() % 9;
        if (n == 0 || n == 1) {
            block = std::make_shared<SBlock>(true,4);
        } else if (n == 2 || n == 3) {
            block = std::make_shared<ZBlock>(true,4);
        } else if (n == 4) {
            block = std::make_shared<IBlock>(true,4);
        } else if (n == 5) {
            block = std::make_shared<JBlock>(true,4);
        } else if (n == 6) {
            block = std::make_shared<LBlock>(true,4);
        } else if (n == 7) {
            block = std::make_shared<OBlock>(true,4);
        } else {
            block = std::make_shared<TBlock>(true,4);
        }
        return block;
    }
}
