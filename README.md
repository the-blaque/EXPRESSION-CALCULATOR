

```
run:
   stage: test
   script:
      - designPattern

memory-leaks:
   stage: quality
   script:
      - make memcheck
```
