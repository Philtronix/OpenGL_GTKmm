# OpenGL_GTKmm
Open an OpenGL window in a GTKmm App

Based on :
https://learnopengl.com/Model-Loading/Model
https://github.com/GNOME/gtkmm/blob/master/demos/gtk-demo/example_glarea.cc

Model by Berk Gedik, from: https://sketchfab.com/3d-models/survival-guitar-backpack-low-poly-799f8c4511f84fab8c3f12887f7e6b36

Modified material assignment (Joey de Vries) for easier load in OpenGL model loading chapter, and renamed albedo to diffuse and metallic to specular to match non-PBR lighting setup.

Creates a simple GTKmm app with some sliders and Gtk::GLArea that is used by OpenGL to show a nifty 3d Model.

