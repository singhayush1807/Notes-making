
# 1. 🧬 Inheritance — Parent-Child Relationship

## Kya Hai?

Inheritance OOP ka ek fundamental pillar hai jo **Parent-Child relationship** represent karta hai classes ke beech mein. Child class apne parent class ke characteristics (variables) aur behaviors (methods) **inherit** kar leta hai — matlab automatically access mil jaata hai bina dobara likhne ke.

**Ek line definition:** "Child ko parents se property milti hai — coding mein bhi!"

## Kyun Exist Karta Hai?

Real world mein cheezein related hoti hain. "Manual Car" aur "Electric Car" dono fundamentally "Car" hain. Inka kuch common hai — engine start karna, accelerate karna, brake lagana. Inheritance isi real-world hierarchy ko code mein mimic karta hai.

## Kya Problem Solve Karta Hai?

**Code duplication eliminate karta hai.**

```cpp
// BINA Inheritance (BAD):
class ManualCar {
    string brand, model;
    void startEngine() { ... }  // ← Yahan
    void accelerate() { ... }   // ← Yahan
};

class ElectricCar {
    string brand, model;
    void startEngine() { ... }  // ← Phir se wahi code!
    void accelerate() { ... }   // ← Again same code!
};
// Agar startEngine() logic change karna pade? Dono jagah change karo!

// Inheritance KE SAATH (GOOD):
class Car {
    void startEngine() { ... }  // ← Ek baar likha
    void accelerate() { ... }   // ← Ek baar likha
};
class ManualCar : public Car { /* sirf unique stuff */ };
class ElectricCar : public Car { /* sirf unique stuff */ };
// startEngine() change karna? Sirf Car class mein karo — done!
```

## Intuition — Desi Analogy 👨‍👩‍👧

Sochlo tere baap ke paas ek factory hai. Tu unka beta hai — tujhe automatically factory milegi + tere apne skills bhi add honge. Teri behen ko bhi factory milegi + uske apne skills honge. Dono ko factory likhne ki zaroorat nahi — ek baar likhi, dono ko mili.

***

## Real-World Example: Car Hierarchy

**Parent (Generic):** `Car`

| Common Characteristics | Common Behaviors |
|---|---|
| `brand` | `startEngine()` |
| `model` | `stopEngine()` |
| `isEngineOn` | `accelerate()` |
| `currentSpeed` | `brake()` |

**Children (Specialized):**

| `ManualCar` | `ElectricCar` |
|---|---|
| `currentGear` (extra) | `batteryLevel` (extra) |
| `shiftGear()` (extra) | `chargeBattery()` (extra) |

## Class Hierarchy Diagram

```
                    ┌─────────────────────────┐
                    │       Parent: Car        │
                    ├─────────────────────────┤
                    │ - brand                  │
                    │ - model                  │
                    │ - isEngineOn             │
                    │ - currentSpeed           │
                    ├─────────────────────────┤
                    │ + startEngine()          │
                    │ + stopEngine()           │
                    │ + accelerate()           │
                    │ + brake()                │
                    └────────────┬────────────┘
                                 │
               ┌─────────────────┴──────────────────┐
               │                                     │
               ▼                                     ▼
┌──────────────────────────┐      ┌──────────────────────────┐
│    Child: ManualCar       │      │    Child: ElectricCar     │
├──────────────────────────┤      ├──────────────────────────┤
│ - currentGear            │      │ - batteryLevel            │
├──────────────────────────┤      ├──────────────────────────┤
│ + shiftGear()            │      │ + chargeBattery()         │
└──────────────────────────┘      └──────────────────────────┘
  (Also has startEngine(),           (Also has startEngine(),
   accelerate() etc. inherited)       accelerate() etc. inherited)
```

## C++ Code — Complete Implementation

```cpp
// 1. PARENT CLASS
class Car {
protected:
    // Protected: child access kar sakte hain, bahar nahi
    string brand;
    string model;
    bool isEngineOn = false;
    int currentSpeed = 0;

public:
    void startEngine() {
        isEngineOn = true;
        cout << "Engine Started!" << endl;
    }

    void stopEngine() {
        isEngineOn = false;
        cout << "Engine Stopped!" << endl;
    }

    void accelerate() {
        currentSpeed += 10;
        cout << "Speed: " << currentSpeed << endl;
    }

    void brake() {
        currentSpeed -= 10;
        cout << "Speed: " << currentSpeed << endl;
    }
};

// 2. CHILD CLASS 1 — Manual Car
class ManualCar : public Car {  // ← public inheritance
private:
    int currentGear = 0;  // ManualCar specific — private kyunki koi ManualCar se inherit nahi karta

public:
    void shiftGear() {
        currentGear++;
        cout << "Shifted to Gear: " << currentGear << endl;
    }
};

// 3. CHILD CLASS 2 — Electric Car
class ElectricCar : public Car {  // ← public inheritance
private:
    int batteryLevel = 100;  // ElectricCar specific

public:
    void chargeBattery() {
        batteryLevel = 100;
        cout << "Battery: Full Charge!" << endl;
    }
};

// 4. MAIN — Usage
int main() {
    ManualCar wagonR;       // Suzuki Wagon R object
    ElectricCar tesla;      // Tesla Model S object

    wagonR.startEngine();   // ✅ Inherited from Car
    wagonR.shiftGear();     // ✅ ManualCar specific

    tesla.startEngine();    // ✅ Inherited from Car
    tesla.chargeBattery();  // ✅ ElectricCar specific

    // tesla.shiftGear();   // ❌ ERROR! Electric car mein gear nahi!
    return 0;
}
```

### Line-by-Line Breakdown

- `protected:` parent mein — child classes access kar sakti hain, `main()` nahi kar sakta. Encapsulation ka perfect balance.
- `class ManualCar : public Car` — ManualCar, Car se publicly inherit kar rahi hai. Colon (`:`) = "inherits from."
- `wagonR.startEngine()` — `wagonR` ek ManualCar hai, lekin `startEngine()` Car mein define tha. Phir bhi kaam karta hai — inheritance ki wajah se.
- `tesla.shiftGear()` — ❌ Compile error! `shiftGear()` sirf `ManualCar` mein hai, `ElectricCar` mein nahi. Yeh real-world logic perfectly represent karta hai — electric car mein gear nahi hota!

### Common Beginner Mistakes ⚠️

```cpp
// Mistake 1: Common methods child mein dobara likhna
class ManualCar {
    void startEngine() { ... }  // ← Duplicate! Car mein already hai
};

// Mistake 2: Wrong class pe child-specific method call karna
ElectricCar tesla;
tesla.shiftGear(); // ← Error! tesla ko gear nahi pata

// Mistake 3: Private members access karna child mein
class Car {
    private:
        int currentSpeed;  // ← Private
};
class ManualCar : public Car {
    void speedUp() {
        currentSpeed += 10;  // ← ERROR! Private member, child bhi access nahi kar sakta
    }
};
// Fix: 'protected' use karo parent mein
```

***

✔ **Summary — Inheritance**
Inheritance = Parent class mein common code likho, Child classes inherit karein. Code duplication khatam. Child apne specialized features add kar sakta hai. Real-world hierarchy exactly represent hoti hai.

✔ **Cheat Sheet**
```
class Child : public Parent { }  ← Inheritance syntax
Child gets: parent ke public + protected members
Child doesn't get: parent ke private members
Child adds: apni unique variables + methods
Common mistake: shiftGear() on ElectricCar = ERROR
```

✔ **Interview Questions**
1. Inheritance kya hai? Kya problem solve karta hai?
2. `protected` aur `private` mein kya fark hai inheritance ke context mein?
3. Agar `startEngine()` ManualCar aur ElectricCar dono mein dobara likha — kya galat hai?
4. `class Child : public Parent` — yahan `public` kyun likha?

✔ **Practice Problems**
1. `Animal` parent class banao — `name`, `age` variables, `eat()`, `sleep()` methods. `Dog` aur `Bird` child classes banao — `Dog` mein `fetch()`, `Bird` mein `fly()` add karo.
2. `SmartPhone` aur `BasicPhone` — dono `Phone` se inherit karein. Common features identify karo.

✔ **Revision Notes**
- Inheritance = code reuse via parent-child
- `:public Parent` = inheritance syntax in C++
- `protected` = child access kar sakta, outside world nahi
- Child-specific method = sirf usi class ka object call kar sakta hai

***

# 2. 🔐 Access Modifiers in Inheritance — Rules Ka Khel

## Teen Modifiers Ka Recap

| Modifier | Class Ke Andar | Child Classes | Outside (`main()`) |
|---|---|---|---|
| `public` | ✅ | ✅ | ✅ |
| `protected` | ✅ | ✅ | ❌ |
| `private` | ✅ | ❌ | ❌ |

## Teen Types of Inheritance

### 1. Public Inheritance `:public Parent` (99% use cases)

Parent ka **public → child mein public** rehta hai
Parent ka **protected → child mein protected** rehta hai
Parent ka **private → child mein inaccessible** (exist karta hai but access nahi)

```cpp
class ManualCar : public Car {
    // Car ka public method startEngine() → ManualCar mein bhi public
    // Car ka protected var currentSpeed → ManualCar mein bhi protected
    // Car ka private var (agar koi ho) → exist karta hai but use nahi kar sakte
};
```

### 2. Private Inheritance `:private Parent` (rare)

Parent ka **public → child mein private ho jaata hai**
Parent ka **protected → child mein private ho jaata hai**

```cpp
class ManualCar : private Car {
    // startEngine() → ab ManualCar mein private hai
};

class WagonR : public ManualCar {
    // WagonR ko Car ka kuch bhi nahi milega!
    // ManualCar ne sab private kar liya
};
```

**Result:** Ek third class jo `ManualCar` se inherit kare, use Car ka kuch bhi nahi milega. **Inheritance chain break ho jaati hai.**

### 3. Protected Inheritance `:protected Parent` (very rare)

Parent ka **public → child mein protected ho jaata hai**

**Interview Rule:** Practically, **99% cases mein public inheritance hi use karo.** Private/Protected inheritance core OOP principle todte hain — child class fully parent represent nahi kar paata.

## Memory Trick 🧠

```
Public    = Sab ko milta hai (students, faculty, visitors)
Protected = Sirf family ko milta hai (parents, children)
Private   = Sirf apna (class ke andar hi)
```

***

✔ **Summary — Access Modifiers in Inheritance**
`public` inheritance = parent's interface fully preserved in child. `private` inheritance = parent's stuff locked inside child, chain breaks. Real-world LLD mein always `public` inheritance use karo.

✔ **Cheat Sheet**
```
Public inheritance:
  parent public → child public ✅
  parent protected → child protected ✅
  parent private → inaccessible ❌

Private inheritance:
  parent public → child private 🔒
  (inheritance chain breaks!)

Best practice: Always use public inheritance in LLD/interviews
```

✔ **Interview Questions**
1. `public`, `private`, `protected` inheritance mein kya fark hai?
2. Private inheritance kyun use nahi karte?
3. `protected` variables parent mein kyun rakhte hain instead of `private`?

***

# 3. 🦆 Polymorphism — Ek Naam, Anek Roop

## Kya Hai?

**Poly** = Many (bahut saare)
**Morphism** = Forms (roop)

**Polymorphism = Ek cheez ke bahut saare roop**

Programming mein iska matlab hai:
1. **Alag-alag objects** same stimulus pe **alag-alag react** karte hain
2. **Ek hi object** same method ko **alag parameters** pe alag tarike se execute karta hai

## Kyun Exist Karta Hai?

Client ko sirf "kya trigger karna hai" pata hona chahiye — "kaise execute hoga" object khud decide kare. System dynamic aur adaptable banta hai bina interface change kiye.

## Real-World Scenario — Animal Example 🐾

**Scenario 1 — Different objects, same stimulus:**
```
Stimulus: run()

Duck runs     → waddling motion, slow
Human runs    → upright bipedal motion
Tiger runs    → quadrupedal sprint, 80 km/h

Same command "run()" — teen alag reactions!
```

**Scenario 2 — Same object, different parameters:**
```
Human.run()              → Normal jog (leisurely)
Human.run(isDanger=true) → Full sprint (tiger peeche hai!)

Same object (human), same method name — different behavior based on input!
```

## Polymorphism Ke 2 Types

| Type | Doosra Naam | Kab Decide Hota Hai? | Mechanism |
|---|---|---|---|
| **Dynamic** | Run-time, Method Overriding | Runtime pe (execution ke time) | `virtual` functions + `override` |
| **Static** | Compile-time, Method Overloading | Compile time pe | Same method name, different parameters |

***

# 4. 🔄 Dynamic Polymorphism — Method Overriding (Runtime)

## Kya Hai?

Jab **child class apne parent class ke method ki naye implementation de deta hai** — same method name, same signature, lekin child ka apna specific logic.

**Dusra naam:** Run-time Polymorphism, Method Overriding

## Kyun "Run-time"?

Kyunki compiler decide nahi karta kaun sa method chalega — **program ke runtime pe** decide hota hai ki object kaunsi class ka hai aur uska `override` method chale.

## Kaise Kaam Karta Hai?

1. Parent class method ko `virtual` declare karta hai → "main declare karta hoon, children define karein"
2. Child classes us method ko `override` karte hain apni specific logic ke saath
3. Method signature (naam, return type, parameters) **exactly same** rehna chahiye
4. Caller same method name use karta hai — runtime pe sahi version automatically chalta hai

## Car Example — ManualCar vs ElectricCar

```
ManualCar.accelerate()   → speed += 20 (high pickup, gears hain)
ElectricCar.accelerate() → speed += 15, battery -= 5 (EV style, lower pickup)

Same method call: car->accelerate()
Different behavior: depends on actual object type at runtime
```

## Code — Complete Dynamic Polymorphism

```cpp
// PARENT — Abstract Interface
class Car {
protected:
    int currentSpeed = 0;

public:
    // virtual + = 0 → Pure virtual (abstract method)
    // "Main declare karta hoon, children ko define karna ZAROORI hai"
    virtual void accelerate() = 0;
    virtual void brake() = 0;

    void startEngine() {
        cout << "Engine Started!" << endl;
    }
};

// CHILD 1 — Manual Car Override
class ManualCar : public Car {
private:
    int currentGear = 0;

public:
    void accelerate() override {     // ← override keyword = "main parent ka method replace kar raha hoon"
        currentSpeed += 20;          // High pickup — gears hain
        cout << "ManualCar accelerated! Speed: " << currentSpeed << endl;
    }

    void brake() override {
        currentSpeed -= 20;
        cout << "ManualCar braked! Speed: " << currentSpeed << endl;
    }

    void shiftGear() {
        currentGear++;
        cout << "Shifted to Gear: " << currentGear << endl;
    }
};

// CHILD 2 — Electric Car Override
class ElectricCar : public Car {
private:
    int batteryLevel = 100;

public:
    void accelerate() override {
        if (batteryLevel > 0) {
            batteryLevel -= 5;           // Battery drain hoti hai
            currentSpeed += 15;          // Lower pickup (EV style)
            cout << "ElectricCar accelerated! Speed: " << currentSpeed
                 << " | Battery: " << batteryLevel << "%" << endl;
        } else {
            cout << "Battery dead! Charge karo pehle!" << endl;
        }
    }

    void brake() override {
        currentSpeed -= 15;              // Regenerative braking style
        cout << "ElectricCar braked (regenerative)! Speed: " << currentSpeed << endl;
    }

    void chargeBattery() {
        batteryLevel = 100;
        cout << "Battery: Full Charge!" << endl;
    }
};

// MAIN — Runtime Polymorphism in action
int main() {
    Car* car1 = new ManualCar();   // ← Car pointer, ManualCar object
    Car* car2 = new ElectricCar(); // ← Car pointer, ElectricCar object

    car1->accelerate();
    // Output: ManualCar accelerated! Speed: 20

    car2->accelerate();
    // Output: ElectricCar accelerated! Speed: 15 | Battery: 95%

    // Runtime pe decide hota hai: car1 ManualCar ka accelerate chalaaye
    // car2 ElectricCar ka accelerate chalaaye
    // Same line: car->accelerate() — alag outputs!

    return 0;
}
```

### Line-by-Line Breakdown

- `virtual void accelerate() = 0;` — Pure virtual. Car class abstract ho gayi — directly instantiate nahi ho sakti. `new Car()` = ERROR.
- `void accelerate() override` — `override` keyword:
  - Compiler ko batata hai ki "main intentionally parent ka method replace kar raha hoon"
  - Agar method signature galat likha toh compiler error dega — safety net!
- `Car* car1 = new ManualCar()` — **Yahi magic hai!** Pointer `Car` type ka hai, lekin actual object `ManualCar` ka. Runtime pe `ManualCar` ka `accelerate()` chalega.
- `batteryLevel -= 5; currentSpeed += 15;` — ElectricCar ka accelerate bilkul alag logic — battery drain aur kam speed increment.

### Advanced: `virtual` Table (vTable) — Andar Kya Hota Hai?

Runtime polymorphism internally **vtable (virtual function table)** ke through kaam karta hai:

```
Car class ki vtable:
  accelerate → [pure virtual, no address]
  brake      → [pure virtual, no address]

ManualCar ki vtable:
  accelerate → ManualCar::accelerate() ka address
  brake      → ManualCar::brake() ka address

ElectricCar ki vtable:
  accelerate → ElectricCar::accelerate() ka address
  brake      → ElectricCar::brake() ka address

Jab car1->accelerate() call hota hai:
  car1 ki vtable dekho → ManualCar::accelerate() → execute!
```

Yahi "runtime" mein decide hota hai — isliye "Runtime Polymorphism."

### Edge Case: `override` Kyun Important Hai?

```cpp
class ManualCar : public Car {
    void accelerate() {    // ← override likhna bhool gaye
        currentSpeed += 20;
    }
};

// Agar parent mein signature change ho: virtual void accelerate(int x) = 0;
// Aur child mein purana: void accelerate() — yeh override nahi hoga!
// Child ek NAYI method define kar raha hoga, override nahi
// 'override' keyword hota toh compiler error deta — caught at compile time!
```

***

✔ **Summary — Dynamic Polymorphism**
Same method name, different behavior in different child classes. `virtual` parent mein + `override` child mein. Runtime pe actual object type decide karta hai kaun sa version chale. vtable internally manage karta hai.

✔ **Cheat Sheet**
```
Dynamic Polymorphism = Method Overriding = Runtime Polymorphism

Parent:  virtual void method() = 0;   ← declare
Child:   void method() override { }   ← define/replace

Car* ptr = new ManualCar();  ← Car pointer, actual ManualCar
ptr->accelerate();           ← ManualCar's version runs at runtime

Rule: Same name + Same return type + Same parameters (signature same!)
```

✔ **Interview Questions**
1. Dynamic polymorphism kya hai? Example do.
2. `virtual` keyword kyun use karte hain?
3. Method overriding mein method signature same kyun rehni chahiye?
4. `override` keyword ka kya faida hai?
5. vtable kya hota hai? Runtime polymorphism internally kaise kaam karta hai?

✔ **Practice Problems**
1. `Shape` abstract class banao — `area()` pure virtual. `Circle`, `Rectangle`, `Triangle` — teeno apna `area()` implement karein.
2. `PaymentGateway` abstract class — `processPayment(int amount)` pure virtual. `Razorpay` aur `Cashfree` override karein different fee logic ke saath.

✔ **Revision Notes**
- Dynamic = runtime pe decide
- `virtual` + `= 0` = pure virtual = abstract method
- `override` = safety keyword, signature mismatch pakadta hai
- Same method name → different class → different behavior

***

# 5. ⚡ Static Polymorphism — Method Overloading (Compile-time)

## Kya Hai?

**Ek hi class mein same naam ke multiple methods** — but different parameters (number ya type).

**Doosra naam:** Compile-time Polymorphism, Method Overloading

## Kyun "Compile-time"?

Kyunki compiler dekh leta hai arguments — `accelerate()` call hai ya `accelerate(40)` call hai — compile hone ke time pe hi decide ho jaata hai kaun sa method chalega. Runtime tak wait nahi karna.

## Kaise Kaam Karta Hai?

Compiler arguments ka **pattern matching** karta hai:
- `accelerate()` — no argument → Method 1
- `accelerate(40)` — int argument → Method 2
- `accelerate(40.5f)` — float argument → Method 3 (agar likha ho)

## Car Example

```
accelerate()       → Default: +20 km/h (normal driving)
accelerate(speed)  → Custom: +speed km/h (specific input)
```

## Code — Complete Static Polymorphism

```cpp
class ManualCar {
private:
    int currentSpeed = 0;

public:
    // Method 1: No arguments — default acceleration
    void accelerate() {
        currentSpeed += 20;
        cout << "Default acceleration! Speed: " << currentSpeed << endl;
    }

    // Method 2: Same name, ONE int argument — custom acceleration
    void accelerate(int speed) {
        currentSpeed += speed;
        cout << "Custom acceleration by " << speed << "! Speed: " << currentSpeed << endl;
    }

    // Method 3: Same name, FLOAT argument — percentage acceleration (bonus example)
    void accelerate(float percentage) {
        int boost = currentSpeed * percentage;
        currentSpeed += boost;
        cout << "Percentage acceleration! Speed: " << currentSpeed << endl;
    }
};

int main() {
    ManualCar wagonR;

    wagonR.accelerate();      // ← Calls Method 1 (no args) → Speed: 20
    wagonR.accelerate(40);    // ← Calls Method 2 (int arg) → Speed: 60
    wagonR.accelerate(0.5f);  // ← Calls Method 3 (float arg) → Speed: 90

    return 0;
}
```

### Compile-Time Decision Making

```
Compile time mein:
wagonR.accelerate()     → No match? Method 1 mein () hai → ✅ Method 1
wagonR.accelerate(40)   → 40 is int → Method 2 mein (int speed) → ✅ Method 2
wagonR.accelerate(0.5f) → 0.5f is float → Method 3 mein (float) → ✅ Method 3
```

### Dynamic vs Static — Side-by-Side

| Aspect | Dynamic (Overriding) | Static (Overloading) |
|---|---|---|
| **Kahan?** | Parent-Child relationship mein | Same class mein |
| **Method signature** | Same (bilkul same) | Same naam, different parameters |
| **Decide kab?** | Runtime pe | Compile time pe |
| **Keyword** | `virtual` + `override` | Koi keyword nahi |
| **Real-world** | ManualCar vs ElectricCar accelerate | accelerate() vs accelerate(40) |
| **Mechanism** | vtable | Compiler argument matching |

### Common Mistake ⚠️

```cpp
// Overloading NAHI hai — sirf return type alag hai — INVALID
void accelerate() { currentSpeed += 20; }
int accelerate()  { return currentSpeed; } // ← ERROR! Same signature, compiler confused!

// Overloading HAI — parameters alag hain
void accelerate()          { } // ← different param count
void accelerate(int speed) { } // ← ✅ Valid overload
```

### Trade-offs

**Advantage:** Intuitive code — `accelerate(40)` likhna `accelerateByAmount(40)` se zyada natural lagta hai.

**Disadvantage:** Bahut zyada overloads → confusion. 5+ versions of same method naam = code samajhna mushkil.

***

✔ **Summary — Static Polymorphism**
Same method naam, different parameters, same class mein. Compiler decide karta hai arguments dekh ke. Readable code — ek naam, multiple use cases.

✔ **Cheat Sheet**
```
Static Polymorphism = Method Overloading = Compile-time Polymorphism

Same class mein:
void method()          ← version 1
void method(int x)     ← version 2
void method(float x)   ← version 3

Compiler sees call → matches arguments → calls correct version
Return type CHANGE karna = NOT overloading (compile error!)
```

✔ **Interview Questions**
1. Method overloading kya hai? Example do.
2. Method overloading aur method overriding mein kya fark hai?
3. Sirf return type change karke overloading ho sakti hai? Kyun nahi?
4. Static polymorphism "compile-time" kyun hai?

✔ **Practice Problems**
1. `Calculator` class banao — `add(int, int)`, `add(float, float)`, `add(int, int, int)` — teeno overloads.
2. `print(int)`, `print(string)`, `print(float)` — ek class mein teeno likho. Compiler kaise decide karta hai?

✔ **Revision Notes**
- Overloading = same name, different params, same class
- Overriding = same name, same params, parent-child
- Compile-time = compiler decides before running
- Return type alone = NOT valid overloading

***

# 6. 🏆 Grand Unified OOP Example — Sab Pillars Ek Saath

## Sab Kuch Ek System Mein

```cpp
// ============================================
// ALL 4 OOP PILLARS IN ONE SYSTEM
// ============================================

// PILLAR 1: ABSTRACTION
// virtual methods expose karte hain interface, implementation chhupate hain
class Car {
protected:
    // PILLAR 2: ENCAPSULATION
    // Protected variables — bahar nahi, lekin children access kar sakte hain
    string brand;
    string model;
    bool isEngineOn = false;
    int currentSpeed = 0;

public:
    Car(string b, string m) : brand(b), model(m) {}

    void startEngine() {
        isEngineOn = true;
        cout << brand << " Engine Started!" << endl;
    }

    void stopEngine() {
        isEngineOn = false;
        cout << brand << " Engine Stopped!" << endl;
    }

    // ABSTRACTION: Pure virtual — children will define HOW
    virtual void accelerate() = 0;
    virtual void brake() = 0;
};

// PILLAR 3: INHERITANCE
// ManualCar inherits from Car
class ManualCar : public Car {
private:
    int currentGear = 0;

public:
    ManualCar(string b, string m) : Car(b, m) {}  // Parent constructor call

    // PILLAR 4: DYNAMIC POLYMORPHISM (Overriding)
    void accelerate() override {
        currentSpeed += 20;
        cout << brand << " accelerated by 20! Speed: " << currentSpeed << endl;
    }

    void brake() override {
        currentSpeed -= 20;
        cout << brand << " braked! Speed: " << currentSpeed << endl;
    }

    // STATIC POLYMORPHISM (Overloading) — same naam, different params
    void accelerate(int customSpeed) {
        currentSpeed += customSpeed;
        cout << brand << " accelerated by " << customSpeed
             << "! Speed: " << currentSpeed << endl;
    }

    void shiftGear() {
        currentGear++;
        cout << "Shifted to Gear " << currentGear << endl;
    }
};

// PILLAR 3: INHERITANCE
// ElectricCar inherits from Car
class ElectricCar : public Car {
private:
    int batteryLevel = 100;

public:
    ElectricCar(string b, string m) : Car(b, m) {}

    // PILLAR 4: DYNAMIC POLYMORPHISM (Overriding — different from ManualCar)
    void accelerate() override {
        if (batteryLevel > 0) {
            batteryLevel -= 5;
            currentSpeed += 15;
            cout << brand << " accelerated by 15! Speed: " << currentSpeed
                 << " | Battery: " << batteryLevel << "%" << endl;
        }
    }

    void brake() override {
        currentSpeed -= 15;  // Regenerative braking
        cout << brand << " regenerative brake! Speed: " << currentSpeed << endl;
    }

    void chargeBattery() {
        batteryLevel = 100;
        cout << brand << " Battery: Full Charge!" << endl;
    }
};

// MAIN — All pillars working together
int main() {
    ManualCar wagonR("Suzuki WagonR", "LXI");
    ElectricCar tesla("Tesla", "Model S");

    // Inheritance + Dynamic Polymorphism
    wagonR.startEngine();      // Engine Started!
    wagonR.accelerate();       // Accelerated by 20!
    wagonR.accelerate(40);     // Static Polymorphism — Accelerated by 40! (overloaded)
    wagonR.shiftGear();        // Shifted to Gear 1
    wagonR.stopEngine();       // Engine Stopped!

    cout << "---" << endl;

    tesla.startEngine();       // Engine Started!
    tesla.accelerate();        // Accelerated by 15! Battery: 95%
    tesla.accelerate();        // Accelerated by 15! Battery: 90%
    tesla.brake();             // Regenerative brake!
    tesla.chargeBattery();     // Battery: Full Charge!
    tesla.stopEngine();        // Engine Stopped!

    return 0;
}
```

## 4 Pillars Ka Map

```
ABSTRACTION:    virtual void accelerate() = 0  → interface exposed, logic hidden
ENCAPSULATION:  protected currentSpeed, brand   → bahar se direct access blocked
INHERITANCE:    ManualCar : public Car           → code reuse, no duplication
POLYMORPHISM:
  Dynamic:      ManualCar/ElectricCar override accelerate() differently
  Static:       accelerate() vs accelerate(int) in ManualCar
```

***

# 7. 🏠 Homework: Operator Overloading

## Interviewer Ka Question

> **"What is Operator Overloading in C++? Why do modern languages like Java and Python not support it?"**

### Operator Overloading Kya Hai?

C++ mein tu built-in operators (`+`, `-`, `*`, `==`, `<<`) ko custom classes ke saath redefine kar sakta hai.

```cpp
class Vector2D {
public:
    int x, y;
    Vector2D(int x, int y) : x(x), y(y) {}

    // '+' operator overload kiya
    Vector2D operator+(const Vector2D& other) {
        return Vector2D(x + other.x, y + other.y);
    }
};

int main() {
    Vector2D v1(1, 2), v2(3, 4);
    Vector2D v3 = v1 + v2;  // ← Custom '+' operator!
    // v3.x = 4, v3.y = 6
}
```

Yeh bhi ek tarah ka **Static Polymorphism** hai — same operator (`+`), different types pe different behavior.

### Java/Python Mein Kyun Nahi?

| C++ | Java/Python |
|---|---|
| Operator overloading allowed | Mostly not allowed (Java), limited (Python) |
| Reason: Maximum control, systems programming | Reason: Readability, predictability |
| `a + b` can mean ANYTHING | `a + b` always means standard addition |
| Risk: `a + b` could delete a file — confusing | Safety: No surprises |

**Java ka stand:** "Operators have clear meanings. Overloading confuses readers — `a + b` should always add, not do something custom." Java prefers explicit method names like `add(b)`.

**Python ka stand:** Python limited operator overloading allow karta hai `__add__`, `__mul__` etc. through **dunder methods** — controlled, but possible.

***

# 8. ✍️ Final One-Page Cheat Sheet

```
╔═══════════════════════════════════════════════════════════════════╗
║       INHERITANCE + POLYMORPHISM — MASTER CHEAT SHEET            ║
╠══════════════════════════╦════════════════════════════════════════╣
║ Inheritance              ║ class Child : public Parent { }        ║
║ Why                      ║ Code reuse, no duplication             ║
║ Protected                ║ Child can access, outside can't        ║
║ Private inheritance      ║ Breaks chain — avoid in LLD            ║
║ Public inheritance       ║ 99% use cases — always use this        ║
╠══════════════════════════╬════════════════════════════════════════╣
║ Dynamic Polymorphism     ║ Method Overriding = Runtime            ║
║ Keywords                 ║ virtual (parent) + override (child)    ║
║ Signature rule           ║ Must be EXACTLY same                   ║
║ How                      ║ vtable decides at runtime              ║
╠══════════════════════════╬════════════════════════════════════════╣
║ Static Polymorphism      ║ Method Overloading = Compile-time      ║
║ Rule                     ║ Same name, different parameters        ║
║ Decided when             ║ Compiler decides before running        ║
║ Return type change       ║ NOT valid overloading!                 ║
╠══════════════════════════╬════════════════════════════════════════╣
║ Operator Overloading     ║ C++ only (mostly), redefine operators  ║
║ Java/Python              ║ Avoid for readability + safety         ║
╚══════════════════════════╩════════════════════════════════════════╝
```
