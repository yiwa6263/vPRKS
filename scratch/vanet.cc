#include <time.h>
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/traci-client-module.h"
#include "ns3/log.h"
//#include "ovnis.h"
#include "ns3/simulator.h"
#include "ns3/wifi-module.h"
#include "ns3/physim-wifi-module.h"
#include "ns3/network-module.h"
#include "ns3/settings.h"

using namespace std;
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("VANET");

int main (int argc, char **argv)
{
  //Set random number
  srand (time (NULL));
  int seedNumber = rand () % MAX_RANDOM_SEED;
  SeedManager::SetSeed (seedNumber);
  srand (time(NULL));
  int runNumber = rand () % MAX_RUN_NUMBER;
  SeedManager::SetRun (runNumber);

  //LogComponentEnable ("TraciApplication", LOG_LEVEL_DEBUG);
  //LogComponentEnable ("YansWifiPhy", LOG_LEVEL_DEBUG);
  //LogComponentEnable ("Observation", LOG_LEVEL_DEBUG);

  Packet::EnablePrinting ();
  //string sumoConfig = "scratch/cross.sumocfg";
  string sumoConfig = "scratch/line.sumocfg";
  string nodeFile = "scratch/line.nod.xml";
  string edgeFile= "scratch/line.edg.xml";
  int startTime = 0;
  int stopTime = 3000;
  bool startSumo = true;

  string sumoHost = "localhost";
  string sumoPath = "/usr/local/bin/sumo";
  CommandLine cmd;
  cmd.AddValue ("sumoConfig", "The SUMO xml config file", sumoConfig);
  cmd.AddValue ("sumoHost", "Name of the machine hosting SUMO", sumoHost);
  cmd.AddValue ("startTime", 
      "Data at which the network simulation starts. Before that, SUMO runs on its own (Seoncds)", startTime);
  cmd.AddValue ("stopTime", "Data at which the simulation stops (Seconds)", stopTime);
  cmd.AddValue ("startSumo", "If true, ns3 will start SUMO by itself (on the same host only). If false, it is assumed that you start SUMO by yourself.", startSumo);
  cmd.Parse (argc, argv);
  Ptr<Ovnis> sim = CreateObjectWithAttributes <Ovnis> (
      "SumoConfig", StringValue (sumoConfig),
      "NodeFile", StringValue (nodeFile),
      "EdgeFile", StringValue (edgeFile),
      "SumoPath", StringValue (sumoPath),
      "SumoHost", StringValue (sumoHost),
      "StartTime", IntegerValue (startTime),
      "StopTime", IntegerValue (stopTime),
      "StartSumo", BooleanValue (startSumo),
      "Application", StringValue ("ns3::TraciApplication")
      );


  Simulator::Schedule (Seconds (0), &Ovnis::run, sim);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;

  //Run Simulation
}
