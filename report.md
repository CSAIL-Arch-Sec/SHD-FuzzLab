
## 1-1


## 1-3

**Based on the printf result, record what are the inputs (eg. values of `mindistance` and `cost[nextnode][i]`) that cause the addition instruction to return an incorrect sum? Does the operation fail for all inputs or just specific ones?**


## 2-1

**What is your approach for finding the operands that can trigger the bug with the `add` instruction? Briefly describe it.**


## 2-3 (optional)

**Did you encounter any bugs while implementing the fuzzer? How did you handle the possibility of `add` instructions being incorrect during control flow instructions (eg. loop condition checks)?**


## 3-2

**Why does the exception handler restore `x2` after all the other registers?**


## 3-3

**Describe your design decisions for the exception handler. What does it do while trying to find the undocumented instruction? How does your exception handler communicate with the test code?**


## 3-5

**Include the hidden backdoor instruction found by your code/script in the report.**


## 3-6

**Describe your approach for finding the correct `x10` value. Does the exception handler behave differently when searching for the correct `x10` value of that instruction compared to searching for hidden instructions?**


## 3-8

**Include the correct `x10` value found by your code/script in the report.**


## 3-10 (optional)

**Did you encounter any challenges while building the code?  How did you overcome the challenges of the `add` instruction occasionally producing an incorrect result? Did you try anything that failed?**


## 4-3

**Include this flag in your report.**


## 4-5

**Include the flag leaked from the remote CPU in your report.**

