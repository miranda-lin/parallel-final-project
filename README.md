# Parallel Othello Solver

15-418 Final Project Spring 2022

Miranda Lin (miranda1), Ashwin Srinivasan (ashwins)

[Watch final presentation here!](https://drive.google.com/file/d/1uSwlAH5ap7q21YhSVKk13c1R3S7rs1Di/view?usp=sharing)

## Summary

We will parallelize an Othello (a variant of Reversi) minimax solver with alpha-beta pruning. We will investigate how we can speed up searching the game tree to find the best available moves as well as the alpha-beta algorithm that reduces the search space.

## Background

Reversi is a two-player board game invented in the late 19th century, in which opponents place white- and black-colored discs on an 8x8 grid. With each move, players try to “outflank” their opponent’s discs by bounding them in a straight line, thus flipping their color. The player with the most discs of their color on the board wins, and the game ends when no more valid moves can be made. We will be studying Othello, a modern variant of the game that has a predefined starting placement of discs.

The minimax algorithm is a recursive decision procedure for choosing the next move in a two-player game, so it can be easily applied to Othello. Each possible resultant state of a move is assigned a value based on a heuristic function, where negative values are chosen by the minimizing player and positive ones are chosen by the maximizing player. We will likely include disc count, move count, and control of corner squares in our heuristic function — of course, this may change depending on the results of our analysis.

In effect, minimax searches the entire tree of possible moves from each starting position, so its performance is strongly tied to the branching factor of the game tree. Alpha-beta pruning is a strategy that reduces the search space by eliminating (or “pruning”) branches that cannot possibly be the maximum or minimum choice from a particular position (i.e., moves that minimax would never choose anyway).

Since the minimax algorithm has to evaluate every possible move from a given board state and this computation is independent, we believe there is a great opportunity for parallel speedup here. We chose Othello because its rules are fairly straightforward but it produces very large game trees, which will demonstrate the parallel speedup we achieve. While the alpha-beta optimization is not as easily parallelizable due to its sequential nature, we believe we can still perform some parallel optimizations in computing the minimum/maximum move and by pruning chunks of moves concurrently.

## Challenges

**Encoding the rules of the game and board state.** Before we can begin parallelizing the Othello minimax solver, we will need to write a representation of the game including board states, moves, etc. This will be a bit of a design and implementation challenge as we want to ensure that our solution is correct, easy to use, and does not hinder the performance of the solver.

**Alpha-beta is inherently sequential.** In order to achieve good speedup, we will need to consider the tradeoff between perfect information and parallelizing, i.e. total amount of work performed vs. parallelizing the work. Deciding what to parallelize in alphabeta will be an important decision: we can reduce the time to find the minimum/maximum child to log(N) from N, but we may also consider losing some information to parallelize different branches and perform alphabeta independently for those.

**Choosing the best method of parallelism.** There are multiple axes of parallelism in this project, and different methods may be suitable for each. We would like to explore CUDA, OpenMP, and possibly Cilk Plus for parallelizing this problem. 

**Choosing the correct search depth.** As the search tree can become very large, we may want to limit the search depth to improve performance. Tuning this parameter may prove to be a challenge. We may need to use heuristics to improve our search space as well. 

## Resources

Software: C++, CUDA, OpenMP

Machines: Gates cluster machines, PSC machines

No datasets will be used for this project as we will be implementing the Othello game and moves will be generated by the solver.

# Goals and deliverables

 - [50%] Othello game implementation that accepts user input
 - [50%] Sequential minimax solver for Othello
 - [75%] Parallel minimax Othello solver
 - [75%] Sequential alpha-beta pruning in solver
 - [100%] Fully parallel Othello solver (including alpha-beta pruning)
 - [125%] Parallel Othello solver using some other optimization revealed via performance testing
 - [125%] Visualization of Othello solver output

# Schedule

**Week of 3/28:**
 - Research parallelization strategies for Othello solver
 - Implement Othello game

**Week of 4/4:**
 - Implement Othello solver using minimax/alphabeta
 - Write checkpoint report

**Week of 4/11 (Checkpoint on M 4/11):**
 - Parallelize solver
 - Explore alternative approaches

**Week of 4/18:**
 - Performance analysis on approach, tune parameters

**Week of 4/25 (Report on F 4/29):**
 - Wrap-up, write report

**Week of 5/2 (Presentation on Th 5/5):**
 - Work on presentation


# MILESTONE

So far, we have implemented a version of Othello that takes in user input for each move and plays the game out. We have begun implementing a minimax solver, and have immediate plans for altering it to also allow for alphabeta pruning as well. When structuring our code, we designed it to be amenable for parallelization using OpenMP. As we explored the solver code, we found that OpenMP is likely our best choice for parallelization. We eliminated MPI due to the high communication costs, and we noticed that if we wanted to use CUDA we would have likely be bound by the memory costs to copy the game state to and from the device and host. Thus we decided to primarily use OpenMP to parallelize our solver.

We plan to create multiple versions of the solver including a sequential minimax, sequential alphabeta, and parallelized versions of both. This will be easily swapped out with our game implementation through subclassing.

With respect to the goals we had originally set, we are fairly on schedule as we have implemented the game as well as the minimax solver. Though we have not yet implemented the alphabeta solver, we anticipate that this will not be much additional work as we designed our code in a modular fashion. We still need to tune the heuristic for our solver, as we would like to create an estimator that performs well but also is fast to improve our searching. We are a few days behind our internal schedule, as we received proposal feedback later than we had anticipated, particularly because it was so close to the spring carnival break. In addition, we expect that we will have less time this week to work on the project due to the exam. However, we expect that we will still be able to produce all of our deliverables especially with the additional time we have in the next few weeks. For our nice-to-haves, we expect that will depend on how performance tuning goes.

At the poster session, we will show a demo of our parallel Othello solver as well as graphs showing the speedups comparing the various versions of our solver.

Some possible issues we may have to deal with include dealing with memory bottlenecks, optimizing locality, and not knowing the upper bound of performance. We would also ideally like to explore a different method of parallelization such as CUDA or Cilk in order to compare speedups, but we’re not certain whether this will provide significant improvements for the amount of time it will take, as we may need to restructure our code significantly for these. Therefore, we have added those to our stretch goals. In addition, there may be better game-solving algorithms that we aren’t familiar with and may perform better. Therefore, we will also explore those during our performance tuning if we’re not seeing enough improvement. In general, we have a set plan and most of our unknowns are related to our stretch goals.

## Updated Goals and deliverables

- [50%] Othello game implementation that accepts user input
- [50%] Sequential minimax solver for Othello
- [75%] Parallel minimax Othello solver
- [75%] Sequential alpha-beta pruning in solver
- [100%] Fully parallel Othello solver (including alpha-beta pruning)
- [125%] Parallel Othello solver using some other optimization revealed via performance testing
- [125%] Visualization of Othello solver output
- [125%] Parallel solver implementations using Cilk or CUDA

## Updated Schedule

**Week of 4/11 (Checkpoint on M 4/11):**
- Parallelize minimax solver using OpenMP
- Work on alphabeta solver
- Tune estimator heuristics

**Week of 4/18:**
- Parallelize alphabeta solver
- Performance analysis on minimax and alpha beta solvers, tune parameters

**Week of 4/25 (Report on F 4/29):**
- Further performance tuning
- Explorations with other algorithms or resources (CUDA, Cilk) if time allows
- Work on report

**Week of 5/2 (Presentation on Th 5/5):**
- Visualization implementation (if time)
- Work on presentation

