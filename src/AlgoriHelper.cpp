#include "AlgoriHelper.h"

int32_t CAlgoriHelper::ListCombination( int n, int m, std::vector<std::string> &combinList )
{
	if (n == m) {
		combinList.push_back(std::string(m, '1'));
		return 0;
	}
	std::string n_str(m, '1');
	std::string m_str(n - m, '0');
	n_str += m_str;

	combinList.push_back(n_str);
	while (true) {
		std::size_t pos = n_str.find("10");
		if (pos == std::string::npos) {
			break;
		}
		if (pos > 1) {
			std::string tmp = n_str.substr(0, pos);
			std::sort(tmp.rbegin(), tmp.rend());
			n_str.replace(0, pos, tmp.c_str());
		}
		n_str[pos] = '0';
		n_str[pos + 1] = '1';
		combinList.push_back(n_str);
	}
	return 0;
}

int32_t CAlgoriHelper::BinarySearch( const int arr[], int low, int high, int key )
{
	int32_t mid;
	while ( low < high )
	{
		mid = low + (high - low)/2;	
		if ( arr[mid] < key ){
			low = mid + 1;
		}
		else if ( arr[mid] > key ){
			high = mid - 1;
		}
		else{
			return mid;
		}
	}
	return -low - 1;	
}
