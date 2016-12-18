README - VRTrees (ereif, murbany, zdixon)


=======================================================================
Build instructions:
Must be built on Windows with MSVC 32 bit compiler (tested using MSVC2015). The correct project file is VRTrees/QVRViewer-master/QVRViewer.pro. You need a folder containing glew 


=======================================================================
Running:
The Vive headset should be connected for VR to work. If it isn’t an error will be printed. Once the window opens, the user must click inside it once to give it focus, or else the keyboard shortcuts won’t work.


=======================================================================
Keyboard shortcuts:
n - View only the normals from the first pass of deferred shading.
p - View only the position values from the first pass of deferred shading.
f - Toggle fog
, - Increase maximum fog distance (move it away)
. - Decrease maximum fog distance (move it closer)
s - Toggle snowy shader
t - Restart tree growth
(Space) - Teleport camera (user) along the direction they are looking


The grip button on the vive controller is also assigned to teleporting the player in the direction they are looking.
 
=======================================================================
Features:
=======================================================================
L-System tree generation (murbany, ereif)
        A series of different grammar rules each serve as blueprints for each tree. There are adjustable parameters including rotation which allows one production rule to generate multiple visually distinct trees . Each level is created recursively according to a maximum depth out of a series of transformed cones. When creating the vertices for the cones as well, a float indicating which branch level is also passed in is used to determine what part of the tree should be visible in its growth animation cycle. The trees are also placed pseudo randomly across the terrain


=======================================================================
Deferred shading (ereif) 
* The rendering was done in two passes, the first storing the normals, positions, and color IDs of the trees and terrain. In the second, we calculated the lighting equation for each pixel, adding noise texture to the trees and hill, as well as the some other shading extras, as described below.


=======================================================================
Fancy shaders (zdixon, murbany, ereif)
* Animating tree growth is done using a running clock, and shaders which use that information to draw the different sets of branches at the same time. 
* The snow shader for the trees uses the normals of a given point to determine if it should have snow on it. For the ground, it takes into account the diffuse lighting properties.
* The fog shader mixes in a fog color based on the distance from the camera
* The sun is implemented in the shader as well, to allow for “blooming” of the light through the tree branches
* Noise is a 3d perlin triplanar noise.


=======================================================================
VR (zdixon)
* The entire codebase had to be converted to be able to compile on MSVC so that openVR could compile with it.
* The output on screen is the right eye of the VR output
* Interactions as well (VR and otherwise)


=======================================================================
Bugs
* The trees are all sunk slightly into the ground. This is intentional, so that trees on slopes don’t float above the ground.