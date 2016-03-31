
Three Characteristics of DB constraints:

  1. Event *(insert, update, delete)*
  2. Condition
  3. Action


=========

 * **Built-in constraints:** system-defined condition + system-defined action  
    *   Defined when a table is created

  Example:
```
	CREATE TABLE Student(
		Sid NUMBER (5) CONSTRAINT Pk_student PRIMARY KEY,
		Sname VARCHAR2 (30),
		gpa NUMBER
	)
```

 * **Assertion:** user-defined condition + system-defined action
 * **Triggers:** both condition and action are user-defined


