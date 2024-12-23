#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <utility>
#include <memory>
#include <string>
#include <cstdlib>
#include "GameController.h"

int main(int argc, char **argv) {
    int level = 0;
    std::string seqfile1 = "sequence1.txt";
    std::string seqfile2 = "sequence2.txt";
    bool textOnly = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-text") {
            textOnly = true;
        } else if (arg == "-seed") {
            int seed = std::stoi(argv[i + 1]);
            srand(seed);
            i++;
        } else if (arg == "-scriptfile1") {
            seqfile1 = argv[i + 1];
            i++;
        } else if (arg == "-scriptfile2") {
            seqfile2 = argv[i + 1];
            i++;
        } else if (arg == "-startlevel") {
            level = std::stoi(argv[++i]);
            if (level > 4 || level < 0) {
                std::cout << "Invalid level" << std::endl;
                return 1;
            }
        } else {
            std::cout << "Invalid Arguments" << std::endl;
            return 1;
        }
    }
    GameController controller(level, textOnly, seqfile1, seqfile2); //fill in when controller is done;
    controller.startGame();
}
