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

std::istream& vasyakin::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return std::getline(in >> DelimeterIO{'"'}, dest.ref, '"');
}

std::istream& vasyakin::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return in >> dest.ref;
}

std::istream& vasyakin::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  DataStruct input{};
  bool got_k1 = false, got_k2 = false, got_k3 = false;
  std::string label;

  in >> DelimeterIO{'('} >> DelimeterIO{':'};
  if (!in)
  {
    return in;
  }

  while (in && in.peek() != ')')
  {
    in >> LabelIO{label};
    if (!in)
    {
      break;
    }

    if (label == "key1")
    {
      in >> CharIO{input.key1};
      if (in)
      {
        got_k1 = true;
      }
    }
    else if (label == "key2")
    {
      in >> RatioIO{input.key2};
      if (in)
      {
        got_k2 = true;
      }
    }
    else if (label == "key3")
    {
      in >> StringIO{input.key3};
      if (in)
      {
        got_k3 = true;
      }
    }
    else
    {
      break;
    }

    in >> DelimeterIO{':'};
  }

  in >> DelimeterIO{')'};

  if (in && got_k1 && got_k2 && got_k3)
  {
    dest = input;
  }
  else
  {
    in.setstate(std::ios_base::failbit);
  }

  return in;
}

std::ostream& vasyakin::operator<<(std::ostream& out, const DataStruct& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  GuardIO guard(out);
  out << "(:key1 '" << dest.key1 << "':";
  out << "key2 (:N " << dest.key2.first << ":D" << dest.key2.second << ":):";
  out << "key3 \"" << dest.key3 << "\":)";

  return out;
}

bool vasyakin::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }

  long double l_val = static_cast< long double >(lhs.key2.first) / lhs.key2.second;
  long double r_val = static_cast< long double >(rhs.key2.first) / rhs.key2.second;

  if (l_val != r_val)
  {
    return l_val < r_val;
  }

  return lhs.key3.length() < rhs.key3.length();
}
