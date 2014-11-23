/*
https://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

解：
只要找到所有上升过程的两个值，累积高低值的差即可满足题目
现实生活中的股票买卖肯定达不到如此高的收效
因为我的算法是“事后诸葛亮”
*/

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
