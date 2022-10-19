# Principles of OOP



- [Introduction](#Introduction)
- [The Principles](#The-Principles)
    1. [Encapsulation](#Encapsulation)
    2. [Abstraction](#Abstraction)
    3. [Inheritance](#Inheritance)
    4. [Polymorphism](#Polymorphism)



## Introduction

The fundamental principles of good software engineering are

1. separating interface from implementation
2. hiding implementation details

These principles form the very foundation of the Object Oriented paradigm. Some of the advantages of adopting Object-Oriented paradigm of development are:

- greater productivity, better quality of software and lesser maintenance cost.
- concepts like inheritance, eliminate redundant code and extend the use of existing classes resulting in better **software reusability**.
- encapsulation and abstraction help maintain an internal state, only accessible via public interface, hence ensuring a **simplified interface** description and **data security**.

## The Principles

The object oriented programming stands on four pillars namely encapsulation, abstraction, inheritance and polymorphism. Although these concepts may somehow be enforced in other programming paradigms, however OOP is specifically designed to enforce these concepts through basic building blocks: classes and objects.

### Encapsulation

Encapsulation is achieved when each object keeps its state **private**, inside a class. Other objects don’t have direct access to this state.  Instead, they can only call a list of public functions — called methods.

So, the object manages its own state via methods — and no other class  can touch it unless explicitly allowed. If you want to communicate with  the object, you should use the methods provided. But (by default), you  can’t change the state.

![Encapsulation Diagram](/home/adeel/workspace/learn/cxx/cpp-oop/assets/encap_cat_bg.png)



### Abstraction

Abstraction can be thought of as a natural extension of encapsulation. Applying abstraction means that each object should **only** expose a high-level mechanism for using it. This mechanism should hide internal implementation details. It should only reveal operations relevant for the other objects.

![Abstraction](/home/adeel/workspace/learn/cxx/cpp-oop/assets/abstract_phone_bg.png)



### Inheritance

Inheritance is the ability of one object to acquire some/all properties of another object. For example, a child inherits the traits of his/her parents.  With inheritance, **re-usability** is a major advantage.

Objects are often very similar and share common logic. But they’re not **entirely** the same. So how do we **reuse** the common logic and extract the unique logic into a separate class? One way to achieve this is **inheritance**. It means that you create a (child) class by deriving from another (parent) class. This way, we form a hierarchy. The child class reuses all fields and methods of the parent class (common part) and can implement its own (unique part).

![Inheritance Diagram](/home/adeel/workspace/learn/cxx/cpp-oop/assets/inherit_person_bg.png)



### Polymorphism

Polymorphism means designing objects to **share behaviors**. Using inheritance, objects can override shared parent behaviors, with  specific child behaviors. Polymorphism allows the same method to execute different behaviors in two ways: method overriding and method  overloading.

Runtime polymorphism uses method overriding. In method overriding, a  child class can provide a different implementation than its parent  class.

When we think about classes, we assume that programs will create objects of that type. However, there are cases in which it’s useful to define classes from which you never intend to instantiate any objects. Such classes are called **abstract classes**. An abstract class provides a base class from which other classes can inherit. Derived classes, called **concrete classes**, can be used to instantiate objects and define every member function they declare.

When a base class pointer to a derived class object calls a function, it always executes the base class function. But if the function is defined as `virtual` in the base class, then the overridden copy in the respective derived class is called.  

>With virtual functions, the type of the object being pointed to, not the type of the handle, determines which version of a virtual function to invoke.

Choosing the appropriate function to call at execution time (rather than at compile time) is known as **dynamic binding** or **late binding**.

Once a function is defined as `virtual` in the base class, its overridden copy in the derived class retains it's `virtual` status even if not declared explicitly.

![Polymorphism Diagram](/home/adeel/workspace/learn/cxx/cpp-oop/assets/polymorph_shape_bg.png)

[^ Top](#Principles-of-OOP)