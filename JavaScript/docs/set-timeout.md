# ⏱️ setTimeout in JavaScript

!!! note "Core Idea"
    JavaScript is single-threaded, but it can still handle asynchronous work using Web APIs, the Callback Queue, and the Event Loop.

`setTimeout()` is one of the most important concepts in JavaScript interviews because it teaches how async code works behind the scenes.

## 1. What happens when `setTimeout()` is used?

When you write:

```javascript
setTimeout(() => {
  console.log("Hello");
}, 3000);
```

JavaScript does not wait forever for the timer. Instead, it hands the callback and timer to the browser/Web API and continues executing the next lines.

### Flow of execution

| Step | What happens |
|---|---|
| 1 | JavaScript receives `setTimeout` |
| 2 | Callback + timer are sent to the Web API |
| 3 | JS continues immediately to the next line |
| 4 | Timer runs in the background |
| 5 | When timer expires, callback goes to the Callback Queue |
| 6 | Event Loop checks whether the Call Stack is empty |
| 7 | Callback is pushed to the Call Stack and executed |

## 2. Exact flow in simple words

```text
JS gets setTimeout
   ↓
Callback + timer → Web API
   ↓
JS continues immediately
   ↓
Timer keeps counting in background
   ↓
Timer expires → callback goes to Callback Queue
   ↓
Event Loop sees Call Stack is empty
   ↓
Callback executes
```

## 3. Example 1 — Annotated walkthrough

```javascript
function x() {
  var i = 1;

  setTimeout(function () {
    console.log(i);
  }, 3000);

  console.log("Namaste JavaScript");
}

x();
```

### Output

```
Namaste JavaScript
1
```

### Why this works

!!! tip "Closure concept"
    The callback closes over the variable `i`. It does not get a copy of the value; it gets a reference to the variable. When the timer finishes, it reads the latest value from memory.

## 4. Important note about delay

!!! warning "Delay is not guaranteed exactly"
    `setTimeout(fn, 3000)` means “wait at least 3000ms”, not “wait exactly 3000ms”.

If the Call Stack is busy, the callback will be delayed even more.

### Example

```javascript
console.log("A");
setTimeout(() => console.log("B"), 0);
console.log("C");
```

### Output

```text
A
C
B
```

Why does `B` appear last? Because even a `0ms` timer still has to go through the event loop pipeline.

## 5. Quick cheat sheet

| Concept | Meaning |
|---|---|
| `setTimeout(fn, delay)` | Runs a function later |
| JS is non-blocking | It does not stop for the timer |
| Web API | Handles the timer outside the main thread |
| Callback Queue | Stores callbacks waiting for execution |
| Event Loop | Moves callbacks to the Call Stack when ready |

## 6. The famous interview question — print 1 to 5 with delays

### Problem

Create a function that prints:

```text
1 after 1 second
2 after 2 seconds
3 after 3 seconds
4 after 4 seconds
5 after 5 seconds
```

### Naive approach

```javascript
function x() {
  for (var i = 1; i <= 5; i++) {
    setTimeout(function () {
      console.log(i);
    }, i * 1000);
  }
  console.log("Namaste JavaScript");
}

x();
```

### Expected output

```text
Namaste JavaScript
1
2
3
4
5
```

### Actual output

```text
Namaste JavaScript
6
6
6
6
6
```

### Why this happens

!!! danger "Common trap"
    `var` is function-scoped, so all callbacks share the same `i`. By the time the timers fire, the loop has already finished and `i` becomes `6`.

## 7. Solution 1 — use `let`

```javascript
function x() {
  for (let i = 1; i <= 5; i++) {
    setTimeout(function () {
      console.log(i);
    }, i * 1000);
  }
}

x();
```

### Why it works

`let` is block-scoped. Every iteration gets its own independent `i`, so each callback captures its own value correctly.

### Quick memory idea

- `var` → one shared variable → problem
- `let` → new variable each iteration → solution

## 8. Solution 2 — use `var` with a wrapper function

```javascript
function x() {
  for (var i = 1; i <= 5; i++) {
    function close(x) {
      setTimeout(function () {
        console.log(x);
      }, x * 1000);
    }

    close(i);
  }
}

x();
```

### Why it works

Each call to `close(i)` creates a new execution context with its own local `x`. So every timer gets a different captured value.

### IIFE version

```javascript
for (var i = 1; i <= 5; i++) {
  (function (x) {
    setTimeout(() => console.log(x), x * 1000);
  })(i);
}
```

## 9. Memory diagram

```text
Memory (function scope of x())
┌──────────────────────────┐
│   var i = 6              │
└──────────────────────────┘
         ↑  ↑  ↑  ↑  ↑
         │  │  │  │  │
      CB1 CB2 CB3 CB4 CB5
```

All callbacks point to the same `i`, so when they run, they see the final value `6`.

## 10. Interview questions

- What is the difference between `setTimeout(fn, 0)` and calling `fn()` directly?
- What is the Event Loop and how does it interact with the Call Stack?
- Why is `setTimeout` delay not exactly guaranteed?
- How does JavaScript handle asynchronous code even though it is single-threaded?
- Why does `var` + `setTimeout` print `6` in a loop?

## 11. Revision notes

!!! success "Remember"
    - `setTimeout` sends work to the Web API.
    - The callback waits in the Callback Queue.
    - The Event Loop brings it to the Call Stack when possible.
    - `var` causes shared binding issues in loops.
    - `let` is the clean modern fix.

## 12. Summary

- `setTimeout` makes code asynchronous.
- It does not block the main thread.
- Delay is a minimum wait, not an exact timer.
- `var` inside loops can cause the classic “all callbacks see the final value” bug.
- `let` or a wrapper function fixes this problem.
