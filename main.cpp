#include <iostream>
#include <exception>

#include "csvparser.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if(argc != 2)
    {
      throw std::invalid_argument("Arguments quantity is invalid");
    }
    else 
    {
      std::string filename(argv[1]);
      std::string filetype = filename.substr(filename.find("."));
      if(filetype == ".csv")
      {
        std::ifstream f;
        f.open(filename, std::fstream::in);
        if(f.is_open())
        {
          CSVParser parser(f);
          parser.printInput();
          parser.completeTable();
          parser.printResault();
          f.close();
        }
        else
        {
          throw std::invalid_argument("File does not exist");
        }
      }
      else
      {
        throw std::invalid_argument("Invalid filetype");
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}