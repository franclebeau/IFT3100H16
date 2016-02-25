// IFT3100H16_LightingFixedPipeline/function.h
// Fonctions utilitaires.

#pragma once

inline void imageExport(const string name, const string extension)
{
	ofImage imageTemp;

	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	string fileName = name + timestamp + "." + extension;

	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}

inline float oscillate(float time, float amplitude, float period, float shift, float offset)
{
	return amplitude * sin((time - shift) * 2 * PI / period) + offset;
}
