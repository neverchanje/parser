
### Algorithm:
```
SetOfItems CLOSURE(SetOfItems I) {
    J = I   
    for (each item i,
         which has a dot on the left of one of its symbol e, 
         e can be the end symbol $) {
        if (e is non-terminal) {
            for(each rule r where e is on its left hand side) {
                if(r is not in J) {
                    add r in J
                }
            }
        }
    }
}
```