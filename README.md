# intstr
Integer (currently unsigned) operations on C++ strings (for dummies)
# How to use it
* stradd(std::string a,std::string b) : adds 2 integer strings
* strsub(std::string a,std::string b) : subtracts 2 integer strings
* strmulb1d(std::string a,std::string b) : multiplies an integer string by an 1-digit integer string
* strmul(std::string a,std::string b) : multiplies 2 integer strings
* strdivb1d(std::string a,std::string b) : divides 2 integer strings (integer division) and returns 1 digit. Returns 9 if division result is larger than 9.
* strdiv(std::string a,std::string b) : divides 2 integer strings (integer division)
* strcmp(std::string a,std::string b) : compares 2 integer strings
* to_str(int n) : works identically to std::string::to_string
* strip_0s(std::string n) : strip leading 0s from string
# Credits
Just some credits to the C++ library.
