#include <iostream>
#include <climits>
#include <cassert>

using std::endl;
using std::cout;
using std::cin;


class Solution {
public:
	/**
	 The main goal:
	 ( dividend >= x * divisor && dividend < (x + 1) * divisor )
	|| (dividend >= x * divisor && (x + 1) * divisor will overflow )

	 the main algo:
	 x = 2**i1 + 2**i2 + 2**i3
	*/
    int divide(int dividend, int divisor) {
        if(dividend == -INT_MAX-1 && divisor == -1) {
            return INT_MAX;
        }
        if(divisor == 0) {
            throw std::invalid_argument( "divisor is 0" );
        }

        
        bool nega = false;
        if(divisor > 0) {
            nega = !nega;
            divisor = -divisor;
        }
        if(dividend > 0) {
            nega = !nega;
            dividend = -dividend;
        }
        
		// pre-condition: divisor < 0 && dividend <= 0
        int i = 0;;
        int sum = 0;
        int gap = dividend - sum;
        while(gap < 0) { // (sum > dividend) != (gap < 0)
			assert(gap < 0);
            int c = 0;
			// if(divisor << c > 0): c make divisor overflow, choose last
            while((divisor << c) > gap && (divisor << c) < 0) {
                c++;
            }
			// divisor < gap, add last divisor and exit
			if(c == 0) {
				c++;
			}
			// may overflow
            sum += (divisor << (c-1));
            i += (1 << (c-1));
			// the gap will always valid even though sum may overflow
            gap = dividend - sum;
        }
        if(sum == dividend) {
            return nega ? -i : i;
        }
        return nega ? -(i - 1) : i - 1;
    }
    
};


int main(int argc, char *argv[]){
	Solution s;
	int dividend, divisor;
	
	while(cin >> dividend >> divisor) {
		cout << s.divide(dividend, divisor) << endl;
	}
	return 0;
}

