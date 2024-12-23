#include "level0.h"
#include <fstream>

Level0::Level0(std::string &seqfile): Level(0), currentBlock(0) { readSeqFile(seqfile); }
void Level0::readSeqFile(std::string &seqfile) {
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
std::shared_ptr<Block> Level0::createBlock() {
    if (currentBlock >= blockSequence.size()) {
        currentBlock = 0;
    }
    char b = blockSequence[currentBlock];
    std::shared_ptr<Block> block = nullptr;
    switch(b){
        case 'J' : block = std::make_shared<JBlock>(0); break;
        case 'O' : block = std::make_shared<OBlock>(0); break;
        case 'L' : block = std::make_shared<LBlock>(0); break;
        case 'I' : block = std::make_shared<IBlock>(0); break;
        case 'S' : block = std::make_shared<SBlock>(0); break;
        case 'Z' : block = std::make_shared<ZBlock>(0); break;
        case 'T' : block = std::make_shared<TBlock>(0); break;  
    }
    currentBlock += 1;
    return block;
}
