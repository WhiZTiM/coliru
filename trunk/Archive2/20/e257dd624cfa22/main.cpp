#include <iostream>
#include <string>

struct Sales_data {                                                             
  // empty bracket initializes to empty string                                  
  std:: string bookNo{};                                                        
  unsigned units_sold = 0;                                                      
  double revenue = 0.0;                                                         
};

int main(){
    static_assert(std::is_same<decltype(Sales_data()), Sales_data&&>::value);
    
//  Sales_data books;
//  double price = 0.0;
//  // some ostream code here
//  for (int i = 0; i >= 0; ++i) {                                                
//    // The for loop keeps track and counts the books                            
//    while (std::cin >> books.bookNo >> books.units_sold >> price) {             
//      /*                                                                        
//       * while loop to allow the user to input as many books as they would      
//       * like                                                                   
//       */                                                                       
//      if (books != Sales_data()) {                                              
//        // if books is not empty print which number book for i                  
//        i += 1;                                                                 
//        std::cout << "Book " << i << " is " << books << std::endl;              
//      }                                                                         
//    }                                                                           
//  }            
//  return 0;
}