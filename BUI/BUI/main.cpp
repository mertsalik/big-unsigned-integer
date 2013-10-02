#include "CombinatorialSolution.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>


#ifndef EXTRAS_H
#define EXTRAS_H
std::string bigUnsignedToString(const BigUnsignedInteger &bui){
	return std::string(BigUnsignedIntegerWithBase(bui,10));
}

BigUnsignedInteger stringToBigUnsigned(const std::string &s){
	return BigUnsignedInteger(BigUnsignedIntegerWithBase(s,10));
}


std::ostream &operator <<(std::ostream &os, const BigUnsignedInteger &bui){
	BigUnsignedIntegerWithBase::Base base;
	long osFlags = os.flags();
	if (osFlags & os.dec)
		base = 10;
	else if (osFlags & os.hex) {
		base = 16;
		if (osFlags & os.showbase)
			os << "0x";
	} else if (osFlags & os.oct) {
		base = 8;
		if (osFlags & os.showbase)
			os << '0';
	} else
		throw "std::ostream << BigUnsigned: Could not determine the desired base from output-stream flags";
	std::string s = std::string(BigUnsignedIntegerWithBase(bui, base));
	os << s;
	return os;
}


std::string bigUnsignedWithBaseToString(const BigUnsignedIntegerWithBase &buiwb){
	std::string result = "";
	for (unsigned int i = 1; i <= buiwb.getLenght(); i++)
	{	
		std::stringstream ss;
		ss << buiwb.getElement(buiwb.getLenght()-i);
		result.append(ss.str());
		ss.clear();
	}
	return result;
}


#endif

#define TEST_MODE 1
#define ONLY_PASCAL 0
#define ONLY_COMBINATORAL 1

using namespace std;

float getCalculationTime(clock_t clock_end,clock_t clock_start){
	float diff = ((float)clock_end - (float)clock_start);
	float seconds = diff / CLOCKS_PER_SEC;
	return seconds;
}

int main(int argc, char *argv[]){

	if (argc < 3 && !TEST_MODE) { 
		std::cerr << "Usage: ./executable_name n(int) k(int)" << std::endl;
		return 1;
	}else if(argc == 3 || TEST_MODE){
		std::vector<std::string> params;
		if(TEST_MODE){
			params.push_back("BigUnsignedIntegerExecutable.exe");
			params.push_back("200");
			params.push_back("4");
		}else{
			std::vector<std::string> console_params(argv, argv+argc);
			params = console_params;
		}



		// max
		BigUnsignedInteger n = stringToBigUnsigned(params[1]);
		// selection
		BigUnsignedInteger k = stringToBigUnsigned(params[2]);


		clock_t clock_start, clock_end;

		ofstream outputFile;

		//*******************************************PASCAL************************************//

		if(!ONLY_COMBINATORAL){
			clock_start = clock();

			PascalsTriangle pAlgorithm;
			pAlgorithm.Calculate(n);
			/**
			PASCAL OUTPUT
			*/
			string selectionKey = params[1].append(" ").append(params[2]);
			
			outputFile.open("pascal.txt");
			PascalsTriangle::TriangleNodes allPascalNodes = pAlgorithm.GetCalculations();
			outputFile << "n k length" << endl;
			for(PascalsTriangle::TriangleNodes::iterator iterator = allPascalNodes.begin(); iterator != allPascalNodes.end(); iterator++) {
				outputFile << iterator->first << " ";
				if(iterator->first == selectionKey){
					outputFile << "is equal to " << BigUnsignedIntegerWithBase(iterator->second,10) << endl;
				}else
				{
					BigUnsignedIntegerWithBase temp(iterator->second,2);
					outputFile << temp.getLenght() << endl;
				}
			}
			outputFile.close();

			clock_end = clock();

			cout << "PascalsTriangle : " << getCalculationTime(clock_end,clock_start) << endl;

		}

		// *******************************************COMBINATORAL************************************//

		if(!ONLY_PASCAL){
			clock_start = clock();
			CombinatorialSolution solution;
			BigUnsignedInteger i(0),j(0);
			outputFile.open("combinatorial.txt");
			outputFile << "n k length" << endl;
			for (i=0; i <= n; i++)
			{
				for(j=0; j <= n && j<=i; j++){
					if(i == n && j == k)
						outputFile << i << " " << j << " is equal to " << solution.Choose(i,j) << endl;
					else
						outputFile << i << " " << j << " " << BigUnsignedIntegerWithBase(solution.Choose(i,j),2).getLenght() << endl;
				}
			}
			outputFile.close();	

			clock_end = clock();
		}
		cout << "CombinatorialSolution : " << getCalculationTime(clock_end,clock_start) << endl;

	}else{
		std::cerr << "Too many command arguments given!";
		return 1;
	}
	return 0;
}