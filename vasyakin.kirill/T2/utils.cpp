#include "utils.hpp"

std::istream& vasyakin::operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char c = '0';
  in >> c;
  if (in && c != dest.exp)
  {
    in.setstate(std::ios_base::failbit);
  }

  return in;
}

std::istream& vasyakin::operator>>(std::istream& in, CharIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char c = '\0';
  in >> c;
  if (in && c != '\'')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  
  in >> dest.ref;
  if (!in)
  {
    return in;
  }

  char k = '\0';
  in >> k;
  if (in && k != '\'')
  {
    in.setstate(std::ios_base::failbit);
  }

  return in;
}


std::istream& vasyakin::operator>>(std::istream& in, RatioIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char label1 = '0';

  in >> DelimeterIO{'('} >> DelimeterIO{':'} >> label1 >> dest.ref.first;
  if (!in)
  {
    return in;
  }
  if (label1 != 'N')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  char label2 = '0';

  in >> DelimeterIO{':'} >> label2 >> dest.ref.second >> DelimeterIO{':'} >> DelimeterIO{')'};
  if (!in)
  {
    return in;
  }
  if (label2 != 'D')
  {
    in.setstate(std::ios_base::failbit);
  }

  return in;
}
