#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int len = 100;
	int width = len * 0.15;

	for (int x = -len * 1.2; x <= len * 1.2; x += len * 1.2) {

		for (int y = -len * 1.2; y <= len * 1.2; y += len * 1.2) {

			ofPushMatrix();
			ofTranslate(x, y, 0);

			for (int z = -len; z <= len; z += width) {

				ofMesh mesh, frame;
				frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
				for (int param = 0; param <= 100; param++) {

					int deg = param * 3.6 - 135;
					auto noise_value = ofNoise(x + cos(deg * DEG_TO_RAD) * 0.15, y + sin(deg * DEG_TO_RAD) * 0.15, z * 0.005, ofGetFrameNum() * 0.008);

					vector<glm::vec3> vertices;
					if (noise_value > 0.5) {

						vertices.push_back(glm::vec3(this->make_point(len, param), z + width * 0.5));
						vertices.push_back(glm::vec3(this->make_point(len, param), z - width * 0.5));
					}
					else {

						vertices.push_back(glm::vec3(len * 0.4 * cos(deg * DEG_TO_RAD), len * 0.4 * sin(deg * DEG_TO_RAD), z + width * 0.5));
						vertices.push_back(glm::vec3(len * 0.4 * cos(deg * DEG_TO_RAD), len * 0.4 * sin(deg * DEG_TO_RAD), z - width * 0.5));
					}

					mesh.addVertices(vertices);
					frame.addVertices(vertices);

					int index = mesh.getNumVertices() - 1;
					if (param > 0) {

						mesh.addIndex(index); mesh.addIndex(index - 2); mesh.addIndex(index - 3);
						mesh.addIndex(index); mesh.addIndex(index - 1); mesh.addIndex(index - 3);

						frame.addIndex(index); frame.addIndex(index - 2);
						frame.addIndex(index - 1); frame.addIndex(index - 3);
					}
				}

				ofSetColor(0);
				mesh.draw();

				ofSetColor(255);
				frame.drawWireframe();
			}

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}