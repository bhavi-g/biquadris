#include "level3.h"
#include <fstream>

Level3::Level3(std::string &seqfile): Level(3), isRandom(true) ,currentBlock(0) { readSeqFile(seqfile); }
void Level3::readSeqFile(std::string &seqfile) {
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
std::shared_ptr<Block> Level3::createBlock() {
    std::shared_ptr<Block> block = nullptr;
    if (!isRandom) {
        if (currentBlock >= blockSequence.size()) {
            currentBlock = 0;
        }
        char b = blockSequence[currentBlock];
        
        switch(b){
            case 'J' : block = std::make_shared<JBlock>(true,3); break;
            case 'O' : block = std::make_shared<OBlock>(true,3); break;
            case 'L' : block = std::make_shared<LBlock>(true,3); break;
            case 'I' : block = std::make_shared<IBlock>(true,3); break;
            case 'S' : block = std::make_shared<SBlock>(true,3); break;
            case 'Z' : block = std::make_shared<ZBlock>(true,3); break;
            case 'T' : block = std::make_shared<TBlock>(true,3); break;  
        }
        currentBlock += 1;
        return block;
    } else {
        int n = rand() % 9;
        if (n == 0 || n == 1) {
            block = std::make_shared<SBlock>(true,3);
        } else if (n == 2 || n == 3) {
            block = std::make_shared<ZBlock>(true,3);
        } else if (n == 4) {
            block = std::make_shared<IBlock>(true,3);
        } else if (n == 5) {
            block = std::make_shared<JBlock>(true,3);
        } else if (n == 6) {
            block = std::make_shared<LBlock>(true,3);
        } else if (n == 7) {
            block = std::make_shared<OBlock>(true,3);
        } else {
            block = std::make_shared<TBlock>(true,3);
        }
        return block;
    }
}
