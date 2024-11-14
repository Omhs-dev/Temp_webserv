// #include "TestHeader.hpp"

// // Declare test functions
// // void testServerInitialization();
// // void testClientRequestHandling();
// // void testParseRequestLine();
// // void testHTTPResponse();

// int main() {
//     testServerInitialization();
//     testClientRequestHandling();
//     testParseRequestLine();
//     testHTTPResponse();

//     std::cout << "All tests completed." << std::endl;
//     return 0;
// }

#include <iostream>
#include <vector>

int main() {
   int i = 0;
   i += 1;
   int j = i+2;
    std::vector<int> vect;
    vect.push_back(i + j);
   for (int i : vect) {
	   std::cout << i << std::endl;
   }
 }