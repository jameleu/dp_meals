#ifndef DEALS_H
#define DEALS_H

#include <iostream>
#include <vector>
#include <functional>
#include <limits>

using namespace std;

// This is a type synonym.
using cost = long long;

// How much you pay for a discounted (25% off) meal.
cost discounted(cost full_price) {
    return full_price * 3 / 4;
}
cost sum_prev_meals(size_t j, const std::vector<cost> &prices) { 
    cost sum = 0;
    for(size_t i = 0; i < j + 1; ++ i) {
        sum += prices[i];
    }
    return sum;
}

cost best_price(const std::vector<cost> &prices) {
    // TODO: put your code here
    // NOTE: if you use a bottom-up approach, initialize your table with
    // std::numeric_limits<cost>::max() / 4 ... you MUST divide by 4!
    
    //0-5 stamps
    vector<vector<cost> > memo (6, vector<cost> (prices.size(), numeric_limits<cost>::max() / 4));
    
    /*
    //for meals before 5:
    for(size_t j = 1; j < 5; ++j) {
        //first row where never use stamps until meal 5:
        memo[0][j] = discounted(prices[j]) + memo[0][j - 1];

        //ignore meals where can't use stamps for free meals. just automatically assume used discount until
        //get to point where have choice between stamp and discount again:
        //(is diagonal of full prices in hint):
        memo[j][j - 1] = sum_prev_meals(j, prices);
    }
    memo[5][4] = sum_prev_meals(j, prices);*/
    for (size_t j = 0; j < prices.size(); ++j) { //meal #
        for (size_t i = 0; i < 6; ++i) { //stamps: have 0 to 5 stamps
            if(j <= 4 && j == i - 1) {
                //ignore meals where can't use stamps for free meals. just automatically assume used discount until
                //get to point where have choice between stamp and discount again:
                //(is diagonal of full prices in hint):
                if(i == 1 && j == 0) {
                    memo[1][0] = prices[0]; //base case
                    break;
                }
                memo[i][j] = sum_prev_meals(j, prices);
                break;
            }
            else {
                //j > 3 since that is when on 5th meal and can have 5 stamps to consider using it 
                if(i == 0 && j > 4) {
                    memo[i][j] = min(discounted(prices[j]) + memo[i][j - 1], memo[5][j - 1]); 
                    //^discounted or use 5 stamps for free
                }
                else if(i == 0) {
                    if(j == 0 && i == 0) {
                        memo[0][0] = discounted(prices[0]);
                        continue; //base case
                    }
                    memo[i][j] = discounted(prices[j]) + memo[i][j - 1];
                }
                else {
                    //i - 1 will never be out of bounds (negative) because of above if and else if statements
                    memo[i][j] = min(discounted(prices[j]) + memo[i][j - 1], prices[j] + memo[i - 1][j - 1]);
                    //^discount or pay full and gain stamp
                }
            }
        }
    }
    return memo[0].back();
    
    /* NOTE: This return value will give you additional tips on the AG.
       It will cost you a submit, but if you are stuck, feel free to use it.
       We encourage you to attempt the problem on your own before using this
       as it is good practice for the final exam! 
    return -281;*/
}

#endif
