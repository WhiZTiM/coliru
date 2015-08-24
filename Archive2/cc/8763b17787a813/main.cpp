
#include <stdio.h>

struct Animal {
    void (*jump)(Animal *self);
};

void Animal_Jump(Animal *self) {
    self->jump(self);
}

struct Cat {
    struct Animal animal;
    int val_unique_to_cat;
};

Animal * Cat_AsAnimal(Cat *self) { return (Animal *)self; }
Cat * Animal_AsCat(Animal *self) { return (Cat *)self; }

void Cat_Jump(Animal *self) {
    Cat *cat_self = Animal_AsCat(self);
    printf("Cat jumped %d meters!\n", cat_self->val_unique_to_cat);
}

void Cat_Init(Cat *self) {
    self->animal.jump = Cat_Jump;
    self->val_unique_to_cat = 10;
}

struct Dog {
    struct Animal animal;
    double val_unique_to_dog;
};

Animal * Dog_AsAnimal(Dog *self) { return (Animal *)self; }
Dog * Animal_AsDog(Animal *self) { return (Dog *)self; }

void Dog_Jump(Animal *self) {
    Dog *dog_self = Animal_AsDog(self);
    printf("Dog jumped %f feet!\n", dog_self->val_unique_to_dog);
}

void Dog_Init(Dog *self) {
    self->animal.jump = Dog_Jump;
    self->val_unique_to_dog = 5.6;
}

int main() {
    Cat cat;
    Dog dog;
    int x;
    
    Cat_Init(&cat);
    Dog_Init(&dog);
    
    Animal_Jump(Cat_AsAnimal(&cat));
    Animal_Jump(Dog_AsAnimal(&dog));
    Animal_Jump(Cat_AsAnimal(&x));
}