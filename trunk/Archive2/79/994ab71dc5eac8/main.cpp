g(obj x) { 
    x.val += 1 //x[0] is of 
    g(x.child) //x.child is of type "obj" 
}

g(obj x) {
    while (true) {
        x.val += 1
        x = g_helper(x.child);
    }
}