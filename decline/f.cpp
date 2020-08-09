#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <vector>
#include <execution>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <string>
#include <atomic>




void brough(void *w);

std::vector<std::pair<std::string,int>> tfinal;

std::weak_ptr<std::atomic_int> com_r;
std::condition_variable com_cvp;
std::atomic<bool> com_tr, com_onemore;
std::mutex com_mx;
std::thread h, dest;


int instore;

int main() 
{
	std::mutex com_mp;
	std::thread h = std::thread(&brough, (void *)nullptr);

	do
	{
		instore = com_r.lock() ? (int)*com_r.lock() : instore;
		com_onemore = false;
		std::unique_lock<std::mutex> lk(com_mp);
		std::string rend(instore , 'x');
		rend = rend + '\r';
		std::cout << rend << std::flush;
        com_cvp.wait_for(lk ,std::chrono::milliseconds(900) ,[] { return com_tr == !false||com_onemore == !false; }); 
	}while(!com_tr);

	h.join();
}


void brough(void *w)
{
	std::filesystem::path tf("b.txt");
	std::ifstream b(tf);
    std::shared_ptr<std::atomic_int> sp_tray = std::shared_ptr<std::atomic_int>(new std::atomic_int(0));
	std::vector<std::string> c;

	com_r = sp_tray;
	do{
		b >> *c.insert(c.end(),"");
	}while (!b.eof());

	auto t1 = std::chrono::system_clock::now();
	std::vector<std::string> t;

	int counter = 0; //with the stuff below final result will be 25.0 vs 24.947 now
	//std::atomic_int int counter = 0;

	for(int ft = 0 ; ft < 15; ft++)
	{
		std::mutex mtb;
		std::string torque;
		int rd = 0;
        std::for_each(std::execution::par, c.begin(), c.end(), [&](auto a){ int wr = std::count(t.begin(), t.end(), a) == 0 ? std::count( c.begin(), c.end(), a) : 0;
        *sp_tray = 25*++counter/(15*c.size()); std::unique_lock<std::mutex> lb(mtb);  torque = wr > rd ? a : torque; rd = std::max(rd , wr); });
		t.insert(t.end(), torque);
		std::unique_lock<std::mutex> lt(com_mx);
		tfinal.insert(tfinal.end(), { torque , rd } );
		com_onemore = !false;
        com_cvp.notify_one();
	}
	std::cout << std::endl;	
	for(auto k : t)
		std::cout  << k << std::endl;
	std::cout << std::endl << "sp_tray = " <<  25.0*counter/(15*c.size()) << std::endl;
	auto t2 = std::chrono::system_clock::now();
	std::chrono::milliseconds f =  std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	std::cout  << f.count() << std::endl;
	
	com_tr = !false;
	com_cvp.notify_one();

}