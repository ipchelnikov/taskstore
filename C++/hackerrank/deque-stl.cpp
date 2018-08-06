#include <iostream>
#include <deque> 
#include <fstream>
using namespace std;

//#define DEBUG

void printKMax(int arr[], int n, int k, std::ofstream& ofstr){
    
    std::deque<int> q;
    
    int i = 0;
    
    for(; i < k; i++){
        while(!q.empty() && arr[q.back()] <= arr[i])
            q.pop_back();
        
        q.push_back(i);
    }
    
    for(; i < n; i++){
        ofstr << arr[q.front()] << " ";
        #ifdef DEBUG
        std::cout << "q.front() = " << q.front() << std::endl;
        std::cout << "i = " << i << "k = " << k << std::endl;
        #endif
        while(!q.empty() && q.front() <= i-k){
            #ifdef DEBUG
            std::cout << "\narr[" << q.front() << "] = " << arr[q.front()] << " is out of the window\n";
            #endif
            q.pop_front();
        }
        
        while(!q.empty() && arr[q.back()] <= arr[i])
            q.pop_back();
        
        q.push_back(i);
    }

    #ifdef DEBUG
    std::cout << "arr[q.back()] = " << arr[q.back()] << " arr[q.front()] = " <<  arr[q.front()] << std::endl;
    #endif
    
    ofstr << (arr[q.back()] > arr[q.front()] ? arr[q.back()] : arr[q.front()]) << std::endl;
}

int main(int argc, char* argv[]){

	std::ifstream ifstr;

	if(argc != 1)
		ifstr.open(argv[1]);
	else 
		ifstr.open("input01.txt");

	std::ofstream ofstr("test_output01.txt");

	int t;
	ifstr >> t;

	while(t > 0) {
		int n,k;

		ifstr >> n >> k;
		int i;
    		int arr[n];
	    	for(i=0;i<n;i++)
      			ifstr  >> arr[i];
		std::cout << '*';
		printKMax(arr, n, k, ofstr);
    		t--;
  	}
	std::cout << "\n";
  	return 0;
}
