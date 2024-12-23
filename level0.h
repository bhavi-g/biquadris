#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Level0 : public Level {
    private:
        std::vector<char> blockSequence;
        int currentBlock;
    public:
        Level0(std::string &seqfile);
        void readSeqFile(std::string &seqfile);
        std::shared_ptr<Block> createBlock() override;
        //getter
        std::vector<char> getSequence() const { return blockSequence; }
        int getCurrent() const { return currentBlock; }
        //setter
        void setSequence(std::vector<char> seq) { blockSequence = seq; }
        void setCurrent(int i) { currentBlock = i; }
};

#endif
