

5a

Because new_size has been used without being initialized or assigned a value, the behavior of the program is undefined. If you compile this code with -Wall, you should get a helpful warning.

Any compiler is within its rights to produce coherent output, but it's also within its rights to not run the code at all.



5b

We cannot determine what the code will do when its run. The insertion statement dereferences v[i], an address at which a value has not been set. This is undefined behavior, and as such any behavior is permitted by the C++ standard.

Say the array was value-initialized:

    int*v = new int[N]();

Then every element would be initialized to 0. Then we can say this code has determinate behavior: It will run in an infinite loop, printing "the third element is 0" every time. This happens because the programmer used the assignment operator (=) instead of the comparison operator (==).

Some programmer prefer to put the literal as the left-hand side argument, so the compiler will emit an error if they accidentally try to assign:

if (3 = i) // Error

And lastly the user has a memory leak by not calling delete[] v at the end of the block.

The code should print 4 5 5

The mistake in the code is the programmer did "delete v" instead of "delete[] v"