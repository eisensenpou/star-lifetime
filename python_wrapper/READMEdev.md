### EPIC 0.1 — Define the Python User’s Goal

#### Python Binder Role
This Python binder serves as a **glue layer** for developers who want to
*consume* the C++ stellar lifetime library without interacting with its
internal physics or numerical implementation.

The binder exposes a **stable, developer-friendly scientific interface**
while preserving the C++ engine as the single source of truth.

---

#### What a Python User Wants
- An easy-to-use, high-level scientific interface
- Clear and complete documentation
- Simple installation and minimal setup
- Sensible defaults that avoid manual configuration

---

#### What a Python User Needs
- Access to validated scientific computation functions
- Explicit and documented unit conventions
- Selection among supported, pre-defined model or integrator options
- Ability to compute results for single stars or defined systems
- Minimal configuration, except for structured system definitions (e.g. JSON)

---

#### What a Python User Must NEVER Do
- Modify or override physics models
- Alter numerical or simulation logic
- Inject custom computation behavior
- Access or mutate internal namespace or state


### EPIC 0.2 — Binding Mindset Calibration

The Python binder exposes **only well-defined function endpoints** of the
C++ library. Python users interact strictly through inputs and outputs and
have no visibility into, or influence over, the internal physics,
numerical methods, or execution flow.

The binder acts as a **pure translation layer**:
- Mapping Python-level parameters to validated C++ calls
- Returning computed results without modification
- Propagating errors explicitly and transparently

No scientific logic, numerical decisions, or fallback behavior exists
in the Python layer.

---

#### Architectural Commitment

A poorly designed binding layer creates long-term maintenance debt.
Therefore, the binding architecture and public APIs must be designed
deliberately so that:

- The **separation between Python and C++ responsibilities** is obvious
- Future developers can reason about the system without reading internals
- Changes to Python bindings **do not require** changes to the C++ core

Maintainability, clarity, and scientific integrity take priority over
short-term convenience.


### EPOCH 1

---

#### EPIC 1.1 — Public vs Internal Boundary

The Python bindings are restricted to a **clearly defined subset of public
C++ headers**. These headers constitute the official, binding-safe API
surface of the library.

Only the following headers are exposed:

**num_analysis namespace**
- differentiation.h     (approved)
- errors.h              (approved)
- integration.h         (approved)

**physics namespace**
- constants.h           (approved)
- star_physics.h        (approved)

**utility**
- util.h (contains writeToCSV; treated as a convenience API)

---

util.h is a provisional convenience API and not part of the core scientific contract.

#### Boundary Enforcement

- Internal headers are not visible to the binding layer
- No implementation-only types leak into public headers
- `using namespace` directives have been removed from all public headers
- Public headers are minimal, explicit, and dependency-controlled

The exposed headers have been reviewed for:
- Clear ownership semantics
- Absence of internal state leakage
- Suitability for long-term binding stability

Any future expansion of the public surface must be deliberate and reviewed
against binding and scientific stability requirements.



#### EPIC 1.2 — Ownership & Lifetime Audit

The following checks were performed as part of the public header review and
constitute the full scope of EPIC 1.2.

---

### Ownership & Lifetime
- All exposed public APIs use value semantics
- No raw pointer ownership crosses the public API boundary
- Python will not be responsible for managing or deleting C++ objects
- No lifetime coupling exists between separate API calls

---

### State & Mutability
- No global mutable state is exposed through public headers
- No hidden static caches affect observable behavior
- Public-facing functions are deterministic and side-effect free
  (except explicitly documented I/O utilities)

---

### Error Safety
- Errors are expressed explicitly through domain-level mechanisms
- No undefined behavior is exposed to API consumers
- Error semantics are suitable for later mapping to Python exceptions

---

### Binding Risk Assessment
- No ABI-hostile constructs are present in public headers
- No template-heavy interfaces are exposed publicly
- No internal or implementation-only types leak into the API surface

---

### Noted Exception
- `util.h` contains I/O and formatting utilities (e.g. CSV export)
- This header is classified as **provisional / convenience**
- It is not part of the core scientific contract and may change independently

---

#### EPIC 1.3 — Scientific Contract Clarification

The C++ core operates under a **fixed and explicit scientific unit system**.
All public APIs assume and enforce this contract.

---

#### Unit System

- Base physical quantities are expressed in **SI units**
  (kilograms, seconds, watts, meters)
- Stellar quantities are expressed using **solar reference constants**
  defined in `include/physics/constants.h`

The following constants define the authoritative reference system:
- Solar mass (M_SUN) in kilograms
- Solar luminosity (L_SUN) in watts
- Time expressed in seconds, with conversion constants provided
- Energy and relativistic terms expressed in SI units

No implicit unit conversion is performed by the library.

---

#### Valid Input Domain

- All public functions expect inputs expressed in the documented unit system
- Physically invalid or nonsensical inputs (e.g. negative mass) are considered
  domain errors
- Behavior for invalid inputs is explicit and documented (error signaling),
  not silently corrected

---

#### Numerical Assumptions

- All computations use double-precision floating-point arithmetic
- Numerical behavior is deterministic for valid inputs
- Overflow or underflow outside physically meaningful ranges is not guaranteed
  to be handled gracefully unless explicitly documented

---

#### Contract Guarantees

- Scientific meaning of inputs and outputs is stable across releases
- Changes to constants or unit conventions constitute breaking changes
- Language bindings must respect and preserve this unit contract

### EPOCH 2

---

#### EPIC 2.1 — Python API Shape Decisions

The Python interface is designed as a **function-centric, stateless API**.
Python users interact with the library by invoking explicit scientific
computation functions and receiving deterministic results.

Python does not expose long-lived model objects, mutable state, or simulation
entities. All computations are performed in the C++ core and invoked through
clear input/output function boundaries.

---

#### Core Design Principles

- The primary mental model for Python users is:
  **“I compute stellar properties.”**
- Not:
  **“I create and manipulate star objects.”**

- Each Python-visible function represents a single, well-defined scientific
  computation.
- All required inputs are provided explicitly per call.
- All results are returned explicitly per call.
- No hidden configuration, caching, or retained state exists across calls.

---

#### Scalar vs Batch Policy

- The API is **scalar-first** by design.
- Each function operates on a single logical system or input set.
- Batch or population-level workflows are achieved through Python-side
  orchestration (e.g. loops, scripts), not implicit vectorization.

This avoids ambiguous error semantics and preserves clarity of scientific
meaning per computation.

---

#### API Surface Layering

The Python interface is conceptually divided into layers:

- **High-Level / Core API**
  - Minimal parameters
  - Strong, documented defaults
  - Intended for most users and common workflows

- **Advanced / Expert API**
  - Exposes lower-level numerical con


#### EPIC 2.2 — Error & Behavior Mapping

The Python API exposes **explicit and fail-fast error behavior** that mirrors
the scientific and numerical guarantees of the C++ core.

Errors are never silently ignored, corrected, or converted into fallback
results.

---

#### Error Classification

All failures fall into one of the following categories:

**Domain Errors (User Input Errors)**
- Inputs that violate physical meaning or documented constraints
- Examples: negative mass, invalid parameter combinations
- Behavior: computation fails immediately with a descriptive error

**Numerical Errors (Computation Failures)**
- Failures due to numerical limits or instability
- Examples: non-convergence, overflow, underflow
- Behavior: computation fails with an explicit numerical error

**Internal Errors (Programmer Errors)**
- Violations of internal assumptions or invariants
- Indicative of bugs, not user misuse
- Behavior: treated as fatal and non-recoverable

---

#### Error Message Quality Requirements

All Python-visible errors must be **descriptive and actionable**.

Each raised error message should:
- Clearly identify the nature of the failure
- State what input or condition caused the error
- Indicate whether the issue is due to user input, numerical limits, or internal failure
- Reference the relevant documentation or contract section where the constraint is defined

Example (conceptual):
- “DomainError: stellar mass must be positive and expressed in solar masses.
  See: Scientific Contract — Valid Input Domain.”

Errors are treated as part of the public API and are subject to the same
clarity and stability expectations as function interfaces.

---

#### Python-Level Error Semantics

- All C++ errors are surfaced as Python exceptions
- No error is converted into a return value
- No warning-only failures are permitted
- One failed computation results in one raised exception

---

#### Behavioral Guarantees

- Valid inputs produce deterministic results
- Identical inputs yield identical outputs
- Invalid inputs never produce partial or approximate results
- Undefined or unsupported behavior is explicitly documented as such

---

#### Architectural Commitment

The Python layer does not alter, suppress, or reinterpret errors originating
from the C++ core. Error handling prioritizes scientific correctness,
predictability, and reproducibility over convenience.

---

#### EPIC 2.3 — Naming & Stability Rules

The Python API follows **strict, scientifically grounded naming and stability
rules** to ensure long-term usability, reproducibility, and trust.

Public names are treated as part of the scientific contract and are not changed
casually.

---

#### Naming Principles

- Public Python names prioritize scientific clarity over brevity
- Names reflect physical meaning, not implementation details
- One scientific concept maps to one public name
- No aliases or redundant naming are introduced without necessity
- Naming remains consistent with documented physics terminology

---

#### C++ to Python Mapping

- Python function names mirror the conceptual meaning of C++ APIs
- No new vocabulary is invented at the Python layer
- Python bindings do not rename or reinterpret scientific concepts
- Helper or convenience abstractions do not obscure underlying physics

---

#### Stability Guarantees

The following are considered **breaking changes**:
- Renaming or removing public functions
- Changing parameter units, meaning, or defaults
- Altering error behavior or error categories
- Changing numerical interpretation of outputs

The following are **non-breaking changes**:
- Adding new functions or capabilities
- Adding optional parameters with safe defaults
- Performance improvements with identical results
- Documentation and example improvements

---

#### Deprecation Policy

- Deprecated APIs are explicitly marked and documented
- No public API is removed without prior deprecation
- Deprecation includes guidance on replacement usage
- Deprecated APIs remain available for at least one minor release cycle

---

#### Architectural Commitment

API stability and scientific reproducibility take precedence over aesthetic or
convenience-driven changes. Evolution of the API is deliberate, additive, and
documented.

---

#### EPIC 3.1 — Binding Layer Responsibilities

The Python binding layer serves strictly as an **invocation and translation
boundary** between Python users and the C++ computational core.

Python users may select which public computation to execute and provide
parameters for that computation, but they have no ability to alter the
underlying implementation, execution flow, or scientific logic.

---

#### Allowed Responsibilities

The binding layer is permitted to:
- Expose selected public C++ functions to Python
- Accept and validate Python-level input parameters
- Translate Python inputs into C++-compatible representations
- Invoke C++ computations exactly as defined
- Return computed results back to Python
- Surface C++ errors as Python exceptions without reinterpretation

---

#### Forbidden Responsibilities

The binding layer must NOT:
- Implement or duplicate scientific or numerical logic
- Modify or override physics models or algorithms
- Alter execution order or computation workflow
- Maintain hidden state that influences results
- Provide extension hooks or user-defined computation paths
- Silently adjust, clamp, or reinterpret user inputs

---

#### Architectural Principle

The binding layer is a **thin, transparent conduit**, not a behavioral layer.

All scientific meaning, numerical correctness, and execution semantics are
defined and enforced by the C++ core. Python acts only as a controlled interface
for parameterization and result retrieval.

Any change in scientific behavior must originate in the C++ implementation and
never in the binding layer.

--- 

#### EPIC 3.2 — Memory Ownership & Thread-Safety

This project follows a conservative and explicit boundary policy for memory
ownership and concurrency to ensure correctness, stability, and maintainability.

---

#### Memory Ownership Policy

- The C++ core owns all internal memory, state, and computation resources.
- Python is a caller-only interface: it provides inputs and receives results.
- Python must not obtain ownership of, or direct access to, internal C++
  buffers or mutable state.
- Returned results must be self-contained from the Python perspective and must
  remain valid independent of C++ internal lifetimes.

The binding layer must not expose APIs that allow Python users to mutate
internal computation state or influence memory lifetimes inside the C++ core.

---

#### Thread-Safety Policy

Thread-safety guarantees are explicit and must not be implied.

- Default guarantee (until proven otherwise): no concurrency guarantee is
  assumed for shared usage.
- The architecture is designed to support *re-entrant / thread-compatible*
  operation (independent calls from multiple threads) provided the C++ core
  does not rely on mutable global state, hidden caches, or shared mutable
  singletons.

If full thread-compatible behavior is claimed in the future, it must be backed
by documented constraints and tests.

---

#### Architectural Commitment

**Correctness and scientific reproducibility take precedence over optimistic
threading claims**. Memory and concurrency semantics are part of the public API
contract and are documented as first-class requirements.

---

### EPIC 3.3 — ABI & Build Assumptions (Notes)

- C++ does NOT provide a stable ABI across:
  - different compilers
  - compiler versions
  - standard libraries
  - operating systems

- Therefore:
  - One binary cannot safely work everywhere
  - Precompiled binaries are environment-specific artifacts

---

#### Distribution Strategy

- Precompiled binaries (Python wheels) are provided as a **convenience**
- Source builds are always supported and considered authoritative
- Users must be able to compile bindings locally if needed

---

#### Compiler & Platform Reality

- Different OSes require different builds
- Different compilers may produce incompatible binaries
- Rebuilding is expected when:
  - compiler changes
  - OS changes
  - Python version changes
  - C++ core changes

---

#### ABI Guarantees

- No global ABI stability is promised
- Binary compatibility is limited to documented CI-tested environments
- Mixing binaries built with incompatible toolchains is unsupported

---

#### CI Role

- CI defines what is officially supported
- If it builds and tests in CI → it is supported
- If not covered by CI → source build is required

---

#### Design Priority

- Scientific correctness > binary convenience
- Transparency > fragile compatibility promises
- Honest constraints > “works everywhere” claims

---

#### EPIC 4.1 — Distribution Model & Installation Paths

The project is distributed using a **dual-path installation model** to balance
usability and portability.

---

#### Supported Distribution Formats

- **Precompiled binaries (Python wheels)**
  - Provided as a convenience for supported platforms
  - Intended for fast installation and common use cases
  - Built and tested only for CI-supported environments

- **Source distribution**
  - Always available and supported
  - Considered the authoritative and most portable installation method
  - Required for unsupported platforms, custom toolchains, or HPC environments

---

#### Installation Guarantees

- All releases provide a source distribution
- Precompiled binaries are provided on a best-effort basis
- Lack of a binary for a platform is not considered a defect if source builds succeed

---

#### Architectural Commitment

Ease of installation must not compromise scientific correctness, ABI honesty,
or long-term maintainability. Source builds remain a first-class installation
path.

---

#### EPIC 4.2 — Platform Support Policy

Platform support is defined explicitly and enforced through continuous
integration. Support claims are based on testing and build verification, not
best intentions.

---

#### Support Tiers

**Tier 1 — Officially Supported**
- Built and tested in CI
- Precompiled binaries (wheels) provided
- Issues are treated as defects and prioritized

**Tier 2 — Source-Supported**
- Source builds are expected to work
- CI coverage may be partial or limited
- Users may need to compile locally
- Issues are investigated on a best-effort basis

**Tier 3 — Unsupported / Best Effort**
- Not tested in CI
- No guarantees are made
- Community contributions are welcome

---

#### Platform Roadmap

**Linux**
- Tier 1 (primary supported platform)
- Wheels and source distributions provided
- CI defines supported environments

**Windows**
- Tier 1 (secondary supported platform)
- Wheels provided once CI coverage is stable
- Source builds always supported

**macOS**
- Tier 2 (source-supported)
- CI-validated only
- Local testing not required
- Wheels provided on a best-effort basis, if available

---

#### Support Definition

A platform is considered supported if and only if it is built and tested
successfully in CI. Platforms outside the CI matrix require source builds and
are not guaranteed to work.

---

#### Architectural Commitment

Support claims are conservative, explicit, and test-driven. Scientific
correctness and maintainability take precedence over broad but fragile platform
coverage.

---

#### EPIC 4.3 — Release, Documentation & CI Alignment

A release is considered **official** only if it meets explicit documentation,
testing, and distribution requirements. Releases are not published solely
because code exists.

---

#### Documentation Requirements

Each release must include clear and complete documentation that:

- Explains the purpose and scientific scope of the library
- Documents all public Python-facing functions
- Explicitly states assumptions, unit systems, and limitations
- Clearly describes what the library **does NOT do**
- Warns against misuse or interpretation outside the documented contract

Documentation is treated as part of the public API.

---

#### CI & Release Gate

- All Tier 1 platforms must pass CI before a release is published
- Source builds must succeed in CI
- Failures in CI block official releases
- Precompiled binaries are published only for CI-validated platforms

CI defines release readiness.

---

#### Artifact Publishing Rules

- Source distributions are always published for every release
- Precompiled binaries are published only for supported platforms
- No “partial” or undocumented releases are allowed

---

#### Reproducibility & Scientific Integrity

- Releases correspond to fixed, versioned scientific behavior
- Changes affecting scientific interpretation require version bumps
- Reproducibility expectations are documented and enforced

---

#### Citation Policy

- Users are requested to cite the project when used in academic or
  scientific work
- Citation instructions are provided in the documentation
- Citation guidance includes version information for reproducibility

---

#### Architectural Commitment

Documentation, CI status, and scientific clarity are first-class release
criteria. Convenience or speed of release must not compromise correctness,
reproducibility, or user understanding.

---

### EPIC 5.1 — Cross-Language Consistency Validation

**Goal:**  
Verify that Python bindings preserve the numerical results, error behavior,
and determinism of the C++ core.

C++ is treated as the authoritative reference implementation.

---

#### Validation Scope

For each C++ function exposed to Python:

1. **Numeric Consistency**
   - Identical inputs must produce numerically equivalent outputs
   - Results must match within the same tolerance used by C++ accuracy tests

2. **Error Consistency**
   - Inputs that fail in C++ must fail in Python
   - Error category and scientific meaning must be preserved
   - No errors are swallowed, converted to warnings, or replaced with defaults

3. **Deterministic Behavior**
   - Repeated calls with the same inputs produce identical results
   - No hidden state is introduced by the binding layer

---

#### Out of Scope

- Physics validation or model correctness
- Performance benchmarking
- Stress or fuzz testing
- Python-only behavior not present in C++

---

#### Acceptance Criteria

A Python binding is considered correct if:
- It numerically matches the C++ reference
- It fails when C++ fails
- It introduces no additional behavior or state

Any deviation is treated as a binding defect.

--- 

### EPIC 5.2 — User-Facing Trust & Confidence

**Goal:**  
Ensure that Python users understand what the library does, how to use it
correctly, and how to avoid misuse that could lead to incorrect scientific
interpretation.

---

#### Trust-Building Principles

- Clarity is prioritized over feature breadth
- Explicit constraints are better than implicit assumptions
- Users are guided toward correct usage, not “best guesses”

---

#### Required User-Facing Elements

- Clear examples demonstrating correct usage of core functions
- Explicit documentation of:
  - Required units
  - Valid input ranges
  - Error behavior
- A clearly visible section describing:
  - What the library does **NOT** do
  - Common misuse patterns and why they are incorrect

---

#### Error Messaging & Guidance

- Errors surfaced to Python users must be:
  - Descriptive
  - Actionable
  - Scientifically meaningful
- Error messages should guide users toward:
  - Correct input usage
  - Relevant documentation sections

Errors are treated as part of the educational interface.

---

#### Reproducibility Expectations

- Users are encouraged to record:
  - Library version
  - Input parameters
  - Units used
- Documentation emphasizes reproducibility as a first-class concern

---

#### Scientific Credit & Citation

- Users are requested to cite the project in academic or scientific work
- Citation instructions are clearly documented
- Citation guidance includes versioning information for reproducibility

---

#### Acceptance Criteria

User-facing documentation and examples must make it difficult to:
- Misinterpret results
- Use incorrect units silently
- Assume unsupported behavior

Trust is established through explicit constraints, not implicit behavior.

---
# END
