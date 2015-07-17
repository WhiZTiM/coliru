#include <stdarg.h>
#include <string.h>
#include <typeinfo>
#include <iostream>
#include <string>

using namespace std;

// pc = print with check
bool pc(const char* format)
{
    if (format == NULL)
		return false;
	else
		cout << "format: " << format << "\n";
	const char* pCrt = format;
	do
	{
		pCrt = strchr(pCrt, '%');
		if (pCrt != NULL)
		{
			// we may have type or another %
			pCrt++;
			if (*pCrt == '%')
				pCrt++;				// ignore %%
			else
				return false;		// unmatched %
		}
	} while(pCrt != NULL);

	return true;
}

// pc = print with check
template <typename T> bool pc(const char* format, const T &value)
{
	int left2Process = 1;
	cout << "got 1 arg left. type: " << typeid(T).name() << "\n";
	if (format == NULL)
		return false;
	else
		cout << "format: " << format << "\n";
	const char* pCrt = format;
	do
	{
		pCrt = strchr(pCrt, '%');
		if (pCrt != NULL)
		{
			// we may have type or another %
			pCrt++;
			switch (*pCrt)
			{
			case '\0':
				return false;		// unmatched %

			case '%':
				pCrt++;				// ignore %%
				break;

			case 'c': case 'C':
				if (is_convertible<T, char>::value && left2Process)
				{
					// do the actual print

					// roll the ball further
					left2Process = 0;
					pCrt++;
					continue;
				}
				else
					return false;	// format mismatched with type

			case 'd': case 'i':	case 'o': case 'u': case 'x': case 'X':
				if (is_convertible<T, int>::value  && left2Process)
				{
					// do the actual print

					// roll the ball further
					left2Process = 0;
					pCrt++;
					continue;
				}
				else
					return false;	// format mismatched with type

			case 'e': case 'E':	case 'f': case 'g': case 'G': case 'a': case 'A':
				if (is_convertible<T, float>::value && left2Process)
				{
					// do the actual print

					// roll the ball further
					left2Process = 0;
					pCrt++;
					continue;
				}
				else
					return false;	// format mismatched with type

			case 'p':
				if (is_convertible<T, const void*>::value && left2Process)
				{
					// do the actual print

					// roll the ball further
					left2Process = 0;
					pCrt++;
					continue;
				}
				else
					return false;	// format mismatched with type

			case 's': case 'S':
				if (is_convertible<T, const char*>::value && left2Process)
				{
					// do the actual print

					// roll the ball further
					left2Process = 0;
					pCrt++;
					continue;
				}
				else
					return false;	// format mismatched with type

			default:
				return false;		// unmatched %
			}
		}
	} while (pCrt != NULL);

	if (left2Process >= 1)
	{
		cout << "we got leftovers :(\n";
		return false;
	}
	else
	{
		return true;
	}
}

// pc = print with check
template <typename T, typename... Types> bool pc(const char* format, const T &value, const Types&... args)
{
	int left2Process = sizeof ...(Types) + 1;
	cout << "got " << left2Process << " args left. first of type: " << typeid(T).name() << "\n";
	if (format == NULL)
		return false;
	else
		cout << "format: " << format << "\n";
	const char* pCrt = format;
	do
	{
		pCrt = strchr(pCrt, '%');
		if (pCrt != NULL)
		{
			// we may have type or another %
			pCrt++;
			switch (*pCrt)
			{
			case '\0':
				return false;		// unmatched %
			
			case '%':
				pCrt++;				// ignore %%
				break;

			case 'c': case 'C':
				if (is_convertible<T, char>::value)
				{
					// do the actual print

					// roll the ball further
					return pc(++pCrt, args...);
				}
				else
					return false;	// format mismatched with type

			case 'd': case 'i':	case 'o': case 'u': case 'x': case 'X':
				if (is_convertible<T, int>::value)
				{
					// do the actual print

					// roll the ball further
					return pc(++pCrt, args...);
				}
				else
					return false;	// format mismatched with type

			case 'e': case 'E':	case 'f': case 'g': case 'G': case 'a': case 'A':
				if (is_convertible<T, float>::value)
				{
					// do the actual print

					// roll the ball further
					return pc(++pCrt, args...);
				}
				else
					return false;	// format mismatched with type

			case 'p':
				if (is_convertible<T, const void*>::value)
				{
					// do the actual print

					// roll the ball further
					return pc(++pCrt, args...);
				}
				else
					return false;	// format mismatched with type

			case 's': case 'S':
				if (is_convertible<T, const char*>::value)
				{
					// do the actual print

					// roll the ball further
					return pc(++pCrt, args...);
				}
				else
					return false;	// format mismatched with type
			default:
				return false;		// unmatched %
			}
		}
	} while (pCrt != NULL);

	if (left2Process >= 1)
	{
		cout << "we got leftovers :(\n";
		return false;
	}
	else
	{	
		return true;
	}
}

int main()
{
    // test print with check
	cout << pc("%%\n") << "\n";																	//	1
	cout << pc("%%%\n") << "\n";																//	0
	cout << pc("%w\n") << "\n";																	//	0
	cout << pc("%d\n", int(42)) << "\n";														//	1
	cout << pc("%d %\n", int(42)) << "\n";														//	0
	cout << pc("%d %d\n", int(42)) << "\n";														//	0
	cout << pc("%d %f\n", int(42), float(2.71)) << "\n";										//	1
	cout << pc("int %d float %f\n", "mordor", "rules") << "\n";							 		//	0
	cout << pc("int %d char* %s float %f\n", "shadow", std::string("of"), "rules") << "\n";		//	0
    
    return 0;
}
