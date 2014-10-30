#include <vector>
#include <stdio.h>

using namespace std;

int maxProfit(vector<int> &prices) 
{
	int min = 0;
	int max = 0;
	bool want_buy = true;
	int result = 0;

    if (prices.size() < 2) {
		return result;
	}

	min = prices[0];
	for (vector<int>::iterator it = prices.begin();
		it != prices.end();
		++it) {
		if (want_buy) {
			if (min >= *it) {
				min = *it;
			}
			else {
				max = *it;
				want_buy = false;
			}
		}
		else {
			if (max <= *it) {
				max = *it;
			}
			else {
				result += (max - min);
				min = *it;
				want_buy = true;
			}
		}
	}
	if (!want_buy) {
		result += (max- min);
	}
	return result;
}

int main()
{
	vector<int> prices;

	prices.push_back(3);
	prices.push_back(33);
	prices.push_back(93);
	prices.push_back(64);
	prices.push_back(43);
	prices.push_back(93);
	prices.push_back(65);
	prices.push_back(77);

    printf("maxProfit=%d\n", maxProfit(prices));
}
