#include "ofxDomemaster.h"

ofxDomemaster::ofxDomemaster(){
    meshScaleExt = 1;
}

//--------------------------------------------------------------
void ofxDomemaster::setup(){    
    width = 1024;
    height = 1024;
        
    for (int i=0; i<renderCount; i++){
        ofCamera c;
        c.setNearClip(.01);
        renderCamera.push_back(c);
        ofFbo f;
        renderFbo.push_back(f);
        ofVboMesh m;
        renderMesh.push_back(m);
    }
    
    resize(width, height);
    
    renderMesh[bottom].load("domemaster/bottom.ply");
    renderMesh[front].load("domemaster/front.ply");
    renderMesh[left].load("domemaster/left.ply");
    renderMesh[right].load("domemaster/right.ply");
    renderMesh[top].load("domemaster/top.ply");
    
    // mask
    mask.load("domemaster/mask.png");
    mask.setUseTexture(true);
}

//--------------------------------------------------------------
void ofxDomemaster::begin(int i){
    renderFbo[i].begin();
    ofClear(0);
    renderCamera[i].begin(view);
}

//--------------------------------------------------------------
void ofxDomemaster::end(int i){
    renderFbo[i].end();
    renderCamera[i].end();
}

//--------------------------------------------------------------
void ofxDomemaster::draw(){
    fisheyeCamera.enableOrtho();
    
    fisheyeCamera.begin(fisheyeView);

        ofEnableNormalizedTexCoords();
    
        for (int i=0; i<renderCount; i++){
            renderFbo[i].getTexture().bind();
            ofPushMatrix();
            ofTranslate(-width/2,-height/2,0);
            ofRotate(90,1,0,0);
            ofRotate(180,0,0,1);
            ofRotate(180,0,1,0);
            ofScale(meshScale, meshScale, meshScale);
            renderMesh[i].drawFaces();
            ofPopMatrix();
            renderFbo[i].getTexture().unbind();
        }
    
        ofDisableNormalizedTexCoords();
    
    fisheyeCamera.end();
    
    fisheyeCamera.draw();
    
    mask.draw(0, 0, width, height);
}

//--------------------------------------------------------------
void ofxDomemaster::resize(int w, int h){
    width = w;
    height = h;

    // set view for cube cameras
    view.setWidth(width);
    view.setHeight(height);
    
    // cube camera
    renderCamera[bottom].setOrientation(ofVec3f(-90,0,0));
    renderCamera[bottom].setFov(90);
    
    renderCamera[front].setOrientation(ofVec3f(0,0,0));
    renderCamera[front].setFov(90);
    
    renderCamera[left].setOrientation(ofVec3f(0,90,0));
    renderCamera[left].setFov(90);
    
    renderCamera[right].setOrientation(ofVec3f(0,-90,0));
    renderCamera[right].setFov(90);
    
    renderCamera[top].setOrientation(ofVec3f(90,0,0));
    renderCamera[top].setFov(90);
    
    // cube camera fbos
    for (int i=0; i<renderCount; i++){
        renderFbo[i].setUseTexture(true);
        renderFbo[i].allocate(width, height);
        renderFbo[i].begin();
        ofClear(0);
        renderFbo[i].end();
    }
    
    // fisheye domemaster
    fisheyeView.setWidth(width);
    fisheyeView.setHeight(height);
    fisheyeCamera.setPosition(-width/2, -height/2, 10);
    meshScale = width*meshScaleExt;
}

void ofxDomemaster::setCameraPosition(float x, float y, float z){
    for (int i=0; i<renderCount; i++){
        renderCamera[i].setPosition(x,y,z);
    }
}

void ofxDomemaster::setMeshScale(float s){
    meshScaleExt = s;
    meshScale = width*meshScaleExt;
}

