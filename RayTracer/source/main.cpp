#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

#include "ColourRGB.h"
#include "Camera.h"
#include "libMath.h"
#include "Ellipsoid.h"
#include "DirectionalLight.h"
#include "Random.h"
#include "Scene.h"
#include "Material.h"

typedef enum input_args
{
	OUTPUT_FILE = 1,
	OUTPUT_WIDTH,
	OUTPUT_HEIGHT,
}input_args;


void displayUsage(char* a_path)
{
	std::string fullpath = a_path; //get the full path as a string
		//strip off the path part of the string to only keep the executable name
	std::string exeName = fullpath.substr(fullpath.find_last_of('\\') + 1, fullpath.length());
	//display a message to the user indicating usage of the executable
	std::cout << "usage: " << exeName << " [output image name] [image width] [image height]" << std::endl;
	std::cout << "\t-h or --help\t\tShow this message" << std::endl;
}

int main(int argv, char* argc[])
{
	//Set up the dimensions of the image
	int imageWidth = 256;
	int imageHeight = 256;
	int channelColours = 255;
	//output file name
	std::string outputFilename;
#pragma region Process Variadic Args
	if (argv < 2) //less than 2 as the path and executable name are always present
	{
		displayUsage(argc[0]);
		return EXIT_SUCCESS;
	}
	else //Some variadic arguments have been passed
	{
		for (int i = 1; i < argv; ++i)
		{
			std::string arg = argc[i];
			if (arg == "-h" || arg == "--help")
			{
				displayUsage(argc[0]);
				return EXIT_SUCCESS;
			}
			switch (i)
			{
			case OUTPUT_FILE:
			{
				outputFilename = argc[OUTPUT_FILE];
				//check to see if the extension was included
				if (outputFilename.find_last_of(".") == std::string::npos)
				{
					//no extension better add one
					outputFilename.append(".ppm");
				}
				break;
			}
			case OUTPUT_WIDTH:
			{
				imageWidth = atoi(argc[OUTPUT_WIDTH]);
				break;
			}
			case OUTPUT_HEIGHT:
			{
				imageHeight = atoi(argc[OUTPUT_HEIGHT]);
				break;
			}
			default:
			{
				continue;
			}
			}
		}

	}
#pragma endregion
	//Need to change std::cout to outputFileName
	std::streambuf* backup = std::cout.rdbuf();	//backup std::cout's stream buffer
	std::ofstream outbuff(outputFilename.c_str());	//create an out file stream and set it to our output file name
	std::cout.rdbuf(outbuff.rdbuf());	//set the stream buffer for cout to the file out stream buffer

	Scene mainScene;

	Camera mainCamera;
	mainCamera.SetPerspective(60.f, (float)imageWidth / (float)imageHeight, 0.1f, 1000.f);
	mainCamera.SetPosition(Vector3(0.f, 0.f, -1.f));
	mainCamera.LookAt(Vector3(0.f, 0.f, -2.5f), Vector3(0.f, 1.f, 0.f));

	Random::SetSeed(time(nullptr));
	int raysPerPixel = 50;
																									//Just showing random nos, can be removed

	//output the Image Header data
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << channelColours << std::endl;

	//Put a light in the scene
	DirectionalLight dl = DirectionalLight(Matrix4::IDENTITY, Vector3(0.5f, 0.f, 0.5f), Vector3(0.f, -0.707f, -0.707f));
	
	//Define some materials for objects in the scene to use
	Material lightBlueSmooth = Material(Vector3(0.2f, 0.6f, 1.f), 0.2f, 0.9f, 0.9f, 0.f);
	Material lightBlueRough = Material(Vector3(0.2f, 0.6f, 1.f), 0.2f, 0.9f, 0.9f, 1.f);
	Material greenSmooth = Material(Vector3(0.f, 0.6f, 0.f), 0.2f, 0.9f, 0.9f, 0.f);
	Material greenRough = Material(Vector3(0.f, 0.6f, 0.f), 0.2f, 0.9f, 0.9f, 1.f);
	Material yellowRough = Material(Vector3(0.5f, 0.5f, 0.f), 0.2f, 0.6f, 0.7f, 1.f);

	//Ground sphere
	Ellipsoid s1(Vector3(0.f, -100.5f, -2.5f), 100.f);
	s1.SetScale(Vector3(1.f, 1.f, 1.f));
	s1.SetMaterial(&greenRough);
	//Left sphere 
	Ellipsoid s2(Vector3(-1.f, 0.f, -2.5f), 0.5f);
	s2.SetScale(Vector3(1.f, 1.f, 1.f));
	s2.SetMaterial(&lightBlueRough);
	//Centre sphere
	Ellipsoid s3(Vector3(0.f, 0.f, -2.5f), 0.5f);
	s3.SetScale(Vector3(1.f, 1.f, 1.f));
	s3.SetMaterial((&yellowRough));
	//Right sphere
	Ellipsoid s4(Vector3(1.f, 0.f, -2.5f), 0.5f);
	s4.SetScale(Vector3(1.f, 1.f, 1.f));
	s4.SetMaterial((&lightBlueSmooth));

	mainScene.AddObject(&s1);
	mainScene.AddObject(&s2);
	mainScene.AddObject(&s3);
	mainScene.AddObject(&s4);
	mainScene.AddLight(&dl);
	mainScene.SetCamera(&mainCamera);
	//get reciprocal of image dimensions
	float invWidth = 1.f / (float)imageWidth;
	float invHeight = 1.f / (float)imageHeight;
	//for each vertical interval of the near plane
	for (int i = 0; i < imageHeight; ++i)
	{
		std::clog << "\rCurrently rendering scanline " << i << " of " << imageHeight << std::flush;
		//for each interval of the near plane horizontally
		
		for (int j = 0; j < imageWidth; ++j)
		{
			ColourRGB rayColour(0.f, 0.f, 0.f);
			for (int p = 0; p < raysPerPixel; ++p)
			{
				// Calculate screen space Y location
				float screenSpaceY = 1.f - 2.f * ((float)i + Random::RandFloat()) * invHeight;
				//Get the current pixel in screen space coordinates (in range -1 to 1)
				float screenSpaceX = 2.f * ((float)j + 0.5f) * invWidth - 1.f;
				Vector2 screenSpacePos = Vector2(screenSpaceX, screenSpaceY);
				rayColour += mainScene.CastRay(screenSpacePos);
			}
			rayColour = rayColour * (1.f / (float)raysPerPixel);
			//write to output stream
			WriteColourRGB(std::cout, rayColour);

		}
		std::cout << std::endl;
	}

	//set the output stream buffer back to what it was previously
	std::cout.rdbuf(backup);
	return EXIT_SUCCESS;
}