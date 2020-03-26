Linked lists are good way to learn about pointers, memory management, and destructors in C++. Let's make a Linked list that can

- be created empty
- insert ints at the front of the list
- check whether an int appears in a list
- remove an int from a list

### Anything to declare?

To start off, make a file called "int_list.hpp", and add a class definition with those methods. In order to avoid changing the tests, please call your class `IntList`, and use the method names `push_front`, `contains`, and `remove`. Decide what arguments each method needs, and what they should return. Remember: you don't need to write the _code_ yet, just the signatures for the functions (their names, arguments, and return types).

### Some theory.

How will we actually store data? In a linked list, data is stored in "nodes" that each contain one item and a pointer to the next item. It looks something like this:

```
┌────────┐      ┌────────┐    ┌────────┐    ┌────────┐    ┌──────────┐
│IntList │ ┌───▶│Node    │┌──▶│Node    │┌──▶│Node    │┌──▶│Node      │
├────────┤ │    ├────────┤│   ├────────┤│   ├────────┤│   ├──────────┤
│head:  ─┼─┘    │data: 5 ││   │data: -1││   │data: 12││   │data: 6   │
└────────┘      │next:  ─┼┘   │next:  ─┼┘   │next:  ─┼┘   │next: NULL│
                └────────┘    └────────┘    └────────┘    └──────────┘
```

Because of the pointer hops, the memory location of 5 is not necessarily near the memory location for -1. We would say that this linked list class exhibits poor "data locality", which is common for linked lists. Structures with poor data locality can slow down your code, because computers uses caches ensure that accessing memory near what you just accessed is very fast. When the data you need is far away, we're not able to take advantage of these caches.

However, the pointers also mean we can grow our list without "running out of room" and needing to move all our data to a spot with more available space. That would be a very expensive operation, and a linked will never need to do it. So there's a tradeoff between data locality and avoiding re-allocating our object.

### Got your Node!

Within your `class IntList`, define a nested class called `Node`. this `Node` class will actually be where data is stored. However, it should be private, as the only way to interact with it will be by going through `IntList`'s public interface. You should have something like this:

```cpp
// int_list.hpp
class IntList {
public:
  // methods for IntList

private:
  class Node {

  };
  // private data for IntList
};
```

You `IntList` will have only a single private data member. I'm calling mine `head`, but you can use any name you like (after all, it's private and only accessible to within your class). `head` should be a pointer to a `Node`. You can declare it like this: `Node* head`. The `*` represents the fact that you have a _pointer_ to a `Node`, not a full node right there.

What makes up a Node? As we saw in the diagram, each node needs to hold an `int data` and a `Node* next`. The `next` pointer will be `null` for the last entry in a list. Make those data members public, so that the IntList can access and modify them.

### Disallowing empty Nodes

What does an empty `IntList` look like? It's `head` is set to `nullptr`. Not too crazy. What does an empty `Node` look like? Less clear. Probably it has `nullptr` for `next`, but what about `data`? If we don't do anything special it will be set to zero, the default value for integers. But zero is a totally valid entry for a list! How would we distinguish between an empty `Node` and a `Node` containing zero?

In my mind, the best way is to disallow empty `Node`s. Impose the rule: "Every `Node` must be created with a value for `data`". It's easy enough to make a single-argument constructor. But C++ will make us a parameterless default constructor unless we ask it not to.

Let's ask it not to. Add a line `Node() = delete` to the class declaration. This tells the compiler "please don't make me a default constructor". Now we won't be able to forget this decision to disallow empty Nodes.

Since we're deleting the default constructor, we'd better make a replacement. Declare a constructor that accepts one or two arguments. First, an int to be stored in the `data` field. Second, a `Node*` to be stored in the `next` field.

### Implementation Time

Let's implement Node first, since it's smaller. To start off, make the constructor. In "int_list.cpp", add the following definition:

```cpp
IntList::Node::Node(int d, Node* n): data{d}, next{n} {}
```

This is another of those funny body-less constructors. All we're doing is copying some parameters into member fields, and C++ gives us special brace initializer syntax for that.

That's actually all we need for `Node`, for now. On to `IntList`. For `IntList`, we can accept the compiler-generated constructor. The default behavior is to set all member fields to their default value. `IntList` has only `head`, whose default value is `nullptr`. We've already decided that a value of `nullptr` for `head` represents an empty (but valid) list.

Write `IntList::push_front`. Linked lists are particularly good at inserting at the front. How does an insert look?

1. Let's assume the IntList already has some data. It won't for the very first insert, but that case is easier to visualize in your head.

```
┌────────┐      ┌──────────┐
│IntList │ ┌───▶│Node      │
├────────┤ │    ├──────────┤
│head:  ─┼─┘    │data: 5   │
└────────┘      │next: NULL│
                └──────────┘
```

2. Make a new `Node`, containing the value-to-be-inserted (3, in this case), and a pointer to the current value of `head`

```
┌────────┐         ┌──────────┐
│IntList │  ┌─────▶│Node      │
├────────┤  │      ├──────────┤
│head: ──┼──┘      │data: 5   │
└────────┘         │next: NULL│
                   └──────────┘
  ┌────────┐        ▲
  │Node    │        │
  ├────────┤        │
  │data: 3 │        │
  │next: ──┼────────┘
  └────────┘
```

3. Update `head` to refer to the node you just created:

```
┌────────┐         ┌──────────┐
│IntList │         │Node      │
├────────┤         ├──────────┤
│head: ──┼┐        │data: 5   │
└────────┘│        │next: NULL│
          ▼        └──────────┘
  ┌────────┐        ▲
  │Node    │        │
  ├────────┤        │
  │data: 3 │        │
  │next: ──┼────────┘
  └────────┘
```

There are a couple things to be careful of when writing this. In step 2, when you make your `Node`, be sure to create it using `new`. `new` is the C++ way of saying "make this thing on the heap, and give me a _pointer_ to it". If your `Node` is created without `new`, using something like `Node temp(5, head)`, it will be cleaned up when the `push_front` function exits. Plus, the types won't match up: `head` expects to be a `Node*`, so we can't assign a full `Node` to it.

#### Check your work.

Comment out all but the first two test cases (`[create]` and `[push_front]`). Run `make` and `./test`.

### Implementing 'contains'

Starting with `head` and continuing until you reach a `nullptr`, check whether any `Node*` has a data member that equals the given argument. Check you work by uncommenting the tests.

### Implementing 'remove'

To remove a value from a list, you first have to navigate to the _immediately preceding_ `Node`. To see why, consider this diagram, where we're trying to remove `6`.

```
                    The node we want to excise, B
                                │
                                ▽
┌────────┐    ┌────────┐     ┌────────┐       ┌──────────┐
│IntList │┌──▶│Node: A │┌───▶│Node: B │ ┌────▶│Node: C   │
├────────┤│   ├────────┤│    ├────────┤ │     ├──────────┤
│head: ──┼┘   │data: 3 ││    │data: 6 │ │     │data: 5   │
└────────┘    │next: ──┼┘    │next: ──┼─┘     │next: NULL│
              └────────┘     └────────┘       └──────────┘
                  △
                  │
          The node whose pointer needs to change, A
```

In order to remove "B" from our list, we need to make it so there's no path there. So we need to change the pointer in "A".

We also need to preserve the rest of the list after "B". So we should change "A" to point to what "B" currently points to—essentially re-routing around "B".

```
┌────────┐    ┌────────┐     ┌────────┐       ┌──────────┐
│IntList │┌──▶│Node: A │┌───▶│Node: B │ ┌────▶│Node: C   │
├────────┤│   ├────────┤│    ├────────┤ │     ├──────────┤
│head: ──┼┘   │data: 3 ││    │data: 6 │ │     │data: 5   │
└────────┘    │next: ──┼┘    │next: ──┼─┘     │next: NULL│
              └────────┘│    └────────┘       └──────────┘
                                                ▲
                        │                       │
                         ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
```

Give this a shot. Reach out for help if you get stuck. I ended up making a mistake in mine and needing to ask Jonah for help. Check you work by running the related tests.

### Cleaning up after ourselves

If you have experience with C or C++, you may have noticed something that's missing. We're not cleaning up the memory we use! After the delete from the diagram above, Node "B" is still hanging around taking up space. We're going to fix that, but first let's demonstrate the problem.

Install `valgrind`, then run `valgrind ./test`. You'll see the happy green "All tests passed" message, but also something like

```
==41926==
==41926== HEAP SUMMARY:
==41926==     in use at exit: 22,715 bytes in 172 blocks
==41926==   total heap usage: 2,021 allocs, 1,849 frees, 288,211 bytes allocated
==41926==
==41926== LEAK SUMMARY:
==41926==    definitely lost: 64 bytes in 4 blocks
==41926==    indirectly lost: 64 bytes in 4 blocks
==41926==      possibly lost: 72 bytes in 3 blocks
==41926==    still reachable: 4,296 bytes in 7 blocks
==41926==         suppressed: 18,219 bytes in 154 blocks
```

For our tests, it's not such a big deal that memory is leaked. The test program exits before it has a chance to use much memory. But what if our `IntList` is used in another project, one with a long-running process like a web server? Memory leaks add up over the course of a program's execution. A good rule to remember is that every `new` should be matched with a `delete`.

So where are our `new`s? Really just in one place: the `push_front` method. There are two times we want to think about `delete`ing `Nodes`:

1. When we explicitly `remove` a value, and
2. when an `IntList` goes out of scope.

Let's do the `remove` case first. In your `remove` method, there's likely a point when you identify that some node has the value you're trying to remove. Before "routing around" that node, save a pointer to it. Then call `delete nodeToDelete` on the pointer you saved.

```
                       1. Identify the node
                        to delete. save a
                          pointer to it.

┌────────┐    ┌────────┐     ┌────────┐       ┌──────────┐
│IntList │┌──▶│Node    │┌───▶│Node    │ ┌────▶│Node      │
├────────┤│   ├────────┤│    ├────────┤ │     ├──────────┤
│head: ──┼┘   │data: 3 ││    │data: 6 │ │     │data: 5   │
└────────┘    │next: ──┼┘    │next: ──┼─┘     │next: NULL│
              └────────┘│    └────────┘       └──────────┘
                                                ▲
                        │                       │
                         ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
                         2. Route around the
                                 node
  3. call "delete" on
  the node you excised
```

#### Check your work

Comment out all the tests other than the Remove block (because we haven't addressed the "when an `IntList` goes out of scope" leaks yet). Compile and run the tests under valgrind. If all went well, you should get "definitely lost: 0 bytes, indirectly lost: 0 bytes". (ignore the "possibly lost").

#### Cleaning up when an `IntList` goes out of scope.

When any C++ object goes out of scope, its destructor is called. That's the perfect time to clean up our un-deleted `Node`s. Let's define a destructor for `IntList`. First, add the following to the public section of our header:

```cpp
  ~IntList();
```

Now, in our implementation file add the following:

```cpp
IntList::~IntList() {
  if (head != nullptr) delete head;
}
```

That should do it right? Uncomment those tests again and check with valgrind. When I ran this, I got the following:

```
==42513==    definitely lost: 32 bytes in 2 blocks
==42513==    indirectly lost: 16 bytes in 1 blocks
```

Uh oh. What's going on? Think about this sequence

```cpp
{ // start of block
  IntList il;
  il.push_front(1);
  il.push_front(2);
  il.push_front(3);

  // il goes out of scope here, destructor is called.
}
```

How many times did we call `new`? Well, we used `new` once in each call to `push_front`, so three total times. How many times did we call `delete`? Just the once, in `IntList`'s destructor.

One way to fix this would be to iterate over the linked list, calling `delete` on each `Node` in the chain. However, that's a bit error prone. A better way is to add a destructor for the `Node`. That way, destroying an `IntList` calls `delete` on the list's `head`. `delete`ing an object also invokes the destructor, so that `delete` calls the destructor on the next `Node`, all the way down the line.

Once I made those changes, I was back at "definitely lost: 0 bytes, indirectly lost: 0 bytes". In the next section we'll see a modern, less error-prone way of attacking this problem.

### automatic deletion with shared_ptr

Watch this video on shared pointers https://www.youtube.com/watch?v=qUDAkDvoLas

Change our raw `Node*` to shared pointers (`shared_ptr<Node>`). You should be able to delete the destructors for both `Node` and `IntList`, and valgrind will still report no memory leaks.

### Where to go from here?

- Convert to a template class so we can store other types of items (not just ints)
- Make an iterator class so we can use std::find and other algorithms
