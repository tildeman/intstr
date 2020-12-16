# intstr
Integer operations on C++ strings (for dummies)
# How to use it
## Signed functions
* stradd(std::string a,std::string b) : adds 2 integer strings
* strsub(std::string a,std::string b) : subtracts 2 integer strings
* strmul(std::string a,std::string b) : multiplies 2 integer strings
* strdiv(std::string a,std::string b) : divides 2 integer strings (integer division)
* strmod(std::string a,std::string b) : modulos 2 integer strings
* strip_0s(std::string n) : strip leading 0s from string
* strcmpr(std::string a,std::string b) : compares 2 integer strings
## Unsigned functions
* stradd_u(std::string a,std::string b) : adds 2 integer strings (unsigned)
* strsub_u(std::string a,std::string b) : subtracts 2 integer strings (unsigned)
* strmulb1d(std::string a,std::string b) : multiplies an integer string by an 1-digit integer string
* strmul_u(std::string a,std::string b) : multiplies 2 integer strings (unsigned)
* strdivb1d(std::string a,std::string b) : divides 2 integer strings (integer division) and returns 1 digit. Returns 9 if division result is larger than 9.
* strdiv_u(std::string a,std::string b) : divides 2 integer strings (integer division) (unsigned)
* strmod_u(std::string a,std::string b) : modulos 2 integer strings (unsigned)
* strip_0s(std::string n) : strip leading 0s from string (unsigned)
* strcmpr_u(std::string a,std::string b) : compares 2 integer strings (unsigned)
## Utility functions
* reduce_sign(std::string n): returns the shortest sign representation of number (e.g.: ++--+--+47 -> 47)
* sign_check(std::string n): Checks whether given number is negative, zero or positive.
* to_str(int n) : works identically to std::string::to_string
# Credits
Just some credits to the C++ library.
