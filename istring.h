#ifndef __ISTRING_H__
#define __ISTRING_H__
#include <iostream>

struct iString{
  char * chars;
  unsigned int length;
  unsigned int capacity;
  iString();
  iString(const char *);
  iString(const iString&);
  iString &operator=(const iString&);
  ~iString();
};

iString operator+ (const iString&, const iString&);
iString operator+ (const iString&, const char*);
iString operator* (const int, const iString&);
iString operator* (const iString&, const int);
std::ostream &operator << (std::ostream &, const iString &);
std::istream &operator >> (std::istream &, iString&);


#endif
