# Linked List 1: Node, Head, Traversal, and Insertion

Linked list ek **linear data structure** hai jisme data contiguous memory mein store nahi hota. Data chhote-chhote blocks, yaani **nodes**, mein store hota hai. Har node apne next node ka address rakhti hai.

> **Core idea:** Linked list = **nodes + pointers**.

---

## 1. Linked List: Advantages and Disadvantages

### Advantages

- **Dynamic size** hoti hai; size pehle se fix nahi hona chahiye.
- **Insertion/deletion** mein pointers change hote hain, elements shift nahi hote.
- **Stack, queue, deque** jaise structures banane mein useful hoti hai.

### Disadvantages

- **Random access slow** hota hai, kyunki `nth` element tak pahunchne ke liye traverse karna padta hai.
- **Extra memory** lagti hai kyunki har node mein pointer store hota hai.
- Memory scattered hone ki wajah se **cache efficiency** kam ho sakti hai.

### Important Points

| Concept | Key Point |
|---|---|
| **Linked list** | Nodes + pointers |
| **Array** | Contiguous memory |
| **Linked list useful when** | Frequent insert/delete chahiye |
| **Array better when** | Fast indexing chahiye |

> **Remember:** Array mein `index` se direct access milta hai. Linked list mein `head` se traversal karke jaana padta hai.

---

## 2. Node Kya Hota Hai?

Node ek chhota packet samjho.

Har packet mein:

- Actual value hoti hai.
- Next packet ka address hota hai.

Linked list inhi nodes se banti hai.

### Kyun Node Chahiye?

Array mein saara data ek jagah hota hai, lekin linked list mein data alag-alag jagah rakhna hota hai.

Isliye har piece of data ke saath next ka link rakhna padta hai.

> **Additional Explanation**
>
> Linked list ka har node apne baad wale node ka address rakhta hai. Is address chain ki wajah se scattered memory bhi ek logical list ki tarah behave karti hai.

---

## 3. Structure of `Node`

Ye code dekho:

```cpp
struct Node
{
    int data;
    Node* next;
};
```

### Line-by-Line Breakdown

| Part | Explanation |
|---|---|
| `struct` | Ek custom data type banana. Jaise `int`, `char`, `float` built-in types hain, waise hi `Node` ko hum apna type bana rahe hain. |
| `Node` | Structure ka naam. Iska matlab hum ek aisa data type bana rahe hain jiska naam `Node` hai. |
| `{ ... }` | Braces structure ke andar ke members ko define karte hain. |
| `int data;` | `int` integer type hai. `data` value store karne wala part hai. Isme actual number hoga, jaise `10`, `20`, `30`. |
| `Node* next;` | Sabse important line. `Node*` means `Node` type ka pointer. `next` next node ka address store karega. |

### Pointer Kyun?

Agar `next` mein direct next node ka data store karoge, toh woh linked nahi hoga.

Hume **address** chahiye, kyunki address se hi hum next node tak pahunch sakte hain.

### `Node*` Kyun?

Kyuki `next` ko kisi aur `Node` ka address store karna hai.

Agar type `Node*` hai, toh iska matlab hai **Node ka address**.

### Why `next`?

Name `next` isliye diya gaya kyunki yeh agle node ko point karta hai.

Singly linked list mein har node sirf next node ko jaanti hai.

---

## 4. Memory Visualization

Maan lo 2 nodes hain:

```text
100:
[ data = 10 | next = 200 ]

200:
[ data = 20 | next = NULL ]
```

Diagram form:

```text
head
 |
 v
+------+------+
|  10  | 200  | ----+
+------+------+     |
                   v
              +------+------+
              |  20  | NULL |
              +------+------+
```

---

## 5. First Node Ka Code

```cpp
Node* head = new Node();
```

### Line-by-Line

| Part | Explanation |
|---|---|
| `Node*` | `Node` type ka pointer. Yeh pointer kisi `Node` ka address store karega. |
| `head` | Starting point. Linked list mein `head` first node ko point karta hai. |
| `=` | Left side wale pointer mein right side ka address store karo. |
| `new Node()` | Heap memory se nayi memory allocate karta hai aur ek naya `Node` object banata hai. |

`new Node()` ka result ek address hota hai. So `head` ko ek memory address milta hai.

### Heap Memory Mein Kya Hota Hai?

Maan lo address `500` mila.

```text
Stack:
head -> 500

Heap:
500 -> [ data ? | next ? ]
```

---

## 6. Proper Creation of First Node

```cpp
Node* head = new Node();
head->data = 10;
head->next = nullptr;
```

### Line-by-Line

#### `head->data = 10;`

- `head` pointer hai.
- `->` means jis object ka address `head` ke paas hai, uske member ko access karo.
- `data = 10` means node ke andar value `10` store karo.

#### `head->next = nullptr;`

- `next` ko null initialize kar rahe hain.
- `nullptr` ka matlab kisi valid node ka address nahi hai.
- Yeh batata hai ki abhi list mein next node nahi hai.

### `NULL` vs `nullptr`

| Term | Meaning |
|---|---|
| `NULL` | Purana C-style null value |
| `nullptr` | Modern C++ ka better version |

Beginner ke liye `nullptr` use karna safer hai.

### Complete Memory Picture

```text
head
 |
 v
500: [ data = 10 | next = nullptr ]
```

---

## 7. Common Mistakes

> **Common Mistakes**
>
> - `Node head = new Node();` likh dena: wrong, kyunki `new` address return karta hai, object nahi.
> - `head->next` set na karna: unsafe.
> - `nullptr` initialize na karna: traversal mein problem ho sakti hai.
> - `delete` later bhool jana: memory leak.

---

## 8. Dry Run: First Node Creation

```cpp
Node* head = new Node();
head->data = 10;
head->next = nullptr;
```

### Steps

1. `new Node()` heap mein node banata hai.
2. Uska address `head` mein store hota hai.
3. `data` ko `10` set karte hain.
4. `next` ko `nullptr` kar dete hain.

### Important Points

- First node create karne ke liye `new` use hota hai.
- `head` address store karta hai, data nahi.
- `->` pointer ke through member access ke liye use hota hai.
- Single node linked list ka `next = nullptr` hota hai.

---

## 9. Traversal Idea

Hum ek temporary pointer `temp` banate hain jo `head` se start karta hai.

Phir jab tak `temp` null na ho:

1. Current node ka data use karte hain.
2. `temp = temp->next` karke agle node par chale jaate hain.

### Basic Code

```cpp
void printList(Node* head)
{
    Node* temp = head;

    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
}
```

### Traversal Diagram

```text
Initial:
temp
 |
 v
[10 | *] -> [20 | *] -> [30 | nullptr]

After temp = temp->next:
             temp
              |
              v
[10 | *] -> [20 | *] -> [30 | nullptr]
```

> **Remember:** Traversal mein `head` ko directly move mat karo. `temp` use karo, warna list ka starting address lose ho sakta hai.

---

## 10. Insertion at Beginning

Insertion at beginning sabse pehla aur sabse important insertion hai.

**Time complexity:** `O(1)`

Reason: sirf `head` pointer update hota hai.

### Idea

Beginning mein insert karne ka matlab hai:

1. Naya node banao.
2. Usko current `head` ke aage laga do.
3. `head` ko naye node par shift kar do.

### Code

```cpp
void insertAtBeginning(Node* &head, int value)
{
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}
```

### Line-by-Line

| Code | Explanation |
|---|---|
| `void insertAtBeginning(Node* &head, int value)` | Function kuch return nahi karega. `Node* &head` means `head` reference se pass ho raha hai, taaki original `head` update ho. |
| `int value` | Jo data insert karna hai woh integer hai. |
| `Node* newNode = new Node();` | Heap mein naya node banta hai. Uska address `newNode` mein store hota hai. |
| `newNode->data = value;` | Naye node ke data part mein value daal rahe hain. |
| `newNode->next = head;` | Naya node purane `head` ko point karega. Matlab naya node sabse pehle aa gaya. |
| `head = newNode;` | `head` ko update karke naye node par le aate hain. Ab list ka start `newNode` ho gaya. |

### Diagram

```text
Before:
head -> [10 | *] -> [20 | nullptr]

Insert 5:
newNode -> [5 | head]

After:
head -> [5 | *] -> [10 | *] -> [20 | nullptr]
```

---

## 11. Insert at End

### Idea

End mein insert karne ke liye:

1. Naya node banao.
2. Usme value daalo.
3. Uska `next = nullptr` rakho.
4. Agar list empty hai, `head` ko naya node bana do.
5. Warna last node tak jao.
6. Last node ka `next` nayi node ko point karao.

### Code

```cpp
void insertAtEnd(Node* &head, int value)
{
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}
```

### Line-by-Line

| Code | Explanation |
|---|---|
| `void insertAtEnd(Node* &head, int value)` | Function kuch return nahi karega. `head` reference se pass kiya, taaki empty list mein `head` update ho sake. |
| `Node* newNode = new Node();` | Naya node heap memory mein banta hai. |
| `newNode->data = value;` | Naye node mein value store hoti hai. |
| `newNode->next = nullptr;` | Kyunki yeh abhi last node banne wala hai. |
| `if (head == nullptr)` | Agar list empty hai. |
| `head = newNode;` | Empty list mein pehla node hi `head` hota hai. |
| `Node* temp = head;` | Traversal ke liye temporary pointer. |
| `while (temp->next != nullptr)` | Jab tak last node nahi mil jaata. |
| `temp = temp->next;` | Aage move karo. |
| `temp->next = newNode;` | Last node ke `next` mein new node ka address store karo. |

### Complexity

| Operation | Time | Reason |
|---|---|---|
| Insert at beginning | `O(1)` | Direct `head` update |
| Insert at end | `O(n)` | Last node tak traverse karna padta hai |

> **Interview Tip:** Agar linked list mein `tail` pointer maintain karte ho, toh insert at end `O(1)` ho sakta hai.

---

## 12. Quick Revision

> **Linked list = nodes connected by pointers.**
>
> **Node = data + next pointer.**
>
> **head = first node ka address.**
>
> **nullptr = no next node.**
>
> **Traversal = temp ko `head` se start karke `temp = temp->next` karna.**

### Final Cheat Sheet

```text
Node structure:
struct Node {
    int data;
    Node* next;
};

First node:
Node* head = new Node();
head->data = 10;
head->next = nullptr;

Traversal:
while (temp != nullptr) {
    use temp->data;
    temp = temp->next;
}

Insert beginning:
newNode->next = head;
head = newNode;

Insert end:
go to last node;
last->next = newNode;
```


