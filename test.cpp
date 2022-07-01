#include "test.h"


void test::test_bandwidth::test_itrace_bandwidth(QString filepath , int ch_num , int sp_rate, float sp_time, int chanelnumofdevice , float sampleintevms)
{
    if(filepath.isEmpty())
        return ;
    ReadSeismFile algotest; //(72, 1000, 4.096, filepath);
    algotest.SetFilePath(filepath);
    algotest.SetParams(ch_num, sp_rate, sp_time);
    algotest.run();
    dx_qc_data_analysis::InstrumentBandwidthDataAnalysis test(sp_time/(sampleintevms/sp_rate), ch_num, chanelnumofdevice, sampleintevms);
    test.SetData(algotest.testdata, dx_qc_data_analysis::QcItemId::InstrumentBandwidth_1_InstrumentBandwidth);
    for(int i = 0; i < test.GetResultLength(); i++)
    {
        qDebug() << i << " " << test.GetResult(i);
    }
}

void test::test_bandwidth::test_obc_bandwidth(QString filepath , int ch_num , int sp_rate, float sp_time, int chanelnumofdevice , float sampleintevms)
{
    if(filepath.isEmpty())
        return ;
    ReadSeismFile algotest; //(72, 1000, 4.096, filepath);
    algotest.SetFilePath(filepath);
    algotest.SetParams(ch_num, sp_rate, sp_time);
    algotest.run();
    dx_qc_data_analysis::ObcInstrumentBandwidthDataAnalysis test(sp_time/(sampleintevms/sp_rate), ch_num, chanelnumofdevice, sampleintevms);
    test.SetData(algotest.testdata, dx_qc_data_analysis::QcItemId::InstrumentBandwidth_1_InstrumentBandwidth);
    for(int i = 0; i < test.GetResultLength(); i++)
    {
        qDebug() << i << " " << test.GetResult(i);
    }
}

void test::test_bandwidth::test_obn_bandwidth(QString filepath , int ch_num , int sp_rate, float sp_time, int chanelnumofdevice , float sampleintevms)
{
    if(filepath.isEmpty())
        return ;
    ReadSeismFile algotest; //(72, 1000, 4.096, filepath);
    algotest.SetFilePath(filepath);
    algotest.SetParams(ch_num, sp_rate, sp_time);
    algotest.run();
    dx_qc_data_analysis::ObnInstrumentBandwidthDataAnalysis test(sp_time/(sampleintevms/sp_rate), ch_num, chanelnumofdevice, sampleintevms);
    test.SetData(algotest.testdata, dx_qc_data_analysis::QcItemId::InstrumentBandwidth_1_InstrumentBandwidth);
    for(int i = 0; i < test.GetResultLength(); i++)
    {
        qDebug() << i << " " << test.GetResult(i);
    }
}

void test::test_noise::test_itrace_noise(QString filepath , int ch_num , int sp_rate, float sp_time, int chanelnumofdevice , float sampleintevms)
{
    if(filepath.isEmpty())
        return ;
    ReadSeismFile algotest; //(72, 1000, 4.096, filepath);
    algotest.SetFilePath(filepath);
    algotest.SetParams(ch_num, sp_rate, sp_time);
    algotest.run();
    dx_qc_data_analysis::InstrumentNoiseDataAnalysis test(4096, ch_num);
    test.SetData(algotest.testdata, dx_qc_data_analysis::QcItemId::InstrumentNoise_1_InstrumentNoise);
    for(int i = 0; i < test.GetResultLength(); i++)
    {
        qDebug() << i << " " << test.GetResult(i);
    }
}

void test::test_noise::test_obc_noise(QString filepath , int ch_num , int sp_rate, float sp_time, int chanelnumofdevice , float sampleintevms)
{
    if(filepath.isEmpty())
        return ;
    ReadSeismFile algotest; //(72, 1000, 4.096, filepath);
    algotest.SetFilePath(filepath);
    algotest.SetParams(ch_num, sp_rate, sp_time);
    algotest.run();
    dx_qc_data_analysis::ObcInstrumentNoiseDataAnalysis test(sp_time/(sampleintevms/sp_rate), ch_num);
    test.SetData(algotest.testdata, dx_qc_data_analysis::QcItemId::InstrumentNoise_1_InstrumentNoise);
    for(int i = 0; i < test.GetResultLength(); i++)
    {
        qDebug() << i << " " << test.GetResult(i);
    }
}

void test::test_noise::test_obn_noise(QString filepath , int ch_num , int sp_rate, float sp_time, int chanelnumofdevice , float sampleintevms)
{
    if(filepath.isEmpty())
        return ;
    ReadSeismFile algotest; //(72, 1000, 4.096, filepath);
    algotest.SetFilePath(filepath);
    algotest.SetParams(ch_num, sp_rate, sp_time);
    algotest.run();
    dx_qc_data_analysis::ObnInstrumentNoiseDataAnalysis test(sp_time/(sampleintevms/sp_rate), ch_num);
    test.SetData(algotest.testdata, dx_qc_data_analysis::QcItemId::InstrumentNoise_1_InstrumentNoise);
    for(int i = 0; i < test.GetResultLength(); i++)
    {
        qDebug() << i << " " << test.GetResult(i);
    }
}

void test::test_capaitance::test_itrace_capaitance(QList<QString>filepath, int ch_num, int sp_rate , float sp_time , int chanelnumofdevice , float smpleintevms )
{
    if(filepath.isEmpty())
        return ;
    QList<dx_qc_data_analysis::QcItemId>ListItemId = {
        dx_qc_data_analysis::QcItemId::WaterSensorCapacitanceAndResistance_1_LowFreqBase,
        dx_qc_data_analysis::QcItemId::WaterSensorCapacitanceAndResistance_2_LowFreqOutput,
        dx_qc_data_analysis::QcItemId::WaterSensorCapacitanceAndResistance_3_HighFreqBase,
        dx_qc_data_analysis::QcItemId::WaterSensorCapacitanceAndResistance_4_HighFreqOutput
    };
    ReadSeismFile algotest;
    dx_qc_data_analysis::ItraceWaterSensorCapacitanceDataAnalysis test(4096, 72, 2, 1.0);
    for(int i = 0; i < filepath.size(); i++)
    {
        //ReadSeismFile algotest; //(72, 1000, 4.096, filepath);
        algotest.SetFilePath(filepath.at(i));
        algotest.SetParams(72, 1000, 4.096);
        algotest.run();
        //dx_qc_data_analysis::ItraceWaterSensorCapacitanceDataAnalysis test(4096, 72, 2, 1.0);
        test.SetData(algotest.testdata, ListItemId.at(i));
        //test.SetData(algotest.testdata, ListItemId.at(i));
        if(i == 3)
        {
            for(int i = 0; i < test.GetResultLength(); i++)
            {
                qDebug() << i << " " << test.GetResult(i);
            }
        }
    }
}
