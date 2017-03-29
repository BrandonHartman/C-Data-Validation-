/*

C++ Data Validation Tutorial, Implementation, and Demonstration

------------
Introduction
------------

This is a tutorial, implementation, and demonstration showing how to
perform data validation in C++. Two basic data validation techniques
are shown:

        1. repetition type-checking data validation

        2. a combination of repetition type-checking data validation
           and repetition range-checking data validation


----------------------------------
Review of Data Validation Concepts
----------------------------------

Type-checking data validation inspects a user input to see if its
value is the correct data type. For example, if the user is asked to
input a value of data type int, then their provided value would be
inspected to see if it actually is an int. Therefore, an input value
of

        7

should be accepted, whereas an input value of

        pizza

should be rejected.

Range-checking data validation inspects a user input of a known data
type to see if its value is within an acceptable (and possibly open)
range of values, or is a member of an acceptable (and possibly
infinite) set of values. For example, if the user is asked to input a
value of data type int that is within the range of 5 to 10, and if
their provided value is assumed to be an int, then this value would be
inspected to see if it actually is within the range of 5 to 10.
Therefore, an input value of

        7

should be accepted, whereas an input value of

        11

should be rejected.

Note that performing range-checking data validation without any
accompanying type-checking data validation is inherently risky, since
the ability to inspect an input value to see if is within an
acceptable range of values or a member of an acceptable set of values
is dependent on being able to get a value with the expected data type n the first place. If range-checking data validation is to be
performed, then ideally it should be preceded by type-checking data
validation. As an example, if the user is asked to input a value of
data type int that is within the range of 5 to 10, then their provided
value would be inspected to see if it actually is an int, and only if
it is would it then be further inspected to see if it actually is
within the range 5 to 10. Therefore, an input value of

        7

would first pass type-checking data validation and then pass
range-checking data validation, and should be accepted; an input value
of
11

would first pass type-checking data validation, but not pass
range-checking data validation, and should be rejected; and an input
value of

        pizza

would not pass type-checking data validation, and should be rejected
without even considering range-checking data validation.

When a program detects that invalid data has been input, it may take
various actions. The program may display an error message and halt
(so-called halting data validation); it may substitute a value of the
programmer's own choosing (so-called default data validation) and
continue; or it may repeatedly ask the user for additional input
values until a valid value is given (so-called repetition data
validation). The remainder of this tutorial as well as the C++
implementation and demonstration that follow will focus on the
repetition data validation approach.


---------------------------------
Performing Data Validation in C++
---------------------------------

In C++, type-checking data validation can be achieved through the
careful use of cin from the standard iostream library.

The typical (and perhaps naive) way to get user input is simply to use
cin along with its extraction operator (">>") and a target variable.
For example:

        int num;
        cout << "Enter a whole number: ";
        cin >> num;

However, when cin is used in this way, it is not type-safe. If the
user enters a value with a data type that is incompatible with the
data type of the target variable, then cin will:

        1. not initialize the target variable, leaving it with
           whatever value it had before, possibly uninitialized;

        2. leave the invalid input value waiting in the so-called
           input buffer, where it could adversely affect later input
           operations; and

        3. disable itself, so that it ignores all further input requests.

As an analogy, think about a situation where someone of questionable
trustworthiness asks you to take a sip from a glass of milk. Unknown
to you, however, the milk in the glass is spoiled. As a result of your
sip:

        1. your stomach doesn't get the milk it was expecting, leaving
           it containing only what it had before, possibly nothing;

        2. the spoiled milk is still in the glass, where it might
           adversely affect later drinkers; and

        3. you will likely refuse to have anything further to do with
           offers of food or drink from this person.

Performing user input in ways that are not type-safe can leave a
variable's value in an unpredictable state, which in turn can lead to
many different kinds of runtime errors and logic errors in the
program, including infinite loops.

Although we often speak of cin as if it were a statement, in reality
it is an object (of class istream). Like other objects, it has methods
(function members) that can be used to control its behavior. Among
its many methods, the cin object has three that we will find
especially helpful for type-checking data validation purposes:

        cin.good()

                This method returns the bool value true if the last
                input operation requested of the cin object was
                successful, and returns the bool value false if it was
                unsuccessful.

        cin.clear()

                If the cin object was previously disabled due to the
                failure of a requested input operation, then this
                method will re-enable the cin object.

        cin.ignore(streamsize, delim)

                This method clears the cin object's input buffer, so
                that any previous invalid value is discarded, making
                room for a newer, hopefully valid, value. It has two
                parameters, an int named streamsize and a char named
                delim. It will discard up to streamsize characters
                from the input buffer, stopping earlier if a character
                value matching delim is encountered.

Using these three methods, repetition type-checking data validation can be achieved as shown in the following algorithm:

        1. Use cin >> to attempt to get an input value whose data type
           matches the data type of the target variable.

        2. Repeat the following as long as the cin.good() method
           reports that this attempt failed:

                2A. Use the cin.clear() method to re-enable the
                    just-disabled cin object.

                2B. Use the cin.ignore() method with a streamsize
                    argument of 80 and a delim argument of a newline
                    character ('\n', i.e. the enter key) to discard
                    the invalid inputs from cin's input buffer.

                2C. Inform the user of the problem, and prompt them
                    for a replacement input value.

                2D. Use cin >> to attempt to get an input value whose
                    data type matches the data type of the target
                    variable.

        3. Return the valid user input.

A combination of repetition type-checking and repetition
range-checking data validation can be achieved as shown in the
following algorithm:

        1. Use the repetition type-checking data validation algorithm
           shown above to get an input value with a valid data type.

        2. Repeat the following as long as this input value is not
           within a given range or a member of a given set of values:

                2A. Inform the user of the problem, and prompt them
                    for a replacement input value.

                2B. Use the repetition type-checking data validation
                    algorithm shown above to get an input value with a
                    valid data type.

        3. Return the valid user input.


----------------------------------------------------------
Implementation and Demonstration of Data Validation in C++
----------------------------------------------------------

 C++ code implementing and demonstrating these repetition type-checking
and range-checking data validation concepts can be found below.

Notice that this code performs data validation for int and float
values, as well for values of an abstract data type named element,
which is simply a nickname for one of the standard primitive C++ data
types such as int, long int, float, double, char, bool, or string. In
order to use the element data type correctly, be sure to uncomment the
correct block of typedef statement and global constant declarations
shown below.


----------------
Review Questions
----------------

1. What are the two kinds of data validation covered in this tutorial?

2. What is the difference between type-checking data validation and
range-checking data validation?

3. What are the dangers of doing range-checking data validation
without preceding it with type-checking data validation?

4. Can type-checking data validation and range-checking data
validation be used together?

5. What are various responses that a program can take in response to
encountering invalid user input?

6. In C++, what is the problem with using cin extractor ("cin >>") if
the user might enter a value of the wrong data type?

7. In C++, if cin extractor encounters a user input of the wrong data
type, what will it do and/or not do?

8. In C++, if cin extractor encounters a user input of the wrong data
type, what problems can arise during the continued execution of the
program?

9. In C++, cin is not really a statement. What is it?

10. In C++, what are three methods of the cin object that can help
with the process of type-checking data validation, and what do each of
them do?

11. What algorithm can be used to implement repetition type-checking
data validation in a C++ program?

12. What algorithm can be used to implement repetition range-checking
data validation in a C++ program?

 13. Can data validation be used with abstract C++ data types such as
element?

*/


//////////////////////////////////////////////////////////////////////


#include <iostream>

using namespace std;


// the following blocks of typedef statements and global constant
// declarations are used for repetition type-checking data
// validation and repetition range-checking data validation for the
// element data type
//
// uncomment one and only one of these blocks, depending on what
// underlying primitive data type (int, long int, float, double, char,
// bool, or string) for which element is a nickname

typedef int element;
const string ELEMENT_NAME = "whole number";
const element ELEMENT_LOW = 17;
const element ELEMENT_HIGH = 52;

// typedef long int element;
// const string ELEMENT_NAME = "big whole number";
// const element ELEMENT_LOW = 17;
// const element ELEMENT_HIGH = 52;

// typedef float element;
// const string ELEMENT_NAME = "fractional number";
// const element ELEMENT_LOW = 28.6;
// const element ELEMENT_HIGH = 73.2;

// typedef double element;
// const string ELEMENT_NAME = "big fractional number";
// const element ELEMENT_LOW = 28.6;
// const element ELEMENT_HIGH = 73.2;

// typedef char element;
// const string ELEMENT_NAME = "character";
// const element ELEMENT_LOW = 'a';
// const element ELEMENT_HIGH = 'z';

// typedef bool element;
// const string ELEMENT_NAME = "boolean";
// const element ELEMENT_LOW = false;
// const element ELEMENT_HIGH = true;

// typedef string element;
// const string ELEMENT_NAME = "string";
// const element ELEMENT_LOW = "Alpha";
// const element ELEMENT_HIGH = "Omega";


//////////////////////////////////////////////////////////////////////


// prototypes for the three basic repetition type-checking data
// validation functions

int read_int();

float read_float();

element read_element();


//////////////////////////////////////////////////////////////////////


// prototype for a function which displays instructions to the user on
// how to use the repetition type-checking and repetition
// range-checking data validation demonstration

void instruct();


//////////////////////////////////////////////////////////////////////


// prototypes for the three functions that demonstrate repetition
// type-checking data validation

void demo_int_type_checking();

void demo_float_type_checking();

void demo_element_type_checking();


//////////////////////////////////////////////////////////////////////


// prototypes for the three functions that demonstrate combined
// repetition type-checking data validation and repetition
// range-checking data validation

void demo_int_type_and_range_checking();

void demo_float_type_and_range_checking();

void demo_element_type_and_range_checking();


//////////////////////////////////////////////////////////////////////


int main() {

    // tell the user how to use this program
    instruct();

    // demonstrate repetition type-checking data validation for
    // ints, floats, and elements
    demo_int_type_checking();
    demo_float_type_checking();
    demo_element_type_checking();

    // demonstrate combined repetition type-checking and
    // repetition range-checking data validation for ints, floats,
    // and elements
    demo_int_type_and_range_checking();
    demo_float_type_and_range_checking();
    demo_element_type_and_range_checking();
}


//////////////////////////////////////////////////////////////////////

int read_int() {

    // PRE:  the user must enter a series of zero or more
    //       non-valid int values, followed by a valid int value
    //
    // POST: all entered non-valid int values will be successfully
    //       discarded, and the first valid int value entered will
    //       be returned

    int userval;    // used to collect the user's input value

    // attempt to get an input value whose data type is an int
    cin >> userval;

    // repeat the following as long as this attempt failed,
    // presumably because the data type of the user's input was
    // not an int
    while (! cin.good()) {

        // re-enable the just-disabled cin object
        cin.clear();

        // from the input buffer, discard up to 80 keystrokes
        // or until the enter key is seen, whichever comes
        // first
        cin.ignore(80, '\n');

        // tell the user what happened, and to try again
        cout << "Invalid data type, should be a whole "
             << "number, try again: ";

        // attempt to get an input value whose data type is an
        // int
        cin >> userval;
    }

    // return the valid int value given by the user
    return userval;
}

float read_float() {

    // PRE:  the user must enter a series of zero or more
    //       non-valid float values, followed by a valid float
    //       value
    //
    // POST: all entered non-valid float values will be
    //       successfully discarded, and the first valid float
    //       value entered will be returned

    float userval;  // used to collect the user's input value

    // attempt to get an input value whose data type is a float
    cin >> userval;

    // repeat the following as long as this attempt failed,
    // presumably because the data type of the user's input was
    // not a float
    while (! cin.good()) {

        // re-enable the just-disabled cin object
        cin.clear();

        // from the input buffer, discard up to 80 keystrokes
        // or until the enter key is seen, whichever comes // first
        cin.ignore(80, '\n');

        // tell the user what happened, and to try again
        cout << "Invalid data type, should be a fractional "
             << "number, try again: ";

        // attempt to get an input value whose data type is a
        // float
        cin >> userval;
    }

    // return the valid float value given by the user
    return userval;
}

element read_element() {

    // PRE:  the user must enter a series of zero or more
    //       non-valid element values, followed by a valid element
    //       value
    //
    // POST: all entered non-valid element values will be
    //       successfully discarded, and the first valid element
    //       value entered will be returned

    element userval;        // used to collect the user's input
    // value

    // attempt to get an input value whose data type is an element
    //
    // the boolalpha manipulator is used in case elements are
    // bools, to allow for inputs using the keystroke sequences of
    // "true" and "false" instead of "1" and "0"
    cin >> boolalpha >> userval;

    // repeat the following as long as this attempt failed,
    // presumably because the data type of the user's input was
    // not an element
    while (! cin.good()) {

        // re-enable the just-disabled cin object
        cin.clear();

        // from the input buffer, discard up to 80 keystrokes
        // or until the enter key is seen, whichever comes
        // first
        cin.ignore(80, '\n');

        // tell the user what happened, and to try again
        cout << "Invalid data type, should be an element ("
             << ELEMENT_NAME
                << "), try again: ";

        // attempt to get an input value whose data type is
        // an element
        //
        // the boolalpha manipulator is used in case elements
        // are bools, to allow for inputs using the keystroke
        // sequences of "true" and "false" instead of "1" and
        // "0"
        cin >> boolalpha >> userval;
    }

    // return the valid element value given by the user
    return userval;
}


//////////////////////////////////////////////////////////////////////


void instruct() {

    // PRE:  none
    //
    // POST: instructions on how to use the repetition
    //       type-checking data validation and repetition
    //       range-checking data validation demonstration have
    //       been displayed to the user

    // tell the user how to use the repetition type-checking data
    // validation and repetition range-checking data validation
    // demonstration
    cout << endl
         << "Demonstration of repetition type-checking"
         << endl
         << "data validation and repetition range checking"
         << endl
         << "data validation."
         << endl
         << endl
         << "For the prompts that follow, try typing inputs"
         << endl
         << "outside of the given range, or even using a"
         << endl
         << "wrong data type."
         << endl
         << endl;
}


//////////////////////////////////////////////////////////////////////

void demo_int_type_checking() {

    // PRE:  the user must enter a series of zero or more
    //       non-valid int values, followed by a valid int value
    //
    // POST: all entered non-valid int values will be successfully
    //       discarded, and the first valid int value entered will
    //       be returned

    int userval;    // used to collect the user's input value

    // prompt the user to input an int value
    cout << "Enter a whole number: ";

    // get the user's input value in a type-safe fashion
    userval = read_int();

    // display the user's input value
    cout << "You entered "
         << userval
         << endl
         << endl;
}

void demo_float_type_checking() {

    // PRE:  the user must enter a series of zero or more
    //       non-valid float values, followed by a valid float
    //       value
    //
    // POST: all entered non-valid float values will be
    //       successfully discarded, and the first valid float
    //       value entered will be returned

    float userval;  // used to collect the user's input value

    // prompt the user to input a float value
    cout << "Enter a fractional number: ";

    // get the user's input value in a type-safe fashion
    userval = read_float();

    // display the user's input value
    cout << "You entered "
         << userval
         << endl
         << endl;
}

void demo_element_type_checking() {

    // PRE:  the user must enter a series of zero or more
    //       non-valid element values, followed by a valid element
    //       value
    //
    // POST: all entered non-valid element values will be
    //       successfully discarded, and the first valid element
    //       value entered will be returned

    element userval;        // used to collect the user's input
    // value

    // prompt the user to input an element value
    cout << "Enter an element (" << ELEMENT_NAME << "): ";

    // get the user's input value in a type-safe fashion
    userval = read_element();

    // display the user's input value
    //
    // the boolalpha manipulator is used in case elements are
    // bools, to allow for outputs to be displayed using the
    // string sequences of "true" and "false" instead of "1" a "0"
    cout << "You entered "
         << boolalpha
         << userval
         << endl
         << endl;
}


//////////////////////////////////////////////////////////////////////


void demo_int_type_and_range_checking() {

    // PRE:  the user must enter a series of zero or more values
    //       that either are not ints, or are ints but are not
    //       within the range of 6 to 37, followed by a value that
    //       is both an int and within the range of 6 to 37
    //
    // POST: all entered values that are either are not ints, or
    //       are ints but are not within the range of 6 to 37,
    //       will be successfully discarded, and the first value
    //       that is both an int and within the range of 6 to 37
    //       will be returned

    int userval;    // used to collect the user's input value

    // prompt the user to input an int value between 6 and 37
    cout << "Enter a whole number between 6 and 37: ";

    // get the user's input value in a type-safe fashion
    userval = read_int();

    // repeat the following as long as this int input value
    // is not between 6 and 37
    while ((userval < 6) || (userval > 37)) {

        // tell the user what happened, and to try again
        cout << "Invalid range, should be between 6 and 37, "
             << "try again: ";

        // get the user's input value in a type-safe fashion
        userval = read_int();
    }

    // display the user's input value
    cout << "You entered "
         << userval
         << endl
         << endl;
}

void demo_float_type_and_range_checking() {

    // PRE:  the user must enter a series of zero or more values
    //       that either are not floats, or are floats but are not
    //       within the range of 5.5 to 42.8, followed by a value
    //       that is both an float and within the range of 5.5 to
    //       42.8
    //
    // POST: all entered values that are either are not floats, or
    //       are floats but are not within the range of 5.5 to
    //       42.8, will be successfully discarded, and the first
    //       value that is both a float and within the range of
    //       5.5 to 42.8 will be returned

    float userval;  // used to collect the user's input value

    // prompt the user to input a float value between 5.5 and 42.8
    cout << "Enter a factional number between 5.5 and 42.8: ";

    // get the user's input value in a type-safe fashion
    userval = read_float();

    // repeat the following as long as this float input value
    // is not between 5.5 and 42.8
    while ((userval < 5.5) || (userval > 42.8)) {

        // tell the user what happened, and to try again
        cout << "Invalid range, should be between 5.5 and "
             << "42.8, try again: ";

        // get the user's input value in a type-safe fashion
        userval = read_float();
    }

    // display the user's input value
    cout << "You entered "
         << userval
         << endl
         << endl;
}

void demo_element_type_and_range_checking() {

    // PRE:  the user must enter a series of zero or more values
    //       that either are not elements, or are elements but are
    //       not within the range of ELEMENT_LOW to ELEMENT_HIGH,
    //       followed by a value that is both an element and
    //       within the range of ELEMENT_LOW to ELEMENT_HIGH
    //
    // POST: all entered values that are either are not elements,
    //       or are elements but are not within the range of
    //       ELEMENT_LOW to ELEMENT_HIGH, will be successfully
    //       discarded, and the first value that is both an
    //       element and within the range of ELEMENT_LOW to
    //       ELEMENT_HIGH will be returned

    element userval;        // used to collect the user's input
    // value

    // prompt the user to input an element value between
    // ELEMENT_LOW and ELEMENT_HIGH
    cout << "Enter an element ("
         << ELEMENT_NAME
         << ") between "
         << ELEMENT_LOW
         << " and "
         << ELEMENT_HIGH << ": ";

    // get the user's input value in a type-safe fashion
    userval = read_element();

    // repeat the following as long as this element input value
    // is not between ELEMENT_LOW and ELEMENT_HIGH
    while ((userval < ELEMENT_LOW) || (userval > ELEMENT_HIGH)) {

        // tell the user what happened, and to try again
        cout << "Invalid range, should be between "
             << ELEMENT_LOW
             << " and "
             << ELEMENT_HIGH
             << ", try again: ";

        // get the user's input value in a type-safe fashion
        userval = read_element();
    }

    // display the user's input value
    //
    // the boolalpha manipulator is used in case elements are
    // bools, to allow for outputs to be displayed using the
    // string sequences of "true" and "false" instead of "1" a "0"
    cout << "You entered "
         << boolalpha
         << userval
         << endl
         << endl;
}

