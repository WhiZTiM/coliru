#include <vector>
#include <iterator>
#include <utility>

typedef std::pair<int, int> edge;
class Polygon
{
public:
    Polygon();
    // Functions...
	
	// Iterator:
	class iterator : public std::iterator<std::bidirectional_iterator_tag, edge>
	{
	private:
		int index;
		Polygon &polygon;
	public:
		iterator(int index, Polygon &polygon);
		iterator(iterator &copy);
		iterator & operator = (const iterator &rhs);
		// Other functions..
	};
	iterator begin()
	{
		return iterator(0, *this);
	}
	iterator end()
	{
		return iterator(-1, *this);
	}
};