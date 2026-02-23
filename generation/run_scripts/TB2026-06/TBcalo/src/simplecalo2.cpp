//**************************************************************************
// \file simplecalo2.cpp
// \brief:  Implementation of simple sandwich calorimeter DD4hep geometry
// \author: Lorenzo Pezzotti
// \date:   March 2025
//**************************************************************************

// Includers from DD4hep
#include "DDRec/Vector3D.h"
#include <DD4hep/DetFactoryHelper.h>

using namespace dd4hep;

// Build simple calo geometry
//
static Ref_t create_detector(Detector &description, xml_h e,
                             SensitiveDetector sens) {
  std::cout << "--> simplecalo2::create_detector() start" << std::endl;

  // Get info from the xml file
  //
  sens.setType("calorimeter");
  xml_det_t x_det = e;
  std::string det_name = x_det.nameStr();
  std::cout << "--> Going to create " << det_name << ", with ID: " << x_det.id()
            << std::endl;
  xml_dim_t x_dim = x_det.dimensions();

  const double CaloX = x_dim.x();
  const double CaloY = x_dim.y();
  const double CaloZ = x_dim.z();
  std::cout << "--> calo dimensions from XML description: x " << CaloX / m
            << " m, y " << CaloY / m << " m, z " << CaloZ / m << " m"
            << std::endl;

  // Retrieve number of layers to populate the calorimeter container with
  //
  auto NumberOfLayers = description.constant<int>("LayersNumber");

  // Info for subdetectors
  //
  xml_det_t x_calo = x_det.child(_Unicode(Calo));
  xml_det_t x_calolayer = x_det.child(_Unicode(CaloLayer));
  xml_det_t x_abslayer = x_det.child(_Unicode(AbsLayer));
  xml_det_t x_carbonfiberLayer = x_det.child(_Unicode(CFLayer));
  xml_det_t x_glue1Layer = x_det.child(_Unicode(Glue1Layer));
  xml_det_t x_cathode1Layer = x_det.child(_Unicode(Cathode1Layer));
  xml_det_t x_senslayer = x_det.child(_Unicode(SensLayer));
  xml_det_t x_cell = x_det.child(_Unicode(Cell));
  xml_det_t x_glue2Layer = x_det.child(_Unicode(Glue2Layer));
  xml_det_t x_cathode2Layer = x_det.child(_Unicode(Cathode2Layer));
  xml_det_t x_pcbLayer = x_det.child(_Unicode(PCBLayer));

  auto iscellsens = x_cell.isSensitive();

  const double CaloLayerX = x_calolayer.x();
  const double CaloLayerY = x_calolayer.y();
  const double CaloLayerZ = x_calolayer.z();

  const double AbsLayerX = x_abslayer.x();
  const double AbsLayerY = x_abslayer.y();
  const double AbsLayerZ = x_abslayer.z();

  const double CarbonFiberLayerX = x_carbonfiberLayer.x();
  const double CarbonFiberLayerY = x_carbonfiberLayer.y();
  const double CarbonFiberLayerZ = x_carbonfiberLayer.z();

  const double Cathode1LayerX = x_cathode1Layer.x();
  const double Cathode1LayerY = x_cathode1Layer.y();
  const double Cathode1LayerZ = x_cathode1Layer.z();

  const double Glue1LayerX = x_glue1Layer.x();
  const double Glue1LayerY = x_glue1Layer.y();
  const double Glue1LayerZ = x_glue1Layer.z();

  const double SensLayerX = x_senslayer.x();
  const double SensLayerY = x_senslayer.y();
  const double SensLayerZ = x_senslayer.z();

  const double Glue2LayerX = x_glue2Layer.x();
  const double Glue2LayerY = x_glue2Layer.y();
  const double Glue2LayerZ = x_glue2Layer.z();

  const double Cathode2LayerX = x_cathode2Layer.x();
  const double Cathode2LayerY = x_cathode2Layer.y();
  const double Cathode2LayerZ = x_cathode2Layer.z();  

  const double PCBLayerX = x_pcbLayer.x();
  const double PCBLayerY = x_pcbLayer.y();
  const double PCBLayerZ = x_pcbLayer.z();


  const double CellX = x_cell.x();
  const double CellY = x_cell.y();
  const double CellZ = x_cell.z();
  const int CellSegmentationX = SensLayerX / CellX;
  const int CellSegmentationY = SensLayerY / CellY;
  const int CellSegmentationZ = SensLayerZ / CellZ;

  std::cout << "--> calorimeter Cell segmentation: " << CellSegmentationX << " x "
            << CellSegmentationY << " x " << CellSegmentationZ << std::endl;
  // Create the geometry
  //

  // Create a container for the calorimeter
  //
  Box Calo(CaloX / 2., CaloY / 2., CaloZ / 2.);
  Volume CaloVol("CaloVol", Calo,
                 description.material(x_calo.attr<std::string>(_U(material))));
  CaloVol.setVisAttributes(description, x_calo.visStr());

  // Create a container for a calorimeter layer
  // (absorber + active elements)
  //
  Box CaloLayer(CaloLayerX / 2., CaloLayerY / 2., CaloLayerZ / 2.);
  Volume CaloLayerVol(
      "CaloLayerVol", CaloLayer,
      description.material(x_calolayer.attr<std::string>(_U(material))));
  CaloLayerVol.setVisAttributes(description, x_calolayer.visStr());
  CaloVol.setRegion(description, x_det.regionStr());
  CaloVol.setLimitSet(description, x_det.limitsStr());
  // Place twenty calorimeter layers inside the container
  //
  for (std::size_t i = 0; i < static_cast<std::size_t>(NumberOfLayers); i++) {
    PlacedVolume CaloLayerPlaced = CaloVol.placeVolume(
        CaloLayerVol, i,
        Position(0., 0., CaloLayerZ / 2. + i * CaloLayerZ));
    CaloLayerPlaced.addPhysVolID("calolayer", i + 1);
  }
  // Place an absorber layer inside the calorimeter layer

  Box AbsLayer(AbsLayerX / 2., AbsLayerY / 2., AbsLayerZ / 2.);
  Volume AbsLayerVol(
      "AbsLayerVol", AbsLayer,
      description.material(x_abslayer.attr<std::string>(_U(material))));
  AbsLayerVol.setVisAttributes(description, x_abslayer.visStr());
  PlacedVolume AbsLayerPlaced = CaloLayerVol.placeVolume(AbsLayerVol, 1, 
    Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ / 2.));
  AbsLayerPlaced.addPhysVolID("abslayer", 1);  

  Box CarbonFiberLayer(CarbonFiberLayerX / 2., CarbonFiberLayerY / 2., CarbonFiberLayerZ / 2.);
  Volume CarbonFiberLayerVol(
      "CarbonFiberLayerVol", CarbonFiberLayer,
      description.material(x_det.child(_Unicode(CFLayer)).attr<std::string>(_U(material))));
  CarbonFiberLayerVol.setVisAttributes(description, x_carbonfiberLayer.visStr());
  PlacedVolume CarbonFiberLayerPlaced = CaloLayerVol.placeVolume(CarbonFiberLayerVol, 1, 
    Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ + CarbonFiberLayerZ / 2.));
  CarbonFiberLayerPlaced.addPhysVolID("abslayer", 1);

  Box Cathode1Layer(Cathode1LayerX / 2., Cathode1LayerY / 2., Cathode1LayerZ / 2.);
  Volume Cathode1LayerVol(
      "Cathode1LayerVol", Cathode1Layer,
      description.material(x_det.child(_Unicode(Cathode1Layer)).attr<std::string>(_U(material))));
  Cathode1LayerVol.setVisAttributes(description, x_cathode1Layer.visStr());
  PlacedVolume Cathode1LayerPlaced = CaloLayerVol.placeVolume(Cathode1LayerVol, 1, 
    Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ + CarbonFiberLayerZ + Cathode1LayerZ / 2.));
  Cathode1LayerPlaced.addPhysVolID("abslayer", 1);

  Box Glue1Layer(Glue1LayerX / 2., Glue1LayerY / 2., Glue1LayerZ / 2.);
  Volume Glue1LayerVol(
      "Glue1LayerVol", Glue1Layer,
      description.material(x_det.child(_Unicode(Glue1Layer)).attr<std::string>(_U(material))));
  Glue1LayerVol.setVisAttributes(description, x_glue1Layer.visStr());
  PlacedVolume Glue1LayerPlaced = CaloLayerVol.placeVolume(Glue1LayerVol, 1, 
    Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ + CarbonFiberLayerZ + Cathode1LayerZ 
      + Glue1LayerZ / 2.));
  Glue1LayerPlaced.addPhysVolID("abslayer", 1);

  // Place an active layer inside the calorimeter layer
  
  Box SensLayer(SensLayerX / 2., SensLayerY / 2., SensLayerZ / 2.);
  Volume SensLayerVol(
      "SensLayerVol", SensLayer,
      description.material(x_senslayer.attr<std::string>(_U(material))));
  SensLayerVol.setVisAttributes(description, x_senslayer.visStr()); 
  PlacedVolume SensLayerPlaced = CaloLayerVol.placeVolume(SensLayerVol, 1, 
    Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ + CarbonFiberLayerZ + Cathode1LayerZ 
      + Glue1LayerZ + SensLayerZ / 2.));//Make sure CaloLayerZ = AbsLayerZ + SensLayerZ
  SensLayerPlaced.addPhysVolID("abslayer", 0);

  Box Glue2Layer(Glue2LayerX / 2., Glue2LayerY / 2., Glue2LayerZ / 2.);
  Volume Glue2LayerVol(
      "Glue2LayerVol", Glue2Layer,
      description.material(x_det.child(_Unicode(Glue2Layer)).attr<std::string>(_U(material))));
  Glue2LayerVol.setVisAttributes(description, x_glue2Layer.visStr());
  PlacedVolume Glue2LayerPlaced = CaloLayerVol.placeVolume(Glue2LayerVol, 1, 
    Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ + CarbonFiberLayerZ + Cathode1LayerZ 
      + Glue1LayerZ + SensLayerZ + Glue2LayerZ / 2.));
  Glue2LayerPlaced.addPhysVolID("abslayer", 1);

  Box Cathode2Layer(Cathode2LayerX / 2., Cathode2LayerY / 2., Cathode2LayerZ / 2.);
  Volume Cathode2LayerVol(
      "Cathode2LayerVol", Cathode2Layer,
      description.material(x_det.child(_Unicode(Cathode2Layer)).attr<std::string>(_U(material))));
  Cathode2LayerVol.setVisAttributes(description, x_cathode2Layer.visStr());
  PlacedVolume Cathode2LayerPlaced = CaloLayerVol.placeVolume(Cathode2LayerVol, 1, 
    Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ + CarbonFiberLayerZ + Cathode1LayerZ 
      + Glue1LayerZ + SensLayerZ + Glue2LayerZ + Cathode2LayerZ / 2.));
  Cathode2LayerPlaced.addPhysVolID("abslayer", 1);

  Box PCBLayer(AbsLayerX / 2., AbsLayerY / 2., PCBLayerZ / 2.);
  Volume PCBLayerVol(
      "PCBLayerVol", PCBLayer,
      description.material(x_pcbLayer.attr<std::string>(_U(material))));
  PCBLayerVol.setVisAttributes(description, x_pcbLayer.visStr());
  PlacedVolume PCBLayerPlaced = CaloLayerVol.placeVolume(PCBLayerVol, 1, 
    Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ + CarbonFiberLayerZ + Cathode1LayerZ 
      + Glue1LayerZ + SensLayerZ + Glue2LayerZ + Cathode2LayerZ + PCBLayerZ / 2.));
  PCBLayerPlaced.addPhysVolID("abslayer", 1);

  //

  // Hands-on 4: Place 100 active cells (pixels) inside the calorimeter sensitive layer
  // and make them sensitive

  // Hands-on 4: Solution
  // uncomment the line below to include the solution
  //include "sc2_solution1.h"

  Box Cell(CellX / 2., CellY / 2., CellZ / 2.);
  Volume CellVol("CellVol", Cell,description.material(x_cell.attr<std::string>(_U(material))));
  CellVol.setVisAttributes(description, x_cell.visStr());
  // Make the cell sensitive
  if (iscellsens) CellVol.setSensitiveDetector(sens);
    double x, y, z = 0;
    int cellid = 0;
  for (std::size_t i = 0; i < CellSegmentationX; i++) {
    for (std::size_t j = 0; j < CellSegmentationY; j++) {
      for (std::size_t k = 0; k < CellSegmentationZ; k++) {
        x = -SensLayerX / 2. + CellX / 2. + i * CellX;
        y = -SensLayerY / 2. + CellY / 2. + j * CellY;
        //z = -SensLayerZ / 2. + CellZ / 2.;
        z = -SensLayerZ / 2. + CellZ / 2. + k * CellZ;
        cellid = k * CellSegmentationX * CellSegmentationY + j * CellSegmentationX + i;
        //cellid = j * CellSegmentationX + i;
        PlacedVolume CellVolPlaced =SensLayerVol.placeVolume(CellVol, cellid, Position(x, y, z));
        CellVolPlaced.addPhysVolID("cellid", cellid);
      }
    }
  }

  // Finalize geometry
  //
  DetElement subdet(det_name, x_det.id());
  Volume motherVolume = description.pickMotherVolume(subdet);
  // Place the calo container inside the mother volume
  PlacedVolume CaloPlaced = motherVolume.placeVolume(CaloVol);
  subdet.setPlacement(CaloPlaced);

  std::cout << "--> simplecalo2::create_detector() end" << std::endl;
  return subdet;
}

DECLARE_DETELEMENT(simplecalo2, create_detector)

//**************************************************************************
