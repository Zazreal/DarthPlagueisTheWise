/*
 * File:   main.cpp
 * Author: Tomek_000
 *
 * Created on 13 wrze�nia 2018, 20:27
 */
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <exception>
#include <Shlobj.h>
#include <sstream>
#include <vector>
std::string The_story_of_DPtW =
"I thought not. It's not a story the Jedi would tell you \n "
"It's a Sith legend \n "
"Darth Plagueis was a Dark Lord of the Sith, \n "
"so powerful and so wise he could use the Force \n "
"to influence the midichlorians to create life \n"
"He had such a knowledge of the dark side \n"
"that he could even keep the ones he cared about from dying \n "
"The dark side of the Force is a pathway to many abilities \n "
"some consider to be unnatural. He became so powerful \n "
"the only thing he was afraid of was losing his power, \n "
"which eventually, of course, he did \n "
"Unfortunately, he taught his apprentice everything he knew, \n "
"then his apprentice killed him in his sleep \n "
"IRONIC \n "
"He could save others from death, but not himself \n";

int RemoveFiles(std::vector<std::string>& Fvector);
int EndProgramFunction();

int main() {
	try {
		wchar_t saveLocation[MAX_PATH] = { 0 };
		SHGetSpecialFolderPath(NULL, saveLocation, CSIDL_DESKTOPDIRECTORY, FALSE);
		std::wstring ws(saveLocation);
		std::string pathname(ws.begin(), ws.end());
		//std::string YesOrNo = " ";
		std::cout << "Did you ever hear the tradgedy of DARTH PLAGUEIS THE WISE?";
		std::cout << "Path: " << pathname << std::endl;
		try {
			std::ofstream CreateFile((pathname + "\\TheGreatTradgedy.txt"));
			CreateFile << The_story_of_DPtW;
			CreateFile.close();
			if (!CreateFile.good()) throw std::runtime_error("FileNotCreatedException");
		}
		catch (std::exception &e) {
			std::cout << "An Exception has occured: " << e.what();
		}



		std::vector<std::string> FilesVector(0);
		std::stringstream ss(The_story_of_DPtW);
		std::string tempstr = "";
		char separator = ' ';
		int breaker = 0;
		while (std::getline(ss, tempstr, separator)) {
			std::string pathname2 = pathname + "\\BACKUP\\" + tempstr + ".txt";
			try {
				std::ofstream TheActualLegend(pathname2);
				TheActualLegend << The_story_of_DPtW;
				if (!TheActualLegend.good()) {
					throw std::runtime_error("FileNotCreatedException, FileName: " + tempstr + ".txt\n");
					TheActualLegend.close();
				}
				TheActualLegend.close();
			}
			catch (std::exception &e) {
				std::cout << "An Exception has occured: " << e.what() << std::endl;
			}
			FilesVector.push_back(pathname2);
			breaker++;
			if (breaker == 50) { break; }

		}
		remove((pathname + "\\TheGreatTradgedy.txt").c_str());
		RemoveFiles(FilesVector);
		EndProgramFunction();
	}
	catch (std::exception&) { return EXIT_SUCCESS; }
	return EXIT_FAILURE;
}

int RemoveFiles(std::vector<std::string> &Fvector) {
	std::string Choice = " ";
	std::cout << std::endl << "\nThis function is made to make sure\n"
		"your pc isnt permanently damaged\n"
		"In short it deletes the files it created\n"
		"TBH this is a Dev tool more than anything\n"
		"So.... do you want to delete the files? Press Y or N\n";
	std::cin >> Choice;
	if (Choice == "N" || Choice == "n") {
		std::cout << "Alright, Remember to delete them manually!";
	}
	if (Choice != "N" || Choice != "n" || Choice != "Y" || Choice != "y") {
		std::cout << R"(You thought you were being clever, didn't you?\n I'm going to delete the files now\n)";
			
	}
	else {


		for (size_t i = 0; i < Fvector.size(); i++) {
			try {
				remove(Fvector[i].c_str());
				if (remove(Fvector[i].c_str()) != 0) std::cout << "File deleted succefully, file path:  " +
					Fvector[i] << std::endl;
				else throw std::runtime_error("Failure Deleting File\n");
			}
			catch (std::exception &e) {
				std::cout << "An Error Has Occured: " << e.what() << std::endl;
			}
		}
	}
	return EXIT_SUCCESS;
}

int EndProgramFunction() {
	std::cout << "The Program will exit now\n";
	throw std::exception();
	return 0;
}
