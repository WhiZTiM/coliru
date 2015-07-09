/*PhoneBookEntry::PhoneBookEntry(const char *aNumber, const char *aName)
      : _number(0),
		_name(0),
		_priority(0)
{
//	aNumber = trim(aNumber);
//	aName   = trim(aName);

	int _len = strlen(aNumber) + 1;
	if ( aName )
		_len += (strlen(aName) + 1);

	_data.reserve(_len);
	char *_wrPtr = _data;
	strcpy(_wrPtr, aNumber);
	_wrPtr += (strlen(aNumber) + 1);

	if ( aName ) {
		strcpy(_wrPtr, aName);
		_name = _wrPtr;
	}

	const char *_rdPtr = strchr(_data, ':');
	if ( _rdPtr ) {
		_priority = atoi(_data);
		_rdPtr++;
	} else
		_rdPtr = _data;

	_number = strchr(_rdPtr, '-');
	if ( _number )
		_number++;
	else
		_number = _rdPtr;
}*/

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

class PhoneBookEntry
{
  private:
    int _priority;
    std::string _number;
    std::string _name;
  public:
    PhoneBookEntry(const std::string& number, const std::string& name)
      : _priority(),
        _number(),
        _name(name)
    {
      std::string::size_type index = number.find(':');
      if(index != std::string::npos)
      {
        _priority = boost::lexical_cast<int>(number.substr(0, index));
        _number = number.substr(index);
      }
      else
        _number = number;
    }
    const std::string& name() const { return _name; };
    const std::string& number() const { return _number; }
    const int priority() const { return _priority; }
};

std::ostream& operator<<(std::ostream& os, const PhoneBookEntry& entry)
{
  return os << "PhoneBookEntry:\n Name: " << entry.name() << "\n Priority: " << entry.priority() << "\n Number: " << entry.number();
}

int main()
{
  const std::string example_number = "4:04987654321";
  const std::string example_name = "bla";
    
  PhoneBookEntry entry(example_number, example_name);
    
  std::cout << entry << '\n';
}
