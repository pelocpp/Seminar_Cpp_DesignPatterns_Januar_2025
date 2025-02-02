// =====================================================================================
// LValue / RValue
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <print>


namespace LValueRValue {

    // lvalue reference
    static void sayHello(std::string& message) {
        std::println("sayHello [std::string&]:  {}", message);
    }

    // rvalue reference
    static void sayHello(std::string&& message) {
        std::println("sayHello [std::string&&]: {}", message);

        std::string copy = std::move(message);

    }

    static void test01() {

        std::string a = "Hello";
        std::string b = " World";
       // std::string tmp =  a + b;

        sayHello( std::move( a ) );

       //  std::move:: Wann ist  std::move eine Option

        sayHello(a + b);  // temp. Objekt // Objekt OHNE Namen

        a.append("fsdfsd");
    }

    // -------------------------------------------------------------------

    static void helper(std::string&& message) {

        sayHello(message);
        // sayHello(std::move(message));    // casting an lvalue to an rvalue
    }

    static void test02() {

        helper(std::string("Where are we going ..."));
    }

    // -------------------------------------------------------------------

    static void test03() {

        std::string s = "Hello";

        sayHello(s);
        // versus
        sayHello(std::move(s));  // casts an lvalue to an rvalue
    }

    // -------------------------------------------------------------------

    static void test04() {

        // int& i = 2;          // invalid: reference to a constant

        // int a = 2;
        // int b = 3;

        // int& k = a + b;     // invalid: reference to a temporary

        int&& i = 2;           // works: reference to a constant

        int a = 2;
        int b = 3;

        int&& k = a + b;       // works: reference to a temporary
    }
}

void main_rvalue_lvalue()
{
    using namespace LValueRValue;
    test01();
    test02();
    test03();
    test04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
