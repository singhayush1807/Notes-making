# SetTimeout

JS single-threaded hai, kabhi nahi rukti. **setTimeout** callback ko **Web API** ko deta hai, JS aage badh jaati hai. Timer expire hone ke baad callback **Callback Queue** mein jaata hai, phir **Event Loop** use **Call Stack** pe push karta hai.

## setTimeout Ka Exact Flow

1. JS ko setTimeout mila
   ↓
2. Callback + Timer → Web API ko de diya
   ↓
3. JS turant aage badh gayi (next line execute ki)
   ↓
4. Background mein timer countdown ho raha hai...
   ↓
5. Timer expire hua → Callback → Callback Queue mein gaya
   ↓
6. Event Loop ne dekha: Call Stack empty hai!
   ↓
7. Callback → Call Stack pe push → Execute!

## Example 1 — Annotated Walkthrough

```javascript
function x() {
  var i = 1;

  setTimeout(function() {   // ← Step 1: Callback Web API ko gaya, 3s ka timer laga
    console.log(i);          // ← Step 4: 3 second baad yahan aayega
  }, 3000);

  console.log("Namaste JavaScript"); // ← Step 2: TURANT execute
}
x(); // ← Step 3: x() poora hua, Call Stack se hata
```

**Output:**

```text
Namaste JavaScript   ← turant
1                    ← 3 second baad
```

> **Cheat Sheet:**
>
> setTimeout(fn, delay):
>   → fn + timer → Web API
>   → JS continues (non-blocking)
>   → Timer expires → fn → Callback Queue
>   → Call Stack empty → Event Loop → fn execute
>
> Delay = MINIMUM wait, not guaranteed exact time
> setTimeout(fn, 0) ≠ fn() directly

> **Interview Questions**
>
> setTimeout(fn, 0) aur direct fn() call mein kya fark hai?
>
> Event Loop kya hai? Call Stack se kaise interact karta hai?
>
> setTimeout ka delay exactly guaranteed kyun nahi hota?
>
> JavaScript single-threaded hote hue bhi async kaise handle karta hai?

> **NOTES:**
> Yeh 1 kyun print hua sahi se?
> Kyunki callback ne closure bana liya i ke saath. Matlab callback ke paas i ka reference (address) tha — value copy nahi. Jab 3 second baad callback chala, usne i dhundha → mila 1 → print ho gaya.
>
> **Ek Aur Important Point — Delay Guaranteed Nahi:**
> setTimeout(fn, 3000) ka matlab ye nahi ki exactly 3000ms baad chalega. Iska matlab hai minimum 3000ms baad chalega. Agar Call Stack us waqt busy hai, toh aur wait karega.
>
> **Example**
> ```javascript
> // Example: setTimeout(fn, 0) bhi immediately nahi chalta
> console.log("A");
> setTimeout(() => console.log("B"), 0); // 0ms delay
> console.log("C");
> // Output: A, C, B
> // B last kyun? Kyunki 0ms ka bhi Web API pipeline se guzarna padta hai
> ```

## Memory Diagram

```text
MEMORY (x() ka function scope):
┌──────────────────────────┐
│   var i = 6              │ ← ek akela i, loop ne 6 kar diya
└──────────────────────────┘
         ↑  ↑  ↑  ↑  ↑
         │  │  │  │  │
       CB1 CB2 CB3 CB4 CB5   ← sab isi ek i ko point kar rahe hain
      (1s)(2s)(3s)(4s)(5s)
```

Jab bhi callback chale: i dhundho → 6 mila → 6 print

## Summary — Section 2

var function-scoped hai = ek shared i. Loop milliseconds mein khatam, i = 6. Sab closures same reference pakde hain. Timer fire hone pe sab i = 6 dekhte hain.

> **Cheat Sheet**
>
> ```text
> var + for loop + setTimeout = TRAP!
> ├── var = function scope = 1 shared i
> ├── Loop ends instantly → i = 6
> ├── All callbacks → same i reference → see 6
> └── Even delay = 0 → same problem
> ```
>
> **Interview Questions**
>
> for(var i=1; i<=5; i++) ke saath setTimeout kyun 6 print karta hai?
>
> Loop khatam hone ke baad i ki value kya hoti hai aur kyun?
>
> setTimeout(fn, 0) bhi 6 print karta hai — explain karo.

## 🎯 The Famous Interview Question: 1 to 5 Print Karo Delays Se

**Problem Statement:**
"Ek function likho jo 1 second baad 1, 2 second baad 2, 3 second baad 3... aisa karke 5 tak print kare."

**Naive Approach — Beginner Galti**
Zyaadatar developers yeh likhte hain:

```javascript
function x() {
  for (var i = 1; i <= 5; i++) {
    setTimeout(function() {
      console.log(i);         // Yahan i ka value kya hoga?
    }, i * 1000);
  }
  console.log("Namaste JavaScript");
}
x();
```

**Developers ka expectation:**

```text
Namaste JavaScript
1  (1 second baad)
2  (2 second baad)
3  (3 second baad)
4  (4 second baad)
5  (5 second baad)
```

**Actual Output:**

```text
Namaste JavaScript     ← turant
6                      ← ~1 second baad
6                      ← ~2 second baad
6                      ← ~3 second baad
6                      ← ~4 second baad
6                      ← ~5 second baad
```

**Kyu Hota Hai??**
Jab 1 second baad pehla callback execute hota hai — loop toh kab ka khatam ho chuka, i = 6 memory mein hai. Callback i ka address dhundha → 6 mila → print kiya. Yahi sab 5 callbacks ke saath hua.

## ✅ Solution 1: let Use Karo — Easy Fix

**Why It Works — Deep Dive**
let block-scoped hai. for loop ka har iteration ek naya block {} create karta hai. Har iteration mein let i ke saath brand new, independent variable banta hai memory mein.

let block-scoped hai = har loop iteration ka apna independent i. Har callback apne i ke saath closure banata hai. Problem solved.

> **Cheat Sheet**
>
> var → function scope → 1 shared i → ❌
> let → block scope → 5 independent i → ✅
> const → for loop mein → ❌ (reassign nahi hoti)
> const → for...of mein → ✅ (new binding per iteration)

**Revision Notes**

let = new variable per iteration = new lexical environment per iteration

Sabse clean aur modern fix

Interviewer agle question mein let ban kar sakta hai → Solution 2 ready rakho

## 🧠 Solution 2: With VAR

**Code:**

```javascript
function x() {
  for (var i = 1; i <= 5; i++) {

    function close(x) {              // Wrapper function
      setTimeout(function() {
        console.log(x);             // x = local variable, i nahi
      }, x * 1000);
    }

    close(i);                        // Turant call karo current i ke saath
  }
}
x();
```

**Output:**

```text
1  (1 second baad) ✅
2  (2 second baad) ✅
...
5  (5 second baad) ✅
```

**Why it Works:**
Jab tu close(i) call karta hai, JavaScript ek brand new execution context banata hai close ke liye apni local memory ke saath. Parameter x us local memory mein store hota hai — bilkul alag, i se connected nahi.

**Uderstand :**
Loop Iteration 1 (i = 1):
  close(1) call hua
  → New Execution Context: { x: 1 }  ← apna alag x
  → setTimeout register: callback closes over x = 1
  → close() execution khatam

Loop Iteration 2 (i = 2):
  close(2) call hua
  → NEW Execution Context: { x: 2 }  ← BILKUL ALAG x
  → setTimeout register: callback closes over x = 2

...same for 3, 4, 5

**MOST IMPORTANT :**
**Summary — Section 4**
Function call karne se new execution context banta hai apni local memory ke saath. close(i) se i ki current value x parameter ke roop mein capture hoti hai. Har call ka apna alag x — problem solved bina let ke.

> **Cheat Sheet**
>
> ```javascript
> // Named wrapper
> function close(x) {
>   setTimeout(() => console.log(x), x * 1000);
> }
> for (var i = 1; i <= 5; i++) { close(i); }
> 
> // IIFE version
> for (var i = 1; i <= 5; i++) {
>   (function(x) {
>     setTimeout(() => console.log(x), x * 1000);
>   })(i);
> }
> ```