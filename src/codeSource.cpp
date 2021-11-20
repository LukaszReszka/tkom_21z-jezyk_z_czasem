/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include "codeSource.h"
#include <iostream>


CodeSource::CodeSource(std::istream &input) {
    std::cout << "\033[33mType code below. To finish program, input \"" + FINISH_TYPING_SYMBOL +
                 "\" in new line.\033[0m" << std::endl;
    std::string code_line;
    do {
        std::getline(input, code_line);
        commands.push_back(code_line);
    } while (code_line != FINISH_TYPING_SYMBOL);

    getCharFunc = &CodeSource::getCharFromTerminal;
}

CodeSource::CodeSource(std::string &file_name) {
    source_file.open(file_name, std::ios::in);
    if (source_file.fail())
        throw std::exception();
    getCharFunc = &CodeSource::getCharFromFile;
}

CodeSource::~CodeSource() {
    if (source_file.is_open())
        source_file.close();
    commands.clear();
}

CharAndPosition CodeSource::getCharFromFile() {
    char c;
    source_file.get(c);

    if (source_file.eof()) {
        CharAndPosition eofChar(line + 1, column + 1);
        source_file.close();
        return eofChar;
    }

    CharAndPosition readChar(c, line + 1, column + 1);
    ++column;
    if (c == '\n') {
        ++line;
        column = 0;
    }

    return readChar;
}

CharAndPosition CodeSource::getCharFromTerminal() {
    if (column == 0 && commands[line] == FINISH_TYPING_SYMBOL) {
        CharAndPosition eofChar(line + 1, column + 1);
        commands.clear();
        return eofChar;
    }

    char c = commands[line][column];
    CharAndPosition readChar(c, line + 1, column + 1);
    ++column;
    if (column >= commands[line].size()) {
        ++line;
        column = 0;
    }

    return readChar;
}