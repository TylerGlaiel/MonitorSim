# MonitorSim
Simulates a monitor (vsyncs and timing) so you can test various game loop timings to see how many missed or double frames your timing control method has


You write your timing control loop in "main". It prints out a bunch of numbers (each vsync it prints out the number of "game updates" that have happened since the previous vsync)

If your simulated game is running smooth, it should print 1111111....

If your simulated game is stuttering, it will print something like 11111111110211111111110211111111...
