<div align="center">
  <h1>Philosophers (42 project)</h1>
</div>

## About
An implementation of the Dining Philosophers Problem in C using POSIX threads and mutexes. Multiple philosophers sit at a round table, each needing two forks to eat. The challenge is to synchronize access to shared resources without deadlocks, race conditions, or starvation — while detecting death within millisecond precision.

## How it works

### Thread architecture
Each philosopher runs as its own thread. A separate monitor thread continuously checks whether any philosopher has starved or whether all have eaten enough. The monitor is the only thread that can end the simulation — philosophers just check a shared `finished` flag on every iteration and exit cleanly.

### Deadlock prevention
Forks are represented as mutexes, one per philosopher, arranged in a circle. To prevent deadlock, even-numbered philosophers grab their left fork first, while odd-numbered ones grab their right fork first. This breaks the circular-wait condition that would otherwise cause all philosophers to lock one fork and wait forever for the second.

### Death detection
The monitor thread iterates over all philosophers in a loop, comparing `current_time - last_eaten` against `time_to_die`. Each philosopher's `last_eaten` timestamp is protected by a per-philosopher mutex, avoiding races between the monitor reading and the philosopher updating. If a philosopher has starved, the monitor logs the death, sets the `finished` flag, and all threads wind down.

### Precision timing
Instead of calling `usleep(full_duration)`, the sleep function uses a busy-wait loop with `usleep(500)` (0.5ms intervals), checking the death flag on every iteration. This gives sub-millisecond reaction time to death events during eat and sleep phases — critical for passing the strict timing tests.

### Edge cases
- **Single philosopher:** Only one fork exists, so eating is impossible. The philosopher picks up the fork, waits, and dies after `time_to_die` — handled as a special case to avoid locking a second mutex that doesn't exist.
- **Optional meal count:** If provided, the simulation ends cleanly once every philosopher has eaten at least N meals.

## Usage
```
make
./philo <n_philos> <time_to_die> <time_to_eat> <time_to_sleep> [n_meals]
```

Examples:
```
./philo 5 800 200 200        # 5 philosophers, no one should die
./philo 4 410 200 200        # 4 philosophers, no one should die
./philo 1 800 200 200        # 1 philosopher, dies after 800ms
./philo 5 800 200 200 7      # stops after each philosopher ate 7 times
```

## Built with
- C (C99)
- POSIX threads (`pthread_create`, `pthread_join`, `pthread_mutex_*`)
- `gettimeofday` for microsecond-precision timestamps
