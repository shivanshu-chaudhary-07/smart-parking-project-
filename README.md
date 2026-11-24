# 🅿️ Smart Parking Lot Management System

**Using Stack and Queue in C**

A menu-driven C program that manages a parking lot with limited capacity. A **stack (LIFO)** holds vehicles parked inside the lot and a **circular queue (FIFO)** holds vehicles waiting outside. When a slot is freed, the vehicle that has waited longest is parked automatically.

🌐 **Live showcase & simulator:** https://smartparking-bice.vercel.app/
📄 **Full project report:** [docs/Smart_Parking_Lot_Report.pdf](docs/Smart_Parking_Lot_Report.pdf)

> B.Tech Project · Data Structures · Maharaja Surajmal Institute of Technology (MSIT), Department of Information Technology (affiliated to GGSIPU, Delhi) · Academic Session 2026–27

---

## Features

- Capacity checking before parking (1–100 slots)
- Duplicate vehicle-number detection across both parked and waiting lists
- FIFO waiting queue implemented as a circular array (wraparound reuses freed positions)
- Automatic allocation of a freed slot to the first waiting vehicle
- Display of parked list (top to bottom), waiting list (front to rear) and parking status
- Bounded input reading, so invalid or over-long input does not crash the program

## Model / assumption

The lot is a **single narrow lane with one gate**. Only the vehicle nearest the gate (the last one parked, i.e. the stack top) can leave. This simplified model shows how a stack and a queue work together.

## Data structures used

| Variable | Type | Purpose |
|---|---|---|
| `parked` | `char[MAX][LEN]` | Stack of parked vehicle numbers |
| `waiting` | `char[MAX][LEN]` | Circular queue of waiting vehicles |
| `top` | `int` | Index of top parked vehicle (-1 if empty) |
| `front`, `rear` | `int` | Front and next-insertion index of the queue |
| `count` | `int` | Number of waiting vehicles |
| `capacity` | `int` | Parking capacity (1 to 100) |
| `MAX`, `LEN` | constants | 100 vehicles per array; 32 characters per record |

| Point | Stack | Queue |
|---|---|---|
| Rule | LIFO | FIFO |
| Insertion / Deletion | Top / Top | Rear / Front |
| Implementation | Array + top index | Circular array + front/rear |
| Role | Parked vehicles | Waiting vehicles |
| Operation time | O(1) | O(1) |

## Getting started

**Requirements:** a C compiler such as GCC (C11). Works on Windows, Linux and macOS.

```bash
git clone https://github.com/<your-username>/smart-parking-lot-management-system.git
cd smart-parking-lot-management-system

# build
gcc -std=c11 -Wall -Wextra src/parking_simple.c -o parking
# or: make

# run
./parking
```

Run the sample session from the report: `make test`

## Menu

```
1. Vehicle Entry
2. Vehicle Exit
3. Display Vehicles
4. Parking Status
0. Exit Program
```

## Algorithm

**Vehicle entry:** read the vehicle number → reject if already present → if a slot is free, push onto the stack → otherwise enqueue if the queue has space, else reject.

**Vehicle exit:** if the stack is empty, show a message → otherwise pop the top vehicle → if the queue is not empty, dequeue the front vehicle and push it onto the stack and announce the automatic allocation.

## Slot allocation example (capacity 3)

| Step | Action | Stack (bottom → top) | Queue (front → rear) |
|---|---|---|---|
| 1 | V1 enters | V1 | Empty |
| 2 | V2 enters | V1, V2 | Empty |
| 3 | V3 enters (full) | V1, V2, V3 | Empty |
| 4 | V4 enters | V1, V2, V3 | V4 |
| 5 | V5 enters | V1, V2, V3 | V4, V5 |
| 6 | V3 leaves; V4 parked | V1, V2, V4 | V5 |
| 7 | V4 leaves; V5 parked | V1, V2, V5 | Empty |
| 8 | V5 leaves | V1, V2 | Empty |

## Sample run (capacity 2)

```
Enter parking capacity (1-100): 2
Enter choice: 1
Enter vehicle number: MH12AB1234
Vehicle MH12AB1234 parked at slot 1.
Enter vehicle number: DL01CD5678
Vehicle DL01CD5678 parked at slot 2.
Enter vehicle number: UP16EF9012
Parking full. UP16EF9012 waiting at position 1.
Enter vehicle number: HR26GH3456
Parking full. HR26GH3456 waiting at position 2.
Enter choice: 2
Vehicle DL01CD5678 has left.
UP16EF9012 parked automatically.
Enter choice: 1
Enter vehicle number: UP16EF9012
Vehicle UP16EF9012 is already in the system.
```

## Test cases

| No. | Test case | Expected result | Status |
|---|---|---|---|
| 1 | Entry with free slot | Parked, slot number shown | Pass |
| 2 | Entry when parking is full | Joins waiting queue | Pass |
| 3 | Exit from empty lot | Empty message, no crash | Pass |
| 4 | Duplicate parked vehicle | Entry rejected | Pass |
| 5 | Duplicate waiting vehicle | Entry rejected | Pass |
| 6 | Exit when vehicles are waiting | Front vehicle parked automatically | Pass |
| 7 | Invalid menu number | Invalid choice message | Pass |
| 8 | Letters instead of menu number | Invalid choice message | Pass |
| 9 | Display vehicle lists | Correct TOP and FRONT order | Pass |
| 10 | Full waiting queue / wraparound | Overflow rejected; freed index reused | Pass |

## Complexity

| Operation | Time | Extra space |
|---|---|---|
| `push()`, `enqueue()` | O(1) | O(1) |
| `entry()` | O(n + m) | O(1) |
| `vehicleExit()` | O(1) | O(1) |
| `display()` | O(n + m) | O(1) |
| `status()` | O(1) | O(1) |

*n = parked vehicles, m = waiting vehicles.* Storage is O(MAX × LEN).

## Limitations

- Only the top vehicle of the stack can exit (single lane).
- Each array stores a maximum of 100 vehicle numbers.
- Data is lost when the program closes.
- No entry time, fee calculation, database or GUI.
- Waiting vehicles cannot cancel; number-plate format is not fully validated.

## Future scope

- Let any vehicle exit using an auxiliary stack to move blocking vehicles
- Entry/exit timestamps and parking-fee calculation
- File or database storage
- GUI and multiple parking lanes
- Priority queue for emergency vehicles

## Applications

Parking at malls, hospitals, colleges and residential societies, and any system with limited capacity and a waiting line.

## Team

| Name | Enrollment No. |
|---|---|
| Himani | 00296302825 |
| Khushboo | 03296302825 |
| Shivanshu | 01596302825 |

**Programme:** B.Tech Information Technology, 3rd Semester, Section IT-E
**Submitted to:** Dr. Sunesh Malik

## References

1. Reema Thareja, *Data Structures Using C*, Oxford University Press.
2. Horowitz, Sahni and Anderson-Freed, *Fundamentals of Data Structures in C*, Universities Press.
3. Seymour Lipschutz, *Data Structures*, Schaum's Outline Series, McGraw-Hill.
4. Kernighan and Ritchie, *The C Programming Language*, 2nd ed., Prentice Hall.
5. [C Reference: string handling](https://en.cppreference.com/w/c/string/byte)
6. [C Reference: input/output](https://en.cppreference.com/w/c/io)

## License

Released under the [MIT License](LICENSE).
