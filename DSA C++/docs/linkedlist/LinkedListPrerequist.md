# Linked List Prerequisites in C++

Linked list start karne se pehle kuch C++ concepts clear hone chahiye. Agar yeh basics strong hain, toh `Node`, `head`, `next`, `new`, aur `nullptr` easily samajh aayenge.

---

## 1. Required Concepts

| Concept | Linked List Mein Use |
|---|---|
| **Pointer** | Node ka address store karne ke liye |
| **Struct / Class** | Custom `Node` type banane ke liye |
| **Heap Memory** | Runtime par nodes create karne ke liye |
| **`new` Operator** | Heap mein new node allocate karne ke liye |
| **`nullptr`** | List end ya empty pointer represent karne ke liye |
| **Reference `&`** | Function ke andar original `head` update karne ke liye |
| **Arrow Operator `->`** | Pointer ke through object members access karne ke liye |

> **Remember:** Linked list ka biggest prerequisite hai pointer ka mental model: variable data store karta hai, pointer address store karta hai.

---

## 2. Pointer Basics

Pointer ek variable hota hai jo kisi doosre variable ka **address** store karta hai.

```cpp
int x = 10;
int* p = &x;
```

### Breakdown

| Code | Meaning |
|---|---|
| `int x = 10;` | Normal integer variable |
| `int* p` | `p` ek pointer hai jo `int` ka address store karega |
| `&x` | `x` ka address |
| `p = &x` | `p` ke andar `x` ka address store ho gaya |

### Memory View

```text
x:
+----+
| 10 |
+----+
 address = 100

p:
+-----+
| 100 |
+-----+
```

> **Additional Explanation**
>
> Linked list mein `Node* next` bhi exactly yahi karta hai: next node ka address store karta hai.

---

## 3. Struct Basics

`struct` ka use custom data type banane ke liye hota hai.

```cpp
struct Student
{
    int rollNo;
    string name;
};
```

Linked list mein hum custom `Node` banate hain:

```cpp
struct Node
{
    int data;
    Node* next;
};
```

### Why Struct for Linked List?

- Node ke andar **data** bhi chahiye.
- Node ke andar **next node ka address** bhi chahiye.
- Dono ko ek unit mein bind karne ke liye `struct Node` use hota hai.

---

## 4. Heap Memory and `new`

Normal local variables stack memory mein bante hain.

Linked list nodes runtime par create hote hain, isliye hum `new` use karke heap memory allocate karte hain.

```cpp
Node* head = new Node();
```

### Meaning

| Part | Meaning |
|---|---|
| `new Node()` | Heap mein ek new `Node` create karo |
| `Node* head` | Us node ka address store karne ke liye pointer |
| `head = new Node()` | New node ka address `head` mein store |

### Stack vs Heap

```text
Stack:
head -> 500

Heap:
500 -> [ data ? | next ? ]
```

> **Common Mistake**
>
> `Node head = new Node();` galat hai, kyunki `new Node()` object nahi, address return karta hai. Correct form: `Node* head = new Node();`

---

## 5. Arrow Operator `->`

Jab object pointer ke through access hota hai, tab `->` use hota hai.

```cpp
head->data = 10;
head->next = nullptr;
```

Equivalent idea:

```cpp
(*head).data = 10;
```

Lekin linked list mein `->` cleaner aur common hai.

### Quick Rule

| Situation | Operator |
|---|---|
| Normal object | `.` |
| Pointer to object | `->` |

```cpp
Node node;
node.data = 10;     // Normal object

Node* head = new Node();
head->data = 10;    // Pointer to object
```

---

## 6. `nullptr`

`nullptr` ka matlab hai pointer kisi valid object ko point nahi kar raha.

Linked list mein `nullptr` ka use hota hai:

- Empty list show karne ke liye
- Last node ka `next` show karne ke liye

```cpp
Node* head = nullptr;  // Empty list
```

```cpp
head->next = nullptr;  // Single node list ka end
```

### `NULL` vs `nullptr`

| Term | Use |
|---|---|
| `NULL` | Old C-style null |
| `nullptr` | Modern C++ null pointer literal |

> **Remember:** Modern C++ mein `nullptr` prefer karo.

---

## 7. Passing `head` by Reference

Linked list functions mein `head` update karna hota hai, especially insert at beginning ya empty list mein insert karte time.

```cpp
void insertAtBeginning(Node* &head, int value)
{
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}
```

### Why `Node* &head`?

`head` ek pointer hai.

`Node* &head` ka matlab:

- `head` pointer ko reference se pass karo.
- Function ke andar `head` change hoga toh original `head` bhi change hoga.

### Without Reference Problem

```cpp
void insertWrong(Node* head, int value)
{
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode; // Sirf local copy update hogi
}
```

> **Common Mistake:** `head` ko value se pass karne par original linked list ka start update nahi hota.

---

## 8. Minimum Code You Should Understand First

```cpp
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

int main()
{
    Node* head = new Node();
    head->data = 10;
    head->next = nullptr;

    cout << head->data;

    delete head;
    return 0;
}
```

### What This Code Teaches

1. `struct Node` custom node type banata hai.
2. `Node* head` first node ka address store karta hai.
3. `new Node()` heap mein node banata hai.
4. `head->data` node ke data ko access karta hai.
5. `head->next = nullptr` list end mark karta hai.
6. `delete head` heap memory free karta hai.

---

## 9. Quick Revision

```text
Pointer      -> Address store karta hai
Node*        -> Node ka address
struct Node  -> data + next pointer ka custom type
new Node()   -> heap mein node create karta hai
head         -> first node ka address
next         -> next node ka address
nullptr      -> no valid next node
->           -> pointer ke through member access
Node* &head  -> original head update karne ke liye reference
```

> **Interview Tip:** Linked list questions mein pehle `head`, `temp`, `next`, aur `nullptr` ka role clearly bolo. Yeh clarity implementation mistakes ko kaafi reduce karti hai.
