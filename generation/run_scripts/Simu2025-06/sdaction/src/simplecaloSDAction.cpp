//**************************************************************************
// \file simplecaloSDAction.cpp
// \brief: Implementation of Geant4SensitiveAction template class for
//         simplecalo
// \author: Lorenzo Pezzotti
// \date: March 2025
//**************************************************************************

#include "DD4hep/Segmentations.h"
#include "DDG4/Factories.h"
#include "DDG4/Geant4GeneratorAction.h"
#include "DDG4/Geant4Mapping.h"
#include "DDG4/Geant4SensDetAction.inl"

#include "G4ThreeVector.hh"
#include "G4TouchableHandle.hh"
#include <cmath>

// #define DEBUG

namespace dd4hep {
namespace sim {
class simplecaloSDData {
  // Constructor and destructor
  //
public:
  simplecaloSDData() = default;
  ~simplecaloSDData() = default;

public:
  Geant4Sensitive *sensitive{};
};
} // namespace sim
} // namespace dd4hep

namespace dd4hep {
namespace sim {

// Function template specialization of Geant4SensitiveAction class.
// Define actions
template <> void Geant4SensitiveAction<simplecaloSDData>::initialize() {
  m_userData.sensitive = this;
}

// Function template specialization of Geant4SensitiveAction class.
// Define collections created by this sensitivie action object
template <> void Geant4SensitiveAction<simplecaloSDData>::defineCollections() {
  std::string ROname = m_sensitive.readout().name();
  m_collectionID = defineCollection<Geant4Calorimeter::Hit>(ROname);
}

// Function template specialization of Geant4SensitiveAction class.
// Method that accesses the G4Step object at each track step.
template <>
bool Geant4SensitiveAction<simplecaloSDData>::process(
    const G4Step *aStep, G4TouchableHistory * /*history*/) {

#ifdef DEBUG
  std::cout << "-------------------------------" << std::endl;
  std::cout << "--> simplecalo: track info: " << std::endl;
  std::cout
      << "----> Track #: " << aStep->GetTrack()->GetTrackID() << " "
      << "Step #: " << aStep->GetTrack()->GetCurrentStepNumber() << " "
      << "Volume: "
      << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()
      << " " << std::endl;
  std::cout << "--> simplecalo:: position info(mm): " << std::endl;
  std::cout << "----> x: " << aStep->GetPreStepPoint()->GetPosition().x()
            << " y: " << aStep->GetPreStepPoint()->GetPosition().y()
            << " z: " << aStep->GetPreStepPoint()->GetPosition().z()
            << std::endl;
  std::cout << "--> simplecalo: particle info: " << std::endl;
  std::cout
      << "----> Particle "
      << aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << " "
      << "Dep(MeV) " << aStep->GetTotalEnergyDeposit() << " "
      << "Mat " << aStep->GetPreStepPoint()->GetMaterial()->GetName() << " "
      << "Vol "
      << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()
      << " " << std::endl;
#endif

  dd4hep::BitFieldCoder decoder("calolayer:5,abslayer:1,cellid:10");
  auto VolID = volumeID(aStep);
#ifdef DEBUG
  auto CaloLayerID = decoder.get(VolID, "calolayer");
  auto AbsLayerID = decoder.get(VolID, "abslayer");
  auto CellID = decoder.get(VolID, "cellid");
  std::cout << "--> CaloLayerID: " << CaloLayerID << " AbsLayerID "
            << AbsLayerID << " CellID " << CellID << std::endl;
#endif

  G4TouchableHandle theTouchable =
      aStep->GetPreStepPoint()->GetTouchableHandle();
  G4ThreeVector origin(0., 0., 0.);
  G4ThreeVector CellPos =
      theTouchable->GetHistory()->GetTopTransform().Inverse().TransformPoint(
          origin);
#ifdef DEBUG
  std::cout << "--> Cell global pos(mm) " << CellPos.x() << " " << CellPos.y()
            << " " << CellPos.z() << std::endl;
#endif

  // Hands-on 5: apply a very short time cut (10 ns) to record the signals
  // and consider the cell border (2 cm) along x and y completely inefficient,
  // i.e. not signal is recorder from that area.
  // Hint: the x,y,z position of the step in the local volume reference frame is
  // G4ThreeVector globalPosition = aStep->GetPreStepPoint()->GetPosition();
  // theTouchable->GetHistory()->GetTopTransform().TransformPoint(globalPosition);
  //

  // Hands-on 5: solution
  //
  /*  
  if (aStep->GetPreStepPoint()->GetGlobalTime() > 10) {
    return true;
  }
  G4ThreeVector globalPosition = aStep->GetPreStepPoint()->GetPosition();
  G4ThreeVector localPosition =
      theTouchable->GetHistory()->GetTopTransform().TransformPoint(
          globalPosition);
  if (std::abs(localPosition.x()) > 30. || std::abs(localPosition.y()) > 30.) {
    return true;
  }
  */

  // Create the hits and accumulate contributions from multiple steps
  //
  Geant4HitCollection *coll = collection(m_collectionID);
  Geant4Calorimeter::Hit *hit =
      coll->findByKey<Geant4Calorimeter::Hit>(VolID); // the hit

  if (!hit) { // if the hit does not exist yet, create it
    hit = new Geant4Calorimeter::Hit();
    hit->cellID = VolID; // this should be assigned only once
    /*dd4hep::Detector& description = dd4hep::Detector::getInstance();
    auto decoder = description.readout("simplecaloRO").idSpec().decoder();
    int calolayer = decoder->get(VolID, "calolayer");
    int abslayer  = decoder->get(VolID, "abslayer");
    int cellid    = decoder->get(VolID, "cellid");
    std::cout << "Creating new hit: CaloLayerID: " << calolayer
         << " AbsLayerID: " << abslayer << " CellID: " << cellid << std::endl;*/
    // we divide the coordinated by 10 to save them as cm
    Position HitCellPos(CellPos.x() / 10, CellPos.y() / 10, CellPos.z() / 10);
    hit->position = CellPos; // this should be assigned only once
    hit->energyDeposit = aStep->GetTotalEnergyDeposit();
    coll->add(VolID, hit); // add the hit to the hit collection
  } else {                 // if the hit exists already, increment its fields
    hit->energyDeposit += aStep->GetTotalEnergyDeposit();
  }

  return true;
} // end of Geant4SensitiveAction::process() method specialization

} // namespace sim
} // namespace dd4hep

//--- Factory declaration
namespace dd4hep {
namespace sim {
typedef Geant4SensitiveAction<simplecaloSDData> SimpleCaloSDAction;
}
} // namespace dd4hep
DECLARE_GEANT4SENSITIVE(SimpleCaloSDAction)

//**************************************************************************
