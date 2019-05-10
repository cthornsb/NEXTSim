#include <vector>
#include <fstream>

#include "G4Run.hh"

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "nDetMasterOutputFile.hh"
#include "photonCounter.hh"

nDetMasterOutputFile &nDetMasterOutputFile::getInstance(){
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static nDetMasterOutputFile instance;
	return instance;
}

nDetMasterOutputFile::nDetMasterOutputFile(){
	persistentMode = false;
	verbose = false;
	printTrace = false;

	outputEnabled = true;
	outputTraces = false;
	outputDebug = false;
	outputBadEvents = false;

	runIndex = 1;
	fFile = NULL;
	fTree = NULL;
	fBranch = NULL;

	runTitle = "NEXT Geant4 output";
	runIndex = 1;

	overwriteExistingFile = false;
}

nDetMasterOutputFile::~nDetMasterOutputFile(){
	// Close the root file, if it's still open.
	closeRootFile();
}

bool nDetMasterOutputFile::openRootFile(const G4Run* aRun){
	if(!outputEnabled || (persistentMode && aRun->GetRunID() != 0)) return false;
	
	// Close the output file if it is open.
	closeRootFile();	
	
	// Open a new one.
	if(filename.empty()){ // Get the system time, and use it to create the filename of root file.
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[180];

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		strftime (buffer,180,"_%H:%M:%S_%a_%b_%d_%Y",timeinfo);

		// Create a root file for the current run
		char defaultFilename[300];
		sprintf(defaultFilename, "run_%03d%s.root",aRun->GetRunID(), buffer);
		filename = std::string(defaultFilename);
		
		// Create a ROOT file
		fFile = new TFile(filename.c_str(), "RECREATE", runTitle.c_str());
		if(!fFile->IsOpen()) {
			G4cout << " nDetRunAction: ERROR! Failed to open file \"" << filename << "\"!\n";
			return false;
		}
	}
	else{ // Load new output file.
		while(true){
			std::stringstream stream; stream << runIndex++;
			std::string runID = stream.str();
		
			std::string newFilename = filenamePrefix + "-" + std::string(3-runID.length(), '0') + runID + filenameSuffix;
			if(!overwriteExistingFile){ // Do not overwrite output
				std::ifstream fCheck(newFilename.c_str());
				if(fCheck.good()){ // File exists. Start over.
					if(verbose)
						std::cout << " nDetRunAction: File \"" << newFilename << "\" already exists.\n";
					fCheck.close();
					continue;
				}
				fCheck.close();
				fFile = new TFile(newFilename.c_str(), "CREATE", runTitle.c_str());
			}
			else{ // Overwrite output
				fFile = new TFile(newFilename.c_str(), "RECREATE", runTitle.c_str());
			}
			if(!fFile->IsOpen()) {
				G4cout << " nDetRunAction: ERROR! Failed to open file \"" << newFilename << "\"!\n";
				return false;
			}
			break;
		}
	}

	// Add user commands to the output file.
	TDirectory *dir = fFile->mkdir("setup");
	//detector->GetMessenger()->write(dir);
	//source->GetMessenger()->write(dir);
	//fActionMessenger->write(dir);

	// Create root tree.
	if(treename.empty()) treename = "data"; //"neutronEvent";
	fTree = new TTree(treename.c_str(),"Photons produced by thermal neutrons");

	if(persistentMode) // Run number
		fTree->Branch("runNb", &data.runNb);
	fTree->Branch("nScatters", &data.nScatters);
	fTree->Branch("nDepEnergy", &data.depEnergy);
	fTree->Branch("nInitEnergy", &data.initEnergy);
	fTree->Branch("nAbsorbed", &data.nAbsorbed);
	fTree->Branch("nPhotonsTot", &data.nPhotonsTot);
	fTree->Branch("nPhotonsDet", &data.nPhotonsDetTot);

	if(outputDebug){ // Output extra neutron scattering information (off by default).
		fTree->Branch("nEnterPosX", &data.neutronIncidentPositionX);
		fTree->Branch("nEnterPosY", &data.neutronIncidentPositionY);
		fTree->Branch("nEnterPosZ", &data.neutronIncidentPositionZ);
		fTree->Branch("nExitPosX", &data.neutronExitPositionX);
		fTree->Branch("nExitPosY", &data.neutronExitPositionY);
		fTree->Branch("nExitPosZ", &data.neutronExitPositionZ);
		fTree->Branch("nComX", &data.neutronCenterOfMass[0]);
		fTree->Branch("nComY", &data.neutronCenterOfMass[1]);
		fTree->Branch("nComZ", &data.neutronCenterOfMass[2]);		
		fTree->Branch("nFirstScatterTime", &data.nTimeToFirstScatter);
		fTree->Branch("nFirstScatterLen", &data.nLengthToFirstScatter);		
		fTree->Branch("nEnterTime", &data.incidentTime);
		fTree->Branch("nTimeInMat", &data.timeInMaterial);		
		fTree->Branch("nScatterX", &data.nScatterX);
		fTree->Branch("nScatterY", &data.nScatterY);
		fTree->Branch("nScatterZ", &data.nScatterZ);
		fTree->Branch("nScatterAngle", &data.nScatterAngle);
		fTree->Branch("nPathLength", &data.nPathLength);
		fTree->Branch("nScatterTime", &data.scatterTime);
		fTree->Branch("impartedE", &data.impartedE);
		fTree->Branch("segmentCol", &data.segmentCol);
		fTree->Branch("segmentRow", &data.segmentRow);
		fTree->Branch("photonsProd", &data.Nphotons);
		fTree->Branch("recoilMass", &data.recoilMass);
		fTree->Branch("nScatterScint", &data.nScatterScint);
	}
	
	fTree->Branch("lightBalance", &data.photonLightBalance);
	fTree->Branch("photonDetEff", &data.photonDetEfficiency);
	fTree->Branch("barTOF", &data.barTOF);
	fTree->Branch("barQDC", &data.barQDC);
	fTree->Branch("barMaxADC", &data.barMaxADC);
	fTree->Branch("goodEvent", &data.goodEvent);
	fTree->Branch("pulsePhase[2]", data.pulsePhase);
	fTree->Branch("photonComX[2]", data.photonDetCenterOfMassX);
	fTree->Branch("photonComY[2]", data.photonDetCenterOfMassY);
	fTree->Branch("reconComX[2]", data.reconstructedCenterX);
	fTree->Branch("reconComY[2]", data.reconstructedCenterY);
	fTree->Branch("photonComCol[2]", data.centerOfMassColumn);
	fTree->Branch("photonComRow[2]", data.centerOfMassRow);

	if(outputDebug){ // Output extra photon information (off by default).
		fTree->Branch("nPhotons[2]", data.nPhotonsDet);
		fTree->Branch("photonMinTime[2]", data.photonMinArrivalTime);
		fTree->Branch("photonAvgTime[2]", data.photonAvgArrivalTime);		
		fTree->Branch("pulseQDC[2]", data.pulseQDC);
		fTree->Branch("pulseMax[2]", data.pulseMax);
		fTree->Branch("pulseMaxTime[2]", data.pulseMaxTime);
		fTree->Branch("pulseArrival[2]", data.pulseWeightedArrival);
		fTree->Branch("detSpdLight", &data.detSpeedLight);
		fTree->Branch("anodePhase", data.anodePhase, "anodePhase[2][4]/F");
	}

	if(outputTraces){ // Add the lilght pulses to the output tree.
			fTree->Branch("lightPulseL", &data.lightPulseL);
			fTree->Branch("lightPulseR", &data.lightPulseR);
	}

	defineRootBranch = true;
		
	std::cout << " nDetRunAction: File " << fFile->GetName() << " opened." << std::endl;
		
	return true;
}//end of open root file...

bool nDetMasterOutputFile::closeRootFile(){
	// Close the root file.
	if(fFile){
		fFile->cd();
		fTree->Write();
		fFile->Close();
		delete fFile;
		fFile = NULL;
	}
	return true;
}

bool nDetMasterOutputFile::fillBranch(const nDetDataPack &pack){
	if(!outputEnabled) return false;

	// Enable the mutex lock to protect file access.
	fileLock.lock();

	// Copy the event data.
	this->data = pack;

	if(outputBadEvents || pack.goodEvent || (pack.nPhotonsDet[0] > 0 || pack.nPhotonsDet[1] > 0))
		fTree->Fill(); // Fill the tree

	// Disable the mutex lock to open access to the file.
	fileLock.unlock();

	return true;
}

void nDetMasterOutputFile::setOutputFilename(const std::string &fname){
	size_t index = fname.find('.');
	std::string prefix = fname;
	if(index != std::string::npos) 
		prefix = fname.substr(0, index);
	filename = prefix + "_m.root";
	filenamePrefix = filename;
	filenameSuffix = "";
	index = filename.find_last_of('.');
	if(index != std::string::npos){
		filenamePrefix = filename.substr(0, index);
		filenameSuffix = filename.substr(index);
	}
	runIndex = 1;
	if(verbose){
		std::cout << " Output filename prefix=" << filenamePrefix << ", suffix=" << filenameSuffix << std::endl;
		std::cout << " Reset output filename run counter to 1\n";
	}
}