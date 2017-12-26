/***************************************************
 * Author: Hua Fan (h27fan@uwaterloo.ca)
 * Copyright (c) 2017 by Hua Fan.  All rights reserved.
 ***************************************************/

#include <string>
#include <iostream>
#include "Double_hash_table_tester.h"

using namespace std;

void usage() {
  cerr << "Usage:./Double_hash_table_driver int|double" << endl;;
}

int main(int argc, char* argv[]) {
  string type;
  if (argc == 1) {
    type = "int";
  } else if ( argc == 2) {
    type = string(argv[1]);
  }
  if (type != "int" && type != "double") {
      usage();
      return 1;
  }

  std::cout << "Starting Test Run" << std::endl;

  if (type == "int") {
    Double_hash_table_tester<int> tester;
    tester.run();
  } else if (type == "double") {
    Double_hash_table_tester<double> tester;
    tester.run();
  }

  std::cout << "Finishing Test Run" << std::endl;
  return 0;
}