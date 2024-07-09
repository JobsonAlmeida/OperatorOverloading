#include <iostream>
#include <cstring>
#include "Mystring.h"
#include <string>

// No-args constructor
Mystring::Mystring()
    : str{ nullptr }
{
    str = new char[1];
    *str = '\0';
}

// Overloaded constructor
Mystring::Mystring(const char* s)
    : str{ nullptr }
{
    if (s == nullptr)
    {
        str = new char[1];
        *str = '\0';
    }
    else
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
}

// Copy constructor
Mystring::Mystring(const Mystring& source)
    : str{ nullptr }
{
    str = new char[strlen(source.str) + 1];
    strcpy(str, source.str);
    //       std::cout << "Copy constructor used" << std::endl;

}

// Move constructor
Mystring::Mystring(Mystring&& source)
    :str(source.str)
{
    source.str = nullptr;
    //        std::cout << "Move constructor used" << std::endl;
}

// Destructor
Mystring::~Mystring()
{
    delete[] str;
}

//// Copy assignment
//Mystring& Mystring::operator=(const Mystring& rhs)
//{
//    //    std::cout << "Using copy assignment" << std::endl;
//
//    if (this == &rhs)
//        return *this;
//    delete[] str;
//    str = new char[strlen(rhs.str) + 1];
//    strcpy(str, rhs.str);
//    return *this;
//}

//// Move assignment
//Mystring& Mystring::operator=(Mystring&& rhs)
//{
//    //   std::cout << "Using move assignment" << std::endl;
//    if (this == &rhs)
//        return *this;
//    delete[] str;
//    str = rhs.str;
//    rhs.str = nullptr;
//    return *this;
//}


// Display method
void Mystring::display() const
{
    std::cout << str << " : " << get_length() << std::endl;
}

// getters
int Mystring::get_length() const { return strlen(str); }
const char* Mystring::get_str() const { return str; }

// overloaded insertion operator
std::ostream& operator<<(std::ostream& os, const Mystring& rhs)
{
    os << rhs.str;
    return os;
}

// overloaded extraction operator
std::istream& operator>>(std::istream& in, Mystring& rhs)
{
    char* buff = new char[1000];
    in >> buff;
    rhs = Mystring{ buff };
    delete[] buff;
    return in;
}

// overloaded equal operator
bool Mystring::operator==(const Mystring &rhs) const
{
    return (std::strcmp(this->str, rhs.str)==0);
}

// overloaded difference operator
bool Mystring::operator!=(const Mystring& rhs) const
{
    return (std::strcmp(this->str, rhs.str)!=0);
}



//overloaded copy assignment operator
Mystring& Mystring::operator=(const Mystring& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    delete[] str;

    str = new char[std::strlen(rhs.str) + 1];
    std::strcpy(str, rhs.str);

    return *this;
}

//overloaded move assignment operator
Mystring& Mystring::operator=(Mystring&& rhs) noexcept
{
    std::cout << "Move assignment operator called\n";

    if (this == &rhs) { return *this; }

    delete[] this->str; //THE PROGRAM STOPS HERE

    str = rhs.str;
    rhs.str = nullptr;

    return *this;

}

//overloaded less than operator
bool Mystring::operator<(const Mystring rhs) const
{
    return (std::strcmp(this->str, rhs.str) < 0) ? true : false;
}

//overloaded greater than operator
bool Mystring::operator>(const Mystring rhs) const
{
    return (std::strcmp(this->str, rhs.str) < 0) ? true : false;
}

//overloaded unary minus operator
Mystring Mystring::operator-() const
{
    char *buff = new char[std::strlen(str) + 1];
    std:strcpy(buff, str); 

    for (size_t i = 0; i < std::strlen(buff); i++)
    {
        buff[i] = std::tolower(buff[i]);
    }

    Mystring temp{ buff };

    delete[] buff;

    return temp;
}

//overloaded unary plus operator
Mystring Mystring::operator+(const Mystring& rhs)
{
    size_t buff_size = std::strlen(str) + std::strlen(rhs.str) + 1;
    char* buff = new char[buff_size];

    std::strcpy(buff, str);
    std::strcat(buff, rhs.str);

    Mystring temp{ buff };

    delete[] buff;

    return temp;

}

//overloaded plus equal operator
Mystring Mystring::operator+=(const Mystring& rhs)
{
    Mystring temp = this->operator+(rhs);

    delete[] str;
    size_t buff_size = std::strlen(temp.str) + 1;  
    str = new char[buff_size];

    std::strcpy(str, temp.str);

    return temp;

    /*
    size_t buff_size = std::strlen(str) + std::strlen(rhs.str) + 1;
    char* buff = new char[buff_size];
    std::strcpy(buff, str);
    std::strcat(buff, rhs.str);

    //int strLength = sizeof(this->str) / sizeof(char); 
    delete[] str; // HERE WE ARE DEALLOCATING THE MEMORY POINTED BY STR BECAUSE WE ARE GOING TO ALLOCATE ANOTHER MEMORY LENGTH. WE HAVE DEALLOCATED STR, BUT WE HAVE ITS PREVIOUSLY LENGHT IN THE strLenght VARIABLE. 

    str = new char[buff_size]; //IF NOT PRESENT, CAUSES THE PROGRAM STOPS AHEAD WHEN THE DELETE OPERATION IS APPLIED AGAIN OVER STR OF THE SAME OBJECT. THE REASON IS BECAUSE WE HAVE PREVIOUSLY WE DEALLOCATED THE MEMORY TO WHICH STR POINTS. SO THE STR IS POINTING TO LOCAL MEMORY NO SECURITY AND ACCONDING TO THE CODE BELOW WE ARE COPING THE CONTENT OF THE BUFF TO THE LOCAL WHERE STR IS POINTING (WHICH IS NOT A SECURITY AREA). SO, IN ANY PLACE AHEAD IN THE CODE WHEN WE TRY TO DEALLOCATE THE AREA TO WHICH STR IS POINTING WE HAVE AN EXCEPTION BECAUSE THAT IS NOT AN ALLOCATED SPACE OF MEMORY. 

    //IF BOTH THE CODES ABOVE DELETE STR AND STR = NEW CHAR[...] ARE NOT PRESENT IN THE CODE WE ARE ALSO HAVE PROBLEMS IN THE FUTURE DUE TO THE MEMORY ALLOCATION. THE IS IS THAT STR IS POINTIN TO A SPACE OF MEMORY LESS THAT THE SPACE OF THE MEMORY POINTED BY BUFF. THEREFORE, WHEN THE STRCPY FUNCTION BELLOW IS EXECUTED AND THE CONTENTE FROM BUFF IS COPIED TO THE SPACE OF MEMORY POINTED BY STR, THE SPACE OF MEMROY POINTED BY STR DON'T HAVE ENOUGH SPACE TO HOLD ALL THE CONTENTE AND THEREFORE SOME DATA IS GOING TO LEAK FROM THE SPACE OF THE MEMORY POINTED BY STR. 

    std::strcpy(str, buff); // THIS FUNCTION JUST COPIES THE CONTENT POINTER BY BUFF TO THE MEMORY AREA PONTED BY STR. IT DOESN'T CHECK IF THE STR IS POINTING TO A SECURY SPACE OF MEMORY, AND DOESN'T MATTER IF THE STR IS NOT POITING TO A SECURY MEMORY AREA, THE STRCPY FUNCTION COPIES ANYWAY.    

    Mystring temp{ buff };

    delete[] buff;

    return temp;  */ 
}

//overloaded times operator 
Mystring Mystring::operator*(int n)
{
    char* buff = new char[std::strlen(str)*n + 1];

    std::strcpy(buff, str);
    for (size_t i = 2; i <= n; i++)
    {
        std::strcat(buff, str);
    }

    Mystring temp{ buff };

    delete[] buff;

    return temp;
}

//overloaded times equal operator
Mystring Mystring::operator*=(int n)
{
    Mystring temp = this->operator*(n);

    delete[] str;
    size_t buff_size = std::strlen(temp.str) + 1;    
    str = new char[buff_size];

    std::strcpy(str, temp.str);

    return *this;

}

//overloaded pre-increment operator
Mystring& Mystring::operator++()
{
    for (size_t i = 0; i < std::strlen(str); i++)
    {
        str[i] = std::toupper(str[i]);
    }

    return *this;
}




