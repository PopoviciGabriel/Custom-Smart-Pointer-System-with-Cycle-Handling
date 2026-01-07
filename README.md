# Custom Smart Pointer System with Cycle Handling

A lightweight C++ implementation of `SharedPtr` and `WeakPtr`, built from scratch with a custom reference-counting `ControlBlock`.  
The library demonstrates how modern C++ manages dynamic memory, ownership, and object lifetimes — including safe handling of cyclic references (e.g., parent–child scene graphs).

---

## ✨ Features

- **SharedPtr**
  - Manual reference counting
  - Full Rule of Five support (copy/move ctor + copy/move assignment + destructor)
  - Const-correct dereference operators
  - `get()` accessor and `explicit operator bool()`
  - Automatic cleanup and controlled resource ownership

- **WeakPtr**
  - Non-owning references to SharedPtr-managed objects
  - `expired()` check + `lock()` for safe temporary access
  - Correct lifecycle behavior matching the semantics of `std::weak_ptr`

- **Cycle-Safe Scene Graph**
  - Children own parents via `SharedPtr`
  - Parents reference children via `WeakPtr`
  - Prevents reference cycles and memory leaks

- **Modular Structure**
  - `SmartPtr.hpp` – smart pointer system
  - `Node.hpp` – example object graph (scene tree)
  - `main.cpp` – demonstration of usage

---

## 📁 Project Structure

/src
SmartPtr.hpp # Custom SharedPtr, WeakPtr, and ControlBlock
Node.hpp # Node type using custom smart pointers
main.cpp # Example usage (scene graph)

yaml
Copiază codul

---

## 🧩 Example

```cpp
SharedPtr<Node> root(new Node());
SharedPtr<Node> child(new Node());

root->children.push_back(child);
child->parent = root; // WeakPtr prevents strong reference cycle
🧪 Building
Compile using any modern C++ compiler supporting C++17 or newer:

bash
Copiază codul
g++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o SmartPtrDemo
./SmartPtrDemo
🎓 Educational Purpose
This project is ideal for:

Learning how smart pointers are implemented internally

Understanding reference counting, weak references, and object lifetime

Interview preparation for modern C++ roles

Portfolio demonstration of memory management concepts

Exploring RAII, Rule of Five, and low-level resource control

📜 License
MIT License — free to study, use, or modify.

👤 Author
Created by Gabris —
C++ enthusiast focused on smart pointers, templates, and modern C++ design.
