#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofSetCircleResolution(60);
	ofSetLineWidth(1.5);

	this->box2d.init();
	this->box2d.setGravity(0, 10);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update() {
	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	if (this->press_position != ofVec2f(0, 0)) {
		// Center button
		if (ofGetMousePressed(1)) {
			ofVec2f mouse_position = ofVec2f(ofGetMouseX(), ofGetMouseY());
			ofVec2f difference = mouse_position - this->press_position;

			ofColor line_color;
			line_color.setHsb(ofGetFrameNum() % 255, 255, 255);
			ofSetColor(line_color);

			ofFill();
			ofDrawRectangle(this->press_position, difference.x, difference.y);
		}

		// Right button
		if (ofGetMousePressed(2)) {
			ofVec2f mouse_position = ofVec2f(ofGetMouseX(), ofGetMouseY());
			float r = mouse_position.distance(this->press_position);

			ofColor line_color;
			line_color.setHsb(ofGetFrameNum() % 255, 255, 255);
			ofSetColor(line_color);

			ofNoFill();
			ofDrawEllipse(this->press_position, r * 2, r * 2);
		}
	}

	ofNoFill();

	for (int i = 0; i < this->circles.size(); i++) {
		ofSetColor(this->circles_color[i]);
		this->circles[i].get()->draw();
	}
	for (int i = 0; i < this->rects.size(); i++) {
		ofSetColor(this->rects_color[i]);
		this->rects[i].get()->draw();
	}

	this->box2d.drawGround();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	// Center or Right button
	if (button == 1 || button == 2) {
		this->press_position = ofVec2f(x, y);
	}
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

	// Center button
	if (button == 1) {
		ofVec2f mouse_position = ofVec2f(x, y);
		ofVec2f difference = mouse_position - this->press_position;

		this->rects.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
		this->rects.back().get()->setPhysics(3.0, 0.53, 0.1);
		this->rects.back().get()->setup(this->box2d.world, this->press_position.x + difference.x / 2, this->press_position.y + difference.y / 2, difference.x, difference.y);

		ofColor rect_color;
		rect_color.setHsb(ofGetFrameNum() % 255, 255, 255);
		this->rects_color.push_back(rect_color);

		this->press_position = ofVec2f(0, 0);
	}

	// Right button
	if (button == 2) {
		ofVec2f mouse_position = ofVec2f(x, y);
		float r = mouse_position.distance(this->press_position);

		this->circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
		this->circles.back().get()->setPhysics(3.0, 0.53, 0.1);
		this->circles.back().get()->setup(this->box2d.getWorld(), this->press_position.x, this->press_position.y, r);

		ofColor circle_color;
		circle_color.setHsb(ofGetFrameNum() % 255, 255, 255);
		this->circles_color.push_back(circle_color);

		this->press_position = ofVec2f(0, 0);
	}
}

//========================================================================
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}