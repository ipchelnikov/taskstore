#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <future>

class LargeClass
{
	int* i;
public:
	LargeClass() : i(new int(1)) {
		std::cout << "Large class created" << std::endl;
	}
	
	~LargeClass() {
		std::cout << "Large class deleted" << std::endl;
		delete i;
	}
	
	void func() {
		std::cout << "i = " << *i << std::endl;
		std::cout << "Large class func" << std::endl;
	}

};

std::unique_ptr<LargeClass, std::function<void(LargeClass*)>>
f_uniq (std::unique_ptr<LargeClass, std::function<void(LargeClass*)>> u) {
	return std::move(u);
}

int main(int argc, char const *argv[]) {
	
	std::function<void(std::shared_ptr<LargeClass>)>fn = ([&] (std::shared_ptr<LargeClass> sp) {
			//std::cout << "sp.use_count() " <<  sp.use_count() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1)); 
			if (sp.use_count() <= 10)
				fn(sp);
		});
	
	auto p = std::make_shared<LargeClass> ();
	std::weak_ptr<LargeClass> wl = p;
	
	std::thread tr([] (std::weak_ptr<LargeClass> wp) {
				while(true) {
					
					if (auto sp = wp.lock()) {
						std::cout << "ok, locked. Count " << sp.use_count() <<  std::endl;
					} else {
						std::cout << "No, no object to lock" << std::endl;
						break;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
				}, std::weak_ptr<LargeClass>(wl));

	fn(std::move(p));
	
	tr.join();
	return 0;
}
