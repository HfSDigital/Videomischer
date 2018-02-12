#include "vmVideoSource.h"

//--------------------------------------------------------------

int vmVideoSource::idCounter = 0;

//--------------------------------------------------------------

vmVideoSource::vmVideoSource(){
	id = idCounter;
	idCounter++;
	cout << "vmVideoSource-ID: " << id << endl;
}

//--------------------------------------------------------------

vmVideoSource::~vmVideoSource()
{
	cout << "Destructor vmVideoSource" << endl;
}

//--------------------------------------------------------------

void vmVideoSource::printName() {
	cout << "Name: " << title << endl;
}

