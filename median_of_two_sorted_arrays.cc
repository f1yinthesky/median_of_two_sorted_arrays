#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  double findMedianSortedArrays(int A[], int m, int B[], int n) {
    vector<double> median;
    if (m > n) {
      median = findMedianSortedArraysLeftSmall(B, n, A, m);
    } else {
      median = findMedianSortedArraysLeftSmall(A, m, B, n);
    }
    return vectorMean(median);
  }

private:
  void printArray(int a[], int size) {
    for (int i = 0; i < size; ++i) {
      cout << a[i] << " ";
    }
    cout << endl;
  }

  vector<double> findMedianSortedArraysLeftSmall(int A[], int m, int B[], int n) {
    printArray(A, m);
    printArray(B, n);
    cout << endl;
    // Base cases.
    // 0=m=n.
    if (n == 0) return makeVector(0);
    // 0=m<n.
    else if (m == 0) return findMedian(B, n);
    // 1=m=n.
    else if (n == 1) return makeVector(A[0], B[0]);
    // 1=m<n.
    else if (m == 1) {
      if (n % 2 == 1) {
	if (A[0] < B[n / 2 - 1]) {
	  return makeVector(B[n / 2 - 1], B[n / 2]);
	}
	else if (A[0] > B[n / 2 + 1]) {
	  return makeVector(B[n / 2 + 1], B[n / 2]); 
	} else {
	  return makeVector(A[0], B[n / 2]);
	}
      } else {
	if (A[0] < B[n / 2 - 1]) return makeVector(B[n / 2 - 1]);
	else if (A[0] > B[n / 2]) return makeVector(B[n / 2]);
	else return makeVector(A[0]);
      }
    }
    // 2=m=n.
    else if (n == 2) {
      if (A[0] < B[0] && A[1] > B[1]) return findMedian(B, 2);
      else if (A[0] < B[0] && A[1] <= B[1]) return makeVector(A[1], B[0]);
      else if (A[0] >= B[0] && A[1] > B[1]) return makeVector(A[0], B[1]);
      else return findMedian(A, 2);
    }
    // 2=m<n.
    else if (m == 2) {
      if (n % 2 == 1) {
	if (A[0] < B[n / 2 - 1]) {
	  if (A[1] < B[n / 2 - 1]) return makeVector(B[n / 2 - 1]);
	  else if (A[1] < B[n / 2]) return makeVector(A[1]);
	  else return makeVector(B[n / 2]);
	} else if (A[0] < B[n / 2]) {
	  if (A[1] < B[n / 2]) return makeVector(A[1]);
	  else return makeVector(B[n / 2]);
	} else if (A[0] < B[n / 2 + 1]) {
	  return makeVector(A[0]);
	} else {
	  return makeVector(B[n / 2 + 1]);
	}
      } else {
	if (A[0] < B[n / 2 - 2]) {
	  if (A[1] < B[n / 2 - 2]) return makeVector(B[n / 2- 2], B[n / 2- 1]);
	  else if (A[1] < B[n / 2]) return makeVector(A[1], B[n / 2 - 1]);
	  else return makeVector(B[n / 2 - 1], B[n / 2]);
	} else if (A[0] < B[n / 2 -1]) {
	  if (A[1] < B[n / 2]) return makeVector(A[1], B[n / 2 - 1]);
	  else return makeVector(B[n / 2 - 1], B[n / 2]);
	} else if (A[0] < B[n / 2]) {
	  if (A[1] < B[n / 2]) return findMedian(A, 2);
	  else return makeVector(A[0], B[n / 2]);
	} else if (A[0] < B[n / 2 + 1]) {
	  return makeVector(A[0], B[n / 2]);
	} else {
	  return makeVector(B[n / 2], B[n / 2 + 1]);
	}
      }
    }
    // Non-Base case
    // 2<m<=n.
    else {
      vector<double> median_a = findMedian(A, m);
      vector<double> median_b = findMedian(B, n);
      int number_to_delete = (m - 1) / 2;
 
      if (median_a.size() == median_b.size() && median_b.size() == 1) {
	// Both array sizes are odd.
	if (median_a[0] == median_b[0]) {
	  return makeVector(median_a[0]);
	} else if(median_a[0] < median_b[0]) {
	  return findMedianSortedArraysLeftSmall(A + number_to_delete,
						 m - number_to_delete,
						 B,
						 n - number_to_delete);
	} else {
	  return findMedianSortedArraysLeftSmall(A,
						 m - number_to_delete,
						 B + number_to_delete,
						 n - number_to_delete);	
	}
      } else if(median_a.size() == median_b.size() && median_b.size() == 2) {
	// Both array sizes are even.
	if (median_a[0] < median_b[0]) {
	  if (median_a[1] < median_b[1]) {
	    return findMedianSortedArraysLeftSmall(A + number_to_delete,
						   m - number_to_delete,
						   B,
						   n - number_to_delete);
	  } else {
	    return median_b;
	  }
	} else if (median_a[0] < median_b[1]) {
	  if (median_a[1] < median_b[1]) {
	    return median_a;
	  } else {
	    return findMedianSortedArraysLeftSmall(A,
						   m - number_to_delete,
						   B + number_to_delete,
						   n - number_to_delete);
	  }
	} else {
	  return findMedianSortedArraysLeftSmall(A,
						 m - number_to_delete,
						 B + number_to_delete,
						 n - number_to_delete);
	}
      } else if (median_a.size() == 1){
	// A size is odd, B size is even.
	if (median_a[0] < median_b[0]) {
	  return findMedianSortedArraysLeftSmall(A + number_to_delete,
						 m - number_to_delete,
						 B,
						 n - number_to_delete);
	} else if (median_a[0] < median_b[1]) {
	  return median_a;
	} else {
	  return findMedianSortedArraysLeftSmall(A,
						 m - number_to_delete,
						 B + number_to_delete,
						 n - number_to_delete);	
	}
      } else {
	// A size is even, B size is odd.
	if (median_b[0] < median_a[0]) {
	  return findMedianSortedArraysLeftSmall(A,
						 m - number_to_delete,
						 B + number_to_delete,
						 n - number_to_delete);
	} else if (median_b[0] < median_a[1]) {
	  return median_b;
	} else {
	  return findMedianSortedArraysLeftSmall(A + number_to_delete,
						 m - number_to_delete,
						 B,
						 n - number_to_delete);	
	}
      }
    }
  }

  vector<double> findMedian(int a[], int size) {
    if (size % 2 == 0) {
      return makeVector(a[size / 2 - 1], a[size / 2]);
    } else {
      return makeVector(a[size / 2]);
    }
  }

  double vectorMean(const vector<double>& v) {
    double sum = 0;
    for (const double ele : v) {
      sum += ele;
    }
    if (v.size() == 0) return sum;
    else return sum / v.size();
  }

  // Return vector contains a & b, sorted ascending.
  vector<double> makeVector(double a, double b) {
    vector<double> result;
    double min = a < b ? a : b;
    double max = a < b ? b : a;
    result.emplace_back(min);
    result.emplace_back(max);
    return result;
  }

  // Return vector contains a.
  vector<double> makeVector(double a) {
    vector<double> result;
    result.emplace_back(a);
    return result;
  }
};

int main() {
  int a[] = {1, 2, 6, 7};
  int b[] = {3, 4, 5, 8};
  Solution solution;
  cout << solution.findMedianSortedArrays(a, 4, b, 4) << endl;
  return 0;
}
