#include <string>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <fstream>
#include "TinyXML/tinyxml2.h"

#define BINF_DIR "binary_files/"
#define XMLF_DIR "xml_files/"

using namespace std;
using namespace tinyxml2;

// Структура для удобного хранения размеров входных данных
typedef struct StructLengths {
    StructLengths() = default;
    StructLengths(uint8_t path_len, uint8_t numCat_len, uint8_t weightCat_len, uint8_t index_len)
    : path_len(path_len), numCat_len(numCat_len), weightCat_len(weightCat_len), index_len(index_len) { }
    
    uint8_t path_len;
    uint8_t numCat_len;
    uint8_t weightCat_len;
    uint8_t index_len;
} t_lengths;

bool convert_to_xml(string filename, t_lengths lens);

int main() {
    convert_to_xml("tab_usk1", t_lengths(100, 6, 4, 6));
    convert_to_xml("tab_usk2", t_lengths(100, 6, 4, 6));
    convert_to_xml("tab_usk3", t_lengths(64, 3, 35, 6));

    return 0;
}


bool convert_to_xml(string filename, t_lengths lens) {
    // К названию входного файла добавляется расширение xml формата
    std::string extention = ".xml";
    std::string new_filename = XMLF_DIR + filename + extention;
    short temp;

    ifstream fin;
    fin.open(BINF_DIR + filename, ios::binary);    

    XMLDocument doc;
    XMLDeclaration *declaration = doc.NewDeclaration();
    doc.InsertFirstChild(declaration);

    XMLNode *root = doc.NewElement("INFO");
    doc.InsertEndChild(root);

    for (int path(0); path < lens.path_len; path++) {
        for (int numCat(0); numCat < lens.numCat_len; numCat++) {
            for (int weightCat(0); weightCat < lens.weightCat_len; weightCat++) {
                for (int index(0); index < lens.index_len; index++) {
                    if (fin.read((char*) &temp, sizeof(temp))) {
                        XMLElement *element = doc.NewElement("ACC");

                        element->SetAttribute("path", path);
                        element->SetAttribute("numCat", numCat);
                        element->SetAttribute("weightCat", weightCat);
                        element->SetAttribute("index", index);
                        element->SetAttribute("U", temp);
                        
                        root->InsertEndChild(element);
                    }
                }
            }
        }
    }

    doc.SaveFile(new_filename.c_str());
    fin.close();

    return true;
}