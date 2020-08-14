#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP
#include <fstream> 
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <cstdlib>
#include <exception>
//Сережа сосет
class CSVParser
{
  public:
    CSVParser(std::ifstream &file);
    ~CSVParser() = default;
    void printResault();
    void printInput();
    // void printAll();  //  ,ethod to print containts of all fields
    std::string getCellAddr(std::string &column, int &row);
    void completeTable();
  private:
    std::list<std::string> column_name_list;
    std::list<int> row_name_list;
    std::map<std::string, int> table;
    std::map<std::string, std::string> raw_cells_map;
};
#endif 