#include "pugixml/src/pugixml.hpp"
#include <zip.h>
#include <chrono>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const char* node_types[] =
{
    "null", "document", "element", "pcdata", "cdata", "comment", "pi", "declaration"
};

struct simple_walker: pugi::xml_tree_walker
{
    virtual bool for_each(pugi::xml_node& node)
    {
        for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation

        std::cout << node_types[node.type()] << ": name='" << node.name() << "', value='" << node.value() << "'"<<endl;

        return true;
    }
};

template <class N>
void getChild(N &node)
{
  N *p = &node;
  N q  = *p;

  for(pugi::xml_node item = q.child(q.first_child().name()); item; item = item.next_sibling(q.first_child().name()))
  {
    std::cout << "WORKED" << std::endl;
  }

}

int main()
{
  pugi::xml_document doc;

  int err = 0;
  zip *z = zip_open("files/7bimestre.zip", 0, &err);
  zip_int64_t num_entries = zip_get_num_entries(z, 0);

  for (zip_uint64_t i = 0; i < (zip_uint64_t)num_entries; i++) {

    const char *name = zip_get_name(z, i, 0);
    //const char *name = "AlteracaoOrcamentaria.xml";

    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    //Alloc memory for its uncompressed contents
    char *contents = new char[st.size];

    //Read the compressed file
    zip_file *f = zip_fopen(z, name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    if(!ofstream(name).write(contents, st.size))
    {
      cerr << "Error writing file" << endl;
      return EXIT_FAILURE;
    }

    //delete allocated memory
    delete[] contents;

    if (!doc.load_file(name)) return -1;

    cout << "Initializing processing of " << name << "..." << endl;
    simple_walker walker;
    doc.traverse(walker);

    //pugi::xml_node sicap = doc.child("Sicap");
    //pugi::xml_node *t = &sicap;

    //getChild<pugi::xml_node>(*t);

  }

  zip_close(z);
  return 0;
}
