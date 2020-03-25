#include "csvparser.hpp"

CSVParser::CSVParser(std::ifstream &file)
{
  std::string line_str;
  std::getline(file, line_str);
  std::istringstream line_istr(line_str);
  line_istr.get();  //  extracting first comma
  while(std::getline(line_istr, line_str, ','))  //  parsing first line
  {
    column_name_list.push_back(line_str);  //   completing list of horizontal headers
  }
  while(std::getline(file, line_str) && (line_str != "")) // parsing rest of the file
  {
    int row = 0;
    line_istr = std::istringstream(line_str);
    line_istr >> row;
    std::list<std::string>::iterator it = column_name_list.begin();
    row_name_list.push_back(row);  //  completing list of vertical headers
    line_istr.get();  //  extracting extra comma from the line
    while(std::getline(line_istr, line_str, ','))  //  parsing rest of the line
    {
      std::string cell_addr = getCellAddr(*it, row);
      if(line_str[0] != '=')  //  checking if the cell is formula
      {
        table.insert(std::pair<std::string, int>(cell_addr, atoi(line_str.c_str())));  //  inserts cell in the table
      }
      else
      {
        table.insert(std::pair<std::string, int>(cell_addr, -112358));  //  inserts "blank" cell in the table
        raw_cells_map.insert(std::pair<std::string, std::string>(cell_addr, line_str));  //  insrts cell to the list of not solved cells
      }
      it++;
    }
  }
}
void CSVParser::printInput()
{
  std::cout << "______Input______" << std::endl;
  std::cout << std::endl;
  for(auto c : column_name_list)
  {
    std::cout <<"," + c;
  }
  std::cout << std::endl;
  for(auto v : row_name_list)
  {
    std::cout << v;
    for(auto h : column_name_list)
    {
      if(raw_cells_map.count(getCellAddr(h, v)) == 0)
      {
        std::cout << "," << table.at(getCellAddr(h, v));
      }
      else
      {
        std::cout << "," << raw_cells_map.at(getCellAddr(h, v));
      }
    }
    std::cout << std::endl;
  }
}
void CSVParser::printResault()
{
  std::cout << "______Output______" << std::endl;
  std::cout << std::endl;
  for(auto c : column_name_list)
  {
    std::cout <<"," + c;
  }
  std::cout << std::endl;
  for(auto v : row_name_list)
  {
    std::cout << v;
    for(auto h : column_name_list)
    {
      std::cout << "," << table.at(getCellAddr(h, v));
    }
    std::cout << std::endl;
  }
}

std::string CSVParser::getCellAddr(std::string &column, int &row)
{
  return column + std::to_string(row);
}

void CSVParser::completeTable()
{
  while(raw_cells_map.size() != 0)
  {
    for(auto raw_cell : raw_cells_map)
    {
      std::string cell1 = "", cell2 = "", raw_cell_addr = raw_cell.first, operators = "+-*/";
      char c, op;
      int arg1, arg2;
      std::istringstream istr(raw_cell.second);
      istr.get();  //  extracting '='
      istr.get(c);
      while(operators.find(c) == std::string::npos)  //  while c is not an operator
      {
        cell1.push_back(c);
        istr.get(c);
      }
      op = c;
      istr >> cell2;
      if(raw_cells_map.count(cell1) != 0 || raw_cells_map.count(cell2) != 0)  //  solve another cell if cell in the formula is not solved yet
      {
        continue;
      }
      else if(table.count(cell1) == 0)
      {
        throw std::invalid_argument("Unsolvable cell " + cell1);
      }
      else if(table.count(cell2) == 0)
      {
        throw std::invalid_argument("Unsolvable cell " + cell2);
      }
      else
      {
        switch(op)
        {
          case '+':
            arg1 = table.find(cell1)->second;
            arg2 = table.find(cell2)->second;
            table.find(raw_cell_addr)->second = arg1 + arg2;
            break;
          case '-':
            arg1 = table.find(cell1)->second;
            arg2 = table.find(cell2)->second;
            table.find(raw_cell_addr)->second = arg1 - arg2;
            break;
          case '*':
            arg1 = table.find(cell1)->second;
            arg2 = table.find(cell2)->second;
            table.find(raw_cell_addr)->second = arg1 * arg2;
            break;
          case '/':
            arg1 = table.find(cell1)->second;
            arg2 = table.find(cell2)->second;
            table.find(raw_cell_addr)->second = arg1 / arg2;
            break;
          default:
            break;  
        }
        raw_cells_map.erase(raw_cell_addr);
        break;  //  start for again to prevent segmentation fault
      }
    }
  }
}

// void CSVParser::printAll()
// {
//   std::cout << "Map values: \n";
//   for(auto t : table)
//   {
//     std::cout << t.first << " is " << t.second << std::endl;
//   }
//   std::cout << std::endl;
//   std::cout << "Vertical headers: \n";
//   for(auto v : row_name_list)
//   {
//     std::cout << v << "    ";
//   }
//   std::cout << std::endl;
//   std::cout << "Horizontal headers: \n";
//   for(auto h : column_name_list)
//   {
//     std::cout << h << "    ";
//   }
//   std::cout << std::endl;
//   std::cout << "Unsolved cells \n";
//   for(auto c : raw_cells_map)
//   {
//     std::cout << c.first << c.second << std::endl;
//   }
//   std::cout << std::endl;
// }