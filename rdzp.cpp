#include <zip.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
  //Open the ZIP archive
  int err = 0;
  zip *z = zip_open("files/test.zip", 0, &err);

  //zip_int64_t num_entries = zip_get_num_entries(z, 0);

  //for (zip_uint64_t i = 0; i < (zip_uint64_t)num_entries; i++) {

    //const char *name = zip_get_name(z, i, 0);

    const char *name = "test.txt";

    struct zip_stat st; 
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    //Alloc memory for its uncompressed contents
    char *contents = new char[st.size];

    //Read the compressed file
    zip_file *f = zip_fopen(z, name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);
    zip_close(z);

    if(!ofstream(name).write(contents, st.size)){
      cerr << "Error writing file" << endl;
      return EXIT_FAILURE;
    }
    //delete allocated memory
    delete[] contents;

    char letter;
    ifstream reader(name);
    if(!reader){

      cout << "Error opening file"  << endl;
      return EXIT_FAILURE;

    } else {

      for(int i = 0; !reader.eof(); i++){
        reader.get(letter);
        if(letter == '<'){
          std::cout << "node beggining at position: " << i << std::endl;
        }

        if(letter == '>'){
          std::cout << "node ending at position: " << i << std::endl;
        }
        //cout << letter;
        //writer << letter << "2";
      }
      reader.close();
    }
  //}
  return 0;
}
