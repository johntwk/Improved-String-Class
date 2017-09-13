#include "istring.h"
#include <iostream>
#include <string>
using namespace std;

/* NOTES
   Commands are given in a regex style, e.g. saba, p a 3, f a, etc
   Copy Constructor needs to work before operator* and operator+ can be tested
   Delete (command e) iStrings before allocating new ones - otherwise memory leak
   e.g. Delete an iString before you try to write to it, if you have previously written to it
        Do something like: 'fa ea na foo' and not 'fa na foo' which would cause a memory leak
   
   Note on commands: Spaces are not necessary but are used here for readability
   Command descriptions:
   s destination source1 source2 // operator+
   t destination source1 string // operator+
   r destination string // operator >>, read a string into an iString object
   p destination source int // operator*
   m destination int source // operator*
   n destination string // iString(char*) - create an iString object with given string as contents
   i destination source // copy constructor - copy an existing iString object (like strdup)
   = destination source // assignment operator - copy an existing iString object
   f destination // default constructor - create empty iString (basically, empty string)
   e source // delete source/call destructor - cleans up memory
   l source // print length of iString
*/
int main() {  
  bool done = false;
  string temp;
  iString *a[4];
  while(!done) {
    char c;
    char which;
    char op1;
    char op2;
    int int_op;
    cerr << "Command?" << endl;  // Valid commands:  r [a-d] string
                                 //                  wa, wb, wc, wd, q
                                 //                  s[a-d][a-d][a-d]
                                 //                  t [a-d] [a-d] string
                                 //                  m [a-d] int [a-d]
                                 //                  p [a-d] [a-d] int
                                 //                  n [a-d] string
                                 //                  i [a-d] [a-d]
                                 //                  = [a-d] [a-d]
                                 //                  f [a-d] 
                                 //                  e [a-d]
                                 //                  l [a-d]
    cin >> c;  // Reads r, p, m, s, w, n, i, e, f, q
    if (cin.eof()) break;
    switch(c) {
      case 'r':
        cin >> which;  // Reads a, b, c, or d
        a[which-'a'] = new iString;
        cin >> *(a[which-'a']);
        break;
      case 'w':
        cin >> which;  // Reads a, b, c, or d
        cout << *(a[which-'a']) << endl;
        break;
      case 'n':
        cin >> which >> temp;
        a[which-'a'] = new iString(temp.c_str());
        break;
      case 'i':
        cin >> op1 >> op2;
        a[op1-'a'] = new iString(*(a[op2-'a']));
        break;
      case '=':
        cin >> op1 >> op2;
        *a[op1-'a'] = *a[op2-'a'];
        break;
      case 's':
        cin >> which >> op1 >> op2;
        a[which-'a'] = new iString(*(a[op1-'a']) + *(a[op2-'a']));
        break;
      case 't':
        cin >> which >> op1 >> temp;
        a[which-'a'] = new iString(*(a[op1-'a']) + temp.c_str());
        break;
      case 'm':
        cin >> which >> int_op >> op2;
        a[which-'a'] = new iString( (int_op * *(a[op2-'a'])) );
        break;
      case 'p':
        cin >> which >> op2 >> int_op;
        a[which-'a'] = new iString( (*(a[op2-'a']) * int_op));
        break;    
      case 'e':
        cin >> which;
        delete a[which-'a'];
        break;
      case 'f':
        cin >> which;
        a[which-'a'] = new iString();
        break;
      case 'l':
         cin >> which;
         cout << a[which-'a']->length << endl;
         break;
      case 'q':
        done = true;
    }
  }
}
