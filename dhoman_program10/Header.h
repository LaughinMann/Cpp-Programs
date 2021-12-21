#include <string>

using namespace std;

class ContestResult {
private:
	string winner = "";
	string secondPlace = "";
	string thirdPlace = "";
public:
	void setWinner(string winner);
	void setSecondPlace(string second);
	void setThirdPlace(string second);
	string getWinner();
	string getSecondPlace();
	string getThirdPlace();
};