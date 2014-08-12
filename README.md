ofxDomemaster
=============

An openFrameworks addon for creating domemasters. A domemaster is the standard format for projection within digital dome theatres. Simply put it is a square composition with a circular mask and fisheye distortion.

This addon addon uses a multi-camera technique to generate a 5-sided cube map and renders each view to pregenerated meshes for spherical distortion. A circular image mask overlays the fisheye render to create a circular composition.

Use of this addon requires that you copy the domemaster folder located within the example project's bin folder to your project. 

Mesh and mask assets generated by Paul Bourke: 
http://paulbourke.net/dome/unity3d/
