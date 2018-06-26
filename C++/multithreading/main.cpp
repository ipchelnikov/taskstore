#include <iostream>
#include <string>
#include <deque>
#include <thread>
#include <chrono>
#include <future>
#include <random>

// Prints in strings to out by 10

int main(int argc, char* argv[])
{
	std::random_device r;
	std::default_random_engine rd_eng(r());
	std::uniform_int_distribution<int> uniform_dist(1, 100);

	std::deque<std::string> str_deq;
	std::mutex str_deq_mutex;

	std::thread printing_thread([&]
	{
		while( true )
		{
			int deq_size = 0;
			{
				std::lock_guard<std::mutex> g(str_deq_mutex);
				deq_size = str_deq.size();
			}
			if(deq_size >= 10)
			{
				bool is_empty = true;
				do {
					std::lock_guard<std::mutex> g(str_deq_mutex);
					std::cout << "size:" << str_deq.size() << "\tpop val: "<< str_deq.front() << std::endl;
					str_deq.pop_front();
					is_empty = str_deq.empty();
				}
				while (!is_empty);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(uniform_dist(rd_eng)));
	});

	std::function<void(int)> f = ([&] (int count) {
	while(true)
	{
		std::string instr =  std::to_string(count++);
		std::this_thread::sleep_for(std::chrono::milliseconds(uniform_dist(rd_eng)));
		std::lock_guard<std::mutex> guard(str_deq_mutex);
		str_deq.push_back(instr);
	}});

	std::thread getting_thread(f, 10000);
	std::thread getting_thread2(f, 40000);
	
	printing_thread.join();
	getting_thread.join();
	getting_thread2.join();

	return 0;
}
