#include <iostream>
#include <deque> 
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
using namespace std;

//#define DEBUG
    
void printKMaxVec(int arr[], int n, int k, std::ofstream& ofstr){
    
    std::vector<int> q;
    
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
            q.erase(q.begin());
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

template <template <typename, typename...> class Container, typename T>
void printKMax(int arr[], int n, int k, std::ofstream& ofstr){
    
    Container<T> q;
    
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

	std::chrono::duration<double> total_duration, total_duration_vector, total_duration_list;

	std::ifstream ifstr;
	std::ofstream ofstr("test_output01.txt");
	std::ofstream ofstr_vec("test_vec_output01.txt");
	std::ofstream ofstr_list("test_list_output01.txt");

	if(argc != 1)
		ifstr.open(argv[1]);
	else 
		ifstr.open("input01.txt");

	int t; // number of test cases
	ifstr >> t;

	while(t > 0) {
		int n,k;
		ifstr >> n >> k;
		int i;
    		int arr[n];
	    	for(i=0;i<n;i++)
      			ifstr  >> arr[i];
		
		/////////////////////////////////////////////
		// Test Deque
		auto start = std::chrono::system_clock::now();
		printKMax<std::deque,int>(arr, n, k, ofstr);
		auto end = std::chrono::system_clock::now();
		
		total_duration+=end-start;
		
		/////////////////////////////////////////////
		// Test Vector
		start = std::chrono::system_clock::now();
		printKMaxVec(arr, n, k, ofstr_vec);
		end = std::chrono::system_clock::now();

		total_duration_vector+=end-start;

		/////////////////////////////////////////////
		// Test List
		start = std::chrono::system_clock::now();
		printKMax<std::list,int>(arr, n, k, ofstr_list);
		end = std::chrono::system_clock::now();

		total_duration_list+=end-start;

    		t--;
  	}
	std::cout << "Total duration deque: " << total_duration.count() << " sec\n";
	std::cout << "Total duration vector: " << total_duration_vector.count() << " sec\n";
	std::cout << "Total duration list: " << total_duration_list.count() << " sec\n";

  	return 0;
}
