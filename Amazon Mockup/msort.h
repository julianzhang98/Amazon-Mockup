
#include <vector>
using namespace std;


#ifndef MSORT_H
#define MSORT_H


class Msort {

  public:	
	template <class T, class Comparator>
	void mergeSort(vector<T> & myArray, Comparator comp);

};

#endif





template <class T, class Comparator>
void Msort::mergeSort (vector<T>& myArray, Comparator comp) {
	
	// if size of that vector is 1, return that list as a sorted list
	if (myArray.size() == 1) { return;}

	// splits the array into two pieces element 0 to (n/2)-1
	// runs merge sorter on the two pieces element (n/2) to n-1
	vector<T> firstHalf;
	vector<T> secondHalf;
	for (unsigned int i = 0; i < myArray.size(); i++) {
		if (i >= 0 && i <= (myArray.size()/2)-1) {
			firstHalf.push_back(myArray[i]);
		} else if (i >= (myArray.size()/2) && i <= myArray.size()-1) {
			secondHalf.push_back(myArray[i]);
		}
	}

	// sets one list equal to run on 1st half
	mergeSort(firstHalf, comp);
	// sets other list equal to run on 2nd half 
	mergeSort(secondHalf, comp);

	// merges two lists and set it equal to myArray
	int i = 0; // index counter of merged list
	int x = 0; // index counter of the first half
	int y = 0; // index counter of the second half
	while (i != myArray.size()) {
		if (x >= firstHalf.size()) { // if x is out of bounds then first half is depleted
			myArray[i] = secondHalf[y]; // just add the yth element from second half
			y++;
		} else if (y >= secondHalf.size()) { // if y is out of bounds then second half is depleted
			myArray[i] = firstHalf[x]; // just add the xth element from first half
			x++;
		//} else if (firstHalf[x] < secondHalf[y]) { // if neither has been depleted then compare
		} else if (comp(firstHalf[x], secondHalf[y])) { // if a < b
		//} else if (firstHalf[x](secondHalf[y])) { // if a < b
			myArray[i] = firstHalf[x];
			x++;
		} else {
			myArray[i] = secondHalf[y];
			y++;
		}
		i++;
	}
}