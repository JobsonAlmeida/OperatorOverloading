#ifndef _MYSTRING_H_
#define _MYSTRING_H_

class Mystring
{
    friend std::ostream& operator<<(std::ostream& os, const Mystring& rhs);
    friend std::istream& operator>>(std::istream& in, Mystring& rhs);

private:
    char* str;      // pointer to a char[] that holds a C-style string
public:
    Mystring();                                         // No-args constructor
    Mystring(const char* s);                            // Overloaded constructor
    Mystring(const Mystring& source);                   // Copy constructor
    Mystring(Mystring&& source);                        // Move constructor
    ~Mystring();                                        // Destructor

    //Mystring& operator=(const Mystring& rhs);     // Copy assignment
    //Mystring& operator=(Mystring&& rhs);          // Move assignment

    void display() const;

    int get_length() const;                                      // getters
    const char* get_str() const;

    bool operator==(const Mystring &rhs) const;  //equal overloaded operator
    bool operator!=(const Mystring& rhs) const;  // overloaded difference operator

    Mystring& operator=(const Mystring& rhs);   //overloaded copy assignment operator
    Mystring& operator=(Mystring&& rhs) noexcept;        //overloaded move assignment operator

    bool operator<(const Mystring rhs) const; //overloaded less than operator
    bool operator>(const Mystring rhs) const; //overloaded greater than operator

    Mystring operator-() const; //overloaded unary minus operator
    Mystring operator+(const Mystring &rhs);       //overloaded plus operator
    Mystring operator+=(const Mystring& rhs);      //overloaded plus iqual operator
    Mystring operator*(int n);  //overloaded times operator 
    Mystring operator*=(int n); //overloaded times equal operator
    Mystring& operator++(); //overloaded pre-increment operator
    Mystring operator++(int); //overloaded post-increment operator

};

#endif // _MYSTRING_H_
