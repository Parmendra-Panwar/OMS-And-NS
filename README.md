# C++ Order Management & Notification System

A clean-code implementation of a decoupled OMS (Order Management System) and Notification service using **Modern C++**. This project demonstrates scalable architecture and **SOLID principles**.

---

## Design Patterns Used
* **Factory Pattern:** Dynamic object creation in `OrderFactory` and `ScheduleFactory`.
* **Strategy Pattern:** Pluggable payment methods (`UPI`, `CreditCard`) via `PaymentStrategy`.
* **Observer Pattern:** Decoupled notification system to alert users/admins on order state changes.
* **Decorator Pattern:** Flexible order customization (e.g., adding toppings or packaging) without modifying base classes.
* **Singleton Pattern:** Centralized state management in `OrderManager` and `RestaurantManager`.

## Project Architecture
* **Factories:** Logic for instantiating diverse order types.
* **Managers:** Core business logic for Orders and Restaurants.
* **Models:** Data entities (User, Cart, MenuItem, Order types).
* **Strategies:** Encapsulated payment algorithms.
* **Services:** Decoupled Notification system.
* **Utils:** Time and helper functions.

## Key Features
* **Independent Systems:** Order handling and Notifications are logically separated for scalability.
* **Extensible Code:** New payment methods or order types can be added without modifying existing core logic.
* **Type Safety:** Heavy use of OOP inheritance and polymorphism.
<!-- 
## Future Roadmap
* **Persistence:** Integrate a database (SQLite/PostgreSQL).
* **Concurrency:** Implement `std::async` for non-blocking notifications.
* **API Layer:** Add a REST/Socket interface to replace the console output. -->

---
*Built with Modern C++ and SOLID Principles.*