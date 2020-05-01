from enum import Enum

class Gender (Enum):
    FEMALE = 0
    MALE = 1


class Person:
    @property
    def partner(self):
        return self.__partner

    @overload
    def __init__(self, mother, father, birthyear):
        self.__mother = mother
        self.__father = father
        self.__birthyear = birthyear
    
    def __init__(self, birthyear):
        # self.__mother = mother
        # self.__father = father
        self.__birthyear = birthyear
        
    def setFather(self, father):
        self.__father = father

    def setMother(self, mother):
        self.__mother = mother

    def setPartner(self, partner):
        self.__partner = partner
        partner.__partner = self

adam = Person(0)
eve = Person(0)
adam.setPartner(eve)


people = [[adam, eve]]

print(adam.partner == eve)
print(eve.partner == adam)

for year in range(0, 2020):
    for p in people:
        