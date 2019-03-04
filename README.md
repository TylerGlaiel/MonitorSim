# MonitorSim
Simulates a monitor (vsyncs and timing) so you can test various game loop timings to see how many missed or double frames your timing control method has


You write your timing control loop in "main". It prints out a bunch of numbers (each vsync it prints out the number of "game updates" that have happened since the previous vsync)

If your simulated game is running smooth, it should print 1111111....
If your simulated game is stuttering, it will print something like 11111111110211111111110211111111...

change the "monitor_refresh_rate" and "vsync" variables at the top to change the type of monitor you're testing on
change the "game_update_time()" (& render, etc) functions to change "how fast your game is rendering" in the simulation. Good test values here are .005 ("fast rendering") and .02 ("slower than 60fps rendering")

common monitor refresh rates:
59.94
60
