# Part B — Answers

**1. Why `shared_ptr` in Fleet and not `unique_ptr`?**

Because `find()` returns a pointer to a robot that the fleet still owns. With `unique_ptr` you can't have two things pointing to the same object. `shared_ptr` keeps a reference count so both the fleet and the caller can hold it at the same time. If I switched to `unique_ptr`, `find()` would break since you can't copy a `unique_ptr`.

---

**2. What container did you use for `robots_`? Why — what is its lookup cost?**

`std::unordered_map` keyed by robot id. Lookup is O(1) average because it uses a hash table, you give it an id and it jumps straight to the right slot.

---

**3. What container did you use for the task queue? What data structure is it built on, and why is it the right fit for "highest priority first"?**

`std::priority_queue`. It's built on a max-heap, which always keeps the biggest element at the top. So `top()` always gives the highest priority task in O(1). I defined `Task::operator<` so that a higher priority number wins, and the heap handles the ordering automatically.

---

**4. `operator<<` is declared `friend` inside Robot. What does `friend` give it that a regular method does not? Why can it not be a regular member function?**

`operator<<` has to be a free function because the left side of `<<` is `std::ostream`, not `Robot`. If it were a member of Robot, you'd have to write `robot << std::cout` which makes no sense. The problem with a free function is it can't see private members, so we declare it `friend` to give it access without making it a member.

---

**5. You used `std::find_if` with a lambda. What does that communicate compared to a hand-written loop?**

A hand-written loop makes you read the whole thing to figure out what it's doing. `std::find_if` tells you immediately: "I'm searching for the first element that matches this condition." The lambda is just the condition, nothing else. It's cleaner.

---

**6. `work()` throws if battery is 0. Why use an exception rather than returning false or printing an error?**

`work()` returns void so it can't return false. And printing inside `work()` would mix robot logic with UI code which is bad design. An exception lets the caller decide what to do; in our case, catch it and print a message. It also can't be silently ignored like a return value can.

---

**7. An exception is thrown inside `assign_task` when the robot is not found. Is the fleet's state consistent afterwards?**

Yes. `find()` throws before anything is modified; the task never gets pushed to the queue and no robot gets marked busy. The fleet is exactly the same as before the call.

---

**8. `start_work` uses a background thread. What did you do with `stop_` and `worker_`, and why?**

`worker_` is the actual thread; I assign a lambda to it that loops and calls `work()` every second. `stop_` is an `atomic<bool>` the thread checks each iteration. When I want it to stop I set `stop_ = true` from the main thread. It needs to be atomic because two threads are reading and writing it at the same time; a regular bool would be a data race. The destructor also sets `stop_ = true` and joins the thread so it never outlives the object.

---

**9. Diamond inheritance — corrected version and explanation:**

The problem is `MaintenanceRobot` inherits from both `MobileRobot` and `CookingRobot`, and both of those inherit from `Robot`. So there end up being **two copies** of `Robot` inside `MaintenanceRobot`, one from each path. When you write `m.name_` the compiler doesn't know which copy you mean and gives an ambiguity error.

The fix is `virtual` inheritance:

```cpp
class Robot             { public: std::string name_ = "base"; };
class MobileRobot       : public virtual Robot {};
class CookingRobot      : public virtual Robot {};
class MaintenanceRobot  : public MobileRobot, public CookingRobot {};

int main() {
    MaintenanceRobot m;
    std::cout << m.name_;  // works now, only one Robot subobject
}
```

Adding `virtual` on the base class tells the compiler to share one single `Robot` subobject across all paths instead of creating one per path. Now there's only one `name_` and the ambiguity is gone.
