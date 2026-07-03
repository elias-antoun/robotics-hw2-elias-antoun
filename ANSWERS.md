# Part B — Answers

1. **Why `shared_ptr` in Fleet and not `unique_ptr`?**

2. **What container did you use for `robots_`? Why — what is its lookup cost?**

3. **What container did you use for the task queue? What data structure is it built on, and why is it the right fit for "highest priority first"?**

4. **`operator<<` is declared `friend` inside Robot. What does `friend` give it that a regular method does not? Why can it not be a regular member function?**

5. **You used `std::find_if` with a lambda. What does that communicate compared to a hand-written loop?**

6. **`work()` throws if battery is 0. Why use an exception rather than returning false or printing an error?**

7. **An exception is thrown inside `assign_task` when the robot is not found. Is the fleet's state consistent afterwards?**

8. **`start_work` uses a background thread. What did you do with `stop_` and `worker_`, and why?**

9. **Diamond inheritance — corrected version and explanation:**
