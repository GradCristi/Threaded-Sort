**Home Project** **Real Time Applications Programming**\
Team: Cristian Gradinaru 2nd Sem, 2020-2021\
e-mail: cgradinaru@stud.acs.upb.ro(student),
gradcristi@yahoo.ro(personal)\
\
****

Introduction- Presenting the proble
===================================

Our task was to solve a problem of our choosing while using the pthread
library in Posix. The problem I chose was sorting a vector of numbers.
The algoritm implemented is a variation of the Producer-Consumer design.
In the source code there is an array of pseudo-random numbers, the
producer thread reads them one by one and puts them into the shared
buffer. The consumer thread reads the numbers from the above-mentioned
buffer and inserts them in a linked list and performs a sorted insert,
ordering the elements from the smallest to biggest number.

Contents of the Solution
------------------------

To solve this problem i chose a 3-file approach:

-   The main file, where we implement the vast majority of functions and
    methods

-   The linked list header, which defines the list, its constructors and
    destructors as well as the data type of the list itself

-   The linked list source code, which contains the implementations of
    the sorted insert, as well as the print and destruct
    functionalities.

Analysis of the given problem
=============================

As we have established previously, we wish to perform a sort on a series
of numbers.

Example
-------

Let’s say we have the following combination of numbers: 32, 21, 90,
-1200, 238, 1273, -5.

Having these numbers, we wish to sort them. So of course we are looking
for the following outcome: -1200, -5, 21, 32, 90, 238, 1273.

The only limitation is that our buffer is 10 elements. So this means
that if our row of numbers consists of more than 10, we shall need the
producer thread to load the first 10 elements, and then proceed with the
consumed thread. After the consumed thread has finished sorting all
available numbers that have been “produced” we can return to the
production queue. A solid analogy would be if we owned a small scale
shop, we cannot/should not order supplies in advance if we still have
some in stock (ideally you would not let yourself run dry, but imagine
you don’t have infinite money: you need to sell in order to be able to
buy more).

Defining the structure of the application
=========================================

As we have mentioned before, our goal is to sort the numbers that we are
given. So, the question remains: exactly how do we do that?

Stages to completion:
---------------------

-   Firstly, we need to take the numbers that have been given to us, and
    introduce them into the production queue. This operation is
    symbolised by the “Input data:” output which shows us the numbers we
    have introduced to be “produced” one by one, until we are done.

-   The next step is to begin the production queue itself, we take each
    number and slowly begin to build our sorted linked list. Each
    element is compared to each other element, starting from the head of
    the list, onward until the end. This is also the stage in which our
    threads are being launched (with the help of pthread$\_$create), and
    ultimately joined.

-   After all the numbers have been cycled through, we have to print
    them out, to show that they have actually been sorted. This stage
    can be observed on the “Output data:” ping on the terminal. After
    this task has been successfully completed and the numbers have been
    printed, we can exit the pthread process and close the log file in
    which we have been storing all our operations.

Defining the Solution
=====================

In this section we shall define the essential elements in the code
implementation, such as functions, syncronization elements etc.

Solution:
---------

We have specified that we need to perform a Producer-Consumer activity,
so therefore we will need:

-   Two threads, one for each of the producer and consumer. These could
    possibly be supercharged to 2 or more each, in order to speed up
    either production or consumption.

-   We are going to declare a buffer of 10 elements, in order to
    simulate real usage, and also we shall need a mutex, in order to
    prevent accessing shared resources at inconvenient times.

-   As additional things we are going to use, we will use a sleep timer,
    in order to put the thread to sleep while the buffer is empty for
    the consumer, or while the buffer is full for the producer

[!htb] ![[fig:taskuri]Diagrams for the production and consumtion
processes](./images/Sad.png "fig:")

The Implementation
==================

We shall begin by showing a figure which will show how our production
and consumer processes work, to be easier to follow up with the code:

The actual code
---------------

Testing and bibliografphy
=========================

To run the app, you can download the whole github repo at:
https://github.com/GradCristi/Threaded-Sort. After that, you will need
to navigate in your terminal to the location of these folders, and once
you are there input into the terminal the following: make build. After
that process is over, you are ready to run the binary, which can be done
by entering : ./pcthread into your terminal and hitting enter. After all
that is done, you should be greeted with a screen similar to this:

[!htb] ![[fig:example]Example of running the
program](./images/Untitled.png "fig:")

We can observe that I navigated to the threads folder (which was located
on my desktop), and followed the commands posted above. After all is
said and done, we can see the input data, the lines which confirm that
the threads were created succesfully (which i forgot to translate from
romanian, my bad) and the output data, which is a fully sorted vector
(not quite a vector) of numbers, from the least big, to the biggest.
