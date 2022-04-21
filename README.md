# MazeScreenSaver
Contains the prototype of a maze runner screensaver project.
![image](https://drive.google.com/uc?export=view&id=1et19Y0vu-rlqaJnF5Af_iw4NQ2pNH3Y9)

Demo video here-> https://youtu.be/e2l2vSTesGw

The main goal is to reproduce the Windows 95 3D Maze Screensaver.
Currently the project consists of a 3D maze prototype with all the basic features required to reproduce the 3D Maze screensaver like:
- Dynamic Maze generation algorithm
- Maze navigation algorithm
- Runner incrementaly moves and rotates during navigation
- Maze's exit condition, represented by the tile blue
- Restart loop at exit position
- Addition of textures to the objects 
- 3D rendering of the maze
- Move the camera around maze navigation
- Maze wall move up at the begining of the run and move down when runner reach the end

# Next Steps
- Improve runner movement
- Add more elements from the original Windows 95 3D maze like the rat sprite
- Start the maze at a random position

## Windows Building
All external files required to build the project are found in the /libs and /include folders. 
This project was created using Visual Studio so you can find the solution and the project files in the repository.
