#include <assert.h>
#include "map.h"

using namespace std;

int main()
{
	cout << "Hello Map." << endl;

    std::vector<int> vec1 {1, 2, 3, 4, 5, 6};
    std::vector<int> vec2 {2, 4, 6, 8, 10, 12};

    map2(vec1, [](int i){
		return i*2;
		});


	assert(vec1 == vec2);
	return 0;
}
