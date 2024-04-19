#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/mobility-module.h>
#include <ns3/lte-module.h>
#include <ns3/pf-ff-mac-scheduler.h>
#include <ns3/config-store-module.h>

using namespace ns3;

int main(int argc, char *argv[])
{   
    Time simTime = Seconds(1);

    CommandLine cmd(__FILE__);
    cmd.AddValue("simTime", "Total duration of the simulation", simTime);
    cmd.Parse(argc, argv);

    ConfigStore inputConfig;
    inputConfig.ConfigureDefaults();
    
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
    lteHelper->SetSchedulerType("ns3::PfFfMacScheduler");
    lteHelper->SetAttribute("PathlossModel", StringValue("ns3::FriisSpectrumPropagationLossModel"));
    //lteHelper->EnableLogComponents ();

    NodeContainer enbNodes;
    enbNodes.Create(1);
    NodeContainer ueNodes;
    ueNodes.Create(2);

    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(enbNodes);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ueNodes);

    NetDeviceContainer enbDevs;
    enbDevs = lteHelper->InstallEnbDevice(enbNodes);
    NetDeviceContainer ueDevs;
    ueDevs = lteHelper->InstallUeDevice(ueNodes);

    lteHelper->Attach(ueDevs, enbDevs.Get(0));

    enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    EpsBearer bearer(q);
    lteHelper->ActivateDataRadioBearer(ueDevs, bearer);

    Simulator::Stop(simTime);

    lteHelper->EnableMacTraces();
    lteHelper->EnableRlcTraces();

    double distance_temp[] = {1000, 1000};
    std::vector<double> userDistance;
    userDistance.assign(distance_temp, distance_temp + 2);
    for (int i = 0; i < 2; i++)
    {
        Ptr<ConstantPositionMobilityModel> mm =
            ueNodes.Get(i)->GetObject<ConstantPositionMobilityModel>();
        mm->SetPosition(Vector(userDistance[i], 0.0, 0.0));
    }

    Simulator::Run();
    Simulator::Destroy();
}