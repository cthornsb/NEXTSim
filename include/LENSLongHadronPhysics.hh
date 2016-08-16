#ifndef LENSLongHadronPhysics_h
#define LENSLongHadronPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"
#include <vector>

#include "G4VPhysicsConstructor.hh"

#include "G4MultipleScattering.hh"
#include "G4hIonisation.hh"

#include "G4HadronElasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"

#include "G4PionPlusInelasticProcess.hh"
#include "G4PionMinusInelasticProcess.hh"
#include "G4KaonPlusInelasticProcess.hh"
#include "G4KaonZeroSInelasticProcess.hh"
#include "G4KaonZeroLInelasticProcess.hh"
#include "G4KaonMinusInelasticProcess.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4AntiProtonInelasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4AntiNeutronInelasticProcess.hh"
#include "G4LambdaInelasticProcess.hh"
#include "G4AntiLambdaInelasticProcess.hh"
#include "G4SigmaPlusInelasticProcess.hh"
#include "G4SigmaMinusInelasticProcess.hh"
#include "G4AntiSigmaPlusInelasticProcess.hh"
#include "G4AntiSigmaMinusInelasticProcess.hh"
#include "G4XiZeroInelasticProcess.hh"
#include "G4XiMinusInelasticProcess.hh"
#include "G4AntiXiZeroInelasticProcess.hh"
#include "G4AntiXiMinusInelasticProcess.hh"
#include "G4DeuteronInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"
#include "G4AlphaInelasticProcess.hh"
#include "G4OmegaMinusInelasticProcess.hh"
#include "G4AntiOmegaMinusInelasticProcess.hh"

#include "G4LElastic.hh"   
#include "G4LFission.hh"
#include "G4LCapture.hh"

#include "G4LEPionPlusInelastic.hh"
#include "G4LEPionMinusInelastic.hh"
#include "G4LEKaonPlusInelastic.hh"
#include "G4LEKaonZeroSInelastic.hh"
#include "G4LEKaonZeroLInelastic.hh"
#include "G4LEKaonMinusInelastic.hh"
#include "G4LEProtonInelastic.hh"
#include "G4LEAntiProtonInelastic.hh"
#include "G4LENeutronInelastic.hh"
#include "G4LEAntiNeutronInelastic.hh"
#include "G4LELambdaInelastic.hh"
#include "G4LEAntiLambdaInelastic.hh"
#include "G4LESigmaPlusInelastic.hh"
#include "G4LESigmaMinusInelastic.hh"
#include "G4LEAntiSigmaPlusInelastic.hh"
#include "G4LEAntiSigmaMinusInelastic.hh"
#include "G4LEXiZeroInelastic.hh"
#include "G4LEXiMinusInelastic.hh"
#include "G4LEAntiXiZeroInelastic.hh"
#include "G4LEAntiXiMinusInelastic.hh"
#include "G4LEDeuteronInelastic.hh"
#include "G4LETritonInelastic.hh"
#include "G4LEAlphaInelastic.hh"
#include "G4LEOmegaMinusInelastic.hh"
#include "G4LEAntiOmegaMinusInelastic.hh"



#include "G4HEPionPlusInelastic.hh"
#include "G4HEPionMinusInelastic.hh"
#include "G4HEKaonPlusInelastic.hh"
#include "G4HEKaonZeroInelastic.hh"
#include "G4HEKaonZeroInelastic.hh"
#include "G4HEKaonMinusInelastic.hh"
#include "G4HEProtonInelastic.hh"
#include "G4HEAntiProtonInelastic.hh"
#include "G4HENeutronInelastic.hh"
#include "G4HEAntiNeutronInelastic.hh"
#include "G4HELambdaInelastic.hh"
#include "G4HEAntiLambdaInelastic.hh"
#include "G4HESigmaPlusInelastic.hh"
#include "G4HESigmaMinusInelastic.hh"
#include "G4HEAntiSigmaPlusInelastic.hh"
#include "G4HEAntiSigmaMinusInelastic.hh"
#include "G4HEXiZeroInelastic.hh"
#include "G4HEXiMinusInelastic.hh"
#include "G4HEAntiXiZeroInelastic.hh"
#include "G4HEAntiXiMinusInelastic.hh"
#include "G4HEOmegaMinusInelastic.hh"
#include "G4HEAntiOmegaMinusInelastic.hh"

#include "G4AntiProtonAnnihilationAtRest.hh"
#include "G4AntiNeutronAnnihilationAtRest.hh"

#ifdef TRIUMF_STOP_PIMINUS
#include "G4PionMinusAbsorptionAtRest.hh"
#else
#include "G4PiMinusAbsorptionAtRest.hh"
#endif
#ifdef TRIUMF_STOP_KMINUS
#include "G4KaonMinusAbsorption.hh"
#else
#include "G4KaonMinusAbsorptionAtRest.hh"
#endif

#include "G4TheoFSGenerator.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4QGSModel.hh"
#include "G4QGSParticipants.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"

class LENSLongHadronPhysics : public G4VPhysicsConstructor
{
  public: 
    LENSLongHadronPhysics(const G4String& name ="Hadron");
    virtual ~LENSLongHadronPhysics();

  public: 

    virtual void ConstructParticle();
 

    virtual void ConstructProcess();

  protected:

   G4HadronElasticProcess theElasticProcess;
   G4LElastic*            theElasticModel;
  

   G4PionPlusInelasticProcess thePionPlusInelastic;
   G4LEPionPlusInelastic* theLEPionPlusModel;
   G4MultipleScattering thePionPlusMult;
   G4hIonisation thePionPlusIonisation;


   G4PionMinusInelasticProcess thePionMinusInelastic;
   G4LEPionMinusInelastic* theLEPionMinusModel;
   G4MultipleScattering thePionMinusMult;
   G4hIonisation thePionMinusIonisation;
#ifdef TRIUMF_STOP_PIMINUS
   G4PionMinusAbsorptionAtRest thePionMinusAbsorption;
#else
   G4PiMinusAbsorptionAtRest thePionMinusAbsorption;
#endif


   
    G4TheoFSGenerator theTheoModel;
    G4ExcitationHandler theHandler;
    G4PreCompoundModel * thePreEquilib;
    G4GeneratorPrecompoundInterface theCascade;
    G4QGSModel< G4QGSParticipants > theStringModel;
    G4QGSMFragmentation theFragmentation;
    G4ExcitedStringDecay * theStringDecay;


   G4KaonPlusInelasticProcess theKaonPlusInelastic;
   G4LEKaonPlusInelastic* theLEKaonPlusModel;
   G4HEKaonPlusInelastic* theHEKaonPlusModel;
   G4MultipleScattering theKaonPlusMult;
   G4hIonisation theKaonPlusIonisation;
	
-
   G4KaonMinusInelasticProcess theKaonMinusInelastic;
   G4LEKaonMinusInelastic* theLEKaonMinusModel;
   G4HEKaonMinusInelastic* theHEKaonMinusModel;
   G4MultipleScattering theKaonMinusMult;
   G4hIonisation theKaonMinusIonisation;
#ifdef TRIUMF_STOP_KMINUS
   G4KaonMinusAbsorption theKaonMinusAbsorption;
#else
   G4PiMinusAbsorptionAtRest theKaonMinusAbsorption;
#endif


   G4KaonZeroLInelasticProcess theKaonZeroLInelastic;
   G4LEKaonZeroLInelastic* theLEKaonZeroLModel;
   G4HEKaonZeroInelastic* theHEKaonZeroLModel;


   G4KaonZeroSInelasticProcess theKaonZeroSInelastic;
   G4LEKaonZeroSInelastic* theLEKaonZeroSModel;
   G4HEKaonZeroInelastic* theHEKaonZeroSModel;


   G4ProtonInelasticProcess theProtonInelastic;
   G4LEProtonInelastic* theLEProtonModel;
   G4HEProtonInelastic* theHEProtonModel;
   G4MultipleScattering theProtonMult;
   G4hIonisation theProtonIonisation;
 

   G4AntiProtonInelasticProcess theAntiProtonInelastic;
   G4LEAntiProtonInelastic* theLEAntiProtonModel;
   G4HEAntiProtonInelastic* theHEAntiProtonModel;
   G4MultipleScattering theAntiProtonMult;
   G4hIonisation theAntiProtonIonisation;
   G4AntiProtonAnnihilationAtRest  theAntiProtonAnnihilation;
    

   G4NeutronInelasticProcess  theNeutronInelastic;
   G4LENeutronInelastic* theLENeutronModel;
   G4HENeutronInelastic* theHENeutronModel;
   G4HadronFissionProcess theNeutronFission;
   G4LFission* theNeutronFissionModel;
   G4HadronCaptureProcess  theNeutronCapture;
   G4LCapture* theNeutronCaptureModel;



   G4AntiNeutronInelasticProcess  theAntiNeutronInelastic;
   G4LEAntiNeutronInelastic* theLEAntiNeutronModel;
   G4HEAntiNeutronInelastic* theHEAntiNeutronModel;
   G4AntiNeutronAnnihilationAtRest  theAntiNeutronAnnihilation;
   

   G4LambdaInelasticProcess  theLambdaInelastic;
   G4LELambdaInelastic*  theLELambdaModel;
   G4HELambdaInelastic*  theHELambdaModel;
  

   G4AntiLambdaInelasticProcess  theAntiLambdaInelastic;
   G4LEAntiLambdaInelastic*  theLEAntiLambdaModel;
   G4HEAntiLambdaInelastic*  theHEAntiLambdaModel;

   G4SigmaMinusInelasticProcess  theSigmaMinusInelastic;
   G4LESigmaMinusInelastic*  theLESigmaMinusModel;
   G4HESigmaMinusInelastic*  theHESigmaMinusModel;
   G4MultipleScattering theSigmaMinusMult;
   G4hIonisation theSigmaMinusIonisation;
  

   G4AntiSigmaMinusInelasticProcess  theAntiSigmaMinusInelastic;
   G4LEAntiSigmaMinusInelastic*  theLEAntiSigmaMinusModel;
   G4HEAntiSigmaMinusInelastic*  theHEAntiSigmaMinusModel;
   G4MultipleScattering theAntiSigmaMinusMult;
   G4hIonisation theAntiSigmaMinusIonisation;
   

   G4SigmaPlusInelasticProcess  theSigmaPlusInelastic;
   G4LESigmaPlusInelastic*  theLESigmaPlusModel;
   G4HESigmaPlusInelastic*  theHESigmaPlusModel;
   G4MultipleScattering theSigmaPlusMult;
   G4hIonisation theSigmaPlusIonisation;
  

   G4AntiSigmaPlusInelasticProcess  theAntiSigmaPlusInelastic;
   G4LEAntiSigmaPlusInelastic*  theLEAntiSigmaPlusModel;
   G4HEAntiSigmaPlusInelastic*  theHEAntiSigmaPlusModel;
   G4MultipleScattering theAntiSigmaPlusMult;
   G4hIonisation theAntiSigmaPlusIonisation;
  

   G4XiZeroInelasticProcess  theXiZeroInelastic;
   G4LEXiZeroInelastic*  theLEXiZeroModel;
   G4HEXiZeroInelastic*  theHEXiZeroModel;
  

   G4AntiXiZeroInelasticProcess  theAntiXiZeroInelastic;
   G4LEAntiXiZeroInelastic*  theLEAntiXiZeroModel;
   G4HEAntiXiZeroInelastic*  theHEAntiXiZeroModel;
  

   G4XiMinusInelasticProcess  theXiMinusInelastic;
   G4LEXiMinusInelastic*  theLEXiMinusModel;
   G4HEXiMinusInelastic*  theHEXiMinusModel;
   G4MultipleScattering theXiMinusMult;
   G4hIonisation theXiMinusIonisation;


   G4AntiXiMinusInelasticProcess  theAntiXiMinusInelastic;
   G4LEAntiXiMinusInelastic*  theLEAntiXiMinusModel;
   G4HEAntiXiMinusInelastic*  theHEAntiXiMinusModel;
   G4MultipleScattering theAntiXiMinusMult;
   G4hIonisation theAntiXiMinusIonisation;

   G4OmegaMinusInelasticProcess  theOmegaMinusInelastic;
   G4LEOmegaMinusInelastic*  theLEOmegaMinusModel;
   G4HEOmegaMinusInelastic*  theHEOmegaMinusModel;
   G4MultipleScattering theOmegaMinusMult;
   G4hIonisation theOmegaMinusIonisation;

   G4AntiOmegaMinusInelasticProcess  theAntiOmegaMinusInelastic;
   G4LEAntiOmegaMinusInelastic*  theLEAntiOmegaMinusModel;
   G4HEAntiOmegaMinusInelastic*  theHEAntiOmegaMinusModel;
   G4MultipleScattering theAntiOmegaMinusMult;
   G4hIonisation theAntiOmegaMinusIonisation;

   
};


#endif // LENSLongHadronPhysics_h

