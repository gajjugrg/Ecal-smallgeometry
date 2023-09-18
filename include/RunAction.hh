/// \file /optical/OpNovice2/include/RunAction.hh
/// \brief Definition of the RunAction class
//
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"
// #include "Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class Run;
class HistoManager;
class PrimaryGeneratorAction;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(PrimaryGeneratorAction* = nullptr);
    virtual ~RunAction();


    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

  private:
    G4Timer* fTimer;
    Run* fRun;
    HistoManager* fHistoManager;
    PrimaryGeneratorAction* fPrimary;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*RunAction_h*/
