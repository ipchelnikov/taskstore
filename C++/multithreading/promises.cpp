#include <chrono>
#include <iostream>
#include <future>
#include <thread>

int main() {

	std::promise<int> prom;

	std::future<int> fut = prom.get_future();

	std::thread th(([](std::promise<int> p) {
				std::this_thread::sleep_for(std::chrono::seconds(10));
				p.set_value(1);
			}), std::move(prom));

	while(fut.wait_for(std::chrono::milliseconds(500)) != std::future_status::ready)
		std::cout << "waiting..." << std::endl;

	std::cout << fut.get() << std::endl;

	th.join();
	return 0;
}
