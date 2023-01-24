


# Demystified Object-Oriented Programming with C++

<a href="https://www.packtpub.com/product/demystified-object-oriented-programming-with-c/9781839218835?utm_source=github&utm_medium=repository&utm_campaign=9781839218835"><img src="https://static.packt-cdn.com/products/9781839218835/cover/smaller" alt="Demystified Object-Oriented Programming with C++" height="256px" align="right"></a>

This is the code repository for [Demystified Object-Oriented Programming with C++](https://www.packtpub.com/product/demystified-object-oriented-programming-with-c/9781839218835?utm_source=github&utm_medium=repository&utm_campaign=9781839218835), published by Packt.

**Implement proven object-oriented design principles to write better code and create robust software**

## What is this book about?
While object-oriented software design helps you write more easily maintainable code, companies choose C++ as an OO language for its speed. Object-oriented programming (OOP) in C++ is not automatic – understanding OO concepts and how they map to C++ language features as well as OOP techniques is crucial. You must also know how to distinguish your code by utilizing well-tested, creative solutions, which can be found in popular design patterns. This book will help you to harness OOP in C++ for writing better code. 

This book covers the following exciting features:
* * Quickly learn the building blocks needed to develop a base for essential OOP features in C++
* * Implement OO designs using both C++ language features and proven programming techniques
* * Understand how well-designed, encapsulated code helps make more easily maintainable software
* * Write robust C++ code that can handle programming exceptions
* * Design extensible and generic code using templates
Apply operator overloading, utilize STL, and perform OO component testing
Examine popular design patterns to provide creative solutions for typical OO problems

If you feel this book is for you, get your [copy](https://www.amazon.com/dp/1839218835) today!

<a href="https://www.packtpub.com/?utm_source=github&utm_medium=banner&utm_campaign=GitHubBanner"><img src="https://raw.githubusercontent.com/PacktPublishing/GitHub/master/GitHub.png" 
alt="https://www.packtpub.com/" border="5" /></a>

## Instructions and Navigations
All of the code is organized into folders. For example, Chapter02.

The code will look like the following:
```
class Singleton
{
protected:
    static Singleton *theInstance;
    static SingletonDestroyer destroyer;
protected:
    Singleton() {}
    Singleton(const Singleton &) = delete; // disallow copies
    Singleton &operator=(const Singleton &) = delete; // disallow assignment
    friend class SingletonDestroyer;  // the two classes are tightly coupled
    virtual ~Singleton() { cout << "Singleton destructor" << endl; }  // virtual because we'll inherit from Singleton
};

```

**Following is what you need for this book:**
Whether you are a professional programmer or an adept college student looking to use C++ as an OOP language, this book will help you create robust and easily maintainable code. Programmers who want to master the implementation of OO designs through both C++ language features and refined implementation techniques will find the book useful. This OOP book assumes prior programming experience; however, if you have no prior C++ or basic C++ experience, the early chapters will help you learn the core building blocks that set the foundation for the many OOP sections, advanced features, and design patterns.

With the following software and hardware list you can run all code files present in the book (Chapter 1-20).
### Software and Hardware List
| Chapter | Software required | OS required |
| -------- | ------------------------------------ | ----------------------------------- |
| 1 | C++ compiler | Windows, Mac OS X, and Linux (Any) |

We also provide a PDF file that has color images of the screenshots/diagrams used in this book. [Click here to download it](https://static.packt-cdn.com/downloads/9781839218835_ColorImages.pdf).

##Code in Action
Please visit the following to check the CiA vides: https://bit.ly/2P1UXlI

### Related products
* C++ High Performance - Second Edition [[Packt]](https://www.packtpub.com/product/c-high-performance-second-edition/9781839216541?utm_source=github&utm_medium=repository&utm_campaign=9781839216541) [[Amazon]](https://www.amazon.com/dp/1839216549)

* Modern C++ Programming Cookbook - Second Edition [[Packt]](https://www.packtpub.com/product/modern-c-programming-cookbook-second-edition/9781800208988?utm_source=github&utm_medium=repository&utm_campaign=9781800208988) [[Amazon]](https://www.amazon.com/dp/B08GM9KKMR)

## Get to Know the Author
**Dorothy R. Kirk** has specialized in OO technologies since nearly their inception. She began as an early adopter of C++ at General Electric in R&D. After working on various projects, she was one of 10 charter members to start GE's Advanced Concepts Center to commercially utilize OO technologies. She later started her own OO Training and Consulting business, specializing in OOP using C++ and Java. She additionally programs in Python. Ms. Kirk has many OO courses and has clients spanning industries such as finance, transportation, software, embedded systems, manufacturing, and medical imaging.
Ms. Kirk earned a B.S. in Computer and Information Sciences from the University of Delaware and an M.S. in Computer Science from Temple University.
