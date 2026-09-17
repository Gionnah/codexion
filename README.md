*This project has been created as part of the 42 curriculum by mvelonja.*

# Codexion

## Description

Codexion is a concurrent programming project based on POSIX threads.

The program simulates several coders competing for shared USB dongles. Each
coder is represented by a thread and needs two dongles at the same time to
compile.

After compiling, a coder releases the dongles, then performs debugging and
refactoring before requesting the dongles again.

The simulation stops when one of the following conditions is reached:

- A coder burns out because they could not start compiling before their
  deadline.
- All coders have completed the required number of compilations.

The project implements two scheduling policies:

- `fifo`: requests are handled according to their arrival order.
- `edf`: requests are handled according to the earliest burnout deadline.

A priority queue implemented as a heap is used for dongle requests.

## Instructions

### Compilation

Compile the project with:

```bash
make
```

Other available commands:

```bash
make clean
make fclean
make re
```

### Execution

The program requires the following arguments:

```text
./codexion number_of_coders time_to_burnout time_to_compile \
time_to_debug time_to_refactor number_of_compiles_required \
dongle_cooldown scheduler
```

The scheduler must be either `fifo` or `edf`.

Example:

```bash
./codexion 10 200 50 50 50 5 0 edf
```

FIFO example:

```bash
./codexion 10 200 50 50 50 5 0 fifo
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coder threads |
| `time_to_burnout` | Maximum time before a coder must start compiling |
| `time_to_compile` | Compilation duration |
| `time_to_debug` | Debugging duration |
| `time_to_refactor` | Refactoring duration |
| `number_of_compiles_required` | Number of successful compilations required |
| `dongle_cooldown` | Time before a released dongle becomes available |
| `scheduler` | `fifo` or `edf` |

All time values are expressed in milliseconds.

## Resources

The project is based on the following concepts and resources:

- POSIX threads (`pthread`)
- Mutexes
- Condition variables
- Thread synchronization
- Priority queues and binary heaps
- FIFO scheduling
- Earliest Deadline First (EDF) scheduling
- `gettimeofday()` and `clock_gettime()`
- `pthread_cond_timedwait()`

The 42 Codexion subject was the main specification used to implement the
simulation.

AI tools were used as a learning and debugging aid during development,
particularly to understand POSIX thread synchronization, mutexes,
condition variables, scheduling concepts, memory management and debugging
strategies. The implementation was tested and adapted manually to the
project requirements.

## Blocking cases handled

The program handles the following situations:

- Multiple coders requesting the same dongle.
- A coder requiring two dongles simultaneously.
- Several requests waiting for the same dongle.
- Dongle cooldown after release.
- FIFO request ordering.
- EDF request ordering.
- Simulation shutdown after a coder burns out.
- Simulation shutdown after all required compilations are completed.
- Synchronization between coder threads and the monitor thread.
- Memory cleanup after normal execution.
- Partial initialization failures.
- The special case of a single coder using one dongle.

The scheduler uses a heap to avoid relying on the order in which threads are
scheduled by the operating system.

## Thread synchronization mechanisms

### Mutexes

Mutexes protect shared simulation data and prevent concurrent modifications.

The project uses synchronization for:

- Simulation state.
- Compilation counters.
- Compilation start times.
- Scheduler state.
- Request queues.
- Logging.

### Condition variables

Condition variables allow coder threads to wait efficiently when the required
dongles are unavailable.

A waiting coder wakes up when the scheduler state changes or when a dongle
becomes available.

Timed waits are also used so that waiting threads periodically re-evaluate
their conditions.

### Scheduler

Each dongle maintains a priority queue of waiting requests.

For `fifo`, requests are ordered using their arrival order.

For `edf`, requests are ordered using their burnout deadline. Arrival order
is used as a tie-breaker.

A coder can acquire its dongles only when:

1. Both required dongles are available.
2. The coder is the first request for both dongles.
3. The simulation has not stopped.

### Monitor thread

A dedicated monitor thread continuously checks coder deadlines.

When a coder reaches its burnout deadline, the monitor:

1. Stops the simulation.
2. Wakes waiting threads.
3. Logs the burnout event.

This prevents coder threads from having to detect their own burnout.

## Project structure

The source code is organized into modules responsible for:

- Argument validation.
- Simulation initialization.
- Coder threads.
- Dongle management.
- Scheduler and priority queues.
- Monitoring.
- Logging.
- Memory management.

The Makefile builds all C source files and provides the standard
`all`, `clean`, `fclean` and `re` targets.