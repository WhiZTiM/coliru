cat>input.txt<<JSON; g++ -std=c++11 -Os -Wall -pedantic main.cpp  && ./a.out
{
    "Foo": {
        "nameofFoo": "foofoo",
        "Bar": [{
            "BarFoo": {
                "BarFooDeep": {
                    "BarFooDeepDeep": {
                        "BarFooValue1": 123,
                        "BarFooValue2": 456
                    }
                }
            },
            "FooBar": [{
                "FooBarDeep0": [{
                    "FooBarDeepDeep1": [{
                        "FooBarValue1": "ineedthis1",
                        "FooBarValue2": "andthis1"
                    }],
                    "FooBarDeepDeep2": [{
                        "FooBarValue1": "ineedthis2",
                        "FooBarValue2": "andthis2"
                    }]
                },
                {
                    "FooBarDeepDeep3": [{
                        "FooBarValue1": "ineedthis3",
                        "FooBarValue2": "andthis3"
                    }],
                    "FooBarDeepDeep4": [{
                        "FooBarValue1": "ineedthis4",
                        "FooBarValue2": "andthis4"
                    }]
                }],
                "FooBarDeep1": [{
                    "FooBarDeepDeep6": [{
                        "FooBarValue1": "ineedthis6",
                        "FooBarValue2": "andthis6"
                    }],
                    "FooBarDeepDeep7": [{
                        "FooBarValue1": "ineedthis7",
                        "FooBarValue2": "andthis7"
                    }]
                },
                {
                    "FooBarDeepDeep8": [{
                        "FooBarValue1": "ineedthis8",
                        "FooBarValue2": "andthis8"
                    }],
                    "FooBarDeepDeep9": [{
                        "FooBarValue1": "ineedthis9",
                        "FooBarValue2": "andthis9"
                    }]
                }]
            }]
        }]
    }
}
JSON