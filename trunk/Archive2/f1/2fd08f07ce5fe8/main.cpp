g(obj x) {
    if (something(x)) {
        return x; //base case
    }
    x.val += 1 //x[0] is of 
    g(x.child) //x.child is of type "obj" 
}

g(obj x) {
    while (true) {
        if (something(x)) {
            return x; // base case
        }
        x.val += 1
        x = x.child
    }
}