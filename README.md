# Instructions
1. Fork the repository.
1. **Choose one** of the two design problems to complete. You will use one of the design patterns presented in class to solve the problem.
1. Write the solution.

# Note about the CI configuration file
As one of the design pattern problems (Problem #8) involves user input, the CI configuration file does not have tasks for running the program or running memory checking. If you do Problem #9, you may want to add the following two items to the `.gitlab-ci.yml` file.

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
