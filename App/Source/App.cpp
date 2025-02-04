#include <iostream>
#include <array>
#include <dlfcn.h>


int main() {

	void* bingoEngine = dlopen("./bingoengine.so", RTLD_LAZY);
	if (!bingoEngine)
		std::cout << "Failed to load the lib.\n";
	else
		std::cout << "Load the lib!\n";


	//typedef void (*signature1)();
	//typedef void (*signature2)(int);
	//typedef std::array<int, 15> (*signature3)();

	//void (*newCardPtr)();
	//void (*checkNumPtr)(int);
	//std::array<int, 15> (*getCrdPtr)();
	//int (*addPtr)(int);




	//void* ptr0 = dlsym(bingoEngine, "increase_num");
	



	auto ptr0 = dlsym(bingoEngine, "StartCredits");
	auto error0 = dlerror();
	if (error0) {
		std::cerr << "Error (when loading the symbol `func0`): " << error0 << std::endl;
	}
	dlerror();
	
	typedef void (*ptrType0)(int);
	ptrType0 startCreditsPtr = reinterpret_cast<ptrType0>(reinterpret_cast<long>(ptr0));

	if (startCreditsPtr != nullptr)
		std::cout << "Load the func0!\n";



	
	auto ptr1 = dlsym(bingoEngine, "NewCard");
	auto error1 = dlerror();
	if (error1) {
		std::cerr << "Error (when loading the symbol `func1`): " << error1 << std::endl;
	}
	dlerror();

	typedef void (*ptrType1)();
	ptrType1 newCardPtr = reinterpret_cast<ptrType1>(reinterpret_cast<long>(ptr1));

	if (newCardPtr != nullptr)
		std::cout << "Load the func1!\n";
	


	auto ptr2 = dlsym(bingoEngine, "CheckNumber");
	auto error2 = dlerror();
	if (error2) {
		std::cerr << "Error (when loading the symbol `func2`): " << error2 << std::endl;
	}
	dlerror();

	typedef void (*ptrType2)(int);
	ptrType2 checkNumberPtr = reinterpret_cast<ptrType2>(reinterpret_cast<long>(ptr2));

	if (checkNumberPtr != nullptr)
		std::cout << "Load the func2!\n";



	auto ptr3 = dlsym(bingoEngine, "GetCard");
	auto error3 = dlerror();
	if (error3) {
		std::cerr << "Error (when loading the symbol `func3`): " << error3 << std::endl;
	}
	dlerror();
	
	typedef std::array<int, 15>(*ptrType3)();
	ptrType3 getCardPtr = reinterpret_cast<ptrType3>(reinterpret_cast<long>(ptr3));

	if (getCardPtr != nullptr)
		std::cout << "Load the func3!\n";



	//void* ptr1 = dlsym(bingoEngine, "NewCard");
	//if (!ptr1)
	//	std::cout << "Failed to load the func1.\n";
	//else
	//	newCardPtr = reinterpret_cast<signature1>(ptr1);
	//if (!newCardPtr)
	//	std::cout << "Failed to load the func1 satge 2.\n";

	//void* ptr2 = dlsym(bingoEngine, "CheckNumber");
	//if (!ptr2)
	//	std::cout << "Failed to load the func2.\n";
	//else
	//	checkNumPtr= reinterpret_cast<signature2>(ptr2);

	//void* ptr3 = dlsym(bingoEngine, "GetCard");
	//if (!ptr3)
	//	std::cout << "Failed to load the func3.\n";
	//else
	//	getCrdPtr = reinterpret_cast<signature3>(ptr3);





	char input = '\0';
	int addedCredits = 0;
	std::cout << "Add credits? (number)\n";
	std::cin >> addedCredits;
	startCreditsPtr(addedCredits);

	std::cout << "Generate card? (y)\n";
	std::cin >> input;
	if (input == 'y')
	{
		newCardPtr();

		std::cout << "Check card? (y)\n";
		std::cin >> input;

		if (input == 'y')
		{
			std::array<int, 15> myArray;
			myArray = getCardPtr();

			for (int element : myArray) {
				std::cout << "CardElement: " << element << "\n";
			}

			int hitNum = 0;
			std::cout << "Hit number? (num)\n";
			std::cin >> hitNum;
			checkNumberPtr(hitNum);

			std::cout << "Check card? (y)\n";
			std::cin >> input;
			if (input == 'y')
			{
				std::array<int, 15> myArray2;
				myArray2 = getCardPtr();

				for (int element : myArray2) {
					std::cout << "CardElement: " << element << "\n";
				}

			}


		}

	}


	std::cout << "Play again? (y/n)\n";
	std::cin >> input;



	dlclose(bingoEngine);
}
