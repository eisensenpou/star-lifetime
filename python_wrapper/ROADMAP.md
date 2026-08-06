# 📌 Project Roadmap — C++ Stellar Lifetime Engine → Python Interface

> Principle:
> C++ is the source of truth.
> Python is a stable, scientific-facing interface.

---

## 🌍 EPOCH 0 — Orientation & Mental Model

**Goal:**  
Understand what is being built before touching bindings or tools.

### EPIC 0.1 — Define the Python User’s Goal
- [X] Write a one-sentence description of what a Python user wants to do
- [X] Decide whether Python users think in terms of:
  - [X] Pure functions
  - [X] Scientific models
  - [X] Batch evaluations
- [X] Explicitly list what Python users must **never** control

### EPIC 0.2 — Binding Mindset Calibration
- [X] Understand that Python will only see the public API
- [X] Accept that bad C++ APIs become permanent Python debt
- [X] Commit to “design first, bind later”

---

## 🧱 EPOCH 1 — C++ Public API Freeze & Hardening

**Goal:**  
Make the C++ interface binding-safe and scientifically explicit.

### EPIC 1.1 — Public vs Internal Boundary
- [X] Identify which headers are truly public
- [X] Confirm no internal headers leak into the public surface
- [X] Ensure public headers are stable and minimal

### EPIC 1.2 — Ownership & Lifetime Audit
- [X] Verify no raw pointer ownership is exposed
- [X] Confirm all outputs have clear ownership rules
- [X] Ensure no global mutable state affects results

### EPIC 1.3 — Scientific Contract Clarification
- [X] Document valid input ranges (mass, assumptions, etc.)
- [X] Document units explicitly
- [X] Define behavior for invalid inputs (errors, not UB)

> 🚫 Do NOT:
> - Refactor internals for Python
> - Add Python-specific conditionals
> - Change algorithms

---

## 🧠 EPOCH 2 — Python API Design (NO BINDINGS YET)

**Goal:**  
Design how Python feels without choosing any binding technology.

### EPIC 2.1 — API Shape Decisions
- [X] Decide scalar vs batch-first usage
- [X] Decide function-based vs object-based API
- [X] Decide whether state exists on the Python side

### EPIC 2.2 — Error & Behavior Mapping
- [X] Define which C++ errors become Python exceptions
- [X] Decide whether Python ever sees partial results
- [X] Define floating-point consistency expectations

### EPIC 2.3 — Naming & Stability Rules
- [X] Choose naming conventions (scientific clarity > brevity)
- [X] Decide what is public vs advanced
- [X] Commit to backward compatibility rules

---

## 🔌 EPOCH 3 — Binding Architecture & Boundary Rules

**Goal:**  
Define how Python and C++ interact safely.

### EPIC 3.1 — Binding Layer Responsibilities
- [X] Binding layer contains no physics
- [X] Binding layer performs validation only
- [X] Binding layer never owns core data

### EPIC 3.2 — Memory & Threading Policy
- [X] C++ owns all internal memory
- [X] Python never deletes core objects
- [X] Thread-safety assumptions are explicit

### EPIC 3.3 — ABI & Build Assumptions
- [X] Decide rebuild vs binary compatibility strategy
- [X] Decide compiler constraints
- [X] Decide supported Python versions (conceptually)

> 🚫 Do NOT:
> - Mix binding logic into core headers
> - Allow Python to mutate internal state
> - Hide errors for convenience

---

## 📦 EPOCH 4 — Packaging & Distribution Strategy

**Goal:**  
Make this usable by real scientific users.

### EPIC 4.1 — Distribution Model
- [X] Decide wheels vs source builds
- [X] Define platform support expectations
- [X] Define minimum toolchain versions

### EPIC 4.2 — Versioning & Reproducibility
- [X] Align version numbers with scientific meaning
- [X] Define deprecation policy
- [X] Document reproducibility guarantees

### EPIC 4.3 — Documentation Expectations
- [X] Write “What this library does” clearly
- [X] Write “What this library does NOT do”
- [X] Add citation / academic usage guidance

---

## 🧪 EPOCH 5 — Validation & Confidence Building

**Goal:**  
Prove the bindings did not damage scientific integrity.

### EPIC 5.1 — Cross-Language Consistency
- [X] Verify Python results match C++ results
- [X] Validate edge cases
- [X] Confirm error behavior parity

### EPIC 5.2 — User-Facing Trust
- [X] Add examples (conceptual, not hacks)
- [X] Document numerical assumptions
- [X] Set expectations clearly

---

## 🧭 Current Status
