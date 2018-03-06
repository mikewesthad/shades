#!/bin/bash

cd ../../../addons/
git clone https://github.com/braitsch/ofxDatGui.git
git clone https://github.com/armadillu/ofxAnimatable.git

# Grab the version of ofxOMXPlayer that is compatible with OF 0.9
git clone --branch 0.9.0-compatible https://github.com/jvcleave/ofxOMXPlayer.git