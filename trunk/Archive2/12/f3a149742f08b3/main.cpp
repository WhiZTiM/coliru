double fun (double (*function)(double)) {
    return function(1);
}

double test (double d) {
    return d;
}

int main () {
    fun(test);
}
