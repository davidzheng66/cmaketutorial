#include <iostream>
#include <cmaketutorial_config.h>

#ifdef USE_ADDER
	#include <adder.hpp>
#endif

int main(int argc, char* argv[]){
	std::cout << argv[0] << " Version " << CMAKETUTORIAL_VERSION_MAJOR << "." << CMAKETUTORIAL_VERSION_MINOR << std::endl;
	std::cout << "Hello World!!!" << std::endl;
#ifdef USE_ADDER
    std::cout << "Using Adder lib" << std::endl;
	std::cout << add(10.0, 20.0) << std::endl;
#else
	std::cout << "Not Using Adder lib" << std::endl;
#endif
}	