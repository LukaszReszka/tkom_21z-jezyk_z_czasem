/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include "../headers/CodeSource.h"


CodeSource::CodeSource() {
    //body required!!!
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
}

CharAndPosition CodeSource::getCharFromFile() {
    char c;
    source_file.get(c);
    if (source_file.eof()) {
        CharAndPosition eofChar(line, column);
        source_file.close();
        return eofChar;
    }
    if (c == '\n') {
        ++column;
        line = 0;
    }
    CharAndPosition readChar(c, line, column);
    ++line;
    return readChar;
}

CharAndPosition CodeSource::getCharFromTerminal() {

}