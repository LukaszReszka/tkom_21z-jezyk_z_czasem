/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include "../headers/CodeSource.h"


CodeSource::CodeSource() {
    //body required!!!
    getCharFunc = &CodeSource::getCharFromTerminal;
}

CodeSource::CodeSource(std::string &file_name) {
    source_file.open(file_name);
    if (source_file.fail())
        throw std::exception();
    getCharFunc = &CodeSource::getCharFromFile;
}

CodeSource::~CodeSource() {
    if (source_file.is_open())
        source_file.close();
}

CharAndPosition CodeSource::getCharFromFile() {

}

CharAndPosition CodeSource::getCharFromTerminal() {

}