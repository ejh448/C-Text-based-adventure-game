#ifndef TEXTCOLORS_H
#define TEXTCOLORS_H

#include <string>

struct TextColors {
    std::string red           = "\033[31m";
    std::string cyan          = "\033[36m";
    std::string default_color = "\033[0m";
};

#endif