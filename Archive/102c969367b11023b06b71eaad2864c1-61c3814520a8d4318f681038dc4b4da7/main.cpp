class MyClass {
    MyClass();                                // Default ctor
	MyClass(int a_param);                     // Ctor
	
	MyClass(MyClass& other);                  // Copy ctor
	MyClass(const MyClass& other);            // Copy ctor
	
	MyClass(MyClass&& other);                 // Move ctor
	
	MyClass& operator=(MyClass& other);       // Copy assignment op
	MyClass& operator=(const MyClass& other); // Copy assignment op
	MyClass& operator=(MyClass&& other);      // Move assignment op
	
	~MyClass();                               // Dtor
};