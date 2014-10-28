/*
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321 

Spoilers:
Have you thought about this? 
Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!

If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.

Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?

Throw an exception? Good, but what if throwing an exception is not an option? You would then have to re-design the function (ie, add an extra parameter).

解：
按数学逻辑解法很简单，取10的余数后，依次乘10即可通过。
但是考虑的Spoilers中的情况，将程序做完善点，就需要加些参数，限制有效取值范围，比如大于2147483641的数转换会失败。
但我认为，这种回文数，还是用字符串处理最好，不用考虑取值范围的情况。
*/

#include <stdio.h>

int reverse(int x) 
{
	int positive = 1;
	if (x<0) {
		positive = -1;
		x *= positive;
	}
	int num = 10;
	int result = 0;
	while (0 != x) {
		result = result * 10;
		result = (x % 10) + result;
		x = x / 10;
		//printf("result=%d, num=%d, x=%d\n", result, num, x);
	}
	return positive*result;
}

void test()
{
	int max = 2147483642;
	for(int min = 2147483600; min < max; min++) {
		int num = min; 
		num = reverse(num);
		//printf("reverse(%010d) = %010d.\n", min, num);

		num = reverse(num);
		
		while (num%10 == 0) {
			num = num / 10;
		}
		int min_tmp = min;
		while (min_tmp%10 == 0) {
			min_tmp = min_tmp / 10;
		}
		if (num != min_tmp) {
			printf("error! reverse(%d) = %d.\n", min, num);
			//return;
		}
	}
}

int main()
{
	int num = 0;

//	test(); return 0;

	num = 0;
	printf("num=%d\n",num);
	printf("%d\n", reverse(num));
	printf("%d\n", reverse(-1 * num));

	num = 1;
	printf("num=%d\n",num);
	printf("%d\n", reverse(num));
	printf("%d\n", reverse(-1 * num));

	num = 999;
	printf("num=%d\n",num);
	printf("%d\n", reverse(num));
	printf("%d\n", reverse(-1 * num));

	num = 123456789;
	printf("num=%d\n",num);
	printf("%d\n", reverse(num));
	printf("%d\n", reverse(-1 * num));

	// 只要转换后的数值超过 0111 1111 1111 1111    1111 1111 1111 1111 时肯定会发生举出
	// 所以最好的办法是增加一个参数， 表示可以正确进行处理的最大值
	num = 2147483647;
	printf("num=%d\n",num);
	printf("%d\n", reverse(num));
	printf("%d\n", reverse(-1 * num));

	num = 2147483641;
	printf("num=%d\n",num);
	printf("%d\n", reverse(num));
	printf("%d\n", reverse(-1 * num));


}
