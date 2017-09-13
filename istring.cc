#include <iostream>
#include <cstring>
#include <locale>
#include "istring.h"
using namespace std;

iString::iString () {
  chars = new char [1];
  chars[0] = '\0';
  length = 0;
  capacity = 0;
}

iString::iString (const char *s) {
  int s_len = strlen(s);
  char *new_c = new char[s_len+1];
  for (int i = 0; i < s_len; i++) {
    new_c[i] = s[i];
  }
  new_c[s_len] = '\0';
  chars = new_c;
  length = s_len;
  capacity = s_len;
}

iString::iString(const iString &s) {
  int new_len = strlen(s.chars);
  char *new_s = new char[new_len+1];
  for (int i = 0; i < new_len; i++) {
    new_s[i] = s.chars[i];
  }
  new_s[new_len] = '\0';
  chars = new_s;
  length = new_len;
  capacity = new_len;
}

iString::~iString () {
  delete [] chars;
}

iString operator+(const iString &s1, const iString &s2) {
  int this_len = strlen(s1.chars);
  int s_len = strlen(s2.chars);
  int new_len = this_len + s_len;
  char *new_s = new char[new_len+1];
  for (int i = 0; i < this_len; i++) {
    new_s[i] = s1.chars[i];
  }
  for (int i = 0; i < s_len; i++) {
    new_s[i+this_len] = s2.chars[i];
  }
  new_s[new_len] = '\0';
  iString rt(new_s);
  delete [] new_s;
  return rt;
}

iString operator+(const iString &s1, const char* s2) {
  int s1_len = strlen(s1.chars);
  int s2_len = strlen(s2);
  int new_len = s1_len + s2_len;
  char *new_s = new char[new_len + 1];
  for (int i =0; i < s1_len; i++) {
    new_s[i] = s1.chars[i];
  }
  for (int i = 0; i < s2_len; i++) {
    new_s[i+s1_len] = s2[i];
  }
  new_s[new_len] = '\0';
  iString rt(new_s);
  delete [] new_s;
  return rt;
}

iString &iString :: operator= (const iString &other) {
  if (this == &other) return *this;
  length = other.length;
  capacity = other.length;
  
  int other_len = strlen(other.chars);
  char *new_s = new char[other_len + 1];

  for (int i = 0; i < other_len; i++) {
    new_s[i] = other.chars[i];
  } 
  new_s[other_len] = '\0';
  delete [] chars;
  chars = new_s;
  return *this;
}

iString operator* (const int k, const iString &s) {
  if (k == 0) return iString();
  if (k == 1) return iString(s);
  iString rt = s;
  //cout << endl;
  for (int i = 1; i < k; i++) {
    rt = rt + s;
    //cout << i << endl;
  }
  //cout <<endl;
  return rt;
}

iString operator* (const iString &s, const int k) {
  return k * s;
}

ostream &operator << (ostream &out, const iString &s) {
  int s_len = strlen(s.chars);

  for (int i = 0; i < s_len; i++) {
    out << s.chars[i];
  }
  return out;
}

istream &operator >> (istream &in, iString &s) { 
  
  char c;
  char *new_s = NULL;
  int counter = 0;
  while (true) {
    in >> c;
    counter++;
    if (in.fail()) {
      break;
    }
    else if (counter == 1) {
      //cout << c << endl;
      new_s = new char[counter+1];
      new_s[counter-1] = c;
      new_s[counter] = '\0';
    }
    else {
      char *new_new_s = new char[counter+1];
      for (int i = 0; i < counter - 1; i++) {
        new_new_s[i] = new_s[i];
      }
      new_new_s[counter-1] = c;
      new_new_s[counter] = '\0';
      //cout << new_new_s[counter-1] <<endl;
      delete [] new_s;
      new_s= new_new_s;
    }
    if (in.peek() == '\n' || isspace(in.peek())) {
      break;
    }
  }
  s.chars = new_s;
  s.length = strlen(new_s);
  s.capacity = strlen(new_s);
  return in;
 /*
  char c[2];
  iString is1;
  while (! isspace(cin.peek()) ) {
    cin >> c[1];
    c[2] = '\0';
    iString is2 = iString(c);
    is1 = is1 + is2;
  }
  */
}

/*
int main() {
  iString i;
  cin >> i;
  cout << "i: " << i << endl;
  cout << "i.length: " << i.length << endl;
  cin >> i;
  cout << "i: " << i << endl;
  cout << "i.length: " << i.length <<endl;
  iString i1("abc");
  cout << "i1: " << i1 << endl;
  iString i2 = i1;
  cout << "i2: " << i2  << endl;
  iString i3;
  i3 = i1;
  iString i4("123");
  cout << "i4: " << i4 << endl;
  cout << "i4+i4: " << i4+i4 << endl;
  cout << "i3: " << i3 << endl;
  i3 = 3 * i3;
  cout << "i3 = 3 * i3: " << i3 << endl;
  cout << "i3 * 3" << i3 * 3  << endl;
}
*/
