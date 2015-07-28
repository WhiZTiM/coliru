#include <memory>
 
int main()
{
    {
		std::shared_ptr<int> p1(new int); // count is 1
		{
			std::shared_ptr<int> p2(p1); // count is 2
			{
				std::shared_ptr<int> p3(p1); // count is 3
			} // count goes back down to 2
		} // count goes back down to 1
	}	// here the count goes to 0 and the int is deleted.
}