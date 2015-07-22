from functools import wraps
# a decorator

# takes a function as a parameter
def first(function):
    # and returns another function
    @wraps(function)
    def wrapped(*args, **kwargs):
        print('Hello World!')
        # delegate over to the wrapped function
        return function(*args, **kwargs)
    
    # return the function
    return wrapped

@first
def cool():
    print('ye')

cool() # calls the wrapped function and then the actual function