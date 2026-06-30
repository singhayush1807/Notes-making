# Abstraction & Encapsulation

These notes cover the first two major pillars of OOP:

- **Abstraction**: zaroorat se zyada details mat dikhao.
- **Encapsulation**: data ko safe rakho.

> **Remember:** Abstraction is about hiding **complexity**. Encapsulation is about protecting **data**.

---

## 1. Pillar 1: Abstraction: "Zaroorat Se Zyada Mat Dikhao"

### Intuition

Abstraction ka core idea simple hai:

> User ko sirf woh controls dikhao jo use karne ke liye zaroori hain. Internal implementation details hide rakho.

### Kya Hai?

**Abstraction** means unnecessary background details chhupao, aur sirf woh expose karo jo user ko interact karne ke liye chahiye.

Simple definition:

> **Abstraction = "What it does, not how it does it."**

### Kyun Exist Karta Hai?

Kya tujhe gaadi chalane ke liye pata hona chahiye ki engine ke andar combustion kaise hoti hai?

Nahi. Tu sirf steering wheel, accelerator, aur brake jaanta hai. Baaki sab abstracted hai.

---

### Real-World Analogies

#### 1. Car

```text
Exposed (Interface):
  - Steering wheel (direction)
  - Accelerator pedal (speed)
  - Brake pedal (stop)
  - Gear shift (gear)

Hidden (Abstracted):
  - Fuel injection logic
  - Combustion engine internals
  - Transmission system
  - ABS brake calculations
```

#### 2. TV Remote

```text
Exposed:
  - Volume +/-
  - Channel +/-
  - Power button

Hidden:
  - IR signal encoding
  - TV circuit logic
  - Display rendering
```

#### 3. Programming Languages Themselves

```text
Exposed:
  if (condition) { ... }

Hidden:
  CPU branch instructions
  Binary comparisons
  Register management
```

High-level languages are themselves an abstraction over machine code.

> **Additional Explanation**
>
> Abstraction reduces cognitive load. User ya client code ko internal details yaad nahi rakhni padti. Sirf public interface use karna hota hai.

---

## 2. C++ Implementation: Virtual Functions + Abstract Classes

### Code Example

```cpp
// Abstract Base Class = Pure Interface
class Car {
public:
    // Virtual functions = "Define karna hai, lekin HOW? Child decide karega"
    virtual void startEngine() = 0;  // Pure virtual: implementation zaroor chahiye
    virtual void shiftGear() = 0;
    virtual void accelerate() = 0;
};

// Concrete Child Class: actual implementation
class SportsCar : public Car {
private:
    int speed = 0;

public:
    void startEngine() override {
        cout << "Sports car engine ROARS!" << endl;
    }

    void shiftGear() override {
        cout << "Sports car gear shifted!" << endl;
    }

    void accelerate() override {
        speed += 20;  // Sports car accelerates fast
        cout << "Speed: " << speed << endl;
    }
};

// Client (Main method): knows nothing about SportsCar internals
int main() {
    Car* myCar = new SportsCar();   // Car type, SportsCar object
    myCar->startEngine();           // Client just calls interface methods
    myCar->shiftGear();
    myCar->accelerate();

    // myCar has no idea if this is SportsCar, SUVCar, TruckCar
    // Completely abstracted!
}
```

### Line-by-Line Breakdown

| Code | Meaning |
|---|---|
| `virtual void startEngine() = 0;` | Pure virtual function. `= 0` matlab implementation mat do, child class degi. `Car` khud instantiate nahi ho sakti. |
| `class SportsCar : public Car` | `SportsCar` inherits `Car`. Ab usse `startEngine()`, `shiftGear()`, `accelerate()` define karni padegi. |
| `void accelerate() override` | `override` keyword confirm karta hai ki yeh parent ka method override kar raha hai. |
| `Car* myCar = new SportsCar()` | Polymorphism + Abstraction combined. Client `Car` type se deal karta hai, andar `SportsCar` hai. Client ko pata bhi nahi. |

> **Interview Tip**
>
> C++ abstraction commonly uses **abstract classes**, **pure virtual functions**, and **base class pointers/references**.

---

### What Happens If You Add Another Car Type?

```cpp
class ElectricCar : public Car {
public:
    void startEngine() override { cout << "Silently starts..." << endl; }
    void shiftGear() override   { cout << "No gears in EV!" << endl; }
    void accelerate() override  { cout << "Instant torque! 0-100 in 3s" << endl; }
};

// Client code unchanged: yahi abstraction ki beauty hai
Car* myCar = new ElectricCar();
myCar->startEngine(); // "Silently starts..."
```

Client code ek line bhi nahi badla. Bas naya type aaya, apna behavior leke.

### Architecture Decision: Use Abstraction for Replaceable Implementations

> **Decision:** Jab multiple implementations possible hon, client code ko base abstraction ke against program karo.
>
> **Reason:** New implementations add karne par existing client code change nahi hota.

---

## 3. Advanced Insight: Abstraction vs Interface vs Abstract Class

| Concept | Kya Hai |
|---|---|
| **Abstract Class** | Partial implementation ho sakti hai + kuch pure virtual methods. |
| **Interface / Pure Abstract Class** | Sirf declarations, koi implementation nahi. |
| **Abstraction** | Concept: complexity chhupao, simple interface expose karo. |

### Common Mistake

```cpp
// GALAT: Abstract class ka object banana
Car* myCar = new Car(); // ERROR! Can't instantiate abstract class
// Car mein pure virtual functions hain: woh concrete nahi

// SAHI:
Car* myCar = new SportsCar();
```

### Summary: Abstraction

Abstraction = complexity chhupao, simple interface expose karo.

Client ko pata nahi kaise kaam hota hai. Woh sirf use karta hai. C++ mein virtual functions + abstract classes se implement karte hain.

### Cheat Sheet

```text
Abstraction = "What it does, not how it does it"
Real world  = Car steering, TV remote, programming languages
C++ impl    = virtual void method() = 0; (pure virtual)
Abstract class -> child must implement all pure virtual methods
Client      -> always interacts with base class pointer/reference
```

---

## 4. Pillar 2: Encapsulation: "Data Ko Safe Rakhao"

### Intuition

Encapsulation ka idea hai:

> Data ko direct public access mat do. Valid methods ke through hi read/write karne do.

### Kya Hai?

Encapsulation ke do specific meanings hain:

1. **Bundling**: Sab related data, yaani variables, aur methods, yaani behaviors, ko ek single unit `Class` mein bandh karo.
2. **Data Security**: Access modifiers se sensitive data ko baahri duniya se protect karo.

### Kyun Exist Karta Hai?

Without encapsulation, koi bhi kisi bhi variable ko directly modify kar sakta hai, chahe value valid ho ya nahi.

Yeh system instability aur logic flaws create karta hai.

---

## 5. Abstraction vs Encapsulation: Interview Ka Most Common Confusion

Yeh bahut frequently interviews mein pucha jaata hai.

| Aspect | Abstraction | Encapsulation |
|---|---|---|
| **Focus** | Complexity chhupao | Data protect karo |
| **Goal** | Simple interface provide karo | Security provide karo |
| **Analogy** | TV remote: engine nahi dikhata | Car odometer: directly change nahi kar sakte |
| **"Hurt" factor** | Engine dikhane se hurt nahi, bas zaroorat nahi | Speed directly set karne se system crash ho sakta hai |
| **Implementation** | Abstract classes, virtual functions | Private variables + getters/setters |

### Memory Trick

> **Abstraction = Access simplify**: kya use karna hai.
>
> **Encapsulation = Enclosed/protected**: bahar se touch mat karo.

---

## 6. Encapsulation Real-World Analogies

### 1. Odometer

```text
Tu directly odometer reading change nahi kar sakta (private).
Tu sirf car drive karta hai -> odometer internally update hoti hai.
```

### 2. Car Speed

```text
Tu directly speed = 500 set nahi kar sakta.
Tu accelerator pedal dabata hai -> speed controlled tarike se badhti hai.
Setter validation karta hai: "500 km/h? Nahi! Max 200 km/h hai."
```

### 3. Bank Account: Prime Cup Payments Relevant

```text
balance directly set nahi kar sakte:
account.balance = 100000;

Sirf deposit()/withdraw() se access:
account.deposit(5000);
```

> **Additional Explanation**
>
> Encapsulation invalid state ko object ke andar enter hone se rokta hai. Object apne rules khud enforce karta hai.

---

## 7. The Problem Without Encapsulation

```cpp
class SportsCar {
public:         // Public means anyone can access
    int currentSpeed;
    string tyre;
};

// Problem: anywhere in code
SportsCar myCar;
myCar.currentSpeed = 500;  // Valid? Possible? Safe? No.
myCar.tyre = "";           // Empty string? Koi validation nahi.
myCar.currentSpeed = -100; // Negative speed? Logic fail.
```

### Problem Summary

| Invalid Change | Risk |
|---|---|
| `currentSpeed = 500` | Unrealistic speed, rule violation |
| `tyre = ""` | Empty invalid value |
| `currentSpeed = -100` | Negative speed, logic fail |

---

## 8. The Solution: Access Modifiers + Getters + Setters

### Access Modifiers Kya Hain?

| Modifier | Accessible From | Use Case |
|---|---|---|
| `public` | Everywhere: class ke andar aur bahar | Methods user call kar sake |
| `private` | Sirf class ke andar | `currentSpeed`, `odometer`, `balance` |
| `protected` | Class + child classes | Inheritance mein use |

### Complete Code: Getters & Setters

```cpp
class SportsCar {
private:
    // Private: baahri duniya directly access nahi kar sakti
    int currentSpeed;
    string tyre;
    int odometer;

public:
    // Getter: read karo bina modify kiye
    int getCurrentSpeed() {
        return this->currentSpeed;  // this -> current object ka reference
    }

    int getOdometer() {
        return this->odometer;      // Read-only access to odometer
    }

    // Setter: write karo, lekin pehle validate karo
    void setTyre(string newTyre) {
        // Validation logic: bad data enter na ho
        if (newTyre == "" || newTyre.length() < 3) {
            cout << "Invalid tyre brand!" << endl;
            return;
        }

        this->tyre = newTyre;       // Valid input: assign karo
    }

    void accelerate(int amount) {
        // Validation: speed 200 se zyada nahi ho sakti
        if (currentSpeed + amount > 200) {
            cout << "Max speed reached!" << endl;
            return;
        }

        currentSpeed += amount;
        odometer += amount;         // Odometer internally update
    }
};
```

### Line-by-Line Breakdown

| Code | Meaning |
|---|---|
| `private: int currentSpeed;` | Compiler error throw karega agar koi `myCar.currentSpeed = 500;` bahar se likhe. |
| `int getCurrentSpeed()` | Getter: sirf read karne deta hai, modify nahi. User value dekh sakta hai but corrupt nahi kar sakta. |
| `void setTyre(string newTyre)` | Setter: set karne ka controlled channel. Validation inject kiya. Agar tyre name valid nahi, assignment hi nahi hogi. |
| `this->currentSpeed` | `this` pointer current object ko point karta hai. `this->currentSpeed` = is specific object ka `currentSpeed`. |
| `void accelerate(int amount)` | Speed setter ki jagah behavior method use kiya. User `accelerate(30)` bolega, internal logic decide karega valid hai ya nahi. |

---

## 9. Why Setters > Making Variable Public?

```cpp
// Public variable (bad):
myCar.tyre = "";              // Koi check nahi, empty string accept
myCar.currentSpeed = -999;    // Negative speed, no error
myCar.currentSpeed = 9999;    // 9999 km/h?! No validation

// Setter / behavior method (good):
myCar.setTyre("");            // Setter blocks it: "Invalid!"
myCar.accelerate(-999);       // Setter validates: "Speed can't be negative!"
```

Setter ek **gatekeeper** hai: sirf valid data entry karne deta hai.

> **Common Mistake**
>
> Har field ke liye blindly getter/setter banana bhi ideal nahi. Agar field ko direct set karna business-wise allowed nahi, toh behavior method use karo, jaise `accelerate()` instead of `setSpeed()`.

---

## 10. `this` Keyword Deep Dive

```cpp
void setTyre(string tyre) {  // Parameter naam bhi 'tyre' hai
    this->tyre = tyre;        // this->tyre = class ka member variable
                              // tyre (without this) = parameter
}

// Agar 'this->' nahi likhte:
void setTyre(string tyre) {
    tyre = tyre;              // Parameter khud ko assign kar raha hai!
                              // Class member unchanged.
}
// Common bug!
```

Memory trick:

> **this = "mera apna"**
>
> `this->speed` = meri car ka speed.

---

## 11. Complete Real-World Example: Prime Cup Tournament Slot

```cpp
class TournamentSlot {
private:
    int registeredPlayers;
    int maxPlayers;
    string tournamentName;

public:
    // Constructor
    TournamentSlot(string name, int max) {
        this->tournamentName = name;
        this->maxPlayers = max;
        this->registeredPlayers = 0;
    }

    // Getter
    int getRegisteredPlayers() {
        return this->registeredPlayers;
    }

    // Behavior method with validation (no direct setter for players)
    bool registerPlayer() {
        if (registeredPlayers >= maxPlayers) {
            cout << "Tournament FULL!" << endl;
            return false;
        }

        registeredPlayers++;
        cout << "Registered! Total: " << registeredPlayers << "/" << maxPlayers << endl;
        return true;
    }
};

// Usage:
TournamentSlot slot("Prime Cup Finals", 100);
slot.registerPlayer();   // Registered! Total: 1/100

// slot.registeredPlayers = 9999;  // Compiler error! Private.
```

### Architecture Decision: Hide Counters Behind Behavior

> **Decision:** `registeredPlayers` ko direct public field nahi banana.
>
> **Reason:** Tournament full hone ka validation `registerPlayer()` ke through enforce karna hai.

### Summary: Encapsulation

Encapsulation = bundling data + methods into one class + protecting data with access modifiers.

Private variables sirf getters/setters ya behavior methods ke through accessible hote hain. Setters validation inject karne dete hain, jisse bad data bahar hi ruk jaata hai.

### Cheat Sheet

```text
Encapsulation = Bundling + Data Security
private -> compiler error if accessed directly from outside
public  -> accessible anywhere
Getter  -> int getValue() { return this->value; }
Setter  -> void setValue(int v) { validate; this->value = v; }
this->  -> current object ka member refer karo
```

---

## 12. Complete Master Summary

### Saare Topics Ka Bird's Eye View

```text
Programming History:
Machine Language -> Assembly -> Procedural -> OOP
(Binary)           (MOV A)    (Functions)  (Objects)

OOP Core:
Object = Variables + Methods
Class  = Blueprint for Objects

Case Study:
Procedural = scattered variables, manual passing, no scaling
OOP        = encapsulated classes, object interaction, clean scaling

Pillars (Covered):
Abstraction   = Chhupao complexity, expose simple interface
Encapsulation = Bundle karo + protect karo data

Pillars (Next Lecture):
Inheritance   = Parent -> Child, code reuse
Polymorphism  = Ek interface, anek forms
```

### OOP Pillars Reference Table

| Pillar | Kya Hai | Real World | Code Mechanism |
|---|---|---|---|
| **Abstraction** | Complexity hide karo | Car steering wheel: engine nahi dikhata | Virtual functions, abstract classes |
| **Encapsulation** | Bundle + protect | Odometer directly change nahi hoti | `private` + getters/setters |
| **Inheritance** | Parent -> Child | Dog is-a Animal | `class Dog : public Animal` |
| **Polymorphism** | Ek naam, anek forms | `makeSound()` -> Dog barks, Cat meows | Virtual + override |

---

## 13. FAQs

### Q1: OOP Sirf C++ Mein Hai?

Nahi. OOP ek paradigm hai. Java, Python, JavaScript classes, C#, Kotlin, Swift: sab OOP support karte hain. Concepts same hain, syntax alag.

### Q2: Har Cheez Ke Liye OOP Use Karein?

Nahi. Simple scripts ya quick utilities ke liye procedural better ho sakta hai. OOP complex, large-scale applications ke liye shine karta hai.

### Q3: Abstract Class Mein Kuch Implementation Bhi De Sakte Hain?

Haan. Abstract class mein kuch concrete methods bhi ho sakte hain, kuch pure virtual bhi. Pure interface mein sab methods pure virtual hote hain.

### Q4: JavaScript Mein OOP Kaise Karte Hain?

```js
class Car {
    #currentSpeed = 0;  // Private field (ES2022)

    get speed() {
        return this.#currentSpeed;
    }

    accelerate(amount) {
        if (this.#currentSpeed + amount > 200) return;
        this.#currentSpeed += amount;
    }
}
```

`#` = private field in modern JavaScript. Same concept, different syntax.

### Q5: Getter/Setter Banana Zaroori Hai? Property Directly Public Kyun Nahi?

Public karna dangerous hai: koi bhi invalid value set kar sakta hai. Getter/Setter se tujhe control milta hai: validation, logging, computed properties.

---

## 14. Real-World Use Cases: Prime Cup Context

### 1. Tournament Registration System

```js
class Tournament {
    #players = [];
    #maxPlayers;

    constructor(max) {
        this.#maxPlayers = max;
    }

    get playerCount() {
        return this.#players.length;  // Getter
    }

    register(playerName) {            // Validated setter equivalent
        if (this.#players.length >= this.#maxPlayers) {
            throw new Error("Tournament full!");
        }

        this.#players.push(playerName);
    }
}
```

### 2. Payment Processing: Abstraction

```js
// Abstract interface
class PaymentGateway {
    processPayment(amount) {
        throw new Error("Implement me!");
    }
}

class Razorpay extends PaymentGateway {
    processPayment(amount) {
        /* Razorpay specific logic */
    }
}

class Cashfree extends PaymentGateway {
    processPayment(amount) {
        /* Cashfree specific logic */
    }
}

// Client code unchanged when switching gateways!
const gateway = new Razorpay(); // or Cashfree
gateway.processPayment(500);
```

> **Additional Explanation**
>
> Payment gateways abstraction ka excellent real-world example hain. Client code sirf `processPayment()` call karta hai. Razorpay ya Cashfree ki internal API details hidden rehti hain.

---

## 15. One-Page Final Cheat Sheet

```text
+---------------------+-----------------------------------------------+
| Topic               | Revision                                      |
+---------------------+-----------------------------------------------+
| Machine Language    | Binary (01010): never for modern apps         |
| Assembly            | MOV A, 61H: hardware coupled                  |
| Procedural          | Functions + loops, no real-world modeling     |
| OOP Reason          | Scalable, reusable, secure, real-world        |
| Object              | Variables (chars) + methods (behaviors)       |
| Class               | Blueprint for creating objects                |
| Abstraction         | Hide complexity, expose interface             |
| Virtual fn (C++)    | virtual void fn() = 0; (pure virtual)         |
| Encapsulation       | Bundle + protect with access modifiers        |
| private             | Compiler error if accessed outside class      |
| Getter              | int get() { return this->val; }               |
| Setter              | void set(T v) { validate; this->val = v; }    |
| this->              | Current object ka reference                   |
| Abstract vs Encap   | Abstraction = hide HOW, Encap = protect DATA  |
+---------------------+-----------------------------------------------+
```
