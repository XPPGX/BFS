- # Idea
    - ### Each thread is responsible for a node(according to their threadID)

    - ### Using a bool array called "Frontier" to inform each thread when should do its task(visiting neighbors)

    - ### It will parallelly visit neighbors of frontier and record level(cost) of each nodes

- # Problem
    - ### Thread divergence
        - Because each thread is responsible for a node, if one node has extremely high degree, then the thread "t" must traverse the nodes neighbors via a "long for loop" while other threads in the same warp will idle until thread "t" finish its work.
        - In addition, when a node is not in "
        Frontier", then it will do nothing. This is another reason that reduces the parallelism of GPU.

