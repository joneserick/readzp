#include "pugixml/src/pugixml.hpp"
#include <chrono>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;

int main()
{
  pugi::xml_document doc;
  auto t1 = Clock::now();

  ofstream writer("itens.txt");

  if (!doc.load_file("data.xml")) return -1;

  pugi::xml_node regions = doc.child("site").child("regions");

  for (pugi::xml_node region = regions.first_child(); region; region = region.next_sibling())
  {
    //get attribute values
    // for (pugi::xml_attribute attr = region.first_attribute(); attr; attr = attr.next_attribute())
    // {
    //   //std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
    // }
    std::cout << "Processing region..." << std::endl;
    auto t3 = Clock::now();
    if(! writer)
    {
      cout << "Error opening file" << endl;
      return -1;
    }
    else
    {
      for (pugi::xml_node item = region.child("item"); item; item = item.next_sibling("item"))
      {
        writer << "\"item\" {"    << endl
               << "\"Location\":" << "\"" << item.child_value("location") << "\"" << endl
               << "\"Quantity\":" << item.child_value("quantity") << endl
               << "\"Name\":"     << "\"" << item.child_value("name") << "\"" << endl
               << "\"Payment\":"  << "\"" << item.child_value("payment") << "\"" << endl
               << "\"Parlist\" {" << endl;

        pugi::xml_node parlist = item.child("description").child("parlist");

        for (pugi::xml_node listItem = parlist.child("listitem"); listItem; listItem = listItem.next_sibling("listitem"))
        {
          writer << "\"ListItem\": {" << endl
                 << "\"text\":"       << "\"" << listItem.child_value("text") << "\"" << endl
                 << "}"               << endl;
        }
        writer << "}"        << endl;
      }
    }
    //After procession a single region
    auto t4 = Clock::now();

    std::cout << "Time elapsed for this region : "
            << std::chrono::duration_cast<std::chrono::minutes>(t4 - t3).count()
            << " minute(s) " << std::chrono::duration_cast<std::chrono::seconds>(t4 - t3).count()
            << " second(s) " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() 
            << " milliseconds" << endl;
  }
  //After processing all the regions
  writer.close();

  auto t2 = Clock::now();
  std::cout << "General time elapsed: "
            << std::chrono::duration_cast<std::chrono::minutes>(t2 - t1).count()
            << " minute(s) " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()
            << " second(s) " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
            << " milliseconds" << endl;
  return 0;
}
