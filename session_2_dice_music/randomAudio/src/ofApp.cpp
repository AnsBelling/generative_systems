/*
 Project Title:
 Description: Music for home made airports: RandomAudio
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 
 sounds samples © Dan Carr : care of https://reverbmachine.com/blog/deconstructing-brian-eno-music-for-airports
 
 */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // load vocal samples
    // loadVocal();
    // or uncomment this instead to load piano samples
    loadPiano();
    
    tempo = 5000; // five seconds tempo
    b_autoPlay = false;
    currTime = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (b_autoPlay){ // choose a voice to play
        if (ofGetSystemTimeMillis() > currTime + tempo){
            int num = ofRandom(totalVoices);
            voices[num].play();
            currTime = ofGetSystemTimeMillis();
            cout << "playing voice " << num << endl;
        }
    }
    
    // onscreen display of voices that are playing
    for (int i = 0; i < totalVoices; i++){
        if ( voices[i].isPlaying() ){
            ofDrawRectangle(90, ((i)*20) + 7 , ofMap( voices[i].getPosition(), 0, 1, 20 , (ofGetWidth() -110) ), 18 ); // draw a while progress bar
            ofDrawBitmapStringHighlight( "voice " + ofToString( i +1 ) + ": ", 10, (i + 1) * 20  );
        } else {
            ofDrawBitmapString( "voice " + ofToString( i +1 ) + ": ", 10, (i + 1) * 20  );
        }
    }
    // on screen instructions
    ofDrawBitmapString("auto play is " + ofToString( b_autoPlay) , 10, 200);
    ofDrawBitmapString("tempo is " + ofToString( tempo ) + " ms" , 10, 220);
    ofDrawBitmapString("press keys 1-7 to play voices \na to autoplay \n+ /- to increase/decrease tempo  \n'p' to load Piano Samples \n'v' to load vocal samples", 10, 240);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            voices[0].play();
            break;
        case '2':
            voices[1].play();
            break;
        case '3':
            voices[2].play();
            break;
        case '4':
            voices[3].play();
            break;
        case '5':
            voices[4].play();
            break;
        case '6':
            voices[5].play();
            break;
        case '7':
            voices[6].play();
            break;
            
        case '8':
            if (voices.size()>7){
                voices[7].play();
            }
            break;
        case 'a':
            b_autoPlay= !b_autoPlay;
            break;
        case '=':
        case'+':
            tempo +=500;
            break;
            
        case '-':
        case'_':
            if (tempo > 1000){
                tempo -=500;
            }
            break;
            
        case 'v':
            loadVocal();
            break;
        case 'p':
            loadPiano();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

void ofApp::loadVocal(){
    // load vocal samples
    totalVoices = 7;
    voices.clear();
    for (int i = 0; i< totalVoices; i++){
        ofSoundPlayer voice;
        string path ="choir/Eno-Choir-0" + ofToString( i+1 ) + ".wav";
        cout << "loading " << path << endl;
        voice.load(path);
        voice.setMultiPlay(true);
        voices.push_back(voice);
    }
}

void ofApp::loadPiano(){
    // load piano samples
    totalVoices = 8;
    voices.clear();
    for (int i = 0; i< totalVoices; i++){
        ofSoundPlayer voice;
        string path ="piano/Eno-Piano-0" + ofToString( i+1 ) + ".wav";
        cout << "loading " << path << endl;
        voice.load(path);
        voice.setMultiPlay(true);
        voices.push_back(voice);
    }
}
